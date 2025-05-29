#include <stdio.h>
#include <string.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.

// Estrutura para armazenar os dados de uma carta
typedef struct {
    char codigo[4];              // Exemplo: A01, B02, etc
    char nome_cidade[100];       // Nome da cidade
    unsigned long int populacao; // População da cidade
    float area;                 // Área da cidade em km²
    float pib;                  // PIB da cidade em bilhões
    int pontos_turisticos;       // Número de pontos turísticos
    float densidade_pop;         // Densidade populacional (hab/km²)
    float pib_per_capita;        // PIB per capita em reais
    float super_poder;           // Super poder da carta
} Carta;

// Função para calcular a densidade populacional
float calcular_densidade(unsigned long int populacao, float area) {
    return (float)populacao / area;
}

// Função para calcular o PIB per capita (PIB em bilhões convertido para reais)
float calcular_pib_per_capita(float pib, unsigned long int populacao) {
    // Convertendo PIB de bilhões para reais (multiplicando por 1.000.000.000)
    return (pib * 1000000000.0) / populacao;
}

// Função para calcular o super poder da carta
float calcular_super_poder(Carta carta) {
    // Convertendo população para float para evitar overflow
    float pop_normalizada = (float)carta.populacao / 1000000.0; // Convertendo para milhões
    
    // Calculando o inverso da densidade (quanto menor a densidade, maior o poder)
    float inverso_densidade = 10000.0 / carta.densidade_pop; // Multiplicando por 10000 para normalizar
    
    // Somando todos os atributos normalizados
    return pop_normalizada + 
           carta.area + 
           carta.pib * 1000.0 + // Multiplicando por 1000 para dar mais peso ao PIB
           (float)carta.pontos_turisticos * 100.0 + // Multiplicando por 100 para dar mais peso aos pontos turísticos
           carta.pib_per_capita / 1000.0 + // Dividindo por 1000 para normalizar
           inverso_densidade;
}

// Função para cadastrar uma carta
Carta cadastrar_carta() {
    Carta carta;
    char estado;
    int numero;
    
    // Leitura do código da carta (estado e número)
    printf("Digite a letra do estado (A-H): ");
    scanf(" %c", &estado);
    printf("Digite o número da cidade (1-4): ");
    scanf("%d", &numero);
    
    // Formata o código da carta (exemplo: A01)
    sprintf(carta.codigo, "%c%02d", estado, numero);
    
    // Limpa o buffer do teclado
    getchar();
    
    // Leitura do nome da cidade
    printf("Digite o nome da cidade: ");
    fgets(carta.nome_cidade, 100, stdin);
    // Remove o \n do final da string
    carta.nome_cidade[strcspn(carta.nome_cidade, "\n")] = 0;
    
    // Leitura dos atributos da carta
    printf("Digite a população da cidade: ");
    scanf("%lu", &carta.populacao);
    
    printf("Digite a área da cidade (em km²): ");
    scanf("%f", &carta.area);
    
    printf("Digite o PIB da cidade (em bilhões): ");
    scanf("%f", &carta.pib);
    
    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &carta.pontos_turisticos);
    
    // Calcula a densidade populacional e o PIB per capita
    carta.densidade_pop = calcular_densidade(carta.populacao, carta.area);
    carta.pib_per_capita = calcular_pib_per_capita(carta.pib, carta.populacao);
    
    // Calcula o super poder
    carta.super_poder = calcular_super_poder(carta);
    
    return carta;
}

// Função para exibir os dados de uma carta
void exibir_carta(Carta carta) {
    printf("\n=== Dados da Carta %s ===\n", carta.codigo);
    printf("Nome da Cidade: %s\n", carta.nome_cidade);
    printf("População: %lu habitantes\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhões de reais\n", carta.pib);
    printf("Pontos Turísticos: %d\n", carta.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidade_pop);
    printf("PIB per Capita: %.2f reais\n", carta.pib_per_capita);
    printf("Super Poder: %.2f\n", carta.super_poder);
    printf("==========================\n\n");
}

