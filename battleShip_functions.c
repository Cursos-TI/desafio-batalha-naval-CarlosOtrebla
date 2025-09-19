#include "battleShip.h"

// Definindo o nome das colunas

char nameColumn[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

// Definindo os tipos de navios

int aircraftCarrier[5];
int battleship[4];
int submarine[3];
int cruiser[3];
int destroyer[2];

// ~~~~~~~~~~~~~~~~~~~~funções~~~~~~~~~~~~~~~~~~~~~

// Função para verificar se a posição é válida

int positionIsValid(int row, int column, int board_size)
{
    return (row >= 0 && row < board_size && column >= 0 && column < board_size);
}

// Função para limpar o tabuleiro

void clearBoard(int board[ROW][COLUMN])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            board[i][j] = 0;
        }
    }
}

// Função para verificar se o navio pode ser posicionado

int canPlaceShip(int board[ROW][COLUMN], int ship[][2], int ship_size)
{
    for (int i = 0; i < ship_size; i++)
    {
        int row = ship[i][0];
        int column = ship[i][1];

        // Verifica se a posição é válida
        if (!positionIsValid(row, column, ROW))
        {
            printf("Erro: Posição [%d][%d] está fora do tabuleiro!\n", row, column);
            return 0;
        }

        // Verifica se a posição já está ocupada
        if (board[row][column] != 0)
        {
            printf("Erro: Posição [%d][%d] já está ocupada!\n", row, column);
            return 0;
        }
    }
    return 1; // Pode posicionar
}

// Função para posicionar um navio no tabuleiro

int placeShip(int board[ROW][COLUMN], int ship[][2], int ship_size, int ship_id)
{
    if (canPlaceShip(board, ship, ship_size))
    {
        for (int i = 0; i < ship_size; i++)
        {
            board[ship[i][0]][ship[i][1]] = ship_id;
        }
        printf("Navio %d posicionado com sucesso!\n", ship_id);
        return 1; // Sucesso
    }
    else
    {
        printf("Não foi possível posicionar o navio %d!\n", ship_id);
        return 0; // Falha
    }
}

// Função para imprimir o tabuleiro

void printBoard(int board[ROW][COLUMN])
{
    printf("\n==== TABULEIRO BATALHA NAVAL ====\n");
    printf("\n");

    // Cabeçalho com números das colunas
    printf("    ");
    for (int column = 0; column < COLUMN; column++)
    {
        printf("%c  ", nameColumn[column]);
    }
    printf("\n");

    // Linhas do tabuleiro
    for (int row = 0; row < ROW; row++)
    {
        printf("%2d ", row + 1); // Número da linha
        for (int column = 0; column < COLUMN; column++)
        {
            if (board[row][column] == 0)
            {
                printf(" ~ "); // Água
            }
            else
            {
                printf(" %d ", board[row][column]); // Navio
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função para imprimir as posições de um navio

void printShipPositions(int ship[][2], int ship_size, int ship_id)
{
    printf("Navio %d - Posições: ", ship_id);
    for (int i = 0; i < ship_size; i++)
    {
        printf("[%d][%d]", ship[i][0], ship[i][1]);
        if (i < ship_size - 1)
            printf(", ");
    }
    printf("\n");
}

// Função para verificar se o navio foi atingido

int isShipSunk(int board[ROW][COLUMN], int ship[][2], int ship_size, int ship_id)
{
    for (int i = 0; i < ship_size; i++)
    {
        if (board[ship[i][0]][ship[i][1]] != ship_id)
            return 0;
    }
    return 1;
}

// Função para verificar se o jogo acabou

int isGameOver(int board[ROW][COLUMN])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if (board[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

