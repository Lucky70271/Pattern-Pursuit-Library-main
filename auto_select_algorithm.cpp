#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include<vector>
using namespace std;
#define NO_OF_CHARS 256
#define d 256  
const int q = 101;

// Function declarations for each algorithm
void KMPSearch(const string &pattern, const string &text);
void BoyerMooreSearch(const string &pattern, const string &text);
void RabinKarpSearch(const string &pattern, const string &text);

void autoSelectAlgorithm(const string &pattern, const string &text) {
    int M = pattern.length();
    int N = text.length();

    // Auto-selection logic based on the pattern and text size
    if (M < 10 && N > 1000) {
        cout << "Auto-selected: Rabin-Karp" << endl;
        RabinKarpSearch(pattern, text);
    } else if (M > 10 && N > 1000) {
        cout << "Auto-selected: Boyer-Moore" << endl;
        BoyerMooreSearch(pattern, text);
    } else {
        cout << "Auto-selected: KMP" << endl;
        KMPSearch(pattern, text);
    }
}

// KMP Algorithm (same as you provided)
void KMPSearch(const string &pattern, const string &text) {
    int M = pattern.length();
    int N = text.length();
    int lps[M];  // Longest prefix suffix array

    // Preprocess the pattern (calculate lps array)
    int len = 0, i = 1;
    lps[0] = 0;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    // Start searching in the text
    i = 0;
    int j = 0;
    bool found = false;
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            cout << "Pattern found at index " << i - j << endl;
            found = true;
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    if (!found) {
        cout << "Pattern not found" << endl;
    }
    cout << "End of KMP Search" << endl;
}

// Boyer-Moore Algorithm (same as modified above)
void badCharHeuristic(const string &pattern, vector<int> &badChar) {
    int M = pattern.length();
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1; // Initialize all occurrences to -1
    }
    for (int i = 0; i < M; i++) {
        badChar[(int)pattern[i]] = i; // Fill the actual value of last occurrence
    }
}

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
    cout << "End of Boyer-Moore Search" << endl;
}

// Rabin-Karp Algorithm (same as modified above)
void RabinKarpSearch(const string &pattern, const string &text) {
    int M = pattern.length();
    int N = text.length();
    int i, j;
    int p = 0;  // Hash value for pattern
    int t = 0;  // Hash value for text
    int h = 1;
    bool found = false;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
        // Check the hash values of current window of text and pattern
        if (p == t) {
            // Check for characters one by one
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == M) {
                cout << "Pattern found at index " << i << endl;
                found = true;
            }
        }

        // Calculate hash value for next window of text
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative value of t, convert it to positive
            if (t < 0) {
                t = (t + q);
            }
        }
    }

    if (!found) {
        cout << "Pattern not found" << endl;
    }
    cout << "End of Rabin-Karp Search" << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <text> <pattern> <algorithm>" << endl;
        return 1;
    }

    string text = argv[1];
    string pattern = argv[2];
    string algorithm = argv[3];

    if (algorithm == "kmp") {
        KMPSearch(pattern, text);
    } else if (algorithm == "boyer-moore") {
        BoyerMooreSearch(pattern, text);
    } else if (algorithm == "rabin-karp") {
        RabinKarpSearch(pattern, text);
    } else if (algorithm == "auto") {
        autoSelectAlgorithm(pattern, text);
    } else {
        cout << "Invalid algorithm choice." << endl;
    }

    return 0;
}
