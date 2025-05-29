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

// Função auxiliar para exibir o menu de atributos
void exibir_menu_atributos(int atributo_escolhido) {
    printf("\nEscolha o atributo para comparar:\n");
    if (atributo_escolhido != 1) printf("1. População\n");
    if (atributo_escolhido != 2) printf("2. Área\n");
    if (atributo_escolhido != 3) printf("3. PIB\n");
    if (atributo_escolhido != 4) printf("4. Pontos Turísticos\n");
    if (atributo_escolhido != 5) printf("5. Densidade Populacional\n");
    if (atributo_escolhido != 6) printf("6. PIB per Capita\n");
    printf("Digite a opção desejada: ");
}

// Função para obter o valor do atributo baseado na opção escolhida
float obter_valor_atributo(Carta carta, int opcao) {
    switch (opcao) {
        case 1: return (float)carta.populacao;
        case 2: return carta.area;
        case 3: return carta.pib;
        case 4: return (float)carta.pontos_turisticos;
        case 5: return carta.densidade_pop;
        case 6: return carta.pib_per_capita;
        default: return 0.0f;
    }
}

// Função para obter o nome do atributo
const char* obter_nome_atributo(int opcao) {
    switch (opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Populacional";
        case 6: return "PIB per Capita";
        default: return "Desconhecido";
    }
}

// Função para obter a unidade do atributo
const char* obter_unidade_atributo(int opcao) {
    switch (opcao) {
        case 1: return "habitantes";
        case 2: return "km²";
        case 3: return "bilhões de reais";
        case 4: return "pontos";
        case 5: return "hab/km²";
        case 6: return "reais";
        default: return "";
    }
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

    int continuar;
    do {
        // Escolha dos dois atributos
        int opcao1, opcao2;
        float valor1_carta1, valor1_carta2, valor2_carta1, valor2_carta2;
        int vitorias_carta1 = 0, vitorias_carta2 = 0;

        // Escolha do primeiro atributo
        exibir_menu_atributos(0);
        scanf("%d", &opcao1);

        if (opcao1 < 1 || opcao1 > 6) {
            printf("Opção inválida!\n");
            return 1;
        }

        // Escolha do segundo atributo
        exibir_menu_atributos(opcao1);
        scanf("%d", &opcao2);

        if (opcao2 < 1 || opcao2 > 6 || opcao2 == opcao1) {
            printf("Opção inválida ou igual à primeira escolha!\n");
            return 1;
        }

        // Obtém os valores dos atributos
        valor1_carta1 = obter_valor_atributo(carta1, opcao1);
        valor1_carta2 = obter_valor_atributo(carta2, opcao1);
        valor2_carta1 = obter_valor_atributo(carta1, opcao2);
        valor2_carta2 = obter_valor_atributo(carta2, opcao2);

        // Exibe o resultado da comparação
        printf("\n=== Resultado da Comparação ===\n\n");

        // Primeiro atributo
        printf("1. %s:\n", obter_nome_atributo(opcao1));
        printf("Carta 1 - %s: %.2f %s\n", carta1.nome_cidade, valor1_carta1, obter_unidade_atributo(opcao1));
        printf("Carta 2 - %s: %.2f %s\n", carta2.nome_cidade, valor1_carta2, obter_unidade_atributo(opcao1));
        
        // Determina o vencedor do primeiro atributo
        if (opcao1 == 5) { // Densidade populacional (menor vence)
            if (valor1_carta1 < valor1_carta2) {
                printf("Carta 1 (%s) venceu este atributo!\n", carta1.nome_cidade);
                vitorias_carta1++;
            } else if (valor1_carta2 < valor1_carta1) {
                printf("Carta 2 (%s) venceu este atributo!\n", carta2.nome_cidade);
                vitorias_carta2++;
            }
        } else { // Outros atributos (maior vence)
            if (valor1_carta1 > valor1_carta2) {
                printf("Carta 1 (%s) venceu este atributo!\n", carta1.nome_cidade);
                vitorias_carta1++;
            } else if (valor1_carta2 > valor1_carta1) {
                printf("Carta 2 (%s) venceu este atributo!\n", carta2.nome_cidade);
                vitorias_carta2++;
            }
        }

        printf("\n2. %s:\n", obter_nome_atributo(opcao2));
        printf("Carta 1 - %s: %.2f %s\n", carta1.nome_cidade, valor2_carta1, obter_unidade_atributo(opcao2));
        printf("Carta 2 - %s: %.2f %s\n", carta2.nome_cidade, valor2_carta2, obter_unidade_atributo(opcao2));

        // Determina o vencedor do segundo atributo
        if (opcao2 == 5) { // Densidade populacional (menor vence)
            if (valor2_carta1 < valor2_carta2) {
                printf("Carta 1 (%s) venceu este atributo!\n", carta1.nome_cidade);
                vitorias_carta1++;
            } else if (valor2_carta2 < valor2_carta1) {
                printf("Carta 2 (%s) venceu este atributo!\n", carta2.nome_cidade);
                vitorias_carta2++;
            }
        } else { // Outros atributos (maior vence)
            if (valor2_carta1 > valor2_carta2) {
                printf("Carta 1 (%s) venceu este atributo!\n", carta1.nome_cidade);
                vitorias_carta1++;
            } else if (valor2_carta2 > valor2_carta1) {
                printf("Carta 2 (%s) venceu este atributo!\n", carta2.nome_cidade);
                vitorias_carta2++;
            }
        }

        // Calcula a soma dos atributos
        float soma_carta1 = valor1_carta1 + valor2_carta1;
        float soma_carta2 = valor1_carta2 + valor2_carta2;

        printf("\n=== Resultado Final ===\n");
        printf("Soma dos atributos:\n");
        printf("Carta 1 (%s): %.2f\n", carta1.nome_cidade, soma_carta1);
        printf("Carta 2 (%s): %.2f\n", carta2.nome_cidade, soma_carta2);
        printf("Vitórias:\n");
        printf("Carta 1 (%s): %d\n", carta1.nome_cidade, vitorias_carta1);
        printf("Carta 2 (%s): %d\n", carta2.nome_cidade, vitorias_carta2);

        // Determina o vencedor final
        if (vitorias_carta1 > vitorias_carta2) {
            printf("\nCarta 1 (%s) é a vencedora!\n", carta1.nome_cidade);
        } else if (vitorias_carta2 > vitorias_carta1) {
            printf("\nCarta 2 (%s) é a vencedora!\n", carta2.nome_cidade);
        } else {
            if (soma_carta1 > soma_carta2) {
                printf("\nCarta 1 (%s) é a vencedora pelo desempate da soma!\n", carta1.nome_cidade);
            } else if (soma_carta2 > soma_carta1) {
                printf("\nCarta 2 (%s) é a vencedora pelo desempate da soma!\n", carta2.nome_cidade);
            } else {
                printf("\nEmpate total!\n");
            }
        }

        // Menu para continuar ou sair
        printf("\nDeseja comparar novamente?\n");
        printf("1 - Sim, comparar outros atributos\n");
        printf("0 - Não, sair do programa\n");
        printf("Digite sua escolha: ");
        scanf("%d", &continuar);

    } while (continuar == 1);

    printf("\nObrigado por jogar Super Trunfo!\n");
    return 0;
}