#ifndef __TIC_TAC_TOE__THREADS__
#define __TIC__TAC__TOE__THREADS__

#include "tic_tac_toe.h"
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m_lock;
int score, x, y;

#define SIZE    3
#define AREA    SIZE*SIZE

typedef struct _move_args
{
    int** board;
    int x, y;
} *move_args;

void copyBoard(int **oldBoard, int**newBoard);
void checkMove(move_args args);

void initialize_lock();
void destroy_lock();
void lock_commands();
void unlock_commands();

#endif /* __TIC__TAC__TOE__THREADS__ */