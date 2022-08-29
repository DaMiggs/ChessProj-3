#include "chess.h"
square board[8][8];
int turn;
char* wName;
char* bName; 
int wFlag = 0;
int bFlag = 0;
int rFlag = 0;
int iFlag = 0;


typedef struct {
    char* src;
    char* trg;
}moveSet, iSet;

void impMv(moveSet iSet) {
    
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;
    
    sourceFile = iSet.src[0];//source = "a5", sourceFile = 'a'
    targetFile = iSet.trg[0];
    sourceRank = iSet.src[1] - '0';//source = "a5", sourceRank = 5
    targetRank = iSet.trg[1] - '0';
    //board[sourceI][sourceJ]: source square...
    //board[targetI][targetJ]: target square...
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
        printf("Invalid mv arguments\n");
        
    }
    //checking the turn first
    if ((int)(board[sourceI][sourceJ] * turn) < 0) {
        printf("Turn violation, it's %s to move\n", turn == WHITE ? "white" : "black");
        
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] != EMPTY) {
        printf("Invalid move: either source square is empty or target square is not empty\n");
        
    }
    if (!isLegalMove(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess move\n");
        
    }
    //end of error checking....

    board[targetI][targetJ] = board[sourceI][sourceJ];
    board[sourceI][sourceJ] = EMPTY;
    turn *= -1;//WHITE --> BLACK and BLACK --> WHITE
}

void impCp(moveSet iSet) {
    
    int sourceFile, sourceRank, targetFile, targetRank, sourceI, sourceJ, targetI, targetJ;

    sourceFile = iSet.src[0];
    targetFile = iSet.trg[0];
    sourceRank = iSet.src[1] - '0';
    targetRank = iSet.trg[1] - '0';
    sourceI = 8 - sourceRank;
    sourceJ = sourceFile - 'a';
    targetI = 8 - targetRank;
    targetJ = targetFile - 'a';
    
    if (sourceI < 0 || sourceJ < 0 || targetI < 0 || targetJ < 0
        || sourceI > 7 || sourceJ > 7 || targetI > 7 || targetJ > 7) {
            printf("invalid cp arguments\n");
        }
    //checking the turn first
    if ((int)(board[sourceI][sourceJ] * turn) < 0) {
        printf("Turn violation, it's %s to move\n", turn == WHITE ? "WHITE" : "BLACK");
    }
    if ((int)board[sourceI][sourceJ] * (int)board[targetI][targetJ] > 0) {
        printf("Violation, %s cannot capture its own piece.\n", turn == WHITE ? "WHITE" : "BLACK",board[sourceI][sourceJ], board[targetI][targetJ]);
    }
    if (board[sourceI][sourceJ] == EMPTY || board[targetI][targetJ] == EMPTY) {
        printf("Invalid capture: either source square is empty or target square is empty\n");
    }
    if (!isLegalCapture(sourceI, sourceJ, targetI, targetJ)) {
        printf("Illegal chess capture\n");
    }
    //end of error checking....
    board[targetI][targetJ] = board[sourceI][sourceJ];
    board[sourceI][sourceJ] = 0;
    turn *= -1;
}

static void resetBoard() {
    turn = WHITE;//WHITE moves first
    int i, j;
    for (i = 2; i < 6;i++)
        for (j = 0;j < 8;j++)
            board[i][j] = EMPTY;
    for (j = 0;j < 8;j++) {
        board[1][j] = BLACK * PAWN;
        board[6][j] = WHITE * PAWN;
    }
    board[0][0] = board[0][7] = BLACK * ROOK;
    board[7][0] = board[7][7] = WHITE * ROOK;
    board[0][1] = board[0][6] = BLACK * KNIGHT;
    board[7][1] = board[7][6] = WHITE * KNIGHT;
    board[0][2] = board[0][5] = BLACK * BISHOP;
    board[7][2] = board[7][5] = WHITE * BISHOP;
    board[0][3] = BLACK * QUEEN;
    board[7][3] = WHITE * QUEEN;
    board[0][4] = BLACK * KING;
    board[7][4] = WHITE * KING;
}
char getCommandWord(char command[], int maxLength) {
    char lastCharacter;//either space or new line
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++);//skip leading white spaces
    if (lastCharacter == '\n') {
        command[0] = '\0';
        return lastCharacter;
    }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}

/* typedef struct {
    char* src;
    char* trg;
}moveSet; */

