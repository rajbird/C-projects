#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <glob.h>

#include "dish_run.h"
#include "dish_tokenize.h"


/**
 * Print a prompt if the input is coming from a TTY
 */
static void prompt(FILE *pfp, FILE *ifp) {
	if (isatty(fileno(ifp))) {
		fputs(PROMPT_STRING, pfp);
	}
}

/**
 * Actually do the work
 */
int execFullCommandLine( FILE *ofp, char ** const tokens, int nTokens, int verbosity, int *bgps){
  int fg = 1; 					//flag to used to decided if process to run in foreground
	int exitStatus = 0;
	int nPipes = 0;
	int nGlobs = 0;
	if (verbosity > 0) {
		fprintf(ofp, " + ");
		fprintfTokens(ofp, tokens, 1);
	}

  if(strcmp(tokens[0], "pwd") == 0)
		return runPWD (ofp);
	else if(strcmp(tokens[0], "cd") == 0){
		if(nTokens > 2){
			perror("cd: too many arguments\n");
			return (-1);
		}
		return runCD(tokens[1]);
	}
	else if(strcmp(tokens[nTokens - 1], "&") == 0 || (nTokens > 1 && strcmp(tokens[nTokens - 2], "&") == 0)){
		*bgps =  *bgps + 1;
		if(*bgps == MAXBGPROCESS){
			fprintf(ofp, "Maximum number (%d) of background process have been created. No more can be created!!\n", MAXBGPROCESS);
			return 1;
		}
		tokens[nTokens - 1] = NULL;
		if(nTokens > 1 && strcmp(tokens[nTokens - 2], "&") == 0)
			tokens[nTokens - 2] = NULL;
		return runInBackground (ofp, tokens, nTokens, *bgps);
	}
	else{
		for (int i = 0; i < nTokens; i++) {
			if(strcmp(tokens[i], "|") == 0)
				nPipes++;
			else if ( strchr(tokens[i], '*') != NULL  || strchr(tokens[i], '?') != NULL || (strchr(tokens[i], '[') != NULL && strchr(tokens[i], ']') != NULL))
				nGlobs++;
		}
		if(nPipes != 0)
			return pipeHandling(ofp, tokens, nTokens);
		else if(nGlobs != 0)
			return runGlobbingOnly(ofp, tokens, nTokens);
	}

	return runInForeground (ofp, tokens, 1);
}

/**
 * Load each line and perform the work for it
 */
int runScript( FILE *ofp, FILE *pfp, FILE *ifp, const char *filename, int verbosity	){
	char linebuf[LINEBUFFERSIZE];
	char *tokens[MAXTOKENS];
	int lineNo = 1;
	int nTokens, executeStatus = 0;
	int bgps = 0;
	int bgPS[MAXBGPROCESS];
	int status = 0;


	fprintf(ofp, "SHELL PID %ld\n", (long) getpid());


	prompt(pfp, ifp);
	while ((nTokens = parseLine(ifp, tokens, MAXTOKENS, linebuf, LINEBUFFERSIZE, verbosity - 3)) > 0) {
		lineNo++;

		if (nTokens > 0) {
			//if exit is first, then return 0
			if (strcmp(tokens[0], "exit") == 0){
				for (int i = 0; i < bgps; i++){
					if(bgPS[i] == 0)
						continue;
					int exitingPid =  wait(&status);
					if (WEXITSTATUS(status) != 0)
						fprintf(ofp, "[%d]  Exit %d       %d\n", i+1, status, bgPS[i]);
					else
						fprintf(ofp, "[%d]  Done           %d\n", i+1, bgPS[i]);
				}
				return 0;
			}

			if (strcmp(filename, "stdin") != 0)
				tokens[nTokens-1][strlen(tokens[nTokens-1])-1] = '\0';

			int currBGPS = bgps;
			executeStatus = execFullCommandLine(ofp, tokens, nTokens, verbosity, &bgps);
			if(currBGPS != bgps){
				bgPS[currBGPS] = executeStatus;
				executeStatus = 0;
			}

			if (executeStatus < 0) {
				fprintf(ofp, "Failure executing '%s' line %d:\n    ",filename, lineNo);
				fprintfTokens(ofp, tokens, 1);
				return executeStatus;
			}
		}

		if(bgps != 0){
			for (size_t i = 0; i < bgps; i++) {
				if(bgPS[i] != 0){
					int result = waitpid(bgPS[i], &status, WNOHANG);

			    if (result < 0) {
						if(status == 0)
							fprintf(ofp, "[%d]  Done           %d\n", i+1, bgPS[i]);
						else
							fprintf(ofp, "[%d]  Exit %d       %d\n", i+1, status, bgPS[i]);
						bgPS[i] = 0;
			    }
				}
			}
		}
		prompt(pfp, ifp);
	}

	for (int i = 0; i < bgps; i++){
		if(bgPS[i] == 0)
			continue;
		int exitingPid =  wait(&status);
		if (WEXITSTATUS(status) != 0)
			fprintf(ofp, "[%d]  Exit %d       %d\n", i+1, status, bgPS[i]);
		else
			fprintf(ofp, "[%d]  Done           %d\n", i+1, bgPS[i]);
	}
	return (0);
}


