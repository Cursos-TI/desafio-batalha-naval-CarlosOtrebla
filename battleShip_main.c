#include "battleShip.h"
#include <ctype.h> // Para usar toupper()

int main()
{
    // Configurando o console para aceitar acentos.
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Definindo o tabuleiro sem navios
    int board[ROW][COLUMN] = {0};
    int option;
    int optionPosition;
    int positioned_destroyer = 0;        // O máximo será 2 navios posicionados
    int positioned_cruiser = 0;          // O máximo será 3 navios posicionados
    int positioned_battleship = 0;       // O máximo será 2 navios posicionados
    int positioned_aircraft_carrier = 0; // O máximo será 1 navio posicionado

    do
    {
        printBoard(board);

        printf("Escolha uma opção:\n");
        printf("1 - Posicionar navios\n");
        printf("2 - Ver status dos navios\n");
        printf("3 - Atacar oponente (em desenvolvimento)\n");
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
                case 1: // Vertical
                    positionShipInteractive(board, 1, &positioned_destroyer, &positioned_cruiser,
                                            &positioned_battleship, &positioned_aircraft_carrier);
                    printBoard(board);
                    break;

                case 2: // Horizontal
                    positionShipInteractive(board, 2, &positioned_destroyer, &positioned_cruiser,
                                            &positioned_battleship, &positioned_aircraft_carrier);
                    printBoard(board);
                    break;

                case 3: // Diagonal crescente
                    positionShipInteractive(board, 3, &positioned_destroyer, &positioned_cruiser,
                                            &positioned_battleship, &positioned_aircraft_carrier);
                    printBoard(board);
                    break;

                case 4: // Diagonal decrescente
                    positionShipInteractive(board, 4, &positioned_destroyer, &positioned_cruiser,
                                            &positioned_battleship, &positioned_aircraft_carrier);
                    printBoard(board);
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

        case 2: // Ver status dos navios
        {
            printf("\n=== STATUS DOS NAVIOS ===\n");
            printf("Destroyers (2 casas):     %d/2 posicionados\n", positioned_destroyer);
            printf("Cruzadores (3 casas):     %d/2 posicionados\n", positioned_cruiser);
            printf("Navio de guerra (4 casas): %d/1 posicionado\n", positioned_battleship);
            printf("Porta-aviões (5 casas):   %d/1 posicionado\n", positioned_aircraft_carrier);
            printf("\nLegenda do tabuleiro:\n");
            printf("~ = Água\n");
            printf("1 = Destroyer\n");
            printf("2 = Cruzador\n");
            printf("3 = Navio de guerra\n");
            printf("4 = Porta-aviões\n");
            printf("\nPressione Enter para continuar...");
            getchar(); // Limpa o buffer
            getchar(); // Espera Enter
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