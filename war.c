// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
// DESAFIO NÍVEL NOVATO - JOGO WAR  - Cadastro de Territórios
// Baseado na estrutura de códigos do CADASTRO DA BIBLIOTECA
// visto nas video aulas de Estruturas de dados.
// O código abaixo serve para cadastrar 5 territórios com o nome,
// cor e quantidade de tropas.Ao final, exibe os dados cadastrados.
// 
// Carlos Toni - 27/09/2025
 

#include <stdio.h>
#include <string.h>

// --- Definição da struct Territorio ---
// Representa um território no jogo WAR.
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército associado ao território
    int tropas;      // Quantidade de tropas no território
};

int main() {
    
    struct Territorio territorios[5]; // Aqui é o Vetor para armazenar os 5 territórios

    // Cadastro das informações
    printf("=== Cadastro de Territórios do WAR (iniciante) ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d\n", i + 1);

        // Lê o nome do território
        printf("Digite o nome do território: "); 
        scanf(" %[^\n]", territorios[i].nome); // lê string com espaços

        // Lê a cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %s", territorios[i].cor); // lê string simples sem espaços

        // Lê a quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("-------------------------------------------\n");
    }

    // Mostra as informações inseridas
    printf("\n=== Territórios cadastrados ===\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-------------------------------------------\n");
    }

    return 0; // Fim
}
