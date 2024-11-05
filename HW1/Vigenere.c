/*
Vigenère Cipher implementation
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_INPUT_SIZE 1000 // i dont want to do dynamic alloc
#define VIGENERE_CIPHER_KEY "VINEGAR"

char* Vigenere_encrypt(char*, char*);
char* Vigenere_decrypt(char*, char*);
char Shift_capital_letter(int, char);

int main()
{
    // allocate and zero memory for input string
    char* input = calloc(MAX_INPUT_SIZE+1, sizeof(char));
    char mode;

    // explanation for user
    printf("Vigenère cipher implementation in C\n");
    printf("WARNING:\n");
    printf("\t1. Non-alphabet characters, including whitespace, will be stripped\n");
    printf("\t2. Case will be ignored\n");
    printf("\t3. Max length is 1000 characters\n");

    // ask user for and allocate ct/pt
    printf("\nEnter the text to process:\n>> ");
    fgets(input, MAX_INPUT_SIZE, stdin);
    printf("\n");
    if (strlen(input) <= 0) {
        printf("Invalid input.\n");
        free(input);
        return 1;
    }

    // change newline to null terminator
    if (input[strlen(input) - 1] == '\n') input[strlen(input) - 1] = '\0';

    // encrypt or decrypt user prompt
    printf("(D)ecrypt or (E)ncrypt?\n>> ");
    scanf("%c", &mode);

	// parsing input
	if (tolower(mode) == 'e') {
        printf("%s\n", Vigenere_encrypt(VIGENERE_CIPHER_KEY, input));
    } else if (tolower(mode) == 'd') {
        printf("%s\n", Vigenere_decrypt(VIGENERE_CIPHER_KEY, input));
    } else {
        printf("Invalid mode.\n");
		return 2;
    }
	free(input);
    return 0;
}

/*
Vigenère cipher encryption implementation.

Input: char* cipher key, char* plaintext
Output: char* ciphertext
*/
char* Vigenere_encrypt(char* key, char* pt)
{
    // allocate and zero memory for cyphertext
    char* ct = calloc(strlen(pt) + 1, sizeof(char));
    // align when writing to "out" by shifting back when skipping characters
    int backShift = 0;
    for(int i = 0; i < strlen(pt); i++) {
        // skip non-alphabetical characters
        if (!isalpha(pt[i])) backShift++;
        // shift = (key[(i - backShift) % strlen(key)] - 'A')
        else ct[i - backShift] = Shift_capital_letter((key[(i - backShift) % strlen(key)] - 'A'), toupper(pt[i]));
    }
    return ct;
}

/*
Vigenère cipher decryption implementation.

Input: char* cipher key, char* plaintext
Output: char* ciphertext
*/
char* Vigenere_decrypt(char* key, char* ct)
{
    // allocate and zero memory for cyphertext
    char* pt = calloc(strlen(ct) + 1, sizeof(char));
    // align when writing to "out" by shifting back when skipping characters
    int backShift = 0;
    for(int i = 0; i < strlen(ct); i++) {
        // skip non-alphabetical characters
        if (!isalpha(ct[i])) backShift++;
        // shift = (key[(i - backShift) % strlen(key)] - 'A')
        else pt[i - backShift] = Shift_capital_letter(-1 * (key[(i - backShift) % strlen(key)] - 'A'), toupper(ct[i]));
    }
    return pt;
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
