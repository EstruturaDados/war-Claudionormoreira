#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =============================
// ESTRUTURA DE DADOS
// =============================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// =============================
// PROTÓTIPOS DE FUNÇÕES
// =============================
Territorio* cadastrarTerritorios(int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// =============================
// FUNÇÃO PRINCIPAL
// =============================
int main() {
    srand(time(NULL)); // garante aleatoriedade nos dados

    int n;
    printf("=====================================\n");
    printf("     JOGO DE GUERRA - PARTE1      \n");
    printf("=====================================\n");

    printf("Digite o numero de territorios no mapa: ");
    scanf("%d", &n);
    getchar(); // limpa o buffer

    Territorio* mapa = cadastrarTerritorios(n);

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirTerritorios(mapa, n);
        } 
        else if (opcao == 2) {
            exibirTerritorios(mapa, n);
            int iAtacante, iDefensor;
            printf("\nEscolha o indice do territorio atacante: ");
            scanf("%d", &iAtacante);
            printf("Escolha o indice do territorio defensor: ");
            scanf("%d", &iDefensor);

            if (iAtacante < 0 || iAtacante >= n || iDefensor < 0 || iDefensor >= n) {
                printf("Indices invalidos!\n");
                continue;
            }

            Territorio* atacante = &mapa[iAtacante];
            Territorio* defensor = &mapa[iDefensor];

            // validação de ataque (não pode atacar território da mesma cor)
            if (strcmp(atacante->cor, defensor->cor) == 0) {
                printf("Nao e possivel atacar um territorio da mesma cor!\n");
                continue;
            }

            atacar(atacante, defensor);
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}

// =============================
// FUNÇÕES AUXILIARES
// =============================

// Cadastra dinamicamente os territórios
Territorio* cadastrarTerritorios(int n) {
    Territorio* mapa = (Territorio*) calloc( n, sizeof(Territorio));
    if (mapa == NULL) { 
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    printf("\n=== Cadastro de Territorios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d:\n", i);
        printf("Nome: ");
        getchar(); // limpar buffer
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove o \n do final

        printf("Cor (ex: vermelho, azul): ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    return mapa;
}

// Exibe os territórios e seus atributos
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== Territorios ===\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %-20s | Cor: %-10s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 1) {
        printf("O territorio atacante nao tem tropas suficientes para atacar!\n");
        return;
    }

    printf("\n--- ATAQUE ---\n");
    printf("%s (%s) atacando %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu a batalha!\n");

        // atacante conquista o território
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;

    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }

    printf("\n--- Situacao apos o ataque ---\n");
    printf("Atacante: %s | Cor: %s | Tropas: %d\n",
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s | Cor: %s | Tropas: %d\n",
           defensor->nome, defensor->cor, defensor->tropas);
}

// Libera memória alocada
void liberarMemoria(Territorio* mapa) {
     printf("\nMemoria liberada com sucesso.\n");
     
     
     free(mapa);
 // Finaliza o programa
    return;
}




