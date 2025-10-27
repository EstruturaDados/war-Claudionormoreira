//==================== NÍVEL MESTRES - MISSÕES E BATALHAS ====================
// Arquivo: nivelmestres.c
// Descrição: Programa para gerenciar missões estratégicas e batalhas entre territórios em C
//Bibliotecas usadas:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== ESTRUTURAS ====================
// Definição da struct Territorio:

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ==================== PROTÓTIPOS ====================
// Declaração das funções usadas no programa
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(char* missao);
void atacar(Territorio* atacante, Territorio* defensor);
void exibirMapa(Territorio* mapa, int tamanho);
void liberarMemoria(char** missoesJogadores, int qtdJogadores, Territorio* mapa);

// ==================== FUNÇÕES ====================

// Sorteia uma missão e copia para o destino (usando strcpy)
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missão do jogador
void exibirMissao(char* missao) {
    printf("\n=== Sua Missão Estratégica ===\n");
    printf("%s\n", missao);
    printf("==============================\n\n");
}

// Simula uma batalha simples entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque inválido! O território pertence ao mesmo jogador.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("%s (A: %d) ataca %s (D: %d)\n", 
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Vitória do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas / 2;
    } else {
        printf("Defensor resiste! Atacante perde uma tropa.\n");
        atacante->tropas--;
    }
}

// Verifica se uma missão foi cumprida (simulação simples)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "Conquistar 3 territorios seguidos")) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                consecutivos++;
                if (consecutivos >= 3)
                    return 1;
            } else {
                consecutivos = 0;
            }
        }
    } 
    else if (strstr(missao, "Eliminar tropas vermelhas")) {
        int existeVermelho = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0)
                existeVermelho = 1;
        }
        return !existeVermelho;
    }

    // Missão não cumprida
    return 0;
}

   //Exibe o estado atual do mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %-15s | Cor: %-8s | Tropas: %d\n", 
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("==================\n");
}

// Libera memória alocada dinamicamente
void liberarMemoria(char** missoesJogadores, int qtdJogadores, Territorio* mapa) {
    for (int i = 0; i < qtdJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
    free(mapa);
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    srand(time(NULL));

    int qtdJogadores = 2;
    int qtdTerritorios = 5;

    // Vetor de missões disponíveis
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar tropas vermelhas",
        "Dominar todos os territorios azuis",
        "Manter pelo menos 2 territorios com 5 tropas",
        "Ser o ultimo jogador restante"
    };
    int totalMissoes = 5;

    // Aloca vetor de missões dos jogadores
    char** missoesJogadores = (char**) malloc(qtdJogadores * sizeof(char*));
    for (int i = 0; i < qtdJogadores; i++) {
        missoesJogadores[i] = (char*) malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
    }

    // Exemplo de mapa
    Territorio* mapa = (Territorio*) malloc(qtdTerritorios * sizeof(Territorio));

    strcpy(mapa[0].nome, "Brasil");    strcpy(mapa[0].cor, "Azul");     mapa[0].tropas = 5;
    strcpy(mapa[1].nome, "Uruguai"); strcpy(mapa[1].cor, "Azul");     mapa[1].tropas = 8;
    strcpy(mapa[2].nome, "China");     strcpy(mapa[2].cor, "Vermelho"); mapa[2].tropas = 6;
    strcpy(mapa[3].nome, "Russia");      strcpy(mapa[3].cor, "Vermelho"); mapa[3].tropas = 2;
    strcpy(mapa[4].nome, "Ucrânia");  strcpy(mapa[4].cor, "Azul");     mapa[4].tropas = 4;

    // Exibe missões iniciais
    for (int i = 0; i < qtdJogadores; i++) {
        printf("Jogador %d:", i + 1);
        exibirMissao(missoesJogadores[i]);
    }

    // Exibe o mapa inicial
    exibirMapa(mapa, qtdTerritorios);

    // Simula rodadas
    printf("\n--- Iniciando rodada de ataque ---\n");
    atacar(&mapa[1], &mapa[2]); // Azul ataca Vermelho

    exibirMapa(mapa, qtdTerritorios);

    // Verifica se algum jogador cumpriu sua missão
    for (int i = 0; i < qtdJogadores; i++) {
        if (verificarMissao(missoesJogadores[i], mapa, qtdTerritorios)) {
            printf("\n🎉 Jogador %d venceu! Cumpriu a missão: %s\n", i + 1, missoesJogadores[i]);
            liberarMemoria(missoesJogadores, qtdJogadores, mapa);
            return 0;
        }
    }

    printf("\nNenhum jogador venceu ainda.\n");

    liberarMemoria(missoesJogadores, qtdJogadores, mapa);
    return 0;
}
