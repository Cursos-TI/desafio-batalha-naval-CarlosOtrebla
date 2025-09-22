#include "battleShip.h"

// Definindo o nome das colunas

char nameColumn[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

// Definindo os tipos de navios

int aircraftCarrier[5];
int battleship[4];
int submarine[3];
int cruiser[3];
int destroyer[2];

// ~~~~~~~~~~~~~~~~~~~~funções~~~~~~~~~~~~~~~~~~~~~

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
    do {
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
        if (ship_type == 0) {
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
                break; // Volta ao loop para escolher outro navio
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
                break; // Volta ao loop para escolher outro navio
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
                break; // Volta ao loop para escolher outro navio
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
                break; // Volta ao loop para escolher outro navio
            }
            ship_size = 5;
            ship_id = 4;
            break;
        default:
            printf("Erro: Navio inválido! Use números de 1 a 4.\n");
            printf("Pressione Enter para tentar novamente...");
            getchar(); // Limpa buffer
            getchar(); // Espera Enter
            break; // Volta ao loop
        }
        
    } while (ship_size == 0); // Repete até conseguir um navio válido

    // Solicita as coordenadas iniciais
    const char* orientations[] = {"vertical", "horizontal", "diagonal crescente", "diagonal decrescente"};
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

