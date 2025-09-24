#include "battleShip.h"

// Definindo o nome das colunas

char nameColumn[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

// Tabuleiro de ataques
char attack_board[ROW][COLUMN];

// Função auxiliar para limpar buffer de entrada
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função para converter entrada no formato "5B" para linha e coluna
int parsePosition(char *input, int *row, int *column)
{
    // Verifica se o input tem pelo menos 2 caracteres
    if (strlen(input) < 2)
    {
        printf("[FORMATO INVALIDO] Use o formato: LinhaColuna (ex: 5B)\n");
        return 0;
    }

    // Converte para maiúscula para facilitar o processamento
    for (int i = 0; input[i]; i++)
    {
        input[i] = toupper(input[i]);
    }

    // Extrai a linha (pode ser 1 ou 2 dígitos)
    int line_num = 0;
    int i = 0;

    // Lê todos os dígitos do início
    while (input[i] >= '0' && input[i] <= '9')
    {
        line_num = line_num * 10 + (input[i] - '0');
        i++;
    }

    // Verifica se encontrou pelo menos um dígito
    if (i == 0)
    {
        printf("[FORMATO INVALIDO] Deve começar com um número (ex: 5B)\n");
        return 0;
    }

    // Verifica se a linha está no intervalo válido
    if (line_num < 1 || line_num > ROW)
    {
        printf("[LINHA INVALIDA] Use numeros de 1 a %d\n", ROW);
        return 0;
    }

    // Verifica se há uma letra para a coluna
    if (input[i] == '\0')
    {
        printf("[FORMATO INVALIDO] Falta a letra da coluna (ex: 5B)\n");
        return 0;
    }

    // Extrai a coluna
    char col_char = input[i];

    // Verifica se é uma letra válida
    if (col_char < 'A' || col_char > 'J')
    {
        printf("[COLUNA INVALIDA] Use letras de A a J\n");
        return 0;
    }

    // Verifica se há caracteres extras
    if (input[i + 1] != '\0')
    {
        printf("[FORMATO INVALIDO] Use apenas LinhaColuna (ex: 5B)\n");
        return 0;
    }

    // Converte para índices 0-based
    *row = line_num - 1;
    *column = col_char - 'A';

    return 1; // Sucesso
}

// Ataque em CONE - ataca em formato triangular para baixo
int performConeAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column)
{
    printf("\n=== ATAQUE EM CONE ===\n");
    printf("Atacando posicao %c%d com padrao em cone!\n\n", nameColumn[column], row + 1);

    int hits = 0;
    int attacks = 0;

    // Percorre as 3 linhas do cone (linha atual + 2 abaixo)
    for (int i = 0; i < 3; i++)
    {
        int current_row = row + i;

        // Para cada linha do cone, ataca posições baseado na distância
        for (int j = -i; j <= i; j++)
        {
            int current_col = column + j;

            // Verifica se a posição é válida
            if (positionIsValid(current_row, current_col, ROW))
            {
                // Verifica se já foi atacada
                if (attack_board[current_row][current_col] == UNKNOWN)
                {
                    attacks++;

                    // Realiza o ataque
                    if (target_board[current_row][current_col] != 0) // Há navio
                    {
                        attack_board[current_row][current_col] = HIT;
                        target_board[current_row][current_col] = -target_board[current_row][current_col];
                        hits++;
                        printf("[ACERTO] em %c%d!\n", nameColumn[current_col], current_row + 1);
                    }
                    else // Água
                    {
                        attack_board[current_row][current_col] = MISS;
                        printf("AGUA em %c%d\n", nameColumn[current_col], current_row + 1);
                    }
                }
                else
                {
                    printf("[AVISO] Posicao %c%d ja foi atacada\n", nameColumn[current_col], current_row + 1);
                }
            }
        }
    }

    printf("\nRESULTADO DO ATAQUE EM CONE:\n");
    printf("Ataques realizados: %d\n", attacks);
    printf("Acertos: %d\n", hits);
    printf("Taxa de acerto: %.1f%%\n", attacks > 0 ? (hits * 100.0) / attacks : 0.0);

    return hits;
}

