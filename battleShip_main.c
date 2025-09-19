#include "battleShip.h"

int main()
{
    // Configurando o console para aceitar acentos.
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Definindo o tabuleiro sem navios
    int board[ROW][COLUMN] = {0};
    int option;
    int optionPosition;

    int ship_1[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}; // Navio 1
    int ship_2[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}; // Navio 2

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
                printf("4 - Diagonal Decrescente\n");
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
                    placeShip(board, ship_2, 3, 1);

                    break;
                }

                case 2:
                    // Implementar posicionamento horizontal
                    break;

                case 3:
                    // Implementar posicionamento diagonal crescente
                    break;

                case 4:
                    // Implementar posicionamento diagonal decrescente
                    break;

                default:
                    if (optionPosition != 0)
                    {
                        printf("Opção inválida!\n");
                    }
                    break;
                }
            } while (optionPosition != 0);

            break;
        }

        default:
            if (option != 0)
                printf("Opção inválida!\n");
            break;
        }

    } while (option != 0);

    printf("Fim do jogo!\n");

    return 0;
}