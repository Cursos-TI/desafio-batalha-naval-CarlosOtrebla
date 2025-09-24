#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h> // Para abs() nos ataques especiais

// Definindo o tamanho do tabuleiro
#define ROW 10
#define COLUMN 10

// Definindo constantes para ataques
#define HIT 'X'     // Acertou navio
#define MISS 'O'    // Errou (água)
#define UNKNOWN '~' // Posição não atacada

// Definindo cores ANSI
#define RESET_COLOR "\033[0m"
#define BLUE "\033[34m"         // Água (~)
#define RED "\033[31m"          // Navios atingidos (X)
#define GREEN "\033[32m"        // Destroyer (1)
#define YELLOW "\033[33m"       // Cruzador (2)
#define MAGENTA "\033[35m"      // Navio de guerra (3)
#define CYAN "\033[36m"         // Porta-aviões (4)
#define WHITE "\033[37m"        // Erro (Água - O)
#define BOLD "\033[1m"          // Negrito
#define BRIGHT_GREEN "\033[92m" // Acerto no tabuleiro de ataques

// Declaração de variáveis globais
extern char nameColumn[];
extern char attack_board[ROW][COLUMN]; // Tabuleiro de ataques

// FUNÇÕES PRINCIPAIS
int positionIsValid(int row, int column, int board_size);
int canPlaceShip(int board[ROW][COLUMN], int ship[][2], int ship_size);
void printBoard(int board[ROW][COLUMN]);
int placeShip(int board[ROW][COLUMN], int ship[][2], int ship_size, int ship_id);
int positionShipInteractiveNew(int board[ROW][COLUMN], int ship_type,
                               int *positioned_destroyer, int *positioned_cruiser,
                               int *positioned_battleship, int *positioned_aircraft_carrier);

// FUNÇÕES DE ATAQUE
void initializeAttackBoard(char attack_board[ROW][COLUMN]);
void enableColors();
int getValidInteger(const char* prompt, int min, int max);
void clearInputBuffer();
int performAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column);
void printAttackBoard(char attack_board[ROW][COLUMN]);
void printBothBoards(int ship_board[ROW][COLUMN], char attack_board[ROW][COLUMN]);
int attackMenu(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN]);

// FUNÇÕES DE ATAQUES ESPECIAIS
int performConeAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column);
int performOctahedronAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column);
int performCrossAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column);
int performCircleAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column);
int parsePosition(char* input, int* row, int* column);

#endif // BATTLESHIP_H