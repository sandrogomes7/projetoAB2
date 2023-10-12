#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Equipe:
// - Sandro Gomes Paulino
// - João Victor Cavalcante da Silva Correia
// - Rychardsson Gonzaga de Souza

// Constantes para o tamanho da prateleira e quantidade de prateleiras
#define tamanhoPrateleira 90
#define quantPrateleira 6

// Estruturas de dados para as estantes, prateleiras e livros
typedef struct Livros
{
    int larguraLivro;
    int alturaLivro;
    char nomeLivro[100];
    struct Livros *proximoL;
} Livros;

typedef struct PilhaLivros
{
    Livros *topo;
} PilhaLivros;

typedef struct Prateleiras
{
    int tamanhoMaximoPrat;
    Livros *livro;
    struct Prateleiras *proximaP;
} Prateleiras;

typedef struct Estantes
{
    Prateleiras *prateleira;
    struct Estantes *proximaEst;
} Estantes;

// Função para criar um livro
Livros *criarLivro(int altura, int largura, const char *nome)
{
    Livros *livro = malloc(sizeof(Livros));
    livro->larguraLivro = largura;
    livro->alturaLivro = altura;
    strncpy(livro->nomeLivro, nome, sizeof(livro->nomeLivro));
    livro->proximoL = NULL;
    return livro;
}

// Função para criar uma prateleira
Prateleiras *criarPrateleira()
{
    Prateleiras *prateleira = malloc(sizeof(Prateleiras));
    prateleira->tamanhoMaximoPrat = tamanhoPrateleira;
    prateleira->livro = NULL;
    prateleira->proximaP = NULL;
    return prateleira;
}

// Função para criar uma estante
Estantes *criarEstante()
{
    Estantes *estante = malloc(sizeof(Estantes));
    estante->prateleira = NULL;
    estante->proximaEst = NULL;
    return estante;
}

// Função para empilhar um livro na pilha de livros
void empilha(PilhaLivros *pilha, Livros *livro)
{
    livro->proximoL = pilha->topo;
    pilha->topo = livro;
}

// Função para desempilhar um livro da pilha de livros
Livros *desempilha(PilhaLivros *pilha)
{
    if (pilha->topo == NULL)
        return NULL;

    Livros *livro = pilha->topo;
    pilha->topo = pilha->topo->proximoL;
    return livro;
}

// Função auxiliar para comparar os títulos dos livros para o MergeSort
int compararTitulosLivros(const char *string1, const char *string2)
{
    while (*string1 && *string2)
    {
        if (*string1 == ' ')
            string1++;

        else if (*string2 == ' ')
            string2++;

        else
        {
            if (*string1 < *string2)
                return -1;

            else if (*string1 > *string2)
                return 1;

            string1++;
            string2++;
        }
    }
    if (*string1)
        return 1;

    else if (*string2)
        return -1;

    return 0;
}

// Função auxiliar para o MergeSort
void merge(Livros *array[], int esquerda, int meio, int direita)
{
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    Livros *L[n1], *R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = array[meio + 1 + j];

    i = 0;
    j = 0;
    k = esquerda;

    while (i < n1 && j < n2)
    {
        if (compararTitulosLivros(L[i]->nomeLivro, R[j]->nomeLivro) <= 0)
            array[k++] = L[i++];

        else
            array[k++] = R[j++];
    }

    while (i < n1)
        array[k++] = L[i++];

    while (j < n2)
        array[k++] = R[j++];
}

// Função de MergeSort
void mergeSort(Livros *array[], int esquerda, int direita)
{
    if (esquerda < direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(array, esquerda, meio);
        mergeSort(array, meio + 1, direita);

        merge(array, esquerda, meio, direita);
    }
}

// Função para ordenar os livros por NOME completo usando o algoritmo MergeSort
void ordenarPorNome(PilhaLivros *pilha)
{
    Livros *livros[9999];
    int n = 0;

    while (pilha->topo != NULL)
        livros[n++] = desempilha(pilha);

    mergeSort(livros, 0, n - 1);

    for (int i = n - 1; i >= 0; i--)
        empilha(pilha, livros[i]);
}

// Função para receber as informações dos livros e empilhar na pilha de livros
void receberLivros(PilhaLivros *estante)
{
    char tituloLivro[100];
    int larguraLivro, alturaLivro;

    printf("Digite o título do livro: ");
    scanf(" %[^\n]", tituloLivro);

    printf("Digite o tamanho do livro em cm: ");
    scanf("%d", &larguraLivro);

    printf("Digite a altura do livro em cm: ");
    scanf("%d", &alturaLivro);

    Livros *livro = criarLivro(alturaLivro, larguraLivro, tituloLivro);

    empilha(estante, livro);
}

