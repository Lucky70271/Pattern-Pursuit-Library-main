#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Boyer-Moore Algorithm
#define NO_OF_CHARS 256

// Preprocess the pattern to create the bad character heuristic array
void badCharHeuristic(const string &pattern, vector<int> &badChar) {
    int M = pattern.length();
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1; // Initialize all occurrences to -1
    }
    for (int i = 0; i < M; i++) {
        badChar[(int)pattern[i]] = i; // Fill the actual value of last occurrence
    }
}

// Boyer-Moore Search
void BoyerMooreSearch(const string &pattern, const string &text) {
    int M = pattern.length();
    int N = text.length();
    vector<int> badChar(NO_OF_CHARS);

    // Preprocess the pattern
    badCharHeuristic(pattern, badChar);

    int shift = 0;  // Shift of the pattern with respect to text
    bool found = false;
    
    while (shift <= (N - M)) {
        int j = M - 1;

        // Decrease j while characters match
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        // If pattern is present at shift
        if (j < 0) {
            cout << "Pattern found at index " << shift << endl;
            found = true;

            // Shift the pattern so that the next character in text aligns with the last occurrence of it in pattern
            shift += (shift + M < N) ? M - badChar[text[shift + M]] : 1;
        } else {
            // Shift the pattern to align the bad character
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }

    if (!found) {
        cout << "Pattern not found" << endl;
    }
    cout << "End of Boyer-Moore Search" << endl;  // End of search
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <text> <pattern>" << endl;
        return 1;
    }

    string text = argv[1];
    string pattern = argv[2];

    BoyerMooreSearch(pattern, text);
    return 0;
}
