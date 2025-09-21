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
                case 1:
                {
                    int row;
                    int column;
                    int ship_type = 0; // Tipo do navio escolhido
                    int ship_size = 0; // Tamanho do navio
                    int ship_id = 0;   // ID do navio no tabuleiro

                    printBoard(board);
                    printf("Qual navio deseja posicionar?\n");
                    printf("1 - Destroyer - Navio de 2 casas (restam: %d)\n", 2 - positioned_destroyer);
                    printf("2 - Cruzador - Navio de 3 casas (restam: %d)\n", 2 - positioned_cruiser);
                    printf("3 - Navio de guerra - Navio de 4 casas (restam: %d)\n", 1 - positioned_battleship);
                    printf("4 - Porta-avioes - Navio de 5 casas (restam: %d)\n", 1 - positioned_aircraft_carrier);
                    scanf("%d", &ship_type);

                    // Define tamanho, ID e verifica limites
                    switch (ship_type)
                    {
                    case 1: // Destroyer
                        if (positioned_destroyer >= 2)
                        {
                            printf("Erro: Você já posicionou todos os destroyers!\n");
                            break;
                        }
                        ship_size = 2;
                        ship_id = 1;

                        break;
                    case 2: // Cruzador
                        if (positioned_cruiser >= 2)
                        {
                            printf("Erro: Você já posicionou todos os cruzadores!\n");
                            break;
                        }
                        ship_size = 3;
                        ship_id = 2;

                        break;
                    case 3: // Navio de guerra
                        if (positioned_battleship >= 1)
                        {
                            printf("Erro: Você já posicionou o navio de guerra!\n");
                            break;
                        }
                        ship_size = 4;
                        ship_id = 3;

                        break;
                    case 4: // Porta-aviões
                        if (positioned_aircraft_carrier >= 1)
                        {
                            printf("Erro: Você já posicionou o porta-aviões!\n");
                            break;
                        }
                        ship_size = 5;
                        ship_id = 4;

                        break;
                    default:
                        printf("Erro: Navio inválido! Use números de 1 a 4.\n");
                        break;
                    }

                    if (ship_size == 0)
                    {
                        break;
                    }

                    // Solicita as coordenadas iniciais
                    printf("O navio será posicionado na vertical de cima para baixo a partir da coordenada que for digitada.\n");
                    printf("Digite as coordenadas iniciais do navio (tamanho %d):\n", ship_size);
                    printf("Linha (1-%d): ", ROW);
                    scanf("%d", &row);

                    // Verifica se a linha é válida
                    if (row < 1 || row > ROW)
                    {
                        printf("Erro: Linha inválida! Use números de 1 a %d.\n", ROW);
                        break; // Volta ao menu sem incrementar contador
                    }

                    row--; // Converte para índice 0-based
                    printf("Coluna (A-J ou a-j): ");
                    char col_char;
                    scanf(" %c", &col_char);
                    col_char = toupper(col_char); // Converte para maiúscula
                    // Converte para índice 0-based usando a tabela ASCII a nosso favor.
                    column = col_char - 'A'; // Converte A=0, B=1, etc.

                    // Verifica se a coluna é válida
                    if (column < 0 || column >= COLUMN)
                    {
                        printf("Erro: Coluna inválida! Use letras de A a J.\n");
                        break;
                    }

                    int ship_temp[ship_size][2];

                    // Gera as posições do navio verticalmente
                    for (int i = 0; i < ship_size; i++)
                    {
                        ship_temp[i][0] = row + i; // Linha cresce para baixo
                        ship_temp[i][1] = column;  // Coluna fica a mesma
                    }

                    // Tenta posicionar o navio
                    printf("\nTentando posicionar navio na posição %c%d...\n", col_char, row + 1);
                    if (placeShip(board, ship_temp, ship_size, ship_id))
                    {
                        printf("✅ Navio posicionado com sucesso!\n");

                        // Incrementa o contador do navio posicionado
                        switch (ship_type)
                        {
                        case 1:
                            positioned_destroyer++;
                            break;
                        case 2:
                            positioned_cruiser++;
                            break;
                        case 3:
                            positioned_battleship++;
                            break;
                        case 4:
                            positioned_aircraft_carrier++;
                            break;
                        }
                    }
                    else
                    {
                        printf("❌ Não foi possível posicionar o navio nesta posição!\n");
                        printf("Verifique se há espaço suficiente e se não há sobreposição.\n");
                        printf("Você pode tentar novamente!\n");
                    }

                    printBoard(board);
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