// Função para imprimir a pilha de livros, auxiliar para testes
void imprimirPilha(PilhaLivros *pilha)
{
    Livros *livroAtual = pilha->topo;

    if (livroAtual == NULL)
    {
        printf("A pilha de livros está vazia.\n");
        return;
    }

    while (livroAtual != NULL)
    {
        printf("Nome: %s\n", livroAtual->nomeLivro);
        printf("Largura: %d\n", livroAtual->larguraLivro);
        printf("Altura: %d\n", livroAtual->alturaLivro);
        printf("\n");

        livroAtual = livroAtual->proximoL;
    }
}

// Função para contar quantas prateleiras tem na estante
int contarPrateleiras(Estantes *estante)
{
    int contador = 0;
    Prateleiras *prateleiraAtual = estante->prateleira;

    while (prateleiraAtual != NULL)
    {
        contador++;
        prateleiraAtual = prateleiraAtual->proximaP;
    }

    return contador;
}

// Função para adicionar um livro na estante
void adicionaLivroNaEstante(Estantes **estante, int altura, int largura, const char *nome)
{
    Livros *novoLivro = criarLivro(altura, largura, nome);
    Estantes *estanteAtual = *estante;

    while (estanteAtual->proximaEst != NULL)
        estanteAtual = estanteAtual->proximaEst;

    Prateleiras *ultimaPrateleira = estanteAtual->prateleira;

    if (ultimaPrateleira == NULL || ultimaPrateleira->livro == NULL)
    {
        Prateleiras *novaPrateleira = criarPrateleira();
        novaPrateleira->livro = novoLivro;
        novaPrateleira->tamanhoMaximoPrat -= novoLivro->larguraLivro;
        estanteAtual->prateleira = novaPrateleira;
    }
    else
    {
        while (ultimaPrateleira->proximaP != NULL && ultimaPrateleira->livro != NULL)
            ultimaPrateleira = ultimaPrateleira->proximaP;

        if (ultimaPrateleira->livro == NULL)
        {
            ultimaPrateleira->livro = novoLivro;
            ultimaPrateleira->tamanhoMaximoPrat -= novoLivro->larguraLivro;
        }
        else if (ultimaPrateleira->tamanhoMaximoPrat >= novoLivro->larguraLivro)
        {
            Livros *livroAtual = ultimaPrateleira->livro;
            while (livroAtual->proximoL != NULL)
                livroAtual = livroAtual->proximoL;

            livroAtual->proximoL = novoLivro;
            ultimaPrateleira->tamanhoMaximoPrat -= novoLivro->larguraLivro;
        }
        else
        {
            int contador = contarPrateleiras(estanteAtual);
            if (contador >= quantPrateleira && ultimaPrateleira->tamanhoMaximoPrat < novoLivro->larguraLivro)
            {
                Estantes *novaEstante = criarEstante();
                Prateleiras *novaPrateleira = criarPrateleira();
                novaPrateleira->livro = novoLivro;
                novaPrateleira->tamanhoMaximoPrat -= novoLivro->larguraLivro;
                novaEstante->prateleira = novaPrateleira;

                estanteAtual->proximaEst = novaEstante;
            }
            else
            {
                Prateleiras *novaPrateleira = criarPrateleira();
                novaPrateleira->livro = novoLivro;
                novaPrateleira->tamanhoMaximoPrat -= novoLivro->larguraLivro;

                Prateleiras *prateleiraAtual = estanteAtual->prateleira;

                while (prateleiraAtual->proximaP != NULL)
                    prateleiraAtual = prateleiraAtual->proximaP;

                prateleiraAtual->proximaP = novaPrateleira;
            }
        }
    }
}

// Função para imprimir a sequência de estantes, prateleiras e livros
void imprimirEstantes(Estantes *primeiraEstante)
{
    Estantes *estanteAtual = primeiraEstante;
    int estanteNumero = 1;

    while (estanteAtual != NULL)
    {
        printf("Estante %d:\n", estanteNumero);

        Prateleiras *prateleiraAtual = estanteAtual->prateleira;
        int prateleiraNumero = 1;

        while (prateleiraAtual != NULL)
        {
            printf("    Prateleira %d (Tamanho disponivel: %d cm):\n", prateleiraNumero, prateleiraAtual->tamanhoMaximoPrat);

            Livros *livroAtual = prateleiraAtual->livro;
            int livroNumero = 1;

            while (livroAtual != NULL)
            {
                printf("\tLivro %d: Título: %s\n\tLargura: %d cm  |  Altura: %d\n\n", livroNumero, livroAtual->nomeLivro, livroAtual->larguraLivro, livroAtual->alturaLivro);

                livroAtual = livroAtual->proximoL;
                livroNumero++;
            }

            prateleiraAtual = prateleiraAtual->proximaP;
            prateleiraNumero++;
        }

        estanteAtual = estanteAtual->proximaEst;
        estanteNumero++;
    }
}

