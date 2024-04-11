#include <stdio.h>


void printBinary(unsigned int number);
int isPalindromeDec(unsigned int number);
int isPalindromeBin(unsigned int number);

int main(){
    unsigned int sumofpalindromes = 0;
    
    // Check all natural numbers less than 1000000: [1, 1000000)
    for(int i = 1; i < 1000000; i++){
        if(isPalindromeDec(i) && isPalindromeBin(i)){
            sumofpalindromes += i;
        }
    }
    
    printf("Sum of all palindromes in range [1, 1000000): %d\n", sumofpalindromes);
}

// printBinary - Prints an integer in binary form using recursion
void printBinary(unsigned int number)
{
    if (number >> 1) {			// Base case: Stop printing bits when right shift 1 reaches 0
        printBinary(number >> 1);
    }
    if(number & 1){
        putc('1', stdout);
    }
    else{
        putc('0', stdout);
    }
}

// isPalindromeDec - Checks whether the given decimal (base 10) number is a palindrome, returning 0 if false or 1 if true
int isPalindromeDec(unsigned int number){
    unsigned int n = number;
    unsigned int remainder;
    unsigned int reverse = 0;
    
    while(n != 0){
        remainder = n % 10;
        reverse = reverse * 10 + remainder;
        n /= 10;
    }
    
    if(number == reverse){
        // printf("base 10 palindrome:\n");
        // printf("%d\n", reverse);
        return 1;
    }
    else{
        return 0;
    }
    
}

// isPalindromeBin - Checks whether the given binary (base 2) number is a palindrome, returning 0 if false or 1 if true
int isPalindromeBin(unsigned int number){
    unsigned int n = number;
    unsigned int remainder;
    unsigned int reverse = 0;
    
    while(n != 0){
        remainder = n % 2;
        reverse = reverse * 2 + remainder;
        n /= 2;
    }
    
    if(number == reverse){
        // printf("base 2 palindrome:\n");
        // printBinary(reverse);
        // printf("\n");
        return 1;
    }
    else{
        return 0;
    }
}
