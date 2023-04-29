## Explanation of Rabin Karp function:
The Rabin-Karp algorithm is a string searching algorithm that works by hashing the pattern and comparing it to substrings of the text. The logic of the Rabin-Karp function in this code is as follows:

* Get the length of the text and the pattern.
* Initialize variables pattern_hash and text_hash to 0.
* Initialize h to 1, which will be used in the hash function.
* Calculate h as d^(pattern_length-1), where d is the number of characters in the input alphabet, and q is a prime number used for hashing.
* Calculate the hash value of the pattern and the first window of text using the formula hash = (d * hash + character) % q, where hash is either pattern_hash or text_hash.
* Slide the pattern over the text one by one.
* Check if the hash values of the pattern and current window of text match.
* If they match, check if all characters of pattern match the current window of text.
* If all characters match, print the starting and ending indices of the match.
* Calculate the hash value of the next window of text using the formula hash = (d * (hash - character_at_start_of_window * h) + character_at_end_of_window) % q.
* If the hash value is negative, make it positive by adding q.
* This algorithm works by using a rolling hash function, which allows the hash of a substring to be calculated efficiently by using the hash of the previous substring. This avoids having to recalculate the hash for each substring, which can be time-consuming. The algorithm also makes use of modular arithmetic to prevent overflow when calculating the hash value.

## Time and Space Complexity:
### `Time Complexity`
The time complexity of the Rabin-Karp algorithm depends on the hash function used, which in this case is a simple polynomial rolling hash function. The worst-case time complexity of the algorithm is O((n-m+1)*m), where n is the length of the text and m is the length of the pattern. However, on average, the algorithm has a much better performance than the worst-case complexity, and its time complexity is usually O(n+m) when the hash function works well.

### `Space Complexity`
The space complexity of the algorithm is O(1) because the only extra space used is for storing some variables such as the hash values and loop counters. Therefore, the space complexity is constant and does not depend on the size of the input.

## Code:
```c
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
```