// Ataque em OCTAEDRO - formato losango (baseado no README)
int performOctahedronAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column)
{
    printf("\n========= ATAQUE EM OCTAEDRO =========\n");
    printf("Atacando posição %c%d com padrão octaedro (losango)!\n\n", nameColumn[column], row + 1);

    int hits = 0;
    int attacks = 0;

    // Direções: cima, baixo, esquerda, direita, centro
    int directions[5][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
    char *dir_names[] = {"cima", "baixo", "esquerda", "direita", "centro"};

    for (int i = 0; i < 5; i++)
    {
        int current_row = row + directions[i][0];
        int current_col = column + directions[i][1];

        // Verifica se a posição é válida
        if (positionIsValid(current_row, current_col, ROW))
        {
            // Verifica se já foi atacada
            if (attack_board[current_row][current_col] == UNKNOWN)
            {
                attacks++;

                // Realiza o ataque
                if (target_board[current_row][current_col] != 0) // Há navio
                {
                    attack_board[current_row][current_col] = HIT;
                    target_board[current_row][current_col] = -target_board[current_row][current_col];
                    hits++;
                    printf("ACERTO em %c%d (%s)!\n", nameColumn[current_col], current_row + 1, dir_names[i]);
                }
                else // Água
                {
                    attack_board[current_row][current_col] = MISS;
                    printf("Água em %c%d (%s)\n", nameColumn[current_col], current_row + 1, dir_names[i]);
                }
            }
            else
            {
                printf("Posição %c%d (%s) já foi atacada\n", nameColumn[current_col], current_row + 1, dir_names[i]);
            }
        }
        else
        {
            printf("Posição fora do tabuleiro (%s)\n", dir_names[i]);
        }
    }

    printf("\nRESULTADO DO ATAQUE EM OCTAEDRO:\n");
    printf("Ataques realizados: %d\n", attacks);
    printf("Acertos: %d\n", hits);
    printf("Taxa de acerto: %.1f%%\n", attacks > 0 ? (hits * 100.0) / attacks : 0.0);

    return hits;
}

// Ataque em CRUZ
int performCrossAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column)
{
    printf("\n=== ATAQUE EM CRUZ ===\n");
    printf("Atacando posição %c%d com padrão em cruz estendida!\n\n", nameColumn[column], row + 1);

    int hits = 0;
    int attacks = 0;

    // Linha superior (só o centro)
    if (positionIsValid(row - 1, column, ROW))
    {
        if (attack_board[row - 1][column] == UNKNOWN)
        {
            attacks++;
            if (target_board[row - 1][column] != 0)
            {
                attack_board[row - 1][column] = HIT;
                target_board[row - 1][column] = -target_board[row - 1][column];
                hits++;
                printf("ACERTO em %c%d (cima)!\n", nameColumn[column], row);
            }
            else
            {
                attack_board[row - 1][column] = MISS;
                printf("Água em %c%d (cima)\n", nameColumn[column], row);
            }
        }
        else
        {
            printf("Posição %c%d (cima) já foi atacada\n", nameColumn[column], row);
        }
    }

    // Linha central (5 posições: 2 à esquerda, centro, 2 à direita)
    for (int j = -2; j <= 2; j++)
    {
        int current_col = column + j;
        if (positionIsValid(row, current_col, ROW))
        {
            if (attack_board[row][current_col] == UNKNOWN)
            {
                attacks++;
                if (target_board[row][current_col] != 0)
                {
                    attack_board[row][current_col] = HIT;
                    target_board[row][current_col] = -target_board[row][current_col];
                    hits++;
                    printf("ACERTO em %c%d (centro)!\n", nameColumn[current_col], row + 1);
                }
                else
                {
                    attack_board[row][current_col] = MISS;
                    printf("Água em %c%d (centro)\n", nameColumn[current_col], row + 1);
                }
            }
            else
            {
                printf("Posição %c%d (centro) já foi atacada\n", nameColumn[current_col], row + 1);
            }
        }
    }

    // Linha inferior (só o centro)
    if (positionIsValid(row + 1, column, ROW))
    {
        if (attack_board[row + 1][column] == UNKNOWN)
        {
            attacks++;
            if (target_board[row + 1][column] != 0)
            {
                attack_board[row + 1][column] = HIT;
                target_board[row + 1][column] = -target_board[row + 1][column];
                hits++;
                printf("ACERTO em %c%d (baixo)!\n", nameColumn[column], row + 2);
            }
            else
            {
                attack_board[row + 1][column] = MISS;
                printf("Água em %c%d (baixo)\n", nameColumn[column], row + 2);
            }
        }
        else
        {
            printf("Posição %c%d (baixo) já foi atacada\n", nameColumn[column], row + 2);
        }
    }

    printf("\nRESULTADO DO ATAQUE EM CRUZ:\n");
    printf("Ataques realizados: %d\n", attacks);
    printf("Acertos: %d\n", hits);
    printf("Taxa de acerto: %.1f%%\n", attacks > 0 ? (hits * 100.0) / attacks : 0.0);

    return hits;
}

