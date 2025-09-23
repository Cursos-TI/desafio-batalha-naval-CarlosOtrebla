#include "battleShip.h"

// Definindo o nome das colunas

char nameColumn[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

// Tabuleiro de ataques
char attack_board[ROW][COLUMN];

// Definindo os tipos de navios

int aircraftCarrier[5];
int battleship[4];
int submarine[3];
int cruiser[3];
int destroyer[2];

//~~~~~~~~~~~~~~~~~~~Funções de ataque ~~~~~~~~~~~~~~~~~~~~~~~~

// Ataque em cone
void ataque_cone(int matriz[10][10], int alvo[2])
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
            // - Deve estar na linha do alvo ou até 2 linhas abaixo
            // - A distância horizontal deve ser <= distância vertical do alvo
            // - Fórmula: abs(j - coluna_alvo) <= (i - linha_alvo)

            if (i >= linha_alvo && i <= linha_alvo + 2 && abs(j - coluna_alvo) <= (i - linha_alvo))
            {
                matriz[i][j] = 3;
            }
        }
    }
}

// ~~~~~~~~~~~~~~~~~~~~Funções de diversas~~~~~~~~~~~~~~~~~~~~~
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
            getchar(); // Limpa buffer
            getchar(); // Espera Enter
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
            getchar(); // Limpa buffer
            getchar(); // Espera Enter
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
            getchar(); // Limpa buffer
            getchar(); // Espera Enter
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
            getchar(); // Limpa buffer
            getchar(); // Espera Enter
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
    printf(" Escolha a orientação para o navio:\n\n");
    printf(" 1 - Vertical (para baixo)\n");
    printf(" 2 - Horizontal (para direita)\n");
    printf(" 3 - Diagonal crescente\n");
    printf(" 4 - Diagonal decrescente\n");
    printf(" 0 - Cancelar\n");
    scanf("%d", &orientation);

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
    printf("\nO navio será posicionado na orientação %s.\n", orientations[orientation - 1]);
    printf("Digite as coordenadas iniciais do navio (tamanho %d):\n", ship_size);
    printf("Linha (1-%d): ", ROW);
    scanf("%d", &row);

    if (row < 1 || row > ROW)
    {
        printf("Erro: Linha inválida! Use números de 1 a %d.\n", ROW);
        return 0;
    }

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
    printf("\n🎯 Tentando posicionar navio na posição %c%d...\n", col_char, row + 1);
    if (placeShip(board, ship_temp, ship_size, ship_id))
    {
        printf("✅ Navio posicionado com sucesso!\n");

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
        getchar();
        getchar();
        return 1; // Sucesso
    }
    else
    {
        printf("❌ Não foi possível posicionar o navio nesta posição!\n");
        printf("Verifique se há espaço suficiente e se não há sobreposição.\n");
        printf("Pressione Enter para tentar novamente...");
        getchar();
        getchar();
        return 0; // Falha
    }
}

// ~~~~~~~~~~~~~~~~~~~~~ FUNÇÕES DE ATAQUE ~~~~~~~~~~~~~~~~~~~~~

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
    if (target_board[row][column] != 0) // Há um navio na posição
    {
        attack_board[row][column] = HIT; // 'X' para acerto
        printf("🎯 ACERTOU! Há um navio na posição %c%d!\n", nameColumn[column], row + 1);

        // Marca o navio como atingido no tabuleiro original
        target_board[row][column] = -target_board[row][column]; // Torna negativo para indicar hit

        return 1; // Acerto
    }
    else
    {
        attack_board[row][column] = MISS; // 'O' para erro
        printf("💧 ÁGUA! Não há navio na posição %c%d.\n", nameColumn[column], row + 1);
        return 0; // Erro (água)
    }
}