/**
 * Open a file and run it as a script
 */
int runScriptFile(FILE *ofp, FILE *pfp, const char *filename, int verbosity){
	FILE *ifp;
	int status;

	ifp = fopen(filename, "r");
	if (ifp == NULL) {
		fprintf(ofp, "Cannot open input script '%s' : %s\n", filename, strerror(errno));
		return -1;
	}

	status = runScript(ofp, pfp, ifp, filename, verbosity);
	fclose(ifp);
	return status;
}

int runInForeground (FILE *ofp, char ** const tokens, int waiting){
	int status = 0;
	int pid;
	int pipedsp[2];
	int oFlag = (ofp != stdout);

	if(oFlag){
		if (pipe(pipedsp) == -1) {
			perror("pipe");
			exit(1);
		}
	}

	/* now run the command */
	if ((pid = fork()) == 0){
		if(oFlag){
			dup2(pipedsp[1], 1);
			close(pipedsp[0]);
			close(pipedsp[1]);
		}

		execvp(tokens[0], tokens);
		perror("failed while running exec()");
		exit (-1);
	}

	if (pid < 1){
		perror("failed while running fork()");
		exit (-1);
	}

	if (oFlag){
		close(pipedsp[1]);
		pipeToFile(&pipedsp[0],ofp);
		close(pipedsp[0]);
	}

	usleep(6000);

	if(waiting){
		wait(&status);
		if (WIFEXITED(status)){
			if (WEXITSTATUS(status) != 0)
				fprintf(ofp,"Child (%d) exitted -- failure (%d)\n",pid, status);

			if (WEXITSTATUS(status) == 0)
				fprintf(ofp,"Child (%d) exitted -- success (%d)\n",pid, status);
		}
		else
			fprintf(ofp,"Child (%d) crashed\n", pid);

		return(WEXITSTATUS(status));
	}
	return pid;
}

int runPWD (FILE *ofp){
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
			fprintf(ofp,"%s\n", cwd);
	} else {
			perror("pwd error");
			return 1;
	}
	return 0;
}