// Ataque em CÍRCULO - ataca todas as posições ao redor em um raio de 1
int performCircleAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column)
{
    printf("\n === ATAQUE EM CÍRCULO ===\n");
    printf(" Atacando posição %c%d com padrão circular!\n\n", nameColumn[column], row + 1);

    int hits = 0;
    int attacks = 0;

    // Percorre um quadrado 3x3 centrado na posição alvo
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int current_row = row + i;
            int current_col = column + j;

            // Verifica se a posição é válida
            if (positionIsValid(current_row, current_col, ROW))
            {
                // Verifica se já foi atacada
                if (attack_board[current_row][current_col] == UNKNOWN)
                {
                    attacks++;

                    // Realiza o ataque
                    if (target_board[current_row][current_col] != 0) // Há navio
                    {
                        attack_board[current_row][current_col] = HIT;
                        target_board[current_row][current_col] = -target_board[current_row][current_col];
                        hits++;
                        printf("ACERTO em %c%d!\n", nameColumn[current_col], current_row + 1);
                    }
                    else // Água
                    {
                        attack_board[current_row][current_col] = MISS;
                        printf("Água em %c%d\n", nameColumn[current_col], current_row + 1);
                    }
                }
                else
                {
                    printf("Posição %c%d já foi atacada\n", nameColumn[current_col], current_row + 1);
                }
            }
        }
    }

    printf("\nRESULTADO DO ATAQUE CIRCULAR:\n");
    printf("Ataques realizados: %d\n", attacks);
    printf("Acertos: %d\n", hits);
    printf("Taxa de acerto: %.1f%%\n", attacks > 0 ? (hits * 100.0) / attacks : 0.0);

    return hits;
}

// ~~~~~~~~~~~~~~~~~~~~Funções de diversas~~~~~~~~~~~~~~~~~~~~~
// Função para verificar se a posição é válida

