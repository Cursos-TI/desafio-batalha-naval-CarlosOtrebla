#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

// Definindo o tamanho do tabuleiro
#define ROW 10
#define COLUMN 10

// Declaração de variáveis globais
extern char nameColumn[];

// Definindo os tipos de navios
extern int aircraftCarrier[5];
extern int battleship[4];
extern int cruiser[3];
extern int submarine[3];
extern int destroyer[2];

// Declaração das funções
int positionIsValid(int row, int column, int board_size);
void clearBoard(int board[ROW][COLUMN]);
int canPlaceShip(int board[ROW][COLUMN], int ship[][2], int ship_size);
int placeShip(int board[ROW][COLUMN], int ship[][2], int ship_size, int ship_id);
void printBoard(int board[ROW][COLUMN]);
void printShipPositions(int ship[][2], int ship_size, int ship_id);

#endif // BATTLESHIP_H