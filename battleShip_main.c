#include "battleShip.h"
#include <ctype.h> // Para usar toupper()

int main()
{
    // Configurando o console para aceitar acentos.
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Habilita cores no terminal Windows
    enableColors();

    // Definindo o tabuleiro sem navios
    int board[ROW][COLUMN] = {0};
    // Inicializando o tabuleiro de ataques
    initializeAttackBoard(attack_board);

    int option;
    int optionPosition;
    int positioned_destroyer = 0;        // O máximo será 2 navios posicionados
    int positioned_cruiser = 0;          // O máximo será 3 navios posicionados
    int positioned_battleship = 0;       // O máximo será 2 navios posicionados
    int positioned_aircraft_carrier = 0; // O máximo será 1 navio posicionado

    do
    {
        printBoard(board);
        // printBothBoards(board, attack_board);

        // Calcula quantos navios foram posicionados
        int total_ships = positioned_destroyer + positioned_cruiser + positioned_battleship + positioned_aircraft_carrier;
        int max_ships = 2 + 2 + 1 + 1;

        printf(" Escolha uma opção:\n\n");
        if (total_ships >= max_ships)
        {
            printf("1 - Posicionar navios (✓ COMPLETO)\n");
        }
        else
        {
            printf("1 - Posicionar navios (%d/%d navios)\n", total_ships, max_ships);
        }
        printf("2 - Ver status dos navios\n");
        printf("3 - Atacar (modo teste)\n");
        printf("4 - Ver ambos os tabuleiros\n");
        printf("0 - Sair\n");
        scanf("%d", &option);

        switch (option)
        {
        case 1: // Posicionar navios
        {
            // Verifica se todos os navios já foram posicionados
            int total_ships = positioned_destroyer + positioned_cruiser + positioned_battleship + positioned_aircraft_carrier;
            int max_ships = 2 + 2 + 1 + 1; // 2 destroyers + 2 cruzadores + 1 battleship + 1 aircraft carrier

            if (total_ships >= max_ships)
            {
                printf("\n✅ TODOS OS NAVIOS JÁ FORAM POSICIONADOS!\n");
                printf("\n=== STATUS COMPLETO ===\n");
                printf("Destroyers (2 casas):     %d/2 posicionados ✓\n", positioned_destroyer);
                printf("Cruzadores (3 casas):     %d/2 posicionados ✓\n", positioned_cruiser);
                printf("Navio de guerra (4 casas): %d/1 posicionado ✓\n", positioned_battleship);
                printf("Porta-aviões (5 casas):   %d/1 posicionado ✓\n", positioned_aircraft_carrier);
                printf("\nAgora você pode:\n");
                printf("- Ver seus navios (opção 2)\n");
                printf("- Fazer ataques de teste (opção 3)\n");
                printf("- Ver ambos os tabuleiros (opção 4)\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                getchar();
                break;
            }

            do
            {
                // Verifica se todos os navios foram posicionados antes de mostrar o menu
                total_ships = positioned_destroyer + positioned_cruiser + positioned_battleship + positioned_aircraft_carrier;
                if (total_ships >= max_ships)
                {
                    printf("\n🎉 PARABÉNS! TODOS OS NAVIOS FORAM POSICIONADOS!\n");
                    printf("Retornando ao menu principal...\n");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    getchar();
                    break; // Sai do loop e volta ao menu principal
                }

                printBoard(board);
                printf(" Qual navio deseja posicionar?\n\n");
                if (positioned_destroyer < 2)
                {
                    printf(" 1 - Destroyer --------- Navio de 2 casas (restam: %d)\n", 2 - positioned_destroyer);
                }
                else
                {
                    printf(" 1 - Destroyer (✓)\n");
                }
                if (positioned_cruiser < 2)
                {
                    printf(" 2 - Cruzador  --------- Navio de 3 casas (restam: %d)\n", 2 - positioned_cruiser);
                }
                else
                {
                    printf(" 2 - Cruzador (✓)\n");
                }
                if (positioned_battleship < 1)
                {
                    printf(" 3 - Navio de guerra --- Navio de 4 casas (restam: %d)\n", 1 - positioned_battleship);
                }
                else
                {
                    printf(" 3 - Navio de guerra (✓)\n");
                }
                if (positioned_aircraft_carrier < 1)
                {
                    printf(" 4 - Porta-avioes ------ Navio de 5 casas (restam: %d)\n", 1 - positioned_aircraft_carrier);
                }
                else
                {
                    printf(" 4 - Porta-avioes (✓)\n");
                }

                printf(" 0 - Menu Principal\n");
                scanf("%d", &optionPosition);

                if (optionPosition == 0)
                {
                    break; // Volta ao menu principal
                }

                // Chama a função interativa que agora vai pedir a orientação
                positionShipInteractiveNew(board, optionPosition, &positioned_destroyer, &positioned_cruiser,
                                           &positioned_battleship, &positioned_aircraft_carrier);

            } while (optionPosition != 0);

            break;
        }

        case 3: // Atacar (modo teste)
        {
            printf("\n=== MODO DE ATAQUE (TESTE) ===\n");
            printf("Você pode atacar seus próprios navios para testar!\n");

            int attack_result;
            do
            {
                attack_result = attackInteractive(board, attack_board);

                if (attack_result == -1)
                {
                    printf("\nErro no ataque! Tente novamente.\n");
                    printf("Pressione Enter para continuar...");
                    getchar();
                    getchar();
                }
                else if (attack_result == 0)
                {
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    getchar();
                    break; // Água - volta ao menu
                }
                else if (attack_result == 1)
                {
                    printf("\nAcertou! Deseja atacar novamente? (s/n): ");
                    char continue_attack;
                    scanf(" %c", &continue_attack);
                    if (continue_attack != 's' && continue_attack != 'S')
                    {
                        break; // Volta ao menu
                    }
                }
            } while (attack_result != 0);

            break;
        }

        case 4: // Ver ambos os tabuleiros
        {
            printBothBoards(board, attack_board);
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
            break;
        }

        case 2: // Ver status dos navios
        {
            printf("\n============== STATUS DOS NAVIOS ==============\n\n");
            printf("Destroyers -------- (2 casas):  %d/2 posicionados\n", positioned_destroyer);
            printf("Cruzadores ---------(3 casas):  %d/2 posicionados\n", positioned_cruiser);
            printf("Navio de guerra --- (4 casas):  %d/1 posicionado\n", positioned_battleship);
            printf("Porta-aviões ------ (5 casas):  %d/1 posicionado\n", positioned_aircraft_carrier);
            printf("\n================================================\n");
            printf("\nLegenda do tabuleiro:\n\n");
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