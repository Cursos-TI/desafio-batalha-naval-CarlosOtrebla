#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#define ROW 10
#define COLUMN 10

int posicao_valida(int linha, int coluna)
{
    return (linha >= 0 && linha < ROW && coluna >= 0 && coluna < COLUMN);
}

// Função para imprimir o tabuleiro
void printBoard(int board[ROW][COLUMN])
{

    for (int linha = 0; linha < ROW; linha++)
    {
        for (int coluna = 0; coluna < COLUMN; coluna++)
        {
            printf("%d ", board[linha][coluna]);
        }
        printf("\n");
    }
}

// Função para limpar o tabuleiro
void clearBoard(char board[ROW][COLUMN])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            board[i][j] = '~';
        }
    }
}

// Função para ataque em cruz
void crossAtack(int board[ROW][COLUMN], int target[2])
{
    int rowAtack = target[0];
    int colAtack = target[1];
    for (int i = 0; i < 3; i++)
    {

        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COLUMN; j++)
            {
                if (i >= rowAtack - 2 && i <= rowAtack + 2 && j == colAtack || j >= colAtack - 2 && j <= colAtack + 2 && i == rowAtack)
                {
                    board[i][j] = 1;
                }
            }
        }
    }
}

void coneAtack(int matriz[10][10], int alvo[2])
{
    int linha_alvo = alvo[0];
    int coluna_alvo = alvo[1];

    // Verificar se o alvo está dentro dos limites da matriz
    if (linha_alvo < 0 || linha_alvo >= 10 || coluna_alvo < 0 || coluna_alvo >= 10)
    {
        printf("ERRO: Coordenada alvo fora dos limites da matriz!\n");
        return;
    }

    printf("=== ATAQUE EM CONE REALIZADO ===\n");
    printf("Alvo: linha %d, coluna %d\n\n", linha_alvo, coluna_alvo);

    // Percorrer toda a matriz com condição matemática para formar o cone
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // Condição para formar o triângulo/cone:
            // - Deve estar na linha do alvo ou abaixo (i >= linha_alvo)
            // - A distância horizontal deve diminuir conforme sobe
            // - Fórmula: abs(j - coluna_alvo) <= (i - linha_alvo)

            if (i >= linha_alvo && abs(j - coluna_alvo) <= (i - linha_alvo))
            {
                matriz[i][j] = 3;
            }
        }
    }
}

// void coneAtack(int board[ROW][COLUMN], int target[])
// {
//     for (int i = 0; i < ROW; i++)
//     {
//         for (int j = 0; j < COLUMN; j++)
//         {
//             if (i >= target[0] && j == target[1] + 2 && j >= target[1] - 2 && j <= target[1] + 2)
//             {
//                 board[i][j] = 1;
//             }
//         }
//     }
// }

int main()
{
    SetConsoleOutputCP(65001); // UTF-8
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int matriz[ROW][COLUMN] = {0};

    for (int linha = 0; linha < ROW; linha++)
    {
        for (int coluna = 0; coluna < COLUMN; coluna++)
        {
            printf("%d ", matriz[linha][coluna]);
        }
        printf("\n");
    }

    printf("\n");

    int target1[2] = {5, 6};
    int target2[2] = {3, 3};

    printf("\n");

    // Ataque em cruz
    // crossAtack(matriz, target1);
    // crossAtack(matriz, target2);

    printf("\n");

    printBoard(matriz);

    printf("\n");

    coneAtack(matriz, target1);

    printf("\n");

    // clearBoard(matriz);

    printBoard(matriz);

    return 0;
}