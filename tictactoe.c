#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int tic[3][3];                      //  The main tic-tac-toe matrix(Logical)
char ttt_m[10];                     //  Display tic-tac-toe matrix(Graphical)
int ph[10];                         //  Safety array
int inc = 0;                        //  inc == increment variable

void intro();
void swiop(int, int);
int check(int);
void printmatr();
char xoro(int);
void clearall();

int main(){

    intro();

    time_t timer;
    srand(time(&timer));
    
    for (int i = 0; i < 3; i++){                            
        for (int j = 0; j < 3; j++){
            tic[i][j] = 2;                         // Assigning all values 2 for easier logical op
        }
    }
    
    for (int i = 0; i < 9; i++){                            
        ttt_m[i] = ' ';                           // Assigning all values ' ' for easier graphical op
    }

    int usc, flag, cc, result;            // cc = computer choice; usc = user choice
    char l;

    for (int i = 0; i < 10; i++){
        ph[i] = 0;
    }

    while (true){

        int n = 1;
        printmatr();                    // Prints graphical tic-tac-toe matrix. Updates with every turn made.
        input:
            printf("Player, enter the location of X:  ");
            scanf("%d", &usc);
            getchar();
            printf("Press to continue.");
            getchar();
        
        for(int i = 0; i < 10; i++){                   // prevents user to type already in use placeholders
            if (usc == ph[i]){
                flag = 0;
                break;
            } else {
                flag = 1;
                continue;
            }
        }

        if (flag == 0){
            printf("Location unavailable. Input another location.\n");
            goto input;
        } else {
            swiop(usc, n);
        }

        if (usc > 9){
            goto input;
        }

        
        ph[inc] = usc;
        inc ++;
        result = check(n);

        if (result == 0){
            printmatr();
            printf("O won!! Better luck next time, Player!");
            getchar();
            printf("Want to play again? Press Y.\n");
            scanf("%c", &l);
            if (l == 'y'){
                clearall();
                continue;
            } else {
                break;
            }
        } else if (result == 1){
            printmatr();
            printf("X won!! Congratulations Player!!");
            getchar();
            printf("Want to play again? Press Y.\n");
            scanf("%c", &l);
            if (l == 'y'){
                clearall();
                continue;
            } else {
                break;
            }
        } else if (result == 5){
            printmatr();
            printf("The match is drawn?! Well fought, Player!");
            getchar();
            printf("Want to play again? Press Y.\n");
            scanf("%c", &l);
            if (l == 'y'){
                clearall();
                continue;
            } else {
                break;
            }
        }

        regen:                                         // computer choice : generates a random number b/w 1 to 9: Then swiop fn. is used to
            cc = (rand() % 9) + 1;                    // convert it into array address.
        
        for(int i = 0; i < 7; i++){                  // prevents computer to use user placeholders
            if (cc == ph[i]){
                goto regen;
            } else {
                continue;
            }
        }
        n = 0;
        swiop(cc, n);
        printf("Computer: Location of O is %d\n", cc);
        ph[inc] = cc;                                     // to prevent user from using computer generated O values, I put the computer generated 
        inc ++;                                          // numbers in the safety array
        result = check(n);

        if (result == 0){
            printmatr();
            printf("O won!! Better luck next time, Player!");
            getchar();
            printf("Want to play again? Press Y.\n");
            scanf("%c", &l);
            if (l == 'y'){
                clearall();
                continue;
            } else {
                break;
            }
        } else if (result == 1){
            printmatr();
            printf("X won!! Congratulations Player!!");
            getchar();
            printf("Want to play again? Press Y.\n");
            scanf("%c", &l);
            if (l == 'y'){
                clearall();
                continue;
            } else {
                break;
            }
        } else if (result == 5){
            printmatr();
            printf("The match is drawn?! Well fought, Player!");
            getchar();
            printf("Want to play again? Press Y.\n");
            scanf("%c", &l);
            if (l == 'y'){
                clearall();
                continue;
            } else {
                break;
            }
        }
    }
    return 0;
}