int pipeHandling(FILE *ofp, char ** const tokens, int nTokens){
	int pipeEven[2];
  int pipeOdd[2];

  if (pipe(pipeEven) == -1 || pipe(pipeOdd) == -1) {
    perror("pipe");
    exit(1);
  }

  int pipes = 1;
  int indexOfNthCmd = 0;
  int i;
	glob_t globList[MAXCOMMANDSINPIPE];
	int globs = 0;
  for (i = 0; i < nTokens; i++) {
    if(strcmp(tokens[i], "|") == 0){
			int cmdSize = i - indexOfNthCmd;
			char * cmds[cmdSize+1];
			int n = cmdSize;

			for (int j = 0; j < cmdSize; j++) {
				cmds[j] = tokens[i-n];
				n--;
			}
			cmds[cmdSize] = NULL;
      if(pipes == 1){
        callingPipe(&pipeOdd[0], &pipeEven[0], cmds, 0, 1, cmdSize, &globList[0], &globs, ofp);
      }
      else if (pipes % 2 == 0 && pipes != 1){
        callingPipe(&pipeEven[0], &pipeOdd[0], cmds, 1, 1, cmdSize, &globList[0], &globs, ofp);
        close(pipeEven[0]);
        close(pipeEven[1]);
        if (pipe(pipeEven) == -1) {
          perror("pipe");
          exit(1);
        }
      }
      else{
        callingPipe(&pipeOdd[0], &pipeEven[0], cmds, 1, 1, cmdSize, &globList[0], &globs, ofp);
        close(pipeOdd[0]);
        close(pipeOdd[1]);
        if (pipe(pipeOdd) == -1) {
          perror("pipe");
          exit(1);
        }
      }
      pipes++;
      indexOfNthCmd = i + 1;
    }
  }

	int oFlag = (ofp != stdout);
  if(i == nTokens && strcmp(tokens[nTokens - 1], "|") != 0){
    int cmdSize = i - indexOfNthCmd;
    char * cmds[cmdSize+1];
    int n = cmdSize;

    for (int j = 0; j < cmdSize; j++) {
      cmds[j] = tokens[i-n];
      n--;
    }
    cmds[cmdSize] = NULL;
		if (pipes % 2 == 0 ){
			callingPipe(&pipeEven[0], &pipeOdd[0], cmds, 1, oFlag, cmdSize, &globList[0], &globs, ofp);
			pipeReading (pipeOdd, pipeEven,  ofp);
		}
		else{
			callingPipe(&pipeOdd[0], &pipeEven[0], cmds, 1, oFlag, cmdSize, &globList[0], &globs, ofp);
			pipeReading (pipeEven, pipeOdd, ofp);
		}
  }
	else{
		if (pipes % 2 == 0 )
			pipeReading (pipeEven, pipeOdd, ofp);
		else
			pipeReading (pipeOdd, pipeEven,  ofp);
	}

  int status = 0;
  for (int i = 0; i < pipes; i++){
    int exitingPid =  wait(&status);
    if (!WIFEXITED(status))
      fprintf(ofp,"PIPING Child (%d) crashed!\n", exitingPid);
  }

	for (size_t k = 0; k < globs; k++) {
		globfree(&(globList[k]));
	}

	return status;
}

int runInBackground (FILE *ofp, char ** const tokens, int nTokens, int bgps){
	int status = 0;
	int pid;

	/* now run the command */
	if ((pid = fork()) == 0){
		fprintf(ofp,"[%d] %ld\n", bgps, (long) getpid());
		execvp(tokens[0], tokens);

		perror("failed while running exec()");
		exit (-1);
	}

	if (pid < 1){
		perror("failed while running fork()");
		exit (-1);
	}

	usleep(6000);
	siginfo_t signalInfo;
	waitid(P_ALL, pid, &signalInfo, WNOWAIT);
	return pid;
}

int runGlobbingOnly (FILE *ofp, char ** const tokens, int nTokens){
	glob_t g;
	memset(&g, 0, sizeof(glob_t));
	int index = 0;
	for (size_t i = 0; i < nTokens; i++) {
		if(strchr(tokens[i], '*') != NULL  || strchr(tokens[i], '?') != NULL || (strchr(tokens[i], '[') != NULL && strchr(tokens[i], ']') != NULL)){
			if(index == 0){
				g.gl_offs = i;
				if(doGlobbing(ofp, tokens[i], &g)){
					for (size_t j = 0; j < i; j++){
						g.gl_pathv[j] = tokens[j];
					}
				}
				else
					return (-1);
			}
			else{
				int rtn = doGlobbing(ofp, tokens[i], &g);
				if(rtn == 0)
					return (-1);
			}
			index = i;
		}
	}

	int pid = runInForeground (ofp, g.gl_pathv, 0);

	int status = 0;
	int result = waitpid(pid, &status, 0);
	if (result < 0) {
		if(status != 0)
			fprintf(ofp,"Glob Child (%d) exitted -- failure (%d)\n", pid, status);
	}
	globfree(&g);

	return status;
}