int positionIsValid(int row, int column, int board_size)
{
    return (row >= 0 && row < board_size && column >= 0 && column < board_size);
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

// Função para posicionar navio - NOVA VERSÃO (escolhe navio primeiro, depois orientação)
int positionShipInteractiveNew(int board[ROW][COLUMN], int ship_type,
                               int *positioned_destroyer, int *positioned_cruiser,
                               int *positioned_battleship, int *positioned_aircraft_carrier)
{
    int row, column;
    int ship_size = 0, ship_id = 0;
    int orientation;

    // Verifica tipo de navio e define tamanho/ID
    switch (ship_type)
    {
    case 1: // Destroyer
        if (*positioned_destroyer >= 2)
        {
            printf("Erro: Você já posicionou todos os destroyers!\n");
            printf("Pressione Enter para escolher outro navio...");
            clearInputBuffer();
            getchar();
            return 0;
        }
        ship_size = 2;
        ship_id = 1;
        printf("\n Posicionando DESTROYER (2 casas)\n\n");
        break;
    case 2: // Cruzador
        if (*positioned_cruiser >= 2)
        {
            printf("Erro: Você já posicionou todos os cruzadores!\n");
            printf("Pressione Enter para escolher outro navio...");
            clearInputBuffer();
            getchar();
            return 0;
        }
        ship_size = 3;
        ship_id = 2;
        printf("\n Posicionando CRUZADOR (3 casas)\n\n");
        break;
    case 3: // Navio de guerra
        if (*positioned_battleship >= 1)
        {
            printf("Erro: Você já posicionou o navio de guerra!\n");
            printf("Pressione Enter para escolher outro navio...");
            clearInputBuffer();
            getchar();
            return 0;
        }
        ship_size = 4;
        ship_id = 3;
        printf("\n Posicionando NAVIO DE GUERRA (4 casas)\n\n");
        break;
    case 4: // Porta-aviões
        if (*positioned_aircraft_carrier >= 1)
        {
            printf("Erro: Você já posicionou o porta-aviões!\n");
            printf("Pressione Enter para escolher outro navio...");
            clearInputBuffer();
            getchar();
            return 0;
        }
        ship_size = 5;
        ship_id = 4;
        printf("\n Posicionando PORTA-AVIÕES (5 casas)\n\n");
        break;
    default:
        printf("Erro: Tipo de navio inválido!\n");
        return 0;
    }

    // Agora escolhe a orientação
    printf("╔═ Escolha a orientação para o navio:\n");
    printf("║\n");
    printf("╠═ 1 - Vertical (para baixo)\n");
    printf("╠═ 2 - Horizontal (para direita)\n");
    printf("╠═ 3 - Diagonal crescente\n");
    printf("╠═ 4 - Diagonal decrescente\n");
    printf("╠═ 0 - Cancelar\n");
    printf("║\n");
    printf("╚════► ");
    orientation = getValidInteger("", 0, 4); // Usa função robusta

    if (orientation == 0)
    {
        return 0; // Cancela
    }

    if (orientation < 1 || orientation > 4)
    {
        printf("Orientação inválida!\n");
        return 0;
    }
    printBoard(board);
    // Solicita as coordenadas iniciais
    const char *orientations[] = {"vertical", "horizontal", "diagonal crescente", "diagonal decrescente"};
    printf("\n╔═ O navio será posicionado na orientação %s.\n", orientations[orientation - 1]);
    printf("║  Digite a posição inicial do navio (tamanho %d). (ex: 5B, 10A, 3F):\n", ship_size);
    printf("║\n");
    printf("╚════► ");
    fflush(stdout); // ADICIONADO: Cursor pisca esperando entrada de coordenadas

    char position[10];
    scanf("%s", position);

    // Converte a entrada para linha e coluna
    if (!parsePosition(position, &row, &column))
    {
        printf("\nDica: Digite linha seguida da coluna, como 5B, 10A, etc.\n");
        return 0;
    }

    int ship_temp[ship_size][2];

    // Gera as posições do navio baseado na orientação
    for (int i = 0; i < ship_size; i++)
    {
        switch (orientation)
        {
        case 1: // Vertical
            ship_temp[i][0] = row + i;
            ship_temp[i][1] = column;
            break;
        case 2: // Horizontal
            ship_temp[i][0] = row;
            ship_temp[i][1] = column + i;
            break;
        case 3: // Diagonal crescente
            ship_temp[i][0] = row - i;
            ship_temp[i][1] = column + i;
            break;
        case 4: // Diagonal decrescente
            ship_temp[i][0] = row + i;
            ship_temp[i][1] = column + i;
            break;
        }
    }

    // Tenta posicionar o navio
    printf("\nTentando posicionar navio na posição %c%d...\n", nameColumn[column], row + 1);
    if (placeShip(board, ship_temp, ship_size, ship_id))
    {
        printf("Navio posicionado com sucesso!\n");

        // Incrementa o contador do navio posicionado
        switch (ship_type)
        {
        case 1:
            (*positioned_destroyer)++;
            break;
        case 2:
            (*positioned_cruiser)++;
            break;
        case 3:
            (*positioned_battleship)++;
            break;
        case 4:
            (*positioned_aircraft_carrier)++;
            break;
        }

        printBoard(board);
        printf("Pressione Enter para continuar...");
        clearInputBuffer();
        getchar();
        return 1; // Sucesso
    }
    else
    {
        printf("Não foi possível posicionar o navio nesta posição!\n");
        printf("Verifique se há espaço suficiente e se não há sobreposição.\n");
        printf("Pressione Enter para tentar novamente...");
        clearInputBuffer();
        getchar();
        return 0;
    }
}

// Função para habilitar cores ANSI no Windows
void enableColors()
{
#ifdef _WIN32
    // Habilita o processamento de sequências de escape ANSI no Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

// Função para obter entrada válida de número inteiro
int getValidInteger(const char *prompt, int min, int max)
{
    int value;
    int result;

    do
    {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result != 1)
        {
            printf("║     Opção inválida: Digite apenas números!\n");
            printf("╚════► ");
            clearInputBuffer();
            continue;
        }

        if (value < min || value > max)
        {
            printf("Opção inválida: Digite um número entre %d e %d!\n", min, max);
            continue;
        }

        return value;

    } while (1);
}

// Função para inicializar o tabuleiro de ataques
void initializeAttackBoard(char attack_board[ROW][COLUMN])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            attack_board[i][j] = UNKNOWN; // '~' para posições não atacadas
        }
    }
}

