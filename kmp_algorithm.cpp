#include <iostream>
#include <string>
using namespace std;

// KMP Algorithm
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
    cout << "End of KMP Search" << endl;  // End of search
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <text> <pattern>" << endl;
        return 1;
    }

    string text = argv[1];
    string pattern = argv[2];

    KMPSearch(pattern, text);
    return 0;
}
