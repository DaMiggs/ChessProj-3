#include"chess.h"
void handleShow() {
    int i, j;
    if (rFlag != 1) {//default print of board
        printf("\nBoard:\n");
        if (bFlag == 1)
            printf("\t\t\t\t  %s\n", bName);
        else
            printf("\t\t\t\t  %s\n", "Player 2");
        for (i = 0; i < 8; i++)//file labels...
        printf("%c%c", 'a' + i, i == 7 ? '\n' : '\t');
        for (i = 0; i < 8; i++)//table itself
        for (j = 0; j < 9; j++)
            printf("%d%c", j == 0 ? 8 - i : board[i][j - 1], j == 8 ? '\n' : '\t');
        if (wFlag == 1) 
            printf("\t\t\t\t  %s\n", wName);
        else 
            printf("\t\t\t\t  %s\n", "Player 1");
    } else {//rotated print of board
        printf("\nBoard:\n");
        if (wFlag == 1)
                printf("\t\t\t\t  %s\n", wName);
            else
                printf("\t\t\t\t  %s\n", "Player 1");
        for (i = 7; i >= 0 ; i--)//file labels...
        printf("%c%c", 'a' + i, i == 0 ? '\n' : '\t');
        for (i = 7; i >= 0; i--)//table itself
        for (j = 8; j >= 0; j--)
            printf("%d%c", j == 8 ? 8 - i : board[i][j], j == 0 ? '\n' : '\t');
        if (bFlag == 1)
            printf("\t\t\t\t  %s\n", bName);
        else
            printf("\t\t\t\t  %s\n", "Player 2");
    }
}