// Função para realizar um ataque
int performAttack(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN], int row, int column)
{
    // Verifica se a posição é válida
    if (!positionIsValid(row, column, ROW))
    {
        printf("Erro: Posição [%d][%d] está fora do tabuleiro!\n", row + 1, column + 1);
        return -1; // Posição inválida
    }

    // Verifica se a posição já foi atacada
    if (attack_board[row][column] != UNKNOWN)
    {
        printf("Erro: Posição %c%d já foi atacada!\n", nameColumn[column], row + 1);
        return -1; // Já atacada
    }

    // Realiza o ataque
    if (target_board[row][column] != 0)
    {
        attack_board[row][column] = HIT; // 'X' para acerto
        printf("ACERTOU! Há um navio na posição %c%d!\n", nameColumn[column], row + 1);

        // Marca o navio como atingido no tabuleiro original
        target_board[row][column] = -target_board[row][column]; // Torna negativo para indicar hit

        return 1; // Acerto
    }
    else
    {
        attack_board[row][column] = MISS; // 'O' para erro
        printf("ÁGUA! Não há navio na posição %c%d.\n", nameColumn[column], row + 1);
        return 0; // Erro (água)
    }
}

// Função para imprimir o tabuleiro de ataques
void printAttackBoard(char attack_board[ROW][COLUMN])
{
    printf("\n========== SEUS ATAQUES ==========\n");
    printf("\n");

    // Cabeçalho com letras das colunas
    printf("     "); // Espaço a mais antes das letras
    for (int column = 0; column < COLUMN; column++)
    {
        printf("%c  ", nameColumn[column]);
    }
    printf("\n");
    printf("\n"); // Linha em branco após o cabeçalho

    // Linhas do tabuleiro
    for (int row = 0; row < ROW; row++)
    {
        printf("%2d  ", row + 1); // Espaço a mais após o número da linha
        for (int column = 0; column < COLUMN; column++)
        {
            char symbol = attack_board[row][column];
            switch (symbol)
            {
            case UNKNOWN: // '~' - Não atacado
                printf(BLUE " %c " RESET_COLOR, symbol);
                break;
            case HIT: // 'X' - Acerto
                printf(BRIGHT_GREEN BOLD " %c " RESET_COLOR, symbol);
                break;
            case MISS: // 'O' - Erro (água)
                printf(WHITE " %c " RESET_COLOR, symbol);
                break;
            default:
                printf(" %c ", symbol);
                break;
            }
        }
        printf("\n");
    }

    printf("\nLegenda: " BLUE "~ = Não atacado" RESET_COLOR " | " BRIGHT_GREEN "X = Acerto" RESET_COLOR " | " WHITE "O = Água" RESET_COLOR "\n\n");
    // printf("\n");
}

// Função para imprimir o tabuleiro

