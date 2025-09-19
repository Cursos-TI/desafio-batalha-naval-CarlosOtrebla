#include <stdio.h>
#include <stdlib.h>

void inicializar_matriz(int matriz[10][10]) {
    // Inicializar toda a matriz com zeros
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matriz[i][j] = 0;
        }
    }
}

// Ataque em cone
void ataque_cone(int matriz[10][10], int alvo[2]) {
    int linha_alvo = alvo[0];
    int coluna_alvo = alvo[1];
    
    // Verificar se o alvo está dentro dos limites da matriz
    if (linha_alvo < 0 || linha_alvo >= 10 || coluna_alvo < 0 || coluna_alvo >= 10) {
        printf("ERRO: Coordenada alvo fora dos limites da matriz!\n");
        return;
    }
    
    printf("=== ATAQUE EM CONE REALIZADO ===\n");
    printf("Alvo: linha %d, coluna %d\n\n", linha_alvo, coluna_alvo);
    
    // Percorrer toda a matriz com condição matemática para formar o cone
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Condição para formar o triângulo/cone:
            // - Deve estar na linha do alvo ou até 2 linhas abaixo
            // - A distância horizontal deve ser <= distância vertical do alvo
            // - Fórmula: abs(j - coluna_alvo) <= (i - linha_alvo)
            
            if (i >= linha_alvo && i <= linha_alvo + 2 && abs(j - coluna_alvo) <= (i - linha_alvo)) {
                matriz[i][j] = 3;
            }
        }
    }
}

// Sua implementação do ataque em cruz (adaptada)
void crossAtack(int matriz[10][10], int alvo[2]) {
    int linha_alvo = alvo[0];
    int coluna_alvo = alvo[1];
    
    printf("=== ATAQUE EM CRUZ REALIZADO ===\n");
    printf("Alvo: linha %d, coluna %d\n\n", linha_alvo, coluna_alvo);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Linha horizontal ou vertical passando pelo alvo
            if ((i >= linha_alvo - 2 && i <= linha_alvo + 2 && j == coluna_alvo) || 
                (j >= coluna_alvo - 2 && j <= coluna_alvo + 2 && i == linha_alvo)) {
                matriz[i][j] = 3;
            }
        }
    }
}

// Ataque em círculo/explosão usando for
void ataque_circulo(int matriz[10][10], int alvo[2], int raio) {
    int linha_alvo = alvo[0];
    int coluna_alvo = alvo[1];
    
    printf("=== ATAQUE EM CÍRCULO REALIZADO ===\n");
    printf("Alvo: linha %d, coluna %d, Raio: %d\n\n", linha_alvo, coluna_alvo, raio);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Calcular distância usando teorema de Pitágoras
            int distancia_quadrada = (i - linha_alvo) * (i - linha_alvo) + 
                                   (j - coluna_alvo) * (j - coluna_alvo);
            
            // Se a distância for menor ou igual ao raio, atingir a posição
            if (distancia_quadrada <= raio * raio) {
                matriz[i][j] = 3;
            }
        }
    }
}

// Versão alternativa - ataque em área 3x3
void ataque_area_3x3(int matriz[10][10], int alvo[2]) {
    int linha_alvo = alvo[0];
    int coluna_alvo = alvo[1];
    
    if (linha_alvo < 0 || linha_alvo >= 10 || coluna_alvo < 0 || coluna_alvo >= 10) {
        printf("ERRO: Coordenada alvo fora dos limites da matriz!\n");
        return;
    }
    
    printf("=== ATAQUE EM ÁREA 3x3 REALIZADO ===\n");
    printf("Alvo: linha %d, coluna %d\n\n", linha_alvo, coluna_alvo);
    
    // Preencher área 3x3 centrada no alvo
    for (int i = linha_alvo - 1; i <= linha_alvo + 1; i++) {
        for (int j = coluna_alvo - 1; j <= coluna_alvo + 1; j++) {
            // Verificar se está dentro dos limites da matriz
            if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                matriz[i][j] = 3;
            }
        }
    }
}

void imprimir_matriz(int matriz[10][10]) {
    printf("Estado atual da matriz:\n");
    
    // Cabeçalho das colunas
    printf("   ");
    for (int j = 0; j < 10; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Matriz com índices das linhas
    for (int i = 0; i < 10; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] == 3) {
                printf(" X ");  // Mostrar X para áreas atingidas
            } else {
                printf(" . ");  // Mostrar ponto para áreas não atingidas
            }
        }
        printf("\n");
    }
    printf("\n");
}

void contar_areas_atingidas(int matriz[10][10]) {
    int contador = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] == 3) {
                contador++;
            }
        }
    }
    printf("Total de áreas atingidas: %d\n\n", contador);
}

int main() {
    int matriz[10][10];
    int alvo[2] = {3, 4}; // Coordenada do alvo (linha, coluna)
    
    printf("=== SIMULADOR DE BATALHA NAVAL ===\n\n");
    
    // Inicializar matriz
    inicializar_matriz(matriz);
    
    // Realizar ataque em cone
    ataque_cone(matriz, alvo);
    
    // Mostrar resultado
    imprimir_matriz(matriz);
    contar_areas_atingidas(matriz);
    
    // Exemplo com diferentes tipos de ataque
    printf("=== TESTANDO OUTROS PADRÕES DE ATAQUE ===\n\n");
    
    // Teste com ataque em cruz (sua implementação)
    inicializar_matriz(matriz);
    int alvo2[2] = {5, 5};
    crossAtack(matriz, alvo2);
    imprimir_matriz(matriz);
    
    // Teste com ataque em círculo
    inicializar_matriz(matriz);
    int alvo3[2] = {7, 2};
    ataque_circulo(matriz, alvo3, 2); // Raio 2
    imprimir_matriz(matriz);
    
    return 0;
}