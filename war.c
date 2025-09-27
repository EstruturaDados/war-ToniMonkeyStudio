// DESAFIO NÍVEL MESTRE - JOGO WAR - Cadastro + ataque + missões
// Baseado na estrutura de códigos do CADASTRO DA BIBLIOTECA
// visto nas video aulas de Estruturas de dados.
// 
// O código abaixo agora:
// 
// - Cadastra territórios (dinamicamente)
// - Ataque entre territórios
// - Missões para cada jogador
// - Modularização, uso de ponteiros e alocação dinâmica
//
// Carlos Toni - 27/09/2025


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Definição da struct Territorio ---
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Função para cadastrar territórios ---
void cadastrarTerritorios(struct Territorio* mapa, int n) {
    printf("\n=== Cadastro de Territórios ===\n\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("---------------------------------\n");
    }
}

// --- Função para exibir territórios ---
void exibirTerritorios(struct Territorio* mapa, int n) {
    printf("\n=== Lista de Territórios ===\n\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------------\n");
    }
}

// --- Função de ataque ---
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Não é possível atacar um território da mesma cor!\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("\n❌ O atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    printf("\n⚔️ Batalha: %s (%s) ataca %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("🎲 Dado Atacante: %d | Dado Defensor: %d\n",
           dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = defensor->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1;
    } else {
        printf("❌ O defensor resistiu! Atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// --- Função para liberar memória ---
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

// --- Função para sortear missão ---
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// --- Função para verificar missão (versão inicial) ---
int verificarMissao(char* missao, struct Territorio* mapa, int n) {
    // Exemplo simples: missão "Conquistar 3 territórios da mesma cor"
    if (strcmp(missao, "Conquistar 3 territórios da mesma cor") == 0) {
        int cont = 0;
        char corRef[10] = "";
        for (int i = 0; i < n; i++) {
            if (i == 0) strcpy(corRef, mapa[i].cor);
            if (strcmp(mapa[i].cor, corRef) == 0) cont++;
        }
        if (cont >= 3) return 1;
    }
    // Outras missões podem ser implementadas de forma similar
    return 0;
}

int main() {
    srand(time(NULL));

    int n, opcao;
    struct Territorio* mapa = NULL;

    printf("=== WAR Estratégico ===\n");
    printf("Digite o número de territórios do mapa: ");
    scanf("%d", &n);

    // Alocação dinâmica
    mapa = (struct Territorio*) calloc(n, sizeof(struct Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro de territórios
    cadastrarTerritorios(mapa, n);

    // --- Missões ---
    int totalMissoes = 5;
    char* missoes[] = {
        "Conquistar 3 territórios da mesma cor",
        "Eliminar todas as tropas da cor vermelha",
        "Ter pelo menos 2 territórios com mais de 5 tropas",
        "Controlar territórios 0 e 1",
        "Conquistar territórios consecutivos 2,3,4"
    };

    // Cada jogador terá uma missão dinâmica
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    if (!missaoJogador) {
        printf("Erro ao alocar memória para a missão!\n");
        free(mapa);
        return 1;
    }
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("\nSua missão: %s\n", missaoJogador);

    // Menu principal
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Listar territórios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirTerritorios(mapa, n);
                break;

            case 2: {
                int idAtacante, idDefensor;
                exibirTerritorios(mapa, n);
                printf("Escolha o ID do território atacante: ");
                scanf("%d", &idAtacante);
                printf("Escolha o ID do território defensor: ");
                scanf("%d", &idDefensor);

                if (idAtacante >= 0 && idAtacante < n &&
                    idDefensor >= 0 && idDefensor < n &&
                    idAtacante != idDefensor) {

                    atacar(&mapa[idAtacante], &mapa[idDefensor]);

                    // Verifica missão
                    if (verificarMissao(missaoJogador, mapa, n)) {
                        printf("\n🎉 Missão cumprida! Você venceu!\n");
                        opcao = 0; // encerra o jogo
                    }

                } else {
                    printf("\n❌ IDs inválidos!\n");
                }
                break;
            }

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\n❌ Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    // Libera memória
    free(missaoJogador);
    liberarMemoria(mapa);

    return 0;
}
