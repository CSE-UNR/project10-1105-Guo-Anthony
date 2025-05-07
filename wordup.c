//Author: Anthony Guo
//Date:4/28/2025
//Purpose:Project 10

//constants makes a variable non modifiable once declared https://www.tutorialspoint.com/cprogramming/c_constants.htm

#include <stdio.h>
#include <stdbool.h>

#define MAX 100
#define LENGTH 5
#define ATTEMPTS 6

// Function prototypes
void inputguess(char guess[]);  // Function declaration
int load(char words[][LENGTH + 1]);
void checkguess(const char guess[], const char answer[], char results[], char marks[]);
void displaypast(int tries, char guesses[][LENGTH + 1], char marks[][LENGTH + 1]);
bool correct(const char guess[], const char answer[]);
bool Limit(char guess[]);

// Main function
int main() {
    char wordbank[MAX][LENGTH + 1];
    char pastguess[ATTEMPTS][LENGTH + 1];
    char pastmark[ATTEMPTS][LENGTH + 1];
    char guess[LENGTH + 1]; // + null terminator

    int wordCount = load(wordbank);
    if (wordCount == 0) {
        printf("Error loading words.\n");
        return 1;
    }

    const char* answer = wordbank[0];

    for (int attempt = 0; attempt < ATTEMPTS; attempt++) {
        if (attempt == ATTEMPTS - 1) {
            printf("FINAL GUESS: ");
        } else {
            printf("GUESS %d! Enter your guess: ", attempt + 1);
        }

        inputguess(guess);

        // Copy guess to past guesses manually
        for (int i = 0; i < LENGTH; i++) {
            pastguess[attempt][i] = guess[i];
        }
        pastguess[attempt][LENGTH] = '\0';  // Null terminate manually

        // func call
        checkguess(guess, answer, pastguess[attempt], pastmark[attempt]);
        displaypast(attempt + 1, pastguess, pastmark);

        if (correct(guess, answer)) {
            printf("================================\n");
            printf("        %s\n", answer);
            printf("    You won in %d guesses!\n", attempt + 1);

            // Printing different messages
            switch (attempt + 1) {
                case 1:
                    printf("        GOATED!\n");
                    break;
                case 2:
                    printf("        Amazing!\n");
                    break;
                case 3:
                    printf("        Amazing!\n");
                    break;
                case 4:
                    printf("        Nice!\n");
                    break;
                case 5:
                    printf("        Nice!\n");
                    break;
                case 6:
                    break;
            }
            return 0; // Exit when player wins
        }
    }

    printf("Out of attempts. The word was: %s\n", answer);
    return 0;
}

// Load words from "mystery.txt"
int load(char words[][LENGTH + 1]) {
    FILE* file = fopen("mystery.txt", "r");
    if (file == NULL) return 0;

    int count = 0;
    while (count < MAX && fscanf(file, "%5s", words[count]) == 1) {
        words[count++][LENGTH] = '\0'; // Null terminate the word
    }

    fclose(file);
    return count;
}

// Check if the guess is exactly 5 letters
bool Limit(char guess[]) {
    int length = 0;
    while (guess[length] != '\0') {
        length++;
    }
    return length == 5;
}

// Function to get a valid guess from the user
void inputguess(char guess[]) {
    bool valid = false;
    int ch;

    while (!valid) {
        int i = 0;
        printf("Enter your guess: ");
        while (i < 5) {
            ch = getchar();
            if (ch == '\n') break;  // Stop reading when Enter is pressed
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                guess[i++] = (char)ch;  // Only accept alphabetic characters
            }
        }

        // Null terminate the guess
        guess[i] = '\0';

        // Check if the guess is exactly 5 letters long using the Limit function
        if (Limit(guess)) {
            valid = true;  // Valid input
        } else {
            // Clear the input buffer if the guess is not 5 characters
            while (getchar() != '\n');  // Discard leftover characters in the buffer
            printf("Your guess must be exactly 5 letters long. Please try again.\n");
        }
    }
}

void checkguess(const char guess[], const char answer[], char results[], char marks[]) {
    bool used[LENGTH] = {false};  // To track used letters for correct position

    // First pass: Check for exact matches (correct letter, correct position)
    for (int i = 0; i < LENGTH; i++) {
        if (guess[i] == answer[i]) {
            // Convert correct letters to uppercase and mark exact match
            if (guess[i] >= 'a' && guess[i] <= 'z') {
                results[i] = guess[i] - ('a' - 'A');  // Convert lowercase to uppercase
            } else {
                results[i] = guess[i];  // Already uppercase
            }
            marks[i] = ' ';  // No up arrow for exact match
            used[i] = true;  // Mark letter as used
        } else {
            // Convert incorrect letters to lowercase
            if (guess[i] >= 'A' && guess[i] <= 'Z') {
                results[i] = guess[i] + ('a' - 'A');  // Convert uppercase to lowercase
            } else {
                results[i] = guess[i];  // Already lowercase
            }
            marks[i] = ' ';  // Placeholder for incorrect letters
        }
    }

    // Second pass: Check for correct letters in the wrong position
    for (int i = 0; i < LENGTH; i++) {
        if (marks[i] == ' ') {  // Only process letters that are not already matched
            for (int j = 0; j < LENGTH; j++) {
                // If letter is correct but not used and not already marked
                if (!used[j] && guess[i] == answer[j]) {
                    marks[i] = '^';  // Up arrow for correct letter, wrong position
                    // Keep lowercase in wrong position
                    if (guess[i] >= 'A' && guess[i] <= 'Z') {
                        results[i] = guess[i] + ('a' - 'A');  // Convert uppercase to lowercase
                    } else {
                        results[i] = guess[i];  // Already lowercase
                    }
                    used[j] = true;  // Mark this letter as used
                    break;
                }
            }
        }
    }

    results[LENGTH] = '\0';  // Null terminate results
    marks[LENGTH] = '\0';    // Null terminate marks
}

void displaypast(int tries, char guesses[][LENGTH + 1], char marks[][LENGTH + 1]) {
    printf("================================\n");
    for (int i = 0; i < tries; i++) {
        printf("%s\n", guesses[i]);
        printf("%s\n", marks[i]);
    }
}

bool correct(const char guess[], const char answer[]) {
    for (int i = 0; i < LENGTH; i++) {
        if (guess[i] != answer[i]) {
            return false;
        }
    }
    return true;
}

