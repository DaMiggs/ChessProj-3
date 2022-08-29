#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAX_COMMAND_TOKEN_LENGTH 6
#define WHITE 1
#define BLACK -1
typedef enum {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
}square;

typedef enum {
    NONE = 0,
    WHITE_SHORT = 1,
    WHITE_LONG = 2,
    BLACK_SHORT = 4,
    BLACK_LONG = 8
}castle;

extern square board[8][8];
extern int turn;
extern char* wName;
extern char* bName;
extern int wFlag;
extern int bFlag;
extern int rFlag;
extern int iFlag;

char getCommandWord(char command[], int maxLength);
void handleShow();
void handleCapture();
void handleMove();
int isLegalMove(int srcI, int srcJ, int trgI, int trgJ);
int isLegalCapture(int srcI, int srcJ, int trgI, int trgJ);