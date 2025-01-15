#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Copies a substring from the source string `src` to the destination `dest`
// starting at index `start` with length `length`
void copy_substring(char *dest, const char *src, int start, int length) {
    for (int i = 0; i < length; i++) {
        dest[i] = src[start + i];
    }
    dest[length] = '\0';
}

// Compares two strings `str1` and `str2` for equality
// Returns true if they are equal, false otherwise
bool compare_strings(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}

// Checks if a given string `x` belongs to the language L
// L is defined as strings in the form ww1w, where w and w1 are non-empty strings
bool is_in_language(const char *x) {
    int n = strlen(x);

    // Loop over possible lengths for the prefix and suffix `w`
    for (int i = 1; i <= n / 2; i++) {
        char w[i + 1];
        copy_substring(w, x, 0, i); // Extract prefix `w` of length `i`

        // Check if the suffix of length `i` matches the prefix `w`
        if (compare_strings(w, x + n - i)) {
            int w1_length = n - 2 * i; // Calculate the length of the middle segment `w1`
            char ww1w[n + 1];
            copy_substring(ww1w, w, 0, i); // Copy `w` to the beginning of `ww1w`
            copy_substring(ww1w + i, x, i, w1_length); // Copy `w1` into `ww1w`
            copy_substring(ww1w + i + w1_length, w, 0, i); // Append `w` at the end of `ww1w`
            ww1w[n] = '\0';

            // Check if constructed string `ww1w` matches `x`
            if (compare_strings(ww1w, x)) {
                return true;
            }
        }
    }

    return false;
}

// Checks if the input string `y` belongs to the language L*
// L* is defined as the set of all concatenations of strings in L
bool is_in_language_star(const char *y) {
    int n = strlen(y);
    bool dp[n + 1];
    dp[0] = true;  // The empty string is always in L*

    // Initialize all other dp values to false
    for (int i = 1; i <= n; i++) {
        dp[i] = false;
    }

    // Fill dp array by checking each substring
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            // Extract substring `y[j:i]` and check if it belongs to L
            char substring[i - j + 1];
            copy_substring(substring, y, j, i - j);

            // If `dp[j]` is true and `y[j:i]` is in L, set `dp[i]` to true
            if (dp[j] && is_in_language(substring)) {
                dp[i] = true;
                break; // No need to check further if `dp[i]` is true
            }
        }
    }

    return dp[n];
}

int main() {
    char y[100];
    printf("Enter the string y: ");
    scanf("%s", y);

    // Check if `y` belongs to L*
    if (is_in_language_star(y)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}
