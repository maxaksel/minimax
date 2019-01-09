/**********************************************************************************
* A simple implementation of the minimax algorithm for solving Tic Tac Toe        *
* For detailed information, please see the readme.md file                         *
***********************************************************************************/
#include <stdio.h>

#define PLAYER -1 // human squares are represented with a -1
#define AI      1 // computer squares are represented with a 1
#define EMPTY   0 // empty squares are represented with a 0
#define INF     2 // for the purposes of this program, since we are not dealing
                  // with numbers with an absolute value over 1

#define min(a, b) ((a > b) ? b : a) // useful macros for determining the minimum
#define max(a, b) ((a > b) ? a : b) // and maximum of two numbers

typedef struct {
  int move;
  int payoff;
} strategy; // a useful struct for packaging a move and its payoff

/* Evaluates a given Tic Tac Toe board
 * Parameter: nine-element array representing a tic tac toe board
 * Returns: 1 represents a computer win, -1 a human win, and 0 a draw or no winner */
int evaluate(int board[9]) {
  // Check columns
  for (int i = 0; i < 3; i++) {
    if (board[i] == board[i + 3] && board[i] == board[i + 6]) return board[i];
  }
  // Check rows
  for (int i = 0; i <=6; i += 3) {
    if (board[i] == board[i + 1] && board[i] == board[i + 2]) return board[i];
  }
  // Check diagonals
  if (board[0] == board[4] && board[0] == board[8]) return board[0];
  if (board[2] == board[4] && board[2] == board[6]) return board[2];

  return 0;
}

/* Analyzes a tic tac toe board and chooses the best move for whoseTurn */
strategy minimax(int board[9], int whoseTurn, int numBlanks) {
  // Our recursive base cases
  int evaluation = evaluate(board);
  if (evaluation != 0) {
    strategy result = {-1, evaluation}; // -1 for the move, since we can't move
    return result;
  }
  if (numBlanks == 0) {
    strategy result = {-1, 0}; // again, -1 for the move because we can't move
    return result;
  }

  // Recursive portion of the minimax algorithm
  int bestMove = -1;
  int bestVal = (whoseTurn == AI) ? -INF : INF;
  for (int i = 0; i < 9; i++) {
    if (board[i] == EMPTY) {
      // Searching through all branches
      board[i] = whoseTurn; // whoseTurn moves
      int branchVal = minimax(board, -whoseTurn, numBlanks - 1).payoff; // 1 and -1 were conveniently chosen
      if (whoseTurn == AI) {
        bestVal = max(branchVal, bestVal); // the computer is the maximizer
      } else {
        bestVal = min(branchVal, bestVal); // the human is the minimizer
      }
      board[i] = EMPTY; // reset the board

      if (bestVal == branchVal) {
        bestMove = i; // keep track of what move yielded the best payoff for whoseTurn
      }
    }
  }
  strategy result = {bestMove, bestVal}; // return the best move and payoff associated with it
  return result;
}

/* Returns a symbol given an integer representation */
char getSymbol(int r) {
  switch (r) {
    case PLAYER:
      return 'X';
    case AI:
      return 'O';
    case EMPTY:
      return ' ';
  }
  return '?';
}

/* Prints the Tic Tac Toe board */
void printBoard(int board[9]) {
  printf("\n");
  printf(" %c | %c | %c \n", getSymbol(board[0]), getSymbol(board[1]), getSymbol(board[2]));
  printf("-----------\n");
  printf(" %c | %c | %c \n", getSymbol(board[3]), getSymbol(board[4]), getSymbol(board[5]));
  printf("-----------\n");
  printf(" %c | %c | %c \n", getSymbol(board[6]), getSymbol(board[7]), getSymbol(board[8]));
  printf("\n");
}

/* Gets and sanitizes player input */
void getPlayerMove(int board[9]) {
  int move;
  printf("Where would you like to move? (1 - 9) ");
  scanf("%d", &move);
  printf("\n");
  while (board[move - 1] != EMPTY || move < 1 || move > 9) {
    printf("Invalid. ");
    scanf("%d", &move);
    printf("\n");
  }
  board[move - 1] = PLAYER;
}

int main() {
  int board[9] = {0}; // initialize board
  int firstMover;
  int numBlanks = 9;

  printf("Welcome to Tic Tac Toe\n");
  printf("\twith the minimax algorithm!\n");
  printf("Human: X\n");
  printf("Machine: O\n");
  printf("-----------------------------------\n");
  do {
    printf("Would you like to go first or second? [1 / 2] ");
    scanf("%d", &firstMover);
  } while (firstMover != 1 && firstMover != 2);
  firstMover %= 2; // firstMover is 1 if going first, 0 otherwise

  for (int i = 0; i < 9; i++) {
    if ((firstMover + i) % 2) {
      printBoard(board);
      getPlayerMove(board);
    } else {
      int aiMove = minimax(board, AI, numBlanks).move;
      board[aiMove] = AI;
    }

    if (evaluate(board) != 0) { // check to see if anyone won
      printBoard(board); // so we can see the final state of the game
      if (evaluate(board) == AI) {
        printf("Ha! I win.\n");
      } else {
        printf("You win.\n"); // this should never happen!
      }
      return 0;
    }
    numBlanks--;
  }
  printBoard(board);
  printf("Draw.\n");
  return 0;
}
