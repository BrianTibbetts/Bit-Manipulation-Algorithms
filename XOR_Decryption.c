/* A solution to project euler problem 59: XOR decryption
 * -Decrypt the included cipher text (0059_cipher.txt) of comma-separated encrypted ASCII codes and find the sum of the original plain text ASCII codes.
 * -The encryption key is three lowercase alphabetic characters.
 * -The plain text must contain common English words. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int letterCount(char letter, char *text, int textlength);
void xorDecrypt(char *key, char *ciphertext, char *plaintext, int textlength);

int main(int argc, char **argv){
    /* Check command line args */
    if (argc != 2) {
	fprintf(stderr, "usage: %s <ciphertext.txt>\n", argv[0]);
	exit(1);
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    
    if(!fp){
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    
    int i, j;				// Counters for various loops
    
    // Get information about the ciphertext file and its contents
    struct stat info;
    stat(argv[1], &info);
    char filetext[info.st_size];	// The ciphertext file size determines how many chars it contains
    int c;
    
    i = 0;
    while ((c = fgetc(fp)) != EOF) {
        filetext[i] = c;
        i++;
    }
    
    fclose(fp);
    
    // Convert the ciphertext file contents to an array of ASCII character codes
    int textlength = 0;
    
    for(i = 0; i < info.st_size; i++){
        if(filetext[i] == ',')
            textlength++;
    }
    textlength++;				// # of ASCII char codes in cipher text = # of ',' chars + 1
    
    char ciphertext[textlength];
    char *token = strtok(filetext, ",");
    	
    for(i = 0; i < textlength; i++){		// Separate the ciphertext file by its commas into ASCII characters
        ciphertext[i] = atoi(token);
        token = strtok(NULL, ",");
    }

    // Frequency analysis: Decrypt the ciphertext into 3 plain text substrings to determine which key characters produce the most 'e' plain text characters
    int textsplitlength = textlength/3;
    char plaintext_keychar0[textsplitlength];
    char plaintext_keychar1[textsplitlength];
    char plaintext_keychar2[textsplitlength];
    char currentletter = 'a';			
    char key[3];				// Characters 'a' to 'z' are valid key characters
    int ecount[] = {0, 0, 0};
    int highecount[] = {0, 0, 0};

    for(i = 0; i < 26; i++){
        // Decrypt each cipher text character to populate the 3 plain text arrays corresponding to each character of the key
        for(j = 0; j < textsplitlength; j++){
            plaintext_keychar0[j] =  ciphertext[j*3] ^ currentletter;
            plaintext_keychar1[j] =  ciphertext[j*3+1] ^ currentletter;
            plaintext_keychar2[j] =  ciphertext[j*3+2] ^ currentletter;
        }

        // Count 'e' characters in the plain text
        ecount[0] = letterCount('e', plaintext_keychar0, textsplitlength);
        ecount[1] = letterCount('e', plaintext_keychar1, textsplitlength);
        ecount[2] = letterCount('e', plaintext_keychar2, textsplitlength);
        
        // Update which key characters have produced the most 'e' characters so far
        if(ecount[0] > highecount[0]){
            highecount[0] = ecount[0];
            key[0] = currentletter;
        }
        if(ecount[1] > highecount[1]){
            highecount[1] = ecount[1];
            key[1] = currentletter;
        }
        if(ecount[2] > highecount[2]){
            highecount[2] = ecount[2];
            key[2] = currentletter;
        }
        
        currentletter++;
    }

    printf("Key character 0: '%c' produced 'e' %d times.\n", key[0], highecount[0]);
    printf("Key character 1: '%c' produced 'e' %d times.\n", key[1], highecount[1]);
    printf("Key character 2: '%c' produced 'e' %d times.\n", key[2], highecount[2]);
    
    // Use the key to decrypt the cipher text
    char plaintext[textlength];
    xorDecrypt(key, ciphertext, plaintext, textlength);
    
    // Find the sum of ASCII codes in the plaintext
    int plaintextsum = 0;
    for(i = 0; i < textlength; i++){
        plaintextsum += plaintext[i];
    }
    printf("key '%s' plaintext:\n%s\n", key, plaintext);
    printf("ASCII code sum = %d\n", plaintextsum);
    
    
    
    return 0;
}

/* letterCount - Counts how many times a specific letter appears in a string
 * 
 * parameters
 *   char letter - The letter which is being counted
 *   char *text - The string to search for the letter
 *   int textlength - The length of the string
 *
 * return value - The number of times the letter appeared in the string
 */
int letterCount(char letter, char *text, int textlength){
    int count = 0;
    int i;
    for(i = 0; i < textlength; i++){
        if(text[i] == letter)
            count++;
    }
    return count;
}

/* xorDecrypt - Attempts to decrypt an XOR-encrypted ciphertext using XOR with a 3-character key.
 *
 * parameters
 *   char *key - A 3-character key to try decrypting the ciphertext with
 *   char *ciphertext - A ciphertext string encrypted by XOR using an unknown 3-character key
 *   char *plaintext - An empty string to write the result of decryption attempt to
 *   int textlength - The number of ASCII character codes in the ciphertext or plaintext (this is always the same value for both)
 */
void xorDecrypt(char *key, char *ciphertext, char *plaintext, int textlength){
    int i;
    for(i = 0; i < textlength; i+=3){
        plaintext[i] = ciphertext[i] ^ key[0];
        plaintext[i+1] = ciphertext[i+1] ^ key[1];
        plaintext[i+2] = ciphertext[i+2] ^ key[2];
    }
}