void printBoard(int board[ROW][COLUMN])
{
    printf("\n==== TABULEIRO BATALHA NAVAL ====\n");
    printf("\n");

    // Cabeçalho com números das colunas
    printf("     "); // Espaço a mais antes das letras
    for (int column = 0; column < COLUMN; column++)
    {
        printf("%c  ", nameColumn[column]);
    }
    printf("\n");
    printf("\n"); // Linha em branco após o cabeçalho

    // Linhas do tabuleiro
    for (int row = 0; row < ROW; row++)
    {
        printf("%2d  ", row + 1); // Espaço a mais após o número da linha
        for (int column = 0; column < COLUMN; column++)
        {
            int value = board[row][column];
            if (value == 0)
            {
                printf(BLUE " ~ " RESET_COLOR); // Água em azul
            }
            else if (value > 0)
            {
                // Navios intactos com cores específicas
                switch (value)
                {
                case 1:
                    printf(GREEN " %d " RESET_COLOR, value);
                    break; // Destroyer verde
                case 2:
                    printf(YELLOW " %d " RESET_COLOR, value);
                    break; // Cruzador amarelo
                case 3:
                    printf(MAGENTA " %d " RESET_COLOR, value);
                    break; // Battleship magenta
                case 4:
                    printf(CYAN " %d " RESET_COLOR, value);
                    break; // Porta-aviões ciano
                default:
                    printf(" %d ", value);
                    break;
                }
            }
            else // value < 0
            {
                printf(RED BOLD " X " RESET_COLOR); // Navio atingido em vermelho negrito
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função para imprimir ambos os tabuleiros lado a lado
void printBothBoards(int ship_board[ROW][COLUMN], char attack_board[ROW][COLUMN])
{
    printf("\n=========== SEUS NAVIOS ===========         =========== SEUS ATAQUES ===========\n\n");

    // Cabeçalhos
    printf("      "); // Espaço a mais antes das letras
    for (int column = 0; column < COLUMN; column++)
    {
        printf("%c  ", nameColumn[column]);
    }
    printf("       ");   // Espaço maior entre tabuleiros
    printf("         "); // Espaço a mais antes das letras
    for (int column = 0; column < COLUMN; column++)
    {
        printf("%c  ", nameColumn[column]);
    }
    printf("\n");
    printf("\n"); // Linha em branco após o cabeçalho

    // Linhas dos tabuleiros
    for (int row = 0; row < ROW; row++)
    {
        // Tabuleiro de navios
        printf("%2d   ", row + 1); // Espaço a mais após o número da linha
        for (int column = 0; column < COLUMN; column++)
        {
            int value = ship_board[row][column];
            if (value == 0)
            {
                printf(BLUE " ~ " RESET_COLOR); // Água em azul
            }
            else if (value > 0)
            {
                // Navios intactos com cores específicas
                switch (value)
                {
                case 1:
                    printf(GREEN " %d " RESET_COLOR, value);
                    break; // Destroyer verde
                case 2:
                    printf(YELLOW " %d " RESET_COLOR, value);
                    break; // Cruzador amarelo
                case 3:
                    printf(MAGENTA " %d " RESET_COLOR, value);
                    break; // Battleship magenta
                case 4:
                    printf(CYAN " %d " RESET_COLOR, value);
                    break; // Porta-aviões ciano
                default:
                    printf(" %d ", value);
                    break;
                }
            }
            else // value < 0
            {
                printf(RED BOLD " X " RESET_COLOR); // Navio atingido em vermelho negrito
            }
        }

        printf("           "); // Espaço maior entre tabuleiros

        // Tabuleiro de ataques
        printf("%2d   ", row + 1); // Espaço a mais após o número da linha
        for (int column = 0; column < COLUMN; column++)
        {
            char symbol = attack_board[row][column];
            switch (symbol)
            {
            case UNKNOWN: // '~' - Não atacado
                printf(BLUE " %c " RESET_COLOR, symbol);
                break;
            case HIT: // 'X' - Acerto
                printf(BRIGHT_GREEN BOLD " %c " RESET_COLOR, symbol);
                break;
            case MISS: // 'O' - Erro (água)
                printf(WHITE " %c " RESET_COLOR, symbol);
                break;
            default:
                printf(" %c ", symbol);
                break;
            }
        }
        printf("\n");
    }

    printf("\nNavios: " BLUE "~ = Água" RESET_COLOR " | " GREEN "1" RESET_COLOR "/" YELLOW "2" RESET_COLOR "/" MAGENTA "3" RESET_COLOR "/" CYAN "4" RESET_COLOR " = Navios | " RED "X = Atingido" RESET_COLOR "      ");
    printf("Ataques: " BLUE "~ = Não atacado" RESET_COLOR " | " BRIGHT_GREEN "X = Acerto" RESET_COLOR " | " WHITE "O = Água" RESET_COLOR "\n\n");
}

// Menu de tipos de ataque
int attackMenu(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN])
{
    int attack_type;
    int row, column;
    char position[10]; // Buffer para entrada no formato "5B"
    int result = 0;

    printf("\n ========= MENU DE ATAQUES =========\n\n");
    printAttackBoard(attack_board);

    printf("╔═ Escolha o tipo de ataque:\n");
    printf("║\n");
    printf("╠═ 1 - Ataque Simples --- (1 posição)\n");
    printf("╠═ 2 - Ataque em Cone --- (triângulo para baixo)\n");
    printf("╠═ 3 - Ataque Octaedro -- (losango - 5 posições)\n");
    printf("╠═ 4 - Ataque em Cruz --- (cruz estendida - 7 posições)\n");
    printf("╠═ 5 - Ataque Circular -- (3x3 ao redor)\n");
    printf("╠═ 0 - Voltar ao menu principal\n");
    printf("║\n");
    printf("╚════► ");
    scanf("%d", &attack_type);

    if (attack_type == 0)
    {
        return 0; // Voltar ao menu principal
    }

    if (attack_type < 1 || attack_type > 5)
    {
        printf("\nTipo de ataque inválido!\n");
        return -1;
    }

    // Solicitar coordenadas para o ataque no novo formato
    printf("\n╔═ Digite a posição do ataque (ex: 5B, 10A, 3F):\n");
    printf("╚════► ");
    fflush(stdout); // ADICIONADO: Cursor pisca esperando coordenadas de ataque
    scanf("%s", position);

    // Converte a entrada para linha e coluna
    if (!parsePosition(position, &row, &column))
    {
        printf("\nDica: Digite linha seguida da coluna, como 5B, 10A, etc.\n");
        return -1;
    }

    // Executa o tipo de ataque escolhido
    switch (attack_type)
    {
    case 1: // Ataque simples
        printf("\nAtacando posição %c%d...\n", nameColumn[column], row + 1);
        result = performAttack(target_board, attack_board, row, column);
        break;

    case 2: // Ataque em cone
        result = performConeAttack(target_board, attack_board, row, column);
        break;

    case 3: // Ataque octaedro
        result = performOctahedronAttack(target_board, attack_board, row, column);
        break;

    case 4: // Ataque em cruz
        result = performCrossAttack(target_board, attack_board, row, column);
        break;

    case 5: // Ataque circular
        result = performCircleAttack(target_board, attack_board, row, column);
        break;
    }

    // Mostra o tabuleiro atualizado
    printf("\n");
    printAttackBoard(attack_board);

    return result;
}







// Função para posicionar navio de forma interativa (elimina repetição de código)

int positionShipInteractive(int board[ROW][COLUMN], int orientation,
                            int *positioned_destroyer, int *positioned_cruiser,
                            int *positioned_battleship, int *positioned_aircraft_carrier)
{
    int row, column;
    int ship_type = 0, ship_size = 0, ship_id = 0;

    // Loop até conseguir selecionar um navio válido
    do
    {
        ship_size = 0; // Reset para controlar o loop

        printBoard(board);
        printf("╔═Qual navio deseja posicionar?\n");
        printf("║\n");
        printf("╠═ 1 - Destroyer --------- Navio de 2 casas (restam: %d)\n", 2 - *positioned_destroyer);
        printf("╠═ 2 - Cruzador ---------- Navio de 3 casas (restam: %d)\n", 2 - *positioned_cruiser);
        printf("╠═ 3 - Navio de guerra --- Navio de 4 casas (restam: %d)\n", 1 - *positioned_battleship);
        printf("╠═ 4 - Porta-avioes ------ Navio de 5 casas (restam: %d)\n", 1 - *positioned_aircraft_carrier);
        printf("╠═ 0 - Menu anterior\n");
        printf("║\n");
        printf("╚════► ");
        scanf("%d", &ship_type);

        // Permite cancelar e voltar ao menu anterior
        if (ship_type == 0)
        {
            return 0;
        }

        // Define tamanho, ID e verifica limites
        switch (ship_type)
        {
        case 1: // Destroyer
            if (*positioned_destroyer >= 2)
            {
                printf("Erro: Você já posicionou todos os destroyers!\n");
                printf("Pressione Enter para escolher outro navio...");
                getchar(); // Limpa buffer
                getchar(); // Espera Enter
                break;     // Volta ao loop para escolher outro navio
            }
            ship_size = 2;
            ship_id = 1;
            break;
        case 2: // Cruzador
            if (*positioned_cruiser >= 2)
            {
                printf("Erro: Você já posicionou todos os cruzadores!\n");
                printf("Pressione Enter para escolher outro navio...");
                getchar(); // Limpa buffer
                getchar(); // Espera Enter
                break;
            }
            ship_size = 3;
            ship_id = 2;
            break;
        case 3: // Navio de guerra
            if (*positioned_battleship >= 1)
            {
                printf("Erro: Você já posicionou o navio de guerra!\n");
                printf("Pressione Enter para escolher outro navio...");
                getchar();
                getchar();
                break;
            }
            ship_size = 4;
            ship_id = 3;
            break;
        case 4: // Porta-aviões
            if (*positioned_aircraft_carrier >= 1)
            {
                printf("Erro: Você já posicionou o porta-aviões!\n");
                printf("Pressione Enter para escolher outro navio...");
                getchar();
                getchar();
                break;
            }
            ship_size = 5;
            ship_id = 4;
            break;
        default:
            printf("Erro: Navio inválido! Use números de 1 a 4.\n");
            printf("Pressione Enter para tentar novamente...");
            getchar();
            getchar();
            break;
        }

    } while (ship_size == 0); // Repete até conseguir um navio válido

    // Solicita as coordenadas iniciais
    const char *orientations[] = {"vertical", "horizontal", "diagonal crescente", "diagonal decrescente"};
    printf("╔═ O navio será posicionado na orientação %s.\n", orientations[orientation - 1]);
    printf("║  Digite as coordenadas iniciais do navio (tamanho %d):\n", ship_size);
    printf("║\n");
    printf("╚════► ");
    row = getValidInteger("Linha (1-10): ", 1, ROW); // Usa função robusta

    row--; // Converte para índice 0-based
    printf("Coluna (A-J ou a-j): ");
    char col_char;
    scanf(" %c", &col_char);
    col_char = toupper(col_char);
    column = col_char - 'A';

    if (column < 0 || column >= COLUMN)
    {
        printf("Erro: Coluna inválida! Use letras de A a J.\n");
        return 0;
    }

    int ship_temp[ship_size][2];

    // Gera as posições do navio baseado na orientação
    for (int i = 0; i < ship_size; i++)
    {
        switch (orientation)
        {
        case 1: // Vertical
            ship_temp[i][0] = row + i;
            ship_temp[i][1] = column;
            break;
        case 2: // Horizontal
            ship_temp[i][0] = row;
            ship_temp[i][1] = column + i;
            break;
        case 3: // Diagonal crescente
            ship_temp[i][0] = row - i;
            ship_temp[i][1] = column + i;
            break;
        case 4: // Diagonal decrescente
            ship_temp[i][0] = row + i;
            ship_temp[i][1] = column + i;
            break;
        }
    }

    // Tenta posicionar o navio
    printf("\nTentando posicionar navio na posição %c%d...\n", col_char, row + 1);
    if (placeShip(board, ship_temp, ship_size, ship_id))
    {
        printf("Navio posicionado com sucesso!\n");

        // Incrementa o contador do navio posicionado
        switch (ship_type)
        {
        case 1:
            (*positioned_destroyer)++;
            break;
        case 2:
            (*positioned_cruiser)++;
            break;
        case 3:
            (*positioned_battleship)++;
            break;
        case 4:
            (*positioned_aircraft_carrier)++;
            break;
        }
        return 1; 
    }
    else
    {
        printf("Não foi possível posicionar o navio nesta posição!\n");
        printf("Verifique se há espaço suficiente e se não há sobreposição.\n");
        printf("Você pode tentar novamente!\n");
        return 0;
    }
}
