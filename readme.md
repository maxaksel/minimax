# Tic Tac Toe Minimax Implementation in C

This program demonstrates the application of the minimax algorithm to solve tic tac toe. The minimax algorithm is a recursive algorithm that allows one to calculate the payoff of a two-person, non-cooperative game. Minimax is useful for games ranging from Tic Tac Toe to chess, but becomes very unwieldy for large games because it recursively explores every possible move made by each of the players. There are computational speedups to the minimax algorithm (for example, alpha-beta pruning) and many games have symmetries that can be exploited to reduce computational time. The goal of this program, however, is to simply provide a straightforward and simple introduction to the minimax algorithm. Additionally, for a simple game such as tic tac toe, computation speedups will be unnecessary.

The entire program resides in "`main.c`." To compile and run, either run the bash script (`./run.sh`) or compile with `gcc -o main main.c` and run `./main`.
