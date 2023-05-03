#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

/*
 * This code generates a random word from a list, and then prompts the user to
 * guess letters one at a time. The game continues until the user either correctly
 * guesses the word or runs out of tries. The graphics can be enhanced by adding
 * ASCII art of a hangman and updating it with each incorrect guess.
 */

using namespace std;

vector<string> words = {"computer", "programming", "algorithm", "language", "developer", "debugging", "syntax", "code", "variable", "function"};

const int MAX_TRIES = 7;

int main() {
    srand(time(NULL)); // Seed the random number generator with the current time
    string word = words[rand() % words.size()]; // Pick a random word from the list
    string hidden(word.length(), '_'); // Initialize a string of underscores the same length as the word
    int wrongGuesses = 0; // Counter for the number of incorrect guesses
    vector<char> guessed; // Keep track of the letters the user has guessed

    cout << "Welcome to Hangman!" << endl;
    while (wrongGuesses < MAX_TRIES && hidden != word) {
        cout << endl << "Word: " << hidden << endl;
        cout << "Guesses: ";
        for (char c : guessed) {
            cout << c << " ";
        }
        cout << endl;

        char guess;
        cout << "Enter a letter: ";
        cin >> guess;
        guessed.push_back(guess);

        bool found = false;
        for (int i = 0; i < word.length(); i++) {
            if (word[i] == guess) {
                hidden[i] = guess;
                found = true;
            }
        }

        if (!found) {
            wrongGuesses++;
            cout << "Incorrect guess! You have " << MAX_TRIES - wrongGuesses << " tries left." << endl;
        }
    }

    if (hidden == word) {
        cout << "Congratulations! You guessed the word: " << word << endl;
    } else {
        cout << "Sorry, you ran out of tries. The word was: " << word << endl;
    }

    return 0;
}
