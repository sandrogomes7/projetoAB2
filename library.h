#ifndef library_h
#define library_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

Livros *criarLivro(int altura, int largura, const char *nome);
Prateleiras *criarPrateleira();
Estantes *criarEstante();
void empilha(PilhaLivros *pilha, Livros *livro);
Livros *desempilha(PilhaLivros *pilha);
int compararTitulosLivros(const char *string1, const char *string2);
void merge(Livros *array[], int esquerda, int meio, int direita);
void mergeSort(Livros *array[], int esquerda, int direita);
void ordenarPorNome(PilhaLivros *pilha);
void receberLivros(PilhaLivros *estante);
void imprimirPilha(PilhaLivros *pilha);
int contarPrateleiras(Estantes *estante);
void adicionaLivroNaEstante(Estantes **estante, int altura, int largura, const char *nome);
void imprimirEstantes(Estantes *primeiraEstante);
int compararPorPrimeiraLetraEAltura(const void *a, const void *b);
void ordenarPorPrimeiraLetra(PilhaLivros *pilha);
void salvarEstantesEmArquivo(FILE *arquivo, Estantes *nEstantes);
Livros *fazerCopiaLivro(const Livros *origem);
PilhaLivros copiarPilha(const PilhaLivros *origem);
void importarLivrosParaPilha(FILE *arquivo, PilhaLivros *pilha);

#endif