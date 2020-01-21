/**
 Author: Christopher Arnoult
 Finished on 1-20-2020
 
 Simple program to check if a given numerical input is a valid Mastercard, American Express, or VISA credit card. I used Luhn's algorithm to mathematically check to see if the number could be a valid generated card number. I purposely did this without using arrays/lists/etc. This does not check for any malicious card numbers that pass the checksum in the mod 10 algorithm.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

void luhnCheck(void);
void validCard(int sum, long count, long cardNumber, long firstTwoDigits);
int mutliplyByTwoAndAddDigits(int digit);

int main(void) {
    luhnCheck();
}

void luhnCheck(void) {
    long cardNumber = get_long("What is your card number? \n");
    
    //counts how many digits are in cardNumber; e.g. 16.
    long count = floor(log10(labs(cardNumber))) + 1;
    bool flag = false;
    int digit;
    int sum = 0;
    long firstTwoDigits = cardNumber;
    
    //get first two digits of the card number.
    while (firstTwoDigits > 100) {
        firstTwoDigits = firstTwoDigits / 10;
    }
    
    for(int i = 0; i < count; i++) {
        //pulls each other number out and prints on separate line.
        while(cardNumber) {
            digit = cardNumber % 10;
            if(flag == true) {
               digit = mutliplyByTwoAndAddDigits(digit);
            }
            sum = sum + digit;
            cardNumber /= 10;
            flag = !flag;
        }
    }
    validCard(sum, count, cardNumber, firstTwoDigits);
}

int mutliplyByTwoAndAddDigits(int digit) {
    digit *= 2;
    if(digit >= 10) {
        digit -= 9;
    }
    return digit;
}

void validCard(int sum, long count, long cardNumber, long firstTwoDigits) {
    
    if(sum % 10 == 0) {
        //Checks what kind of card cardNumber is.
        if(firstTwoDigits > 50 && firstTwoDigits < 56 && count == 16) {
            printf("MASTERCARD\n");
        }
        else if((firstTwoDigits == 34 || firstTwoDigits == 37) && count == 15) {
            printf("AMEX\n");
        }
        else if(firstTwoDigits / 10 == 4 && (count == 13 || count == 16)) {
            printf("VISA\n");
        }
        else {
            printf("INVALID\n");
        }
    }
    else {
        printf("INVALID\n");
    }
}
