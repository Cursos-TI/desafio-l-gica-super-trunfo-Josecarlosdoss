#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// Enum para representar os atributos
typedef enum {
    POPULACAO = 1,
    AREA,
    PIB,
    PONTOS_TURISTICOS,
    DENSIDADE_POPULACIONAL,
    PIB_PER_CAPITA,
    SUPER_PODER
} Atributo;

// Estrutura para facilitar a exibição de atributos
typedef struct {
    Atributo codigo;
    char nome[50];
} AtributoInfo;

// Array de informações sobre os atributos
AtributoInfo atributos_info[] = {
    {POPULACAO, "Populacao"},
    {AREA, "Area"},
    {PIB, "PIB"},
    {PONTOS_TURISTICOS, "Pontos Turisticos"},
    {DENSIDADE_POPULACIONAL, "Densidade Demografica"},
    {PIB_PER_CAPITA, "PIB per Capita"},
    {SUPER_PODER, "Super Poder"}
};

// Função para obter o nome do atributo a partir do código
char* getNomeAtributo(Atributo codigo) {
    for (int i = 0; i < sizeof(atributos_info) / sizeof(AtributoInfo); i++) {
        if (atributos_info[i].codigo == codigo) {
            return atributos_info[i].nome;
        }
    }
    return "Desconhecido";
}

// Função para obter o valor de um atributo de uma carta
float getValorAtributo(CartaSuperTrunfo carta, Atributo atributo) {
    switch (atributo) {
        case POPULACAO:
            return (float)carta.populacao;
        case AREA:
            return carta.area;
        case PIB:
            return carta.pib;
        case PONTOS_TURISTICOS:
            return (float)carta.pontos_turisticos;
        case DENSIDADE_POPULACIONAL:
            return carta.densidade_populacional;
        case PIB_PER_CAPITA:
            return carta.pib_per_capita;
        case SUPER_PODER:
            return carta.super_poder;
        default:
            return 0.0;
    }
}

