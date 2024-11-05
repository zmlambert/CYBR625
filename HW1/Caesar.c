/*
Caesar Cipher implementation
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_INPUT_SIZE 1000 // i dont want to do dynamic alloc

char* Caesar(int, char*);
char* Caesar_encrypt(int, char*);
char* Caesar_decrypt(int, char*);
char Shift_capital_letter(int, char);

int main()
{
    // allocate and zero memory for input string
    char* input = calloc(MAX_INPUT_SIZE+1, sizeof(char));
    // mode: encrypt and decrypt
    char mode;
    // cipher shift
    int shift;

    // explanation for user
    printf("Caesar cipher implementation in C\n");
    printf("WARNING:\n");
    printf("\t1. Non-alphabet characters, including whitespace, will be stripped\n");
    printf("\t2. Case will be ignored\n");
    printf("\t3. Max length is 1000 characters\n");

    // ask user for and allocate for input
    printf("\nEnter the text to process:\n>> ");
    fgets(input, MAX_INPUT_SIZE, stdin);
    printf("\n");
    if (strlen(input) <= 0) {
        printf("Invalid input.\n");
        free(input);
        return 1;
    }

    // get shift amount
    printf("Input shift amount:\n>> ");
    scanf("%d", &shift);
    printf("\n");
    // there are 26 different shifts (0 and 26 are the same shifts)
    shift = shift % 26;

    // clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != '\0') {}

    // encrypt or decrypt user prompt
    printf("(D)ecrypt or (E)ncrypt?\n>> ");
    scanf("%c", &mode);

	// parsing input
	if (tolower(mode) == 'e') {
        printf("%s\n", Caesar_encrypt(shift, input));
    } else if (tolower(mode) == 'd') {
        printf("%s\n", Caesar_decrypt(shift, input));
    } else {
        printf("Invalid mode.\n");
		return 2;
    }

	free(input);
    return 0;
}

/*
Caesar cipher implementation

Input: char* cipher shift, char* text
Output: char* shifted text
*/
char* Caesar(int shift, char* inp)
{
	// allocate and zero memory for cyphertext
    char* out = calloc(strlen(inp)+1, sizeof(char));

    // align when writing to "out" by shifting back when skipping characters
    short backShift = 0;
    for(int i = 0; i < strlen(inp); i++) {
		// skip non-alphabetical characters
        if (!isalpha(inp[i])) backShift++;
        else out[i - backShift] = Shift_capital_letter(shift, toupper(inp[i]));
    }
	return out;
}

/*
Function to decrypt Caesar cipher.

Input: char* cipher shift, char* ciphertext
Output: char* plaintext
*/
char* Caesar_decrypt(int shift, char* ct)
{
    // the "reverse shift" is the shift applied backwards :)
    return Caesar(-1 * shift, ct);
}

/*
Function to decrypt Caesar cipher.

Input: char* cipher shift, char* plaintext
Output: char* ciphertext
*/
char* Caesar_encrypt(int shift, char* pt)
{
 return Caesar(shift, pt);
}

/*
Shift character along the alphabet, looping back
from Z to A and vice versa for negative shifts.

Input:
*/
char Shift_capital_letter(int shift, char c)
{
    // shift char by shift amount
    c += shift;
    // edge case when encrypting: greater than 'Z' is meant to be 'A'
    if(c > 'Z') c -= 26;
    // edge case when decrypting: less than 'A' is meant to be 'Z'
    if(c < 'A') c += 26;
    return c;
}
