#include "tic_tac_toe.h"

int main() {
    // variables to alloc time
    struct timeval init;
    struct timeval final; 
    int **board = newBoard();
    int numberOfPlays = 0, winner = 0, start = false; // if the computer starts first or not
    char answer;
    printf("Quer comecar em primeiro (1) ou em segundo (2)?\n");
    scanf("%c", &answer);
    if (answer == '2') start = true;

    while (numberOfPlays < 9 && !winner) {
        int i, j, turn = numberOfPlays % 2;

        if((turn+start) % 2 != 0) {
            // take initial time
            getTime(&init);
            computerMove(board);
            // take final time and display the difference
            getTime(&final);
            displayTime(init, final);
            winner = checkWinner(board);
        }
        else {
            printf("Sua vez de jogar\n\n");
            printBoard(board);
            printf("\nCoordenadas da proxima jogada\nx - ");
            scanf("%d", &i);
            printf("y - ");
            scanf("%d", &j);

            if (checkCoord(i) || checkCoord(j)) {
                printf("Posicao fora do tabuleiro!\n");
                continue;
            }

            if (board[i-1][j-1] != empty) {
                printf("Posicao ocupada\n");
                continue;
            }
            playerMove(board, player1, i-1, j-1);
            winner = checkWinner(board);
        }
        numberOfPlays++;
    }
    printBoard(board);
    switch (winner) {
        case player1:
            printf("Jogador 1 ganhou\n");
            break;
        case player2:
            printf("Jogador 2 ganhou\n");
            break;
        default:
            printf("Jogo empatado\n");
            break;
    }
    destroyBoard(board);
    return 0;
}

int ** newBoard() {
    int **board = (int **) malloc(sizeof(int) * 3); 
    for (int i=0; i < 3; i++){
        board[i] = (int *) malloc(sizeof(int) * 3);
        for (int j=0; j < 3; j++){
            board[i][j] = empty;
        }
    }
    return board;
}

int checkCoord(int coord) {
    if (coord < 1 || coord > 3) {
        return true;
    }
    return false;
}

void playerMove(int ** board, int player, int i, int j) {
    if (player == player1)
        board[i][j] = player1;
    else 
        board[i][j] = player2;
}

void computerMove(int **board) {
    int x = -1, y = -1;
    int score = -2;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; j++){
            if(board[i][j] == empty) {
                board[i][j] = player2;
                int tempScore = -minimax(board, -2, 2, player1);
                board[i][j] = empty;
                if(tempScore > score) {
                    score = tempScore;
                    x = i;
                    y = j;
                }
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[x][y] = player2;
}

int minimax(int **board, int alpha, int beta, int player) {
    //How is the position like for player (their turn) on board?
    int winner = checkWinner(board);
    if(winner != tie) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    for(int i = 0; i < 3; ++i) {//For all moves,
        for (int j = 0; j < 3; j++) {
            if(board[i][j] == empty) {//If legal,
                board[i][j] = player;//Try the move
                int thisScore = -minimax(board, alpha, beta, player*-1);
                if(thisScore > score) {
                    score = thisScore;
                    move = i;
                }//Pick the one that's worst for the opponent
                board[i][j] = empty;//Reset board after try
                if (score <= alpha) return score;
                if (score < beta)
                    beta = score;
            }
        }
    }
    if(move == -1) return tie;
    return score;
}

int checkWinner(int **board) {
    int result = 0;
    if ((result = checkLines(board))) return result;
    if ((result = checkColumns(board))) return result;
    if ((result = checkDiagonals(board))) return result;
    return tie;
}

int checkLines(int **board){
    for (int i=0; i < 3; i++) {
        int counter = 1, aux = board[i][0];
        for (int j=1; j < 3; j++) {
            if (aux != empty && aux == board[i][j]) counter++;
        }
        if (counter == 3) {
            return aux;
        }
    }
    return false;
}

int checkColumns(int **board) {
    for (int i=0; i < 3; i++) {
        int counter = 1, aux = board[0][i];
        for (int j=1; j < 3; j++) {
            if (aux != empty && aux == board[j][i]) counter++;
        }
        if (counter == 3) {
            return aux;
        }
    }
    return false;
}

int checkDiagonals(int **board) {
    int j = 1;
    int counter = 1, aux = board[0][0];
    for (int i=1; i < 3; i++) {
        if (aux != empty && aux == board[i][j]) counter++;
        if (counter == 3) {
            return aux;
        }
        j++;
    }

    j = 1;
    counter = 1, aux = board[0][2];
    for (int i=1; i < 3; i++) {
        if (aux != empty && aux == board[i][j]) counter++;
        if (counter == 3) {
            return aux;
        }
        j--;
    }

    return false;
}

void printBoard(int **board) {
    printf("  1   2   3  \n");
    printf("1 %c | %c | %c \n", playerChar(board[0][0]), playerChar(board[0][1]), playerChar(board[0][2]));
    printf(" ---+---+---\n");
    printf("2 %c | %c | %c \n", playerChar(board[1][0]), playerChar(board[1][1]), playerChar(board[1][2]));
    printf(" ---+---+---\n");
    printf("3 %c | %c | %c \n", playerChar(board[2][0]), playerChar(board[2][1]), playerChar(board[2][2]));
    printf("\n");
}

char playerChar(int id) {
    switch (id) {
        case player1:
            return 'X';
        case player2:
            return 'O';
        default:
            return ' ';
    }
}

void destroyBoard(int **board) {
    for (int i = 0; i < 3; i++){
        free(board[i]);
    }
    free(board);
}

/*Gets the current time*/
void getTime(struct timeval* time){
    if(gettimeofday(time,NULL)){
        fprintf(stderr, "Error in requesting time\n");
        exit(EXIT_FAILURE);
    }
}

/*Prints the execution time of the program*/
void displayTime(struct timeval init, struct timeval final){
    printf("Play selection completed in %0.6lf seconds.\n", calc_run_time(final, init));
}

/* calculates difference between final and initial time */
double calc_run_time(struct timeval final, struct timeval init)
{
    return final.tv_sec - init.tv_sec+ 0.000001*(final.tv_usec - init.tv_usec);
}