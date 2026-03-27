#include <stdio.h>
#include <string.h>

// Definição da struct
struct Cidade
{
    char estado;
    char codigo[6];
    char nome[20];
    unsigned int populacao;
    float area;
    float pib;
    int turismo;
    int PontosTuristicos;
    float densidade, PibPerCapita;
    float SuperPoder;
};

// Letreiro
void letreiro(void)
{
    printf("----------------------------------------\n");
    printf("         CADASTRO DE CIDADES\n");
    printf("----------------------------------------\n\n");
}

void compararCartas(void)
{
    printf("----------------------------------------\n");
    printf("         COMPARAÇÃO DE CARTAS\n");
    printf("----------------------------------------\n\n");

    printf("Escolha a categoria para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Índice de turismo\n");
    printf("5 - Número de pontos turísticos\n");
    printf("6 - Densidade populacional\n\n");
}

// Leitura da cidade
void lerCidade(struct Cidade *c)
{
    char buffer[100];

    printf("Estado (sigla A-H): ");
    fgets(buffer, sizeof(buffer), stdin);
    c->estado = buffer[0];

    printf("Codigo da cidade (4 digitos): ");
    fgets(c->codigo, sizeof(c->codigo), stdin);
    c->codigo[strcspn(c->codigo, "\n")] = '\0';

    printf("Nome da cidade: ");
    fgets(c->nome, sizeof(c->nome), stdin);
    c->nome[strcspn(c->nome, "\n")] = '\0';

    printf("Populacao (em milhares): ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%u", &c->populacao);

    printf("Area (em km2): ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &c->area);

    printf("PIB (em milhoes R$): ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &c->pib);

    printf("Indice de turismo (0-100): ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &c->turismo);

    printf("Numero de pontos turisticos: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &c->PontosTuristicos);

    // Cálculos
    c->densidade = (c->area != 0) ? c->populacao / c->area : 0;
    c->PibPerCapita = (c->populacao != 0) ? c->pib / c->populacao : 0;

    if (c->densidade != 0)
    {
        c->SuperPoder = c->populacao + c->pib + c->area +
                        c->PibPerCapita + c->turismo +
                        c->PontosTuristicos + (1.0 / c->densidade);
    }
    else
        c->SuperPoder = 0;

    printf("\n");
}

// Impressão da cidade
void imprimirCidade(struct Cidade c, int numero)
{
    printf("Carta %d:\n", numero);
    printf("Estado: %c\n", c.estado);
    printf("Codigo: %s\n", c.codigo);
    printf("Nome: %s\n", c.nome);
    printf("População: %u\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f milhões\n", c.pib);
    printf("Turismo: %d\n", c.turismo);
    printf("Pontos turísticos: %d\n", c.PontosTuristicos);
    printf("Densidade: %.2f hab/km²\n", c.densidade);
    printf("PIB per capita: %.2f\n", c.PibPerCapita);
    printf("Super Poder: %.2f\n", c.SuperPoder);
    printf("----------------------------------------\n\n");
}

// Função de comparação
int compararCategoria(struct Cidade c1, struct Cidade c2, int opcao)
{
    switch (opcao)
    {
        case 1: return c1.populacao > c2.populacao;
        case 2: return c1.area > c2.area;
        case 3: return c1.pib > c2.pib;
        case 4: return c1.turismo > c2.turismo;
        case 5: return c1.PontosTuristicos > c2.PontosTuristicos;
        case 6: return c1.densidade > c2.densidade;
        default: return -1;
    }
}

// Função principal
int main(void)
{
    struct Cidade cidades[2];
    int opcao1, opcao2;
    int resultado1, resultado2;

    printf("\033[2J\033[H");
    letreiro();
    printf("Digite os dados da primeira carta:\n\n");
    lerCidade(&cidades[0]);

    printf("\033[2J\033[H");
    letreiro();
    printf("Digite os dados da segunda carta:\n\n");
    lerCidade(&cidades[1]);

    printf("\033[2J\033[H");
    printf("----------------------------------------\n");
    printf("         DADOS DAS CIDADES\n");
    printf("----------------------------------------\n\n");

    imprimirCidade(cidades[0], 1);
    imprimirCidade(cidades[1], 2);

    compararCartas();
    scanf(" %d", &opcao1);

    printf("\033[2J\033[H");
    compararCartas();
    scanf(" %d", &opcao2);

    resultado1 = compararCategoria(cidades[0], cidades[1], opcao1);
    resultado2 = compararCategoria(cidades[0], cidades[1], opcao2);

    printf("\nResultado da categoria 1: ");
    if (resultado1)
        printf("Carta 1 venceu\n");
    else
        printf("Carta 2 venceu\n");

    printf("Resultado da categoria 2: ");
    if (resultado2)
        printf("Carta 1 venceu\n");
    else
        printf("Carta 2 venceu\n");

    printf("\nResultado final:\n");

    if (resultado1 && resultado2)
        printf("Carta 1 é a vencedora!\n");
    else if (!resultado1 && !resultado2)
        printf("Carta 2 é a vencedora!\n");
    else
        printf("Empate!\n");

    return 0;
}