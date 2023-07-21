#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int mainMenu();
void newGame();
int gameMenu(int);
int dice();
int search(int [], int);
bool game(int);
void display();

int snakesHead[] = {17, 54, 62, 64, 87, 93, 95, 98};
int snakesTail[] = {7, 34, 19, 60, 36, 73, 75, 79};
int ladderStart[] = {1, 4, 9, 21, 28, 51, 72, 80};
int ladderEnd[] = {38, 14, 31, 42, 84, 67, 91, 99};
int playerOnePos = 0, playerTwoPos = 0;

int main(){
    int choice, code, player;
    while(true){
        choice = mainMenu();
        if(choice == 1){
            player = 1;
            newGame();
            while(true){
                code = game(player);
                if(!code){
                    printf("\nExiting the current game. . .");
                    break;
                }
                printf("\n\nCurrent Position :");
                display();
                if(player == 1) player++;
                else player--;
                if(playerOnePos == 100) {
                    printf("\n\n\t\t\tPlayer 1 WON!");
                    break;
                }
                if(playerTwoPos == 100){
                    printf("\n\n\t\t\tPlayer 2 WON!");
                    break;
                }
            }
        }
        else if(choice == 2){
            printf("\n\n\t\t\tThanks for Playing. . .");
            break;
        }
        else{
            printf("\n\n\t\t\tInvalid Choice!");
        }
    }
    return 0;
}

// Displaying the MAIN MENU and taking choice.
int mainMenu(){
    printf("\n\n\t\t\tMENU");
    printf("\n\t\t\t-----------");
    printf("\n\t\t\t1. New Game");
    printf("\n\t\t\t2. Exit");
    printf("\nEnter your choice : ");
    int ch;
    scanf("%d", &ch);
    return ch;
}

// Resetting the player values.
void newGame(){
    playerOnePos = playerTwoPos = 0;
}

// Displaying the Game Menu and taking the choice.
int gameMenu(int player){
    printf("\n\n\t\t\tGame Menu [Player : %d]", player);
    printf("\n\t\t\t----------------------");
    printf("\n\t\t\t1. Roll Dice");
    printf("\n\t\t\t2. Exit");
    printf("\nEnter your choice : ");
    int ch;
    scanf("%d", &ch);
    return ch;
}

// Function to return random number between 1 and 6.
int dice(){
    srand(time(0));
    int lowerBound = 1;
    int upperBound = 6;

    int val = rand() % upperBound + 1;
    return val;
}

// Function to search for the key.
int search(int arr[], int key){
    int len = 8; // For both ladders and snakes array size is 8.
    int l = 0;
    int h = len-1;

    while(l <= h){
        int mid = (l+h)/2;

        if(arr[mid] == key){
            return mid;
        }
        else if(arr[mid] > key){
            h = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    
    return -1;
}

// Function to run the Game.
bool game(int player){
    int ch = gameMenu(player);
    if(ch == 1){
        int val = dice();
        printf("\nYou got %d", val);

        int playerPos;
        if(player == 1){
            if(playerOnePos + val > 100) return true;
            playerOnePos += val;
            playerPos = playerOnePos;
        }
        else{
            if(playerTwoPos + val > 100) return true;
            playerTwoPos += val;
            playerPos = playerTwoPos;
        }

        // Checking if the current position has Snake.
        int check = search(snakesHead, playerPos);
        if(check != -1){
            if(player == 1){
                playerOnePos = snakesTail[check];
                printf("\n\n# [A snake was there you came down from %d to %d]", playerPos, playerOnePos);
            }
            else{
                playerTwoPos = snakesTail[check];
                printf("\n\n# [A snake was there you came down from %d to %d]", playerPos, playerTwoPos);
            }
            return true;
        }

        // Checking if the current position has Ladder.
        check = search(ladderStart, playerPos);
        if(check != -1){
            if(player == 1){
                playerOnePos = ladderEnd[check];
                printf("\n\n# [A ladder was there you came up from %d to %d]", playerPos, playerOnePos);
            }
            else{
                playerTwoPos = ladderEnd[check];
                printf("\n\n# [A ladder was there you came up from %d to %d]", playerPos, playerTwoPos);
            }
            return true;
        }

        return true;
    }
    else if(ch == 2){
        return false;
    }
    else{
        printf("\n\n\t\t\tInvalid Choice! Try Again!");
        return game(player);
    }
}

// Function to display the Snake and Ladder Board.
void display(){
    int count = 0;
    printf("\n\n[\t");
    for(int i=100; i>=1; i--){
        if(count%10 == 0 && count != 0){
            printf("]\n[\t");
        }
        if(playerOnePos == playerTwoPos && playerOnePos == i){
            printf("[#]\t");
        }
        else if(i == playerOnePos){
            printf("[X]\t");
        }
        else if(i == playerTwoPos){
            printf("[O]\t");
        }
        else{
            printf("%d\t", (i));
        }
        count++;
    }
    printf("]\n");
    printf("\nX : First Player, O : Second Player, # : Both at same place.");
    printf("\n\n1st Player Position : %d, 2nd Player Position : %d", playerOnePos, playerTwoPos);
}