moveSet iMove(char* tok){
    char *token = tok;
    moveSet t;
    char *sr = (char*)malloc(3);
    char *tr = (char*)malloc(3);
    sr[0] = token[0], sr[1] = token[1], sr[2] = '\0';
    if (token[2]=='x')
        tr[0] =token[3], tr[1] = token[4], tr[2] = '\0';
    else { 
        tr[0] = token[2], tr[1] = token[3], tr[2] = '\0';
    }
    t.src = sr, t.trg = tr;
    return t;
}

int main(int argc, char *argv[]) {
    
    /*
    * You can access all the command-line arguments here
    * argv[1], argv[2], ...
    * Example of import option: -i d2d4,d7d5,e2e4,d5xe4,Ng1h3,Ke8d7,Qd1d3
    * which is equivalent to a new game started this way:
    * mv d2 d4
    * mv d7 d5
    * mv e2 e4
    * cp d5 e4
    * mv g1 h3
    * mv e8 d7
    * mv d1 d3
    */
    
    wName = (char*)malloc(sizeof(char));
    bName = (char*)malloc(sizeof(char));

  //This is a test to understand argv string locations :D
  
    for (int i = 0; i < argc; i++){
        if (strcmp("-w", argv[i])==0) {
            wFlag = 1;            
            strcat(wName, argv[++i]);            
        }
        if (strcmp("-b", argv[i])==0) {
            bFlag = 1;            
            strcat(bName, argv[++i]);            
        }
        if (strcmp("-r", argv[i])==0) {
            rFlag = 1;
        }
        if (strcmp("-i", argv[i])==0) {
            iFlag = 1;
            resetBoard();
            char *moveList = argv[++i], *token = strtok(moveList, " , ");
            moveSet turnMove;
    
            while (token!=NULL) {
                // printf("First: %c %c\n",token[1], token[1]+1);
                
                if (token[0] == 'N'|| token[0] == 'R'|| token[0] == 'Q'|| token[0] == 'K') {
                    turnMove = iMove(token+1);
                    if (token[3]=='x') {
                        impCp(turnMove);
                    } else {
                        // printf("%s to %s\n", turnMove.src, turnMove.trg);
                        impMv(turnMove);
                    }
                }
                 else {
                    if (token[2]=='x') {
                        turnMove = iMove(token);
                        impCp(turnMove);
                    } else {
                        turnMove = iMove(token);
                        // printf("%s to %s\n", turnMove.src, turnMove.trg);
                        impMv(turnMove);
                    }
                }
                token = strtok(NULL,",");
            }
        }
    }
        //printf("argv[%d]:%s\n", i, argv[i]);
    //for (int i = 0; i < strlen(argv); i++)
        //printf("argv[1][%d]:%c\n", i, argv[1][i]);

//broken for loop ignores "-w"
    /* for (int i = 0; i < argc; i++) {
        //printf("argv[%d]:%s\ncmp=%d\n", i, argv[i], strcmp(argv[i], "-w"));
        if (strcmp("-w", argv[i])==0) {
            wFlag = 1;
            i++;
            strcat(wName, argv[i]);
            printf("%s\n", wName);
        }
        //does itterating through a for loop less save memory?
        i++;
    } */
    
    
    
    char command[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;
    if(iFlag != 1)
        resetBoard();
    //printf("%s ", wName);
    printf("Start the game using a mv command! Valid commands are quit, show, mv and cp.\n");
    while (1) {//infinite while loop...
        printf(">>");
        lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        if (strcmp(command, "quit") == 0)//if command === "quit"
            break;
        else if (!strcmp(command, "mv"))//if command == "mv"
        {
            if (lastCharacter == '\n')//mv\n
                printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
            else
                handleMove();
        }
        else if (!strcmp(command, "cp"))//if command == "cp"
        {
            if (lastCharacter == '\n')//cp\n
                printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
            else
                handleCapture();
        }
        else if (!strcmp(command, "show"))//if command == "show"
        {
            if (lastCharacter != '\n') {//show x\n
                printf("Too many arguments for show command! It must be in the form of show.\n");
                while (getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the ramainder of the invalid show command...	
            }
            else
                handleShow();
        }
        else {
            printf("invalid command! Your command must start either with quit, show, mv or cp.\n");
            while (lastCharacter != '\n')//skip the remainder of my invalid command...
                lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        }
    }
}