// Função para calcular o Super Poder
float calcularSuperPoder(CartaSuperTrunfo *carta) {
    float inverso_densidade_populacional = 0.0;
    if (carta->densidade_populacional > 0) {
        inverso_densidade_populacional = 1.0 / carta->densidade_populacional;
    }
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

// Função para exibir o menu de escolha de atributos
void exibir_menu_atributos(Atributo atributo_ja_escolhido) {
    printf("\n--- Escolha um Atributo para Comparacao ---\n");
    for (int i = 0; i < sizeof(atributos_info) / sizeof(AtributoInfo); i++) {
        if (atributos_info[i].codigo != atributo_ja_escolhido) {
            printf("%d. %s\n", atributos_info[i].codigo, atributos_info[i].nome);
        }
    }
}

// Função para obter a escolha do jogador, garantindo que seja válida
Atributo obter_escolha(Atributo atributo_ja_escolhido) {
    int escolha;
    while (1) {
        printf("Digite sua opcao: ");
        if (scanf("%d", &escolha) == 1) {
            limpar_buffer();
            if (escolha >= POPULACAO && escolha <= SUPER_PODER && escolha != atributo_ja_escolhido) {
                return (Atributo)escolha;
            } else {
                printf("Opcao invalida ou ja escolhida. Tente novamente.\n");
            }
        } else {
            limpar_buffer();
            printf("Entrada invalida. Digite um numero.\n");
        }
    }
}

int main() {
    CartaSuperTrunfo carta1, carta2;
    Atributo escolha1, escolha2;
    float valor1_c1, valor1_c2;
    float valor2_c1, valor2_c2;
    float soma_c1, soma_c2;

    // --- ENTRADA DE DADOS E CÁLCULOS ---
    ler_carta(&carta1, 1);
    ler_carta(&carta2, 2);

    carta1.densidade_populacional = (carta1.area > 0) ? (float)carta1.populacao / carta1.area : 0;
    carta1.pib_per_capita = (carta1.populacao > 0) ? (carta1.pib * 1000000000) / carta1.populacao : 0;
    carta1.super_poder = calcularSuperPoder(&carta1);

    carta2.densidade_populacional = (carta2.area > 0) ? (float)carta2.populacao / carta2.area : 0;
    carta2.pib_per_capita = (carta2.populacao > 0) ? (carta2.pib * 1000000000) / carta2.populacao : 0;
    carta2.super_poder = calcularSuperPoder(&carta2);

    // --- Exibição das Cartas (Opcional) ---
    printf("\n--- Exibicao das Cartas ---\n");
    exibir_carta(carta1);
    exibir_carta(carta2);

    // --- ESCOLHA DOS DOIS ATRIBUTOS ---
    exibir_menu_atributos(0); // 0 indica que nenhum atributo foi escolhido ainda
    printf("\nEscolha o PRIMEIRO atributo para a batalha.\n");
    escolha1 = obter_escolha(0);

    exibir_menu_atributos(escolha1);
    printf("\nEscolha o SEGUNDO atributo para a batalha.\n");
    escolha2 = obter_escolha(escolha1);

    // --- COMPARAÇÃO E RESULTADO ---
    valor1_c1 = getValorAtributo(carta1, escolha1);
    valor1_c2 = getValorAtributo(carta2, escolha1);
    valor2_c1 = getValorAtributo(carta1, escolha2);
    valor2_c2 = getValorAtributo(carta2, escolha2);

    // Se o atributo for Densidade Demográfica, inverte o valor para a soma
    // para que o menor valor tenha um "peso" maior
    if (escolha1 == DENSIDADE_POPULACIONAL) {
        valor1_c1 = (valor1_c1 > 0) ? 1.0 / valor1_c1 : 1000000.0;
        valor1_c2 = (valor1_c2 > 0) ? 1.0 / valor1_c2 : 1000000.0;
    }

    if (escolha2 == DENSIDADE_POPULACIONAL) {
        valor2_c1 = (valor2_c1 > 0) ? 1.0 / valor2_c1 : 1000000.0;
        valor2_c2 = (valor2_c2 > 0) ? 1.0 / valor2_c2 : 1000000.0;
    }

    soma_c1 = valor1_c1 + valor2_c1;
    soma_c2 = valor1_c2 + valor2_c2;

    // --- EXIBIÇÃO DO RESULTADO ---
    printf("\n--- Resultado da Batalha ---\n");
    printf("Atributos de comparacao: %s e %s\n", getNomeAtributo(escolha1), getNomeAtributo(escolha2));
    printf("-----------------------------------\n");

    // Detalhes da Carta 1
    printf("Carta 1 (%s):\n", carta1.nome_cidade);
    printf("  - %s: %.2f\n", getNomeAtributo(escolha1), getValorAtributo(carta1, escolha1));
    printf("  - %s: %.2f\n", getNomeAtributo(escolha2), getValorAtributo(carta1, escolha2));
    printf("  - Soma dos Atributos: %.2f\n", soma_c1);

    printf("\n");

    // Detalhes da Carta 2
    printf("Carta 2 (%s):\n", carta2.nome_cidade);
    printf("  - %s: %.2f\n", getNomeAtributo(escolha1), getValorAtributo(carta2, escolha1));
    printf("  - %s: %.2f\n", getNomeAtributo(escolha2), getValorAtributo(carta2, escolha2));
    printf("  - Soma dos Atributos: %.2f\n", soma_c2);

    printf("-----------------------------------\n");

    if (soma_c1 > soma_c2) {
        printf("\nResultado: Carta 1 (%s) venceu com a maior soma!\n", carta1.nome_cidade);
    } else if (soma_c2 > soma_c1) {
        printf("\nResultado: Carta 2 (%s) venceu com a maior soma!\n", carta2.nome_cidade);
    } else {
        printf("\nResultado: Empate!\n");
    }

    return 0;
}
  
