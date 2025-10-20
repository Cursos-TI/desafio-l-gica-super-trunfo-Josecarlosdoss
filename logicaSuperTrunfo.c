
#include <stdio.h>
#include <string.h>

// Definir a estrutura para representar uma carta do Super Trunfo
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
    return (float)carta->populacao + carta->area + (carta->pib * 1000000000) + carta->pontos_turisticos + carta->pib_per_capita + inverso_densidade_populacional;
}

// Limpa o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler os dados de uma carta
void ler_carta(CartaSuperTrunfo *carta) {
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
    printf("Area da cidade: ");
    scanf("%f", &carta->area);
    printf("Qual o PIB da cidade (em bilhoes)? ");
    scanf("%f", &carta->pib);
    printf("Quantos pontos turisticos: ");
    scanf(" %d", &carta->pontos_turisticos);
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

int main() {
    CartaSuperTrunfo carta1, carta2;

    printf("--- ENTRADA DE DADOS CARTA 1 ---\n");
    ler_carta(&carta1);

    printf("\n--- ENTRADA DE DADOS CARTA 2 ---\n");
    ler_carta(&carta2);
    
    // Cálculos para as cartas
    carta1.densidade_populacional = (float)carta1.populacao / carta1.area;
    carta1.pib_per_capita = (carta1.pib * 1000000000) / carta1.populacao;
    carta1.super_poder = calcularSuperPoder(&carta1);

    carta2.densidade_populacional = (float)carta2.populacao / carta2.area;
    carta2.pib_per_capita = (carta2.pib * 1000000000) / carta2.populacao;
    carta2.super_poder = calcularSuperPoder(&carta2);

    // Exibição das cartas
    exibir_carta(carta1);
    exibir_carta(carta2);
    
    // --- COMPARAÇÃO DE CARTAS ---
    printf("\n--- Comparacao de Cartas ---\n");

    // Escolha o atributo para comparação (mude a string para comparar outro)
    char atributo_comparacao[] = "Super Poder"; 

    // Lógica para determinar a carta vencedora
    if (strcmp(atributo_comparacao, "Populacao") == 0) {
        printf("Atributo: Populacao\n");
        printf("Carta 1 - %s: %d\n", carta1.nome_cidade, carta1.populacao);
        printf("Carta 2 - %s: %d\n", carta2.nome_cidade, carta2.populacao);
        if (carta1.populacao > carta2.populacao) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
        } else if (carta2.populacao > carta1.populacao) {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
        } else {
            printf("Resultado: Empate!\n");
        }
    } else if (strcmp(atributo_comparacao, "Area") == 0) {
        printf("Atributo: Area\n");
        printf("Carta 1 - %s: %.2f km²\n", carta1.nome_cidade, carta1.area);
        printf("Carta 2 - %s: %.2f km²\n", carta2.nome_cidade, carta2.area);
        if (carta1.area > carta2.area) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
        } else if (carta2.area > carta1.area) {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
        } else {
            printf("Resultado: Empate!\n");
        }
    } else if (strcmp(atributo_comparacao, "PIB") == 0) {
        printf("Atributo: PIB\n");
        printf("Carta 1 - %s: %.2f bilhoes\n", carta1.nome_cidade, carta1.pib);
        printf("Carta 2 - %s: %.2f bilhoes\n", carta2.nome_cidade, carta2.pib);
        if (carta1.pib > carta2.pib) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
        } else if (carta2.pib > carta1.pib) {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
        } else {
            printf("Resultado: Empate!\n");
        }
    } else if (strcmp(atributo_comparacao, "Densidade Populacional") == 0) {
        printf("Atributo: Densidade Populacional\n");
        printf("Carta 1 - %s: %.2f hab/km²\n", carta1.nome_cidade, carta1.densidade_populacional);
        printf("Carta 2 - %s: %.2f hab/km²\n", carta2.nome_cidade, carta2.densidade_populacional);
        // Para densidade, o menor valor vence
        if (carta1.densidade_populacional < carta2.densidade_populacional) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
        } else if (carta2.densidade_populacional < carta1.densidade_populacional) {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
        } else {
            printf("Resultado: Empate!\n");
        }
    } else if (strcmp(atributo_comparacao, "PIB per capita") == 0) {
        printf("Atributo: PIB per capita\n");
        printf("Carta 1 - %s: %.2f reais\n", carta1.nome_cidade, carta1.pib_per_capita);
        printf("Carta 2 - %s: %.2f reais\n", carta2.nome_cidade, carta2.pib_per_capita);
        if (carta1.pib_per_capita > carta2.pib_per_capita) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
        } else if (carta2.pib_per_capita > carta1.pib_per_capita) {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
        } else {
            printf("Resultado: Empate!\n");
        }
    } else if (strcmp(atributo_comparacao, "Super Poder") == 0) {
        printf("Atributo: Super Poder\n");
        printf("Carta 1 - %s: %.2f\n", carta1.nome_cidade, carta1.super_poder);
        printf("Carta 2 - %s: %.2f\n", carta2.nome_cidade, carta2.super_poder);
        if (carta1.super_poder > carta2.super_poder) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
        } else if (carta2.super_poder > carta1.super_poder) {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
        } else {
            printf("Resultado: Empate!\n");
        }
    } else {
        printf("Atributo de comparacao invalido.\n");
    }

    return 0;
}
