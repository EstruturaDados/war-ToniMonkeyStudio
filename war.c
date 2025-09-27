// DESAFIO NÍVEL AVENTUREIRO - JOGO WAR - Cadastro + ataque
// Baseado na estrutura de códigos do CADASTRO DA BIBLIOTECA
// visto nas video aulas de Estruturas de dados.
// 
// O código abaixo agora:
// 
// - Cadastra territórios (dinamicamente)
// - Exibe territórios
// - Permite atacar de um território a outro
// - Atualiza tropas e cor do exército conforme o resultado
//
// Carlos Toni - 27/09/2025


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Definição da struct Territorio ---
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Número de tropas
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

// --- Função de ataque entre territórios ---
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Não é possível atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n❌ O atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    printf("\n⚔️ Batalha: %s (%s) ataca %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Rolagem dos dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("🎲 Dado Atacante: %d | Dado Defensor: %d\n",
           dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ O atacante venceu a batalha!\n");

        // Defensor muda de cor e perde metade das tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = defensor->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1; // pelo menos 1 tropa

    } else {
        printf("❌ O defensor resistiu! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// --- Função para liberar memória ---
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // garante aleatoriedade

    int n, opcao;
    struct Territorio* mapa = NULL;

    printf("=== WAR - Estruturado ===\n\n");
    printf("Digite o número de territórios do mapa: ");
    scanf("%d", &n);

    // Alocação dinâmica
    mapa = (struct Territorio*) calloc(n, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, n);

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
    liberarMemoria(mapa);

    return 0;
}