// Função auxiliar para ordenar os livros por LETRA e ALTURA
int compararPorPrimeiraLetraEAltura(const void *a, const void *b)
{
    Livros *livroA = *((Livros **)a);
    Livros *livroB = *((Livros **)b);

    char primeiraLetraA = tolower(livroA->nomeLivro[0]);
    char primeiraLetraB = tolower(livroB->nomeLivro[0]);

    if (primeiraLetraA != primeiraLetraB)
        return primeiraLetraB - primeiraLetraA;

    return livroB->alturaLivro - livroA->alturaLivro;
}

// Função para ordenar os livros por LETRA e ALTURA
void ordenarPorPrimeiraLetra(PilhaLivros *pilha)
{
    int numLivros = 0;
    Livros *livroAtual = pilha->topo;

    while (livroAtual != NULL)
    {
        numLivros++;
        livroAtual = livroAtual->proximoL;
    }

    Livros **livrosArray = malloc(numLivros * sizeof(Livros *));
    livroAtual = pilha->topo;

    for (int i = 0; i < numLivros; i++)
    {
        livrosArray[i] = livroAtual;
        livroAtual = livroAtual->proximoL;
    }

    qsort(livrosArray, numLivros, sizeof(Livros *), compararPorPrimeiraLetraEAltura);

    while (pilha->topo != NULL)
        desempilha(pilha);

    for (int i = 0; i < numLivros; i++)
        empilha(pilha, livrosArray[i]);

    free(livrosArray);
}

// Funçã para salvar as estantes em um arquivo txt
void salvarEstantesEmArquivo(FILE *arquivo, Estantes *nEstantes)
{
    Estantes *estanteAtual = nEstantes;
    int estanteNumero = 1;

    while (estanteAtual != NULL)
    {
        fprintf(arquivo, "Estante %d:\n", estanteNumero);

        Prateleiras *prateleiraAtual = estanteAtual->prateleira;
        int prateleiraNumero = 1;

        while (prateleiraAtual != NULL)
        {
            fprintf(arquivo, "Prateleira %d (Tamanho disponivel: %d cm):\n", prateleiraNumero, prateleiraAtual->tamanhoMaximoPrat);

            Livros *livroAtual = prateleiraAtual->livro;
            int livroNumero = 1;

            while (livroAtual != NULL)
            {
                fprintf(arquivo, "\tLivro %d: Título: %s\tLargura: %d cm  |  Altura: %d\n", livroNumero, livroAtual->nomeLivro, livroAtual->larguraLivro, livroAtual->alturaLivro);

                livroAtual = livroAtual->proximoL;
                livroNumero++;
            }
            prateleiraAtual = prateleiraAtual->proximaP;
            prateleiraNumero++;
            fprintf(arquivo, "\n");
        }

        estanteAtual = estanteAtual->proximaEst;
        estanteNumero++;
    }
}

// Função que auxilia na copia da pilha
Livros *fazerCopiaLivro(const Livros *origem)
{
    if (origem == NULL)
        return NULL;

    Livros *copia = malloc(sizeof(Livros));
    if (copia == NULL)
        exit(1);

    copia->larguraLivro = origem->larguraLivro;
    copia->alturaLivro = origem->alturaLivro;
    strcpy(copia->nomeLivro, origem->nomeLivro);
    copia->proximoL = NULL;

    return copia;
}

// Função para copiar uma pilha
PilhaLivros copiarPilha(const PilhaLivros *origem)
{
    PilhaLivros copia;
    copia.topo = NULL;

    PilhaLivros auxiliar;
    auxiliar.topo = NULL;

    Livros *atual = origem->topo;
    while (atual != NULL)
    {
        Livros *novoLivro = fazerCopiaLivro(atual);
        if (novoLivro == NULL)
            exit(1);

        novoLivro->proximoL = auxiliar.topo;
        auxiliar.topo = novoLivro;
        atual = atual->proximoL;
    }

    atual = auxiliar.topo;
    while (atual != NULL)
    {
        Livros *novoLivro = fazerCopiaLivro(atual);
        if (novoLivro == NULL)
            exit(1);

        novoLivro->proximoL = copia.topo;
        copia.topo = novoLivro;
        atual = atual->proximoL;
    }

    return copia;
}

// Função para importar os livros do arquivo txt com os livros para a pilha de livros
void importarLivrosParaPilha(FILE *arquivo, PilhaLivros *pilha)
{
    char linha[1000];
    char tituloLivro[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "Livro") != NULL)
        {
            int livroNumero, largura, altura;
            if (sscanf(linha, "     Livro %d: Título: %99[^\t]\tLargura: %d cm  |  Altura: %d", &livroNumero, tituloLivro, &largura, &altura) == 4)
            {
                Livros *novoLivro = malloc(sizeof(Livros));
                novoLivro->larguraLivro = largura;
                novoLivro->alturaLivro = altura;
                strcpy(novoLivro->nomeLivro, tituloLivro);
                novoLivro->proximoL = NULL;

                empilha(pilha, novoLivro);
            }
        }
    }
}

int main()
{
    PilhaLivros estante, copiaLivros;
    estante.topo = NULL;

    Estantes *MinhasEstantes = NULL;
    FILE *TXTLivros;

    int opcao;
    do
    {
        printf("\n\n");
        printf("1 - Receber livros\n");
        printf("2 - Ordenar livros por nome\n");
        printf("3 - Ordenar livros por letra e altura\n");
        printf("4 - Printar na tela estantes, prateleiras e livros\n");
        printf("5 - Importar livros do arquivo txt\n");
        printf("6 - Salvar estantes no arquivo txt\n");
        printf("0 - Sair\n");
        printf("\n");
        printf("Digite a opção desejada: ");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            // Recebe os livros e empilha na pilha de livros
            receberLivros(&estante);
            break;

        case 2:
            // Ordena os livros por NOME completo
            ordenarPorNome(&estante);

            // Cria uma cópia da pilha de livros e adiciona na estante
            MinhasEstantes = criarEstante();
            copiaLivros = copiarPilha(&estante);
            Livros *livroAtualC2 = desempilha(&copiaLivros);
            adicionaLivroNaEstante(&MinhasEstantes, livroAtualC2->alturaLivro, livroAtualC2->larguraLivro, livroAtualC2->nomeLivro);

            while (livroAtualC2 != NULL)
            {
                livroAtualC2 = desempilha(&copiaLivros);
                adicionaLivroNaEstante(&MinhasEstantes, livroAtualC2->alturaLivro, livroAtualC2->larguraLivro, livroAtualC2->nomeLivro);

                livroAtualC2 = livroAtualC2->proximoL;
            }

            break;

        case 3:
           // Ordena os livros por LETRA e ALTURA
            ordenarPorPrimeiraLetra(&estante);

            // Cria uma cópia da pilha de livros e adiciona na estante
            MinhasEstantes = criarEstante();
            copiaLivros = copiarPilha(&estante);
            Livros *livroAtualC3 = desempilha(&copiaLivros);
            adicionaLivroNaEstante(&MinhasEstantes, livroAtualC3->alturaLivro, livroAtualC3->larguraLivro, livroAtualC3->nomeLivro);

            while (livroAtualC3 != NULL)
            {
                livroAtualC3 = desempilha(&copiaLivros);
                adicionaLivroNaEstante(&MinhasEstantes, livroAtualC3->alturaLivro, livroAtualC3->larguraLivro, livroAtualC3->nomeLivro);

                livroAtualC3 = livroAtualC3->proximoL;
            }

            break;

        case 4:
            // Imprime as estantes, prateleiras e livros
            imprimirEstantes(MinhasEstantes);
            break;

        case 5:
            // Importa os livros do txt
            TXTLivros = fopen("seus-livros.txt", "r");
            if (TXTLivros == NULL)
            {
                perror("Erro ao abrir o arquivo");
                return 1;
            }

            importarLivrosParaPilha(TXTLivros, &estante);

            fclose(TXTLivros);

            printf("Livros importados com sucesso!\n");
            break;

        case 6:
            // Salva os livros no txt
            TXTLivros = fopen("seus-livros.txt", "w");
            if (TXTLivros == NULL)
            {
                perror("Erro ao abrir o arquivo");
                return 1;
            }

            salvarEstantesEmArquivo(TXTLivros, MinhasEstantes);

            fclose(TXTLivros);

            printf("Livros salvos com sucesso!\n");
            break;

        case 0:
            break;

        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
