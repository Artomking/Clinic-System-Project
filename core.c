/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Artom Zabihi
Student ID#: 137978227
Email      : azabihi1@myseneca.ca
Section    : NLL

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "core.h"

void clearInputBuffer(void)
{
// Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n'){
        ; // do nothing!
    }
}

void suspend(void){
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

int inputInt(void){
    char newLine = 'x';
    int value;

    do {
        scanf(" %d%c", &value, &newLine);

        if (newLine != '\n'){
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLine != '\n');

    return value;
}

int inputIntPositive(void){
    char newLine = 'x';
    int value;

    do {
        scanf(" %d%c", &value, &newLine);

        if (newLine != '\n'){
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }

        if (value <= 0){
            printf("ERROR! Value must be > 0: ");
        }

    } while (newLine != '\n' || value <= 0);

    return value;
}

int inputIntRange(int lower, int higher){
    char newLine = 'x';
    int value;

    do {
        scanf(" %d%c", &value, &newLine);

        if (newLine != '\n'){
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        } else if (value < lower || value > higher){
            printf("ERROR! Value must be between %d and %d inclusive: ", lower, higher);
        }
    } while (newLine != '\n' || (value < lower || value > higher));

    return value;
}

char inputCharOption(const char list[]){
    int flag = 0;
    char input;

    do{
        scanf(" %c", &input);

        if (strchr(list, input) != NULL){
            flag = 1;
        }

        if (flag == 0){
            printf("ERROR: Character must be one of [%s]: ", list);
        }
    } while (flag == 0);

    clearInputBuffer();
    return input;
}

void inputCString(char* string, int min, int max){
    int length, exit = 0;
    char character;

    do {
        character = ' ';
        length = 0;

        do {
            character = getchar();
            string[length] = character;
            length++;
        } while (character != '\n' && length <= max );

        if (character == '\n' && length <= max + 1){
            length--;
            string[length] = '\0';
        } else {
            string[max] = '\0';
            clearInputBuffer();
        }

        if (min == max && length != min){
            printf("ERROR: String length must be exactly %d chars: ", min);
        } else if (length > max){
            printf("ERROR: String length must be no more than %d chars: ", max);

        } else if (length < min){
            printf("ERROR: String length must be between %d and %d chars: ", min, max);
        } else {
            exit = 1;
        }
    } while (exit == 0);

}

void inputPhoneNumber(char* string, int min, int max){
    int length, exit = 0;
    char character;

    do {
        character = ' ';
        length = 0;

        do {
            character = getchar();
            string[length] = character;
            length++;
        } while (character != '\n' && length <= max );

        if (character == '\n' && length <= max + 1){
            length--;
            string[length] = '\0';
        } else {
            string[max] = '\0';
            clearInputBuffer();
        }

        if (min == max && length != min){
            printf("Invalid 10-digit number! Number: ");
        } else {
            exit = 1;
        }
    } while (exit == 0);
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

void displayFormattedPhone(const char* string){
    int length = 0;

    length = strlen(string);
    
    if (length != 10){
        printf("(___)___-____");
    } else {
        printf("(%c%c%c)%c%c%c-%c%c%c%c", string[0], string[1], string[2], string[3], string[4],
        string[5], string[6], string[7], string[8], string[9]);
    }

}