// Função para imprimir o tabuleiro de ataques
void printAttackBoard(char attack_board[ROW][COLUMN])
{
    printf("\n==== SEUS ATAQUES ====\n");
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

    printf("\nLegenda: " BLUE "~ = Não atacado" RESET_COLOR " | " BRIGHT_GREEN "X = Acerto" RESET_COLOR " | " WHITE "O = Água" RESET_COLOR "\n");
    printf("\n");
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

// Função para atacar de forma interativa
int attackInteractive(int target_board[ROW][COLUMN], char attack_board[ROW][COLUMN])
{
    int row, column;
    char col_char;

    printf("\n=== REALIZAR ATAQUE ===\n");
    printAttackBoard(attack_board);

    printf("Digite as coordenadas do ataque:\n");
    printf("Linha (1-%d): ", ROW);
    scanf("%d", &row);

    // Verifica se a linha é válida
    if (row < 1 || row > ROW)
    {
        printf("Erro: Linha inválida! Use números de 1 a %d.\n", ROW);
        return -1;
    }

    row--; // Converte para índice 0-based

    printf("Coluna (A-J ou a-j): ");
    scanf(" %c", &col_char);
    col_char = toupper(col_char);
    column = col_char - 'A';

    // Verifica se a coluna é válida
    if (column < 0 || column >= COLUMN)
    {
        printf("Erro: Coluna inválida! Use letras de A a J.\n");
        return -1;
    }

    printf("\n🎯 Atacando posição %c%d...\n", col_char, row + 1);

    // Realiza o ataque
    int result = performAttack(target_board, attack_board, row, column);

    // Mostra o resultado atualizado
    printAttackBoard(attack_board);

    return result;
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

// Função para verificar se o navio foi atingido

int isShipSunk(int board[ROW][COLUMN], int ship[][2], int ship_size, int ship_id)
{
    for (int i = 0; i < ship_size; i++)
    {
        if (board[ship[i][0]][ship[i][1]] != ship_id)
            return 0;
    }
    return 1;
}

// Função para verificar se o jogo acabou

int isGameOver(int board[ROW][COLUMN])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if (board[i][j] == 0)
                return 0;
        }
    }
    return 1;
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
        printf("Qual navio deseja posicionar?\n");
        printf("1 - Destroyer - Navio de 2 casas (restam: %d)\n", 2 - *positioned_destroyer);
        printf("2 - Cruzador - Navio de 3 casas (restam: %d)\n", 2 - *positioned_cruiser);
        printf("3 - Navio de guerra - Navio de 4 casas (restam: %d)\n", 1 - *positioned_battleship);
        printf("4 - Porta-avioes - Navio de 5 casas (restam: %d)\n", 1 - *positioned_aircraft_carrier);
        printf("0 - Voltar ao menu de orientações\n");
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
                break;     // Volta ao loop para escolher outro navio
            }
            ship_size = 3;
            ship_id = 2;
            break;
        case 3: // Navio de guerra
            if (*positioned_battleship >= 1)
            {
                printf("Erro: Você já posicionou o navio de guerra!\n");
                printf("Pressione Enter para escolher outro navio...");
                getchar(); // Limpa buffer
                getchar(); // Espera Enter
                break;     // Volta ao loop para escolher outro navio
            }
            ship_size = 4;
            ship_id = 3;
            break;
        case 4: // Porta-aviões
            if (*positioned_aircraft_carrier >= 1)
            {
                printf("Erro: Você já posicionou o porta-aviões!\n");
                printf("Pressione Enter para escolher outro navio...");
                getchar(); // Limpa buffer
                getchar(); // Espera Enter
                break;     // Volta ao loop para escolher outro navio
            }
            ship_size = 5;
            ship_id = 4;
            break;
        default:
            printf("Erro: Navio inválido! Use números de 1 a 4.\n");
            printf("Pressione Enter para tentar novamente...");
            getchar(); // Limpa buffer
            getchar(); // Espera Enter
            break;     // Volta ao loop
        }

    } while (ship_size == 0); // Repete até conseguir um navio válido

    // Solicita as coordenadas iniciais
    const char *orientations[] = {"vertical", "horizontal", "diagonal crescente", "diagonal decrescente"};
    printf("O navio será posicionado na orientação %s.\n", orientations[orientation - 1]);
    printf("Digite as coordenadas iniciais do navio (tamanho %d):\n", ship_size);
    printf("Linha (1-%d): ", ROW);
    scanf("%d", &row);

    if (row < 1 || row > ROW)
    {
        printf("Erro: Linha inválida! Use números de 1 a %d.\n", ROW);
        return 0;
    }

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
        printf("✅ Navio posicionado com sucesso!\n");

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
        return 1; // Sucesso
    }
    else
    {
        printf("❌ Não foi possível posicionar o navio nesta posição!\n");
        printf("Verifique se há espaço suficiente e se não há sobreposição.\n");
        printf("Você pode tentar novamente!\n");
        return 0; // Falha
    }
}
