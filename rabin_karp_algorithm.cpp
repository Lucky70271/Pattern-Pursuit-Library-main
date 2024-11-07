#include <iostream>
#include <string>
using namespace std;

// Rabin-Karp Algorithm
#define d 256  // Number of characters in the input alphabet
const int q = 101;  // A prime number for hashing

// Rabin-Karp Search
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
    cout << "End of Rabin-Karp Search" << endl;  // End of search
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <text> <pattern>" << endl;
        return 1;
    }

    string text = argv[1];
    string pattern = argv[2];

    RabinKarpSearch(pattern, text);
    return 0;
}
