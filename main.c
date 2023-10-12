#include "library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Equipe:
// - Sandro Gomes Paulino
// - João Victor Cavalcante da Silva Correia
// - Rychardsson Gonzaga de Souza

int main()
{
    PilhaLivros meusLivros, copiaLivros;
    meusLivros.topo = NULL;

    Estantes *MinhasEstantes = NULL;
    FILE *TXTLivros;

    int opcao;
    do
    {
        // printf("\n");
        // printf("1 - Receber livros\n");
        // printf("2 - Ordenar livros por nome\n");
        // printf("3 - Ordenar livros por letra e altura\n");
        // printf("4 - Printar na tela estantes, prateleiras e livros\n");
        // printf("5 - Importar livros do arquivo txt\n");
        // printf("6 - Salvar estantes no arquivo txt\n");
        // printf("0 - Sair\n");
        // printf("\n");
        // printf("Digite a opção desejada: ");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            // Recebe os livros e empilha na pilha de livros
            receberLivros(&meusLivros);
            break;

        case 2:
            // Ordena os livros por NOME completo
            ordenarPorNome(&meusLivros);

            // Cria uma cópia da pilha de livros e adiciona na estante
            MinhasEstantes = criarEstante();
            copiaLivros = copiarPilha(&meusLivros);
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
            ordenarPorPrimeiraLetra(&meusLivros);

            // Cria uma cópia da pilha de livros e adiciona na estante
            MinhasEstantes = criarEstante();
            copiaLivros = copiarPilha(&meusLivros);
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

            importarLivrosParaPilha(TXTLivros, &meusLivros);

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
