
#include <stdio.h>
#include <stdlib.h>

#define FNAME "Lab5integers.txt"
#define FOR_READ "r"

//global variable
int INPUTSIZE = 0;

void decToBinary(int ra[32], int decNum); // function prototype

void printNames(char *arr[], int size); //function prototype

void dice_game(char *arr[], int size); // function prototype



int main()
{
    //seeding random value
    srand(time(NULL));
    //declares a file pointer
    FILE *inputfile;
    //declares a int pointer (int array)
    int *array;
    //array of int with size of 32 to store int converted to 32 bit binary
    int binArr[32];

    //array of strings,
    char *names[15] = {"Alfred", "Ben", "Catherine", "Dana", "Ether", "Frank", "Gab", "Harry", "Ian", "Johnny", "Kerry", "Leo", "Mike", "Nathan", "Olivia"} ;


    //if statement, checks whether the opened file is empty(NULL)
    if ((inputfile = fopen(FNAME, FOR_READ)) == NULL)
    {
        //if file opening is unsuccessful, program prompts and error and then ends
        printf("Unable to open input file.\n");
        return 1;
    }

    printf("Memory was successfully allocated.\n");

    //file scan takes the first integer from the file and assigns the value to the global variable INPUTSIZE
    fscanf(inputfile, "%d", &INPUTSIZE);



    //utilize Dynamic Memory Allocation to set the size of the array
    array = (int*) malloc(INPUTSIZE * sizeof (int));

    //for loop runs fscanf, until I reaches the size of the array, uses pointer arithmetic
    //to store the scanned integers into the array
    for(int i = 0; i < INPUTSIZE; i++)
    {
        //scans integer from the inputed file
        fscanf(inputfile, "%d", array + i);

        //invokes the function to turn the integer into binary
        decToBinary(binArr, *(array + i));

        //use format specifiers to print labels
        printf("%s: %10d |%5s: %s%08X| %5s: ", "DEC", *(array + i), "HEX", "0x", *(array + i), "BIN");

        //nested for loop prints the binary number that is stored in the arr binArr
        for(int i = 31; i >= 0; i--)
        {
            //uses pointer arithmetic to print the contents of the array
            printf("%d", *(binArr + i));

        }

        //stand alone new line character to print new line after for loop ends
        printf("\n");

    }

    //close file
    fclose(inputfile);

    //free the dynamically allocated memory
    free(array);


    //END PART 1
    //START PART 2

    printf("\nName List\n------------\n");

    printNames(names, 15);

    //END PART 2
    //START PART 3

    printf("\n\nDice Games Results:\n------------\n\n");
    dice_game(names,15);

    //END PART 3

    //elegantly end program
    return 0;

}//end main

//FUNCTIONS

//function used to turn integer into a binary number
void decToBinary(int arr[32], int decNum)
{
    //counter variable
    int i = 0;

    //remainder value to hold the stripped digit
    //for 1's compliment, will flip the remainder to 1 if its 0 and vice versa
    int remainder;

    //argNum is set as a place holder for the read integer, to identify if the number is positive or negative
    int argNum = decNum;


    //if the argument num is greater than or equal to zero
    if(argNum >= 0)
    {
        while(i < 32)
        {
            //value of the place where the pointer points is equal to the remainder of decNum modulo 2;
            *(arr + i) = decNum % 2;

            //decNum is equal to itself divided by 2
            decNum /= 2;

            //i increments
            i++;
        }


    }
    //else, the number is negative
    else
    {
        while(i < 32)
        {
            //remainder equals decNum modulo 2;
            remainder = decNum % 2;

            //in accordance with 1's compliment, 1's and 0's are flipped
            //if remainder is 0, the array stores a 1
            if(remainder == 0)
            {
                *(arr + i) = 1;
            }
            //else the array stores a 0
            else
            {
                *(arr + i) = 0;
            }
            //decNum is equal to itself divided by 2
            decNum /= 2;

            //i increments
            i++;
        }

    }

}//end decToBinary

//function to print out the names in the array of string
void printNames(char *arr[], int size)
{
    //for loop runs until it reaches the size of the array
    for(int i = 0; i < size; i++)
    {
        //prints the names utilizing pointer arithmetic
        printf("%20s", *(arr + i));

        //after the fourth name has been printed, the program will print a new line
        if((i + 1) % 4 == 0)
        {
            printf("\n");
        }
    }
}//end printNames

//function for the dice game
void dice_game(char *arr[], int size)
{
    //variables to hold random integers
    int ran1;
    int ran2;

    //array of integers set to the size of the amount of players
    int scores[size];

    //variable lowest used to store the lowest score
    int lowest;

    //counter will be used to count the number of winners
    int counter = 0;


    //for loop, runs for the size of the names(size of players) and generates 2 random numbers
    for(int i = 0; i < size; i++)
    {
        ran1 = rand() % 10 + 1;
        ran2 = rand() % 10 + 1;

        //prints the player's name, their 2 dice roll values and the absolute value difference of the dice roll
        printf("%-10s%5s:%3d,%5s:%3d,%15s%3d\n", *(arr + i), "die1", ran1, "die2", ran2, "difference is:" ,abs(ran1 - ran2));

        //stores the difference of the rolls into the array scores
        *(scores + i) = abs(ran1 - ran2);

    }

    //set the lowest value to the first score
    lowest = *scores;

    //finds the lowest value in the array of scores
    for(int i = 0; i < size; i++)
    {
        //if the score in that index of the array is lower than the value in lowest, the value
        //in that index is set to the lowest value
        if(*(scores + i) < lowest)
        {
            lowest = *(scores + i);

        }
    }

    //finds how many times the lowest number occurs in the array of scores
    //this determines if there was more than one person with that score(a tie) or if only one person won
    for(int i = 0; i < size; i++)
    {
        //if the score in the array equals the lowest score, the counter increments
        if(*(scores + i) == lowest)
        {
            counter++;

        }
    }



    //if counter increased past 1, there was more than one winner, prompts the tie game
    if(counter  > 1)
    {
        printf("\n\nTie game!... and the winners are...\n");
        //for loop used to identify is the value in the array of scores is equal to the lowest score
        for(int i = 0; i < size; i++)
        {
            //since the order that the scores were taken matches the names, where the lowest score is present at the index of scores
            //we can return the name in the similar index of the name array
            if(*(scores + i) == lowest)
            {
                printf("%s\n", *(arr + i));
            }

        }

    }
    //else there was only one winner, prompts for a single winner using same for loop as above
    else
    {
        //since the counter was not greater than 1, only one player will be found in the loop
        //and they will be prompted as the winner
        for(int i = 0; i < size; i++)
        {
            if(*(scores + i) == lowest)
            {
                printf("\n\nand the winner is...%s\n", *(arr + i));
            }
        }
    }
}//end dice_game

//end program
