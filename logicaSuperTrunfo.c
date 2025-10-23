#include <stdio.h>
#include <string.h>

// Definição da estrutura para representar uma carta do Super Trunfo
typedef struct {
    char estado[50];
    char codigo_carta[50];
    char nome_cidade[100];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
    float super_poder;
} CartaSuperTrunfo;

// Função para calcular o Super Poder
float calcularSuperPoder(CartaSuperTrunfo *carta) {
    float inverso_densidade_populacional = 0.0;
    if (carta->densidade_populacional > 0) {
        inverso_densidade_populacional = 1.0 / carta->densidade_populacional;
    }
    // A fórmula do super poder foi ajustada para evitar valores muito grandes
    return (float)carta->populacao / 1000000 + carta->area + carta->pib + carta->pontos_turisticos + carta->pib_per_capita / 10000 + inverso_densidade_populacional * 100;
}

// Limpa o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler os dados de uma carta
void ler_carta(CartaSuperTrunfo *carta, int numero_carta) {
    printf("--- ENTRADA DE DADOS CARTA %d ---\n", numero_carta);
    printf("Digite o codigo da carta: ");
    fgets(carta->codigo_carta, sizeof(carta->codigo_carta), stdin);
    carta->codigo_carta[strcspn(carta->codigo_carta, "\n")] = 0;

    printf("Digite o estado: ");
    fgets(carta->estado, sizeof(carta->estado), stdin);
    carta->estado[strcspn(carta->estado, "\n")] = 0;

    printf("Digite o nome da cidade: ");
    fgets(carta->nome_cidade, sizeof(carta->nome_cidade), stdin);
    carta->nome_cidade[strcspn(carta->nome_cidade, "\n")] = 0;

    printf("Qual a populacao? ");
    scanf("%d", &carta->populacao);
    printf("Area da cidade (em km²): ");
    scanf("%f", &carta->area);
    printf("Qual o PIB da cidade (em bilhoes)? ");
    scanf("%f", &carta->pib);
    printf("Quantos pontos turisticos: ");
    scanf("%d", &carta->pontos_turisticos);
    limpar_buffer();
}

// Função para exibir uma carta
void exibir_carta(CartaSuperTrunfo carta) {
    printf("\n--- Super Trunfo - %s (%s) ---\n", carta.nome_cidade, carta.estado);
    printf("Codigo da Carta: %s\n", carta.codigo_carta);
    printf("Populacao: %d\n", carta.populacao);
    printf("Area: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhoes de reais\n", carta.pib);
    printf("Pontos Turisticos: %d\n", carta.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidade_populacional);
    printf("PIB per Capita: %.2f reais\n", carta.pib_per_capita);
    printf("Super Poder: %.2f\n", carta.super_poder);
}

// Função para exibir o resultado da comparação
void exibir_resultado_comparacao(CartaSuperTrunfo carta1, CartaSuperTrunfo carta2, const char* atributo, float valor1, float valor2) {
    printf("\n--- Resultado da Batalha ---\n");
    printf("Atributo de comparacao: %s\n", atributo);
    printf("-----------------------------------\n");
    printf("Carta 1 (%s): %.2f\n", carta1.nome_cidade, valor1);
    printf("Carta 2 (%s): %.2f\n", carta2.nome_cidade, valor2);

    if (valor1 > valor2) {
        printf("\nResultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
    } else if (valor2 > valor1) {
        printf("\nResultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
    } else {
        printf("\nResultado: Empate!\n");
    }
    printf("-----------------------------------\n");
}

int main() {
    CartaSuperTrunfo carta1, carta2;
    int escolha;

    // --- ENTRADA DE DADOS E CÁLCULOS ---
    ler_carta(&carta1, 1);
    ler_carta(&carta2, 2);

    carta1.densidade_populacional = (carta1.area > 0) ? (float)carta1.populacao / carta1.area : 0;
    carta1.pib_per_capita = (carta1.populacao > 0) ? (carta1.pib * 1000000000) / carta1.populacao : 0;
    carta1.super_poder = calcularSuperPoder(&carta1);

    carta2.densidade_populacional = (carta2.area > 0) ? (float)carta2.populacao / carta2.area : 0;
    carta2.pib_per_capita = (carta2.populacao > 0) ? (carta2.pib * 1000000000) / carta2.populacao : 0;
    carta2.super_poder = calcularSuperPoder(&carta2);

    // --- MENU E COMPARAÇÃO (EXECUÇÃO ÚNICA) ---
    printf("\n--- Exibicao das Cartas ---\n");
    exibir_carta(carta1);
    exibir_carta(carta2);

    printf("\n--- Super Trunfo: Escolha o Atributo ---\n");
    printf("1. Populacao\n");
    printf("2. Area\n");
    printf("3. PIB\n");
    printf("4. Numero de Pontos Turisticos\n");
    printf("5. Densidade Demografica (menor valor vence)\n");
    printf("6. PIB per Capita\n");
    printf("7. Super Poder\n");
    printf("8. Sair (Encerrar o programa)\n");
    printf("Digite sua opcao: ");
    scanf("%d", &escolha);
    limpar_buffer();

    switch (escolha) {
        case 1:
            exibir_resultado_comparacao(carta1, carta2, "Populacao", (float)carta1.populacao, (float)carta2.populacao);
            break;
        case 2:
            exibir_resultado_comparacao(carta1, carta2, "Area", carta1.area, carta2.area);
            break;
        case 3:
            exibir_resultado_comparacao(carta1, carta2, "PIB", carta1.pib, carta2.pib);
            break;
        case 4:
            exibir_resultado_comparacao(carta1, carta2, "Pontos Turisticos", (float)carta1.pontos_turisticos, (float)carta2.pontos_turisticos);
            break;
        case 5: { // Densidade: menor valor vence
            printf("\n--- Resultado da Batalha ---\n");
            printf("Atributo de comparacao: Densidade Populacional\n");
            printf("-----------------------------------\n");
            printf("Carta 1 (%s): %.2f hab/km²\n", carta1.nome_cidade, carta1.densidade_populacional);
            printf("Carta 2 (%s): %.2f hab/km²\n", carta2.nome_cidade, carta2.densidade_populacional);
            if (carta1.densidade_populacional < carta2.densidade_populacional) {
                printf("\nResultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
            } else if (carta2.densidade_populacional < carta1.densidade_populacional) {
                printf("\nResultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
            } else {
                printf("\nResultado: Empate!\n");
            }
            printf("-----------------------------------\n");
            break;
        }
        case 6:
            exibir_resultado_comparacao(carta1, carta2, "PIB per Capita", carta1.pib_per_capita, carta2.pib_per_capita);
            break;
        case 7:
            exibir_resultado_comparacao(carta1, carta2, "Super Poder", carta1.super_poder, carta2.super_poder);
            break;
        case 8:
            printf("\nSaindo do jogo. Ate a proxima!\n");
            break;
        default:
            printf("\nOpcao invalida! O programa sera encerrado.\n");
            break;
    }

    return 0;
}