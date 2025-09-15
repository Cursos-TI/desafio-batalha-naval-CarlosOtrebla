#include <stdio.h>

#define SIZE 12

void printBoard(int board[SIZE][SIZE])
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int column = 0; column < SIZE; column++)
        {
            printf("%d ", board[row][column]);
        }
        printf(" \n");
    }
};

int main()
{
    // Definindo o tabuleiro
    int board[SIZE][SIZE] = {0};

    // Posição do navio 1
    int ship_1[3][2] = {{0, 2}, {1, 2}, {2, 2}};

    // Posição do navio 2
    int ship_2[3][2] = {{8, 3}, {8, 4}, {8, 5}};

    // Posição do navio 3
    int ship_3[3][2] = {{3, 5}, {4, 6}, {5, 7}};

    // Posicionando os navios
    for (int i = 0; i < 3; i++)
    {
        board[ship_1[i][0]][ship_1[i][1]] = 3;
        board[ship_2[i][0]][ship_2[i][1]] = 3;
        board[ship_3[i][0]][ship_3[i][1]] = 3;
    }

   

    printBoard(board);

    return 0;
}
