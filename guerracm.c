//Codigo completo nível novato:
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define NUM_TERRITORIOS 5
#define TAM_MAX 50

// Definição da estrutura de dados para um território
typedef struct {
    char nome[TAM_MAX];
    char corExercito[TAM_MAX];
    int tropas;
} Territorio;

// Função para limpar o buffer do teclado
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio mapa[], int tamanho) {
    printf("=== Cadastro de Territórios ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, TAM_MAX, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';  // Remove o \n do final

        printf("Cor do Exército: ");
        fgets(mapa[i].corExercito, TAM_MAX, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada(); // Limpa o buffer para evitar problemas nas próximas leituras
    }
}

// Função para exibir o mapa
void exibirMapa(const Territorio mapa[], int tamanho) {
    printf("\n=== Estado Atual do Mapa ===\n");
    printf("%-20s | %-15s | %-6s\n", "Território", "Cor do Exército", "Tropas");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%-20s | %-15s | %-6d\n", mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
}

// Função principal
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Territorio mapa[NUM_TERRITORIOS]; // Vetor estático de 5 territórios

    cadastrarTerritorios(mapa, NUM_TERRITORIOS);
    exibirMapa(mapa, NUM_TERRITORIOS);

    return 0;
}


