#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

// Definindo o tamanho do tabuleiro
#define ROW 10
#define COLUMN 10
// Definindo o nome das colunas
char nameColumn[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

// Definindo os tipos de navios
int aircraftCarrier[5];
int battleship[4];
int cruiser[3];
int submarine[3];
int destroyer[2];

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
int ship_1[3][2] = {{0, 2}, {11, 2}, {2, 2}};
int ship_2[3][2] = {{8, 3}, {8, 4}, {8, 5}};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main()
{
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Definindo o tabuleiro sem navios
    int board[ROW][COLUMN] = {0};
    int option;
    int optionPosition;

    do
    {
        printBoard(board);

        printf("Escolha uma opção:\n");
        printf("1 - Posicionar navio 1\n");
        printf("0 - Sair\n");
        scanf("%d", &option);

        switch (option)
        {
        case 1: // Posicionar navios
        {
            do
            {
                printf("Escolha o tipo de posicionamento:\n");
                printf("1 - Vertical\n");
                printf("2 - Horizontal\n");
                printf("3 - Diagonal Crescente\n");
                printf("3 - Diagonal Antecrescente\n");
                printf("0 - Menu Principal\n");
                scanf("%d", &optionPosition);
                switch (optionPosition)
                {
                case 1:
                {

                    int row;
                    int column;
                    printf("Digite as coordenadas do navio:\n");
                    printf("Linha: ");
                    scanf("%d", &row);
                    printf("Coluna: ");
                    scanf("%d", &column);
                    placeShip(board, ship_2, 4, 1);

                    break;
                }

                case 2:
                    break;

                default:
                    break;
                }
            } while (optionPosition != 0);

            break;
        }

        default:
            break;
        }

    } while (option != 0);

    // Definindo os navios
    // Navio 1 - Tem uma posição inválida (11, 2)
    int ship_1[3][2] = {{0, 2}, {11, 2}, {2, 2}};
    // Navio 2 - Todas válidas
    int ship_2[3][2] = {{8, 3}, {8, 4}, {8, 5}};
    // Navio 3 - Todas válidas (diagonal)
    int ship_3[3][2] = {{3, 5}, {4, 6}, {5, 7}};
    // Navio 4 - Todas válidas (diagonal)
    int ship_4[3][2] = {{7, 1}, {6, 2}, {5, 3}};

    // Tentativa de posicionamento dos navios
    // printf("Tentando posicionar navios...\n\n");

    // Navio 1
    // printShipPositions(ship_1, 3, 1);
    // placeShip(board, ship_1, 3, 1);
    // printBoard(board);
    // printf("\n");

    return 0;
}