//territorio2.c
// Programa para gerenciar informações de territórios usando struct em C
#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Essa estrutura agrupa informações relacionadas a um território
typedef struct {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército
    int tropas;        // Quantidade de tropas no território
} Territorio;

//-- Função para limpar o buffer de entrada  ( Uma Prevenção contra o buffer overflow) ----------------------------------------------
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int main() {
    // Declaração de um vetor de 5 territórios
    Territorio territorios[5];
    
    // Entrada de dados
    printf("=== Cadastro de Territórios ===\n\n");
    
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        
        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o '\n'
        
        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada(); // Limpa o buffer para evitar problemas nas próximas leituras
        getchar(); // consome o '\n' deixado pelo scanf
        
        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=== Territórios Cadastrados ===\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("--------------------------\n");
    }

    return 0; // Fim do programa

}


// FIM DO CÓDIGO NÍVEL NOVATO
//eXemplo de execução:
/*=== Cadastro de Territórios ===

Território 1
Nome: Brasil
Cor do Exército: Verde
Número de Tropas: 8

Território 2
Nome: Argentina
Cor do Exército: Azul
Número de Tropas: 5

Território 3
Nome: Chile
Cor do Exército: Vermelho
Número de Tropas: 6

Território 4
Nome: Peru
Cor do Exército: Amarelo
Número de Tropas: 7

Território 5
Nome: Uruguai
Cor do Exército: Verde
Número de Tropas: 4

=== Estado Atual do Mapa ===
Território           | Cor do Exército | Tropas
--------------------------------------------------
Brasil               | Verde           | 8
Argentina            | Azul            | 5
Chile                | Vermelho        | 6
Peru                 | Amarelo         | 7
Uruguai              | Verde           | 4
       */