void intro(){

    printf("\n\n------------TIC-TAC-TOE------------\n            --- --- ---\n\n");

    printf("The game is played as follows:\n\nPlayer takes control of X while the computer takes control of O. Player types in the position of the X\nwhen asked. Follow the below indexing system.\n");

    puts("\n\n|\t1\t|\t2\t|\t3\t|\n-------------------------------------------------\n|\t4\t|\t5\t|\t6\t|\n-------------------------------------------------\n|\t7\t|\t8\t|\t9\t|\n\n\nPress to continue.");
    getchar();

}

void swiop(int c, int n){                       // for converting 1s, 2s, ....., 9s to array addresses using switch statements
    switch(c){
        case 1:
            tic[0][0] = n;
            ttt_m[c - 1] = xoro(n);
            break;

        case 2:
            tic[0][1] = n;
            ttt_m[c - 1] = xoro(n);
            break;

        case 3:
            tic[0][2] = n;
            ttt_m[c - 1] = xoro(n);
            break;

        case 4:
            tic[1][0] = n;
            ttt_m[c - 1] = xoro(n);
            break;

        case 5:
            tic[1][1] = n;
            ttt_m[c - 1] = xoro(n);
            break;

        case 6:
            tic[1][2] = n;
            ttt_m[c - 1] = xoro(n);
            break;
        
        case 7:
            tic[2][0] = n;
            ttt_m[c - 1] = xoro(n);
            break;

        case 8:
            tic[2][1] = n;
            ttt_m[c - 1] = xoro(n);
            break;
        
        case 9:
            tic[2][2] = n;
            ttt_m[c - 1] = xoro(n);
            break;

        default:
            printf("Take a look at the indexing above and type proper input.\n");
            getchar();
            break;
    }
}

int check(int n){

    int count = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){

            if (n == tic[i][j]){             // if x or o exists in this locations, the if statements will be executed

                if ((tic[i][0] == tic[i][1] && tic[i][2] == tic[i][1]) || (tic[0][j] == tic[1][j] && tic[2][j] == tic[1][j])){   // horizontal and vertical check

                    if (n == 1){
                        return 1;
                        break;
                    } else {
                        return 0;
                        break;
                    }
                }

                if (i == 0 && j == 0){                                            // diagonal -- forward slash check
                    if (tic[0][0] == tic[1][1] && tic [1][1] == tic [2][2]){
                        if (n == 1){
                            return 1;
                            break;
                        } else {
                            return 0;
                            break;
                        }
                    }
                }

                if (i == 0 && j == 2){                                            // diagonal -- backward slash check
                    if (tic[0][2] == tic[1][1] && tic [1][1] == tic [2][0]){
                        if (n == 1){
                            return 1;
                            break;
                        } else {
                            return 0;
                            break;
                        }
                    }
                }

            } else {                                                                                        
                continue;
            }
        }
    }

    for (int i = 0; i < 3; i++){               // check for draw match
        for (int j = 0; j < 3; j++){
            if (tic[i][j] != 2){
                count ++;
                continue;
            }
        }
    }
    if (count == 9){
        return 5;
    } else {
        return 6;
    }
}

// return 0 : O win
// return 1 : X win
// return 5 : Draw
// return 6 : Normal flow

void printmatr(){           // To print ttr_m matrix
    printf("\n");

    for (int i = 0; i < 9; i += 3){
        if (i == 6){
            printf("\n|\t%c\t|\t%c\t|\t%c\t|\n", ttt_m[i],ttt_m[i+1],ttt_m[i+2]);
        } else {
        printf("\n|\t%c\t|\t%c\t|\t%c\t|\n-------------------------------------------------", ttt_m[i],ttt_m[i+1],ttt_m[i+2]);
        }
    }
    printf("\n\n");
}

char xoro(int n){           // Helps assigning X or O to the ttr_m matrix
    if (n == 1){
        return 'X';
    } else if (n == 0){
        return 'O';
    }
}

void clearall(){
    for (int i = 0; i < 3; i++){                            
        for (int j = 0; j < 3; j++){
            tic[i][j] = 2;                         // Assigning all values 2 for easier logical op
        }
    }
    
    for (int i = 0; i < 9; i++){                            
        ttt_m[i] = ' ';                           // Assigning all values ' ' for easier logical op
    }

    for (int i = 0; i < 10; i++){
        ph[i] = 0;
    }
    inc = 0;
}