int main() {
    printf("=== Super Trunfo - Cadastro de Cartas ===\n\n");
    
    printf("Cadastro da primeira carta:\n");
    Carta carta1 = cadastrar_carta();
    
    printf("\nCadastro da segunda carta:\n");
    Carta carta2 = cadastrar_carta();
    
    printf("\nExibindo os dados das cartas cadastradas:\n");
    exibir_carta(carta1);
    exibir_carta(carta2);

    // Menu interativo
    int opcao;
    printf("\nEscolha o atributo para comparar:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional\n");
    printf("6. PIB per Capita\n");
    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: // População
            printf("Comparação de cartas (Atributo: População):\n\n");
            printf("Carta 1 - %s: %lu habitantes\n", carta1.nome_cidade, carta1.populacao);
            printf("Carta 2 - %s: %lu habitantes\n", carta2.nome_cidade, carta2.populacao);
            if (carta1.populacao > carta2.populacao) {
                printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
            } else if (carta2.populacao > carta1.populacao) {
                printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;
        case 2: // Área
            printf("Comparação de cartas (Atributo: Área):\n\n");
            printf("Carta 1 - %s: %.2f km²\n", carta1.nome_cidade, carta1.area);
            printf("Carta 2 - %s: %.2f km²\n", carta2.nome_cidade, carta2.area);
            if (carta1.area > carta2.area) {
                printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
            } else if (carta2.area > carta1.area) {
                printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;
        case 3: // PIB
            printf("Comparação de cartas (Atributo: PIB):\n\n");
            printf("Carta 1 - %s: %.2f bilhões de reais\n", carta1.nome_cidade, carta1.pib);
            printf("Carta 2 - %s: %.2f bilhões de reais\n", carta2.nome_cidade, carta2.pib);
            if (carta1.pib > carta2.pib) {
                printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
            } else if (carta2.pib > carta1.pib) {
                printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;
        case 4: // Pontos Turísticos
            printf("Comparação de cartas (Atributo: Pontos Turísticos):\n\n");
            printf("Carta 1 - %s: %d pontos turísticos\n", carta1.nome_cidade, carta1.pontos_turisticos);
            printf("Carta 2 - %s: %d pontos turísticos\n", carta2.nome_cidade, carta2.pontos_turisticos);
            if (carta1.pontos_turisticos > carta2.pontos_turisticos) {
                printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
            } else if (carta2.pontos_turisticos > carta1.pontos_turisticos) {
                printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;
        case 5: // Densidade Populacional
            printf("Comparação de cartas (Atributo: Densidade Populacional):\n\n");
            printf("Carta 1 - %s: %.2f hab/km²\n", carta1.nome_cidade, carta1.densidade_pop);
            printf("Carta 2 - %s: %.2f hab/km²\n", carta2.nome_cidade, carta2.densidade_pop);
            if (carta1.densidade_pop < carta2.densidade_pop) {
                printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
            } else if (carta2.densidade_pop < carta1.densidade_pop) {
                printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;
        case 6: // PIB per Capita
            printf("Comparação de cartas (Atributo: PIB per Capita):\n\n");
            printf("Carta 1 - %s: %.2f reais\n", carta1.nome_cidade, carta1.pib_per_capita);
            printf("Carta 2 - %s: %.2f reais\n", carta2.nome_cidade, carta2.pib_per_capita);
            if (carta1.pib_per_capita > carta2.pib_per_capita) {
                printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
            } else if (carta2.pib_per_capita > carta1.pib_per_capita) {
                printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;
        case 7: // Super Poder
            printf("Comparação de cartas (Atributo: Super Poder):\n\n");
            printf("Carta 1 - %s: %.2f\n", carta1.nome_cidade, carta1.super_poder);
            printf("Carta 2 - %s: %.2f\n", carta2.nome_cidade, carta2.super_poder);
            if (carta1.super_poder > carta2.super_poder) {
                printf("Resultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
            } else if (carta2.super_poder > carta1.super_poder) {
                printf("Resultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;
        default:
            printf("Opção inválida!\n");
    }

    return 0;
}