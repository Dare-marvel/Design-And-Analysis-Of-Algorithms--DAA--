#include <stdio.h>
#include <string.h>

#define d 256  // The number of characters in the input alphabet
#define q 101  // A prime number used for hashing

void rabin_karp(char* text, char* pattern) {
    int text_length = strlen(text);
    int pattern_length = strlen(pattern);
    int i, j;
    int pattern_hash = 0;  
    int text_hash = 0;  
    int h = 1;  

    // Calculate h as d^(pattern_length-1) to be used in hash function
    for (i = 0; i < pattern_length - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate the hash value of pattern and the first window of text
    for (i = 0; i < pattern_length; i++) {
        pattern_hash = (d * pattern_hash + pattern[i]) % q;
        text_hash = (d * text_hash + text[i]) % q;
    }

    // Slide the pattern over the text one by one
    for (i = 0; i <= text_length - pattern_length; i++) {
 
        // Check if the hash values of the pattern and current window of text match
        if (pattern_hash == text_hash) {
        
            // Check if all characters of pattern match the current window of text
            for (j = 0; j < pattern_length; j++) {
                if (text[i+j] != pattern[j]) {
                    break;
                }
            }

            // If all characters match, print the starting and ending indices of the match
            if (j == pattern_length) {
                printf("Pattern found in text starting at index %d and ending at index %d.\n", i, i+pattern_length-1);
            }
        }

        // Calculate hash value of the next window of text
        if (i < text_length - pattern_length) {
            text_hash = (d * (text_hash - text[i] * h) + text[i+pattern_length]) % q;

            // If the hash value is negative, make it positive by adding q
            if (text_hash < 0) {
                text_hash += q;
            }
        }
    }
}

int main() {
    char text[1000], pattern[1000];

    // Take input of text and pattern from user
    printf("Enter the text: ");
    fgets(text, 1000, stdin);
    printf("Enter the pattern to search for: ");
    fgets(pattern, 1000, stdin);

    // Remove newline characters from input strings
    text[strcspn(text, "\n")] = 0;
    pattern[strcspn(pattern, "\n")] = 0;

    // Call the Rabin-Karp function and print the matches found
    printf("Matches found:\n");
    rabin_karp(text, pattern);

    return 0;
}