int runCD(char * path){
	int rtn = 0;
  if(path == NULL || strcmp(path, "~") == 0 || strcmp(path, " ") == 0 || strcmp(path, "") == 0){
		char* home = getenv("HOME");
		rtn = chdir(home);
	}
	else{
		rtn = chdir(path);
	}

	if(rtn != 0){
		char buffer[(strlen(path) + 6)];
		buffer[0] = 'c';
		buffer[1] = 'd';
		buffer[2] = ':';
		buffer[3] = ' ';
		buffer[4] = '\0';
		strcat(buffer, path);
		perror(buffer);
	}

	return 0;
}


//HELPER FUNCTIONS
int doGlobbing (FILE *ofp, char * const globPattern, glob_t * g) {
		if (glob(globPattern, GLOB_DOOFFS | GLOB_APPEND, NULL, g) != 0) {
			fprintf(ofp, "error: globbing error!\n");

			return (0);
		}
	return (1);
}

void pipeForking(int * readP, int * writeP, char ** const cmd, int reading, int writing){
	pid_t pid = fork();
  if (pid == -1) {
    perror("failed running fork()");
    exit(1);
  } else if (pid == 0) {
    if(writing)
      dup2(writeP[1], 1);
    if(reading)
      dup2(readP[0], 0);

    close(readP[0]);
    close(readP[1]);
    close(writeP[0]);
    close(writeP[1]);
    execvp(cmd[0], cmd);

    perror("failed running exec()");
    exit(1);
  }
}

void pipeToFile(int * pipeRead, FILE * ofp){
	char buf;
  int bytesread;
  while ((bytesread = read(*pipeRead, &buf, 1)) > 0) {
      fprintf(ofp,"%c", buf);
  }
}

void pipeReading (int * pipeRead, int * pipeWrite, FILE * ofp){
	close(pipeWrite[0]);
	close(pipeWrite[1]);
	close(pipeRead[1]);
	pipeToFile(&pipeRead[0],ofp);
	close(pipeRead[0]);
}

int pipeGlobbing (FILE * ofp, char ** const cmd, int nCmds, glob_t * g){
	int found = 0;
	for (size_t i = 0; i < nCmds; i++) {
	  if(strchr(cmd[i], '*') != NULL  || strchr(cmd[i], '?') != NULL || (strchr(cmd[i], '[') != NULL && strchr(cmd[i], ']') != NULL)){
	    if(found == 0){
				memset(g, 0, sizeof(glob_t));
	      g->gl_offs = i;
	      if(doGlobbing(ofp, cmd[i], g)){
	        for (size_t j = 0; j < i; j++){
	          g->gl_pathv[j] = cmd[j];
	        }
	      }
	      else
	        return (-1);
				found = 1;
	    }
	    else{
	      int rtn = doGlobbing(ofp, cmd[i], g);
	      if(rtn == 0)
	        return (-1);
	    }
	  }
	}

	if(found)
		return 1;
	else
		return 0;
}

void callingPipe(int * readP, int * writeP, char ** const cmd, int reading, int writing, int nCmds, glob_t * globList, int * globs, FILE * ofp){
	int rtn = pipeGlobbing(ofp, cmd, nCmds, &(globList[*globs]));

	if(rtn){
		pipeForking(readP, writeP, globList[*globs].gl_pathv, reading, writing);
		*globs = *globs + 1;
	}
	else
		pipeForking(readP, writeP, cmd, reading, writing);
}
