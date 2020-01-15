#ifndef __TIC_TAC_TOE__
#define __TIC__TAC__TOE__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

enum playerId { player1 = -1, player2 = 1, tie = 0 };
enum boolean { false = 0, true = 1 };

#define empty 0

int ** newBoard();
int checkCoord(int coord);
void playerMove(int ** board, int player, int i, int j);
void computerMove(int **board);
int minimax(int **board, int alpha, int beta, int player);
int checkWinner(int **board);
int checkLines(int **board);
int checkColumns(int **board);
int checkDiagonals(int **board);
void printBoard(int **board);
char playerChar(int id);
void destroyBoard(int **board);
void getTime(struct timeval* time);
void displayTime(struct timeval init, struct timeval final);
double calc_run_time(struct timeval final, struct timeval init);

#endif /* __TIC_TAC_TOE__ */