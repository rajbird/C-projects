#ifndef __DISH_RUN_SCRIPT_HEADER__
#define __DISH_RUN_SCRIPT_HEADER__

int runScript(FILE *ofp, FILE *pfp, FILE *ifp, const char *filename, int verbosity);
int runScriptFile(FILE *ofp, FILE *pfp, const char *filename, int verbosity);

int runInForeground (FILE *ofp, char ** const tokens, int waiting);
int runPWD (FILE *ofp);
int pipeHandling(FILE *ofp, char ** const tokens, int nTokens);
int runInBackground (FILE *ofp, char ** const tokens, int nTokens, int bgps);
int runGlobbingOnly (FILE *ofp, char ** const tokens, int nTokens);
int runCD(char * path);

//HELPER FUNCTIONS
int getTokensToStr (FILE *ofp, char *buf, int bufsiz, char ** const tokens, int useQuotes);
void pipeForking(int * readP, int * writeP, char ** const cmd, int reading, int writing);
void pipeToFile(int * pipeRead, FILE * ofp);
void pipeReading (int * pipeRead, int * pipeWrite, FILE * ofp);
int pipeGlobbing (FILE * ofp, char ** const cmd, int nCmds, glob_t * g);
int doGlobbing (FILE *ofp, char * const globPattern, glob_t * g);
void callingPipe(int * readP, int * writeP, char ** const cmd, int reading, int writing, int nCmds, glob_t * globList, int * globs, FILE * ofp);

#define	LINEBUFFERSIZE	(1024 * 8)
#define	MAXTOKENS		(1024 * 2)

#define	MAXCOMMANDSINPIPE	128

#define	MAXBGPROCESS	169

#define	PROMPT_STRING	"(dish) % "

#endif /* __DISH_RUN_SCRIPT_HEADER__ */
