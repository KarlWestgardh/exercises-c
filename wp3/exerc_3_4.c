/*
File name: exerc_3_4.c (or cpp)
Date: YYYY-MM-DD
Group nr 1
Members that contribute to the solutions
Emanuel Dellsén
Niklas Möller
Karl Westgårdh 

Member not present at demonstration time:
NONE

Demonstration code: []
Important
No code no exercise points!
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// -----Typedefs -------//
typedef struct
{
    char firstname[20];
    char famnamne[20];
    char pers_number[13];
} PERSON;

#define MAX 1024 //1 Kb to not overflow
char buffer[MAX];
char *ptr_buffer = buffer;

FILE *file;
char *filename = "persons.bin";

// Function declaration (to be extend)
PERSON input_record(void); // Reads in a person record

void write_new_file(PERSON *inrecord); //Creates a file and write a first record

void printfile(void); // print out all persons in the file

void search_by_firstname(char *name); // print out person if in list

void append_file(PERSON *inrecord); // appends a new person to the file

void print_menu();

void createPerson(PERSON *ptr_ppost);

void getInput(char *ptr_buffer);

int main(void)
{
    PERSON ppost;
    PERSON *ptr_ppost = &ppost;
    PERSON *ptr_dummy;

    //create a dummy struct
    PERSON dummy = {.firstname = "John", .famnamne = "Doe", .pers_number = "9001019999"};

    //assign the pointer to the address of the dummy
    ptr_dummy = &dummy;

    puts("Hello and welcome! \n");

MENU:
    print_menu();

    //get user input of choice to direct from menu
    getInput(ptr_buffer);
    int choice = atoi(ptr_buffer);

    switch (choice)
    {
    case 1:
        write_new_file(ptr_dummy);
        break;
    case 2:
        ppost = input_record();
        append_file(ptr_ppost);
        break;
    case 3:
        puts("Enter the name you would like to search for:");
        getInput(ptr_buffer);
        search_by_firstname(ptr_buffer);
        break;
    case 4:
        printfile();
        break;
    case 5:
        puts("Goodbye! :)");
        exit(0);
    default:
        puts("Please enter a valid number between 1 - 5.");
    }

    goto MENU;

    return (0);
}

void print_menu()
{
    puts("Please pick one of the options:\n");
    puts("1 Create a new and delete the old file");
    puts("2 Add a new person to the file");
    puts("3 Search for a person in the file");
    puts("4 Print out all in the file");
    puts("5 Exit the program.\n");
}

void getInput(char *ptr_buffer)
{
    //get input
    fgets(ptr_buffer, MAX, stdin);

    //remove enter of input
    ptr_buffer[strlen(ptr_buffer) - 1] = '\0';
}

PERSON input_record(void)
{
    PERSON myperson;

    //get user input
    puts("Please enter the firstname of the new person:");
    getInput(myperson.firstname);

    //get user input
    puts("Please enter the family name of the new person:");
    getInput(myperson.famnamne);

    //get user input
    puts("Please enter the personnumber of the new person:");
    getInput(myperson.pers_number);

    return myperson;
};

void write_new_file(PERSON *inrecord)
{
    //Solution from the book: An Introduction to C Programming for Java Programmers by Mark Handley

    /* open the file for writing. w+ means create a empty file for writing to multiple values */
    file = fopen(filename, "w+");

    if (file == NULL)
    {
        fprintf(stderr, "File %s could not be opened \n", filename);
        exit(1);
    }

    /* write to the file */
    fprintf(file, "%s %s %s", inrecord->firstname, inrecord->famnamne, inrecord->pers_number);

    /* close the file */
    fclose(file);
};

void printfile(void)
{
    //Solution from the book: An Introduction to C Programming for Java Programmers by Mark Handley

    /* open the file for writing. R means opening the file for reading. The file must exist*/
    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File %s could not be opened \n", filename);
        exit(1);
    }
    /* loop while reading a line at a time from the file and printing */
    while (1)
    {
        char c = fgetc(file);
        /* if it’s the end of file, break out of this loop */
        if (feof(file))
            break;
        printf("%c", c);
    }
    //end print with a new line
    printf("\n");

    /* close the file */
    fclose(file);
};

void search_by_firstname(char *name)
{
CHOICE:
    puts("Enter 1 if you search for firstname, alt. 2 is you seach for familyname:");

    char choice[MAX];
    char *ptr_choice = choice;
    getInput(ptr_choice);

    printf("Choice is: %s \n", choice);

    int find_result = 0;
    char temp[1024];
    //char name[100]; //Creating a shar array to store the name
    char tempName[1024];

    int lenghtOfInputName = strlen(name); //Remove a digit for /n

    //gcc users
    if ((file = fopen(filename, "r")) == NULL)
    {
        puts("Could not open the file");
        return -1;
    }
    else
    {

        //Read the entire file until the last line which is NULL
        while (fgets(temp, 1024, file) != NULL) //Gets one line at a time and stores it as temp
        {

            if (ptr_choice[0] == '1')
            {

                int i;
                for (i = 0; i < lenghtOfInputName; i++)
                {
                    tempName[i] = temp[i];
                }

                printf("tempName is %s and length is %d \n", tempName, strlen(tempName));
                printf("name is %s and length is %d \n", name, strlen(name));

                if (strcmp(tempName, name) == 0)
                {
                    printf("Found a %s with info: %s \n", name, temp);
                }
            }
            else if (ptr_choice[0] == '2')
            {

                printf("Temp is %s \n", temp);

                char *token;
                token = strtok(temp, " ");
                printf("Token is %s \n ", token);
                printf("Temp is %s \n", temp[1]);

                int i = strlen(token) + 1;
                printf("I is %d, \n", i);

                /*                 i = 0; */
                for (; i < strlen(temp); i++)
                {

                    /*                     if(temp[i] == " "){

                    } */
                    tempName[i] = temp[i];
                }

                printf("tempName is %s and length is %d \n", tempName, strlen(tempName));
                printf("name is %s and length is %d \n", name, strlen(name));

                if (strcmp(tempName, name) == 0)
                {
                    printf("Found a %s with info: %s \n", name, temp);
                }
            }
            else
            {
                puts("Please give correct input");
                if (file)
                {
                    fclose(file);
                }
                goto CHOICE;
            }
        }

        //printf("Printing temp:   %s \n", temp);
        /* 
            char *foundName = strtok(temp, " ");
            // loop through the string to extract all other tokens
            int i = 0;
            //1 for first name
            //2 for last name

            //for(; i < 1; i++){
            //foundName = strtok(NULL, " ");
            //}

            //comparing the name with the input
            if ((strstr(foundName, name) != NULL))
            { //Compares "haystack" and "needle"
                printf("Found the searched name:   %s \n", temp);
                find_result++;
            }

            foundName = strtok(NULL, " "); */
    }

    //Visual Studio users on Windows
    //if((fopen_s(&file, fname, "r")) != NULL) {
    //	return(-1);
    //}

    //Close the file if still open.
    if (file)
    {
        fclose(file);
    }
    //return(0);
};

void append_file(PERSON *inrecord)
{

    /* open the file for writing. a for append */
    file = fopen(filename, "a");

    if (file == NULL)
    {
        fprintf(stderr, "File %s could not be opened \n", filename);
        exit(1);
    }

    /* write to the file */
    fprintf(file, "\n%s %s %s", inrecord->firstname, inrecord->famnamne, inrecord->pers_number);
    /* close the file */
    fclose(file);
};