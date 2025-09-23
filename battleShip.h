#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

// Definindo o tamanho do tabuleiro
#define ROW 10
#define COLUMN 10

// Definindo constantes para ataques
#define HIT 'X'     // Acertou navio
#define MISS 'O'    // Errou (água)
#define SUNK 'S'    // Navio afundado
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

// Definindo os tipos de navios
extern int aircraftCarrier[5];
extern int battleship[4];
extern int cruiser[3];
extern int destroyer[2];

// Declaração das funções
int positionIsValid(int row, int column, int board_size);
int canPlaceShip(int board[ROW][COLUMN], int ship[][2], int ship_size);
void clearBoard(int board[ROW][COLUMN]);
void printBoard(int board[ROW][COLUMN]);
int isShipSunk(int board[ROW][COLUMN], int ship[][2], int ship_size, int ship_id);
int isGameOver(int board[ROW][COLUMN]);
void printShipPositions(int ship[][2], int ship_size, int ship_id);
int placeShip(int board[ROW][COLUMN], int ship[][2], int ship_size, int ship_id);
int positionShipInteractive(int board[ROW][COLUMN], int orientation,
                            int *positioned_destroyer, int *positioned_cruiser,
                            int *positioned_battleship, int *positioned_aircraft_carrier);
int positionShipInteractiveNew(int board[ROW][COLUMN], int ship_type,
                               int *positioned_destroyer, int *positioned_cruiser,
                               int *positioned_battleship, int *positioned_aircraft_carrier);

// Funções de ataque
void initializeAttackBoard(char attack_board[ROW][COLUMN]);
void enableColors(); // Função para habilitar cores no Windows
int performAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column);
void printAttackBoard(char attack_board[ROW][COLUMN]);
void printBothBoards(int ship_board[ROW][COLUMN], char attack_board[ROW][COLUMN]);
int attackInteractive(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN]);

// Função de ataque em cone
int performConeAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int alvo[2]);

#endif // BATTLESHIP_H