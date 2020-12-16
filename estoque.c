#include "structs.h"
#include "estoque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void listarEstoque(Produtos* produtosDisponiveis, int* contadorProdutos) {

    for( int i = 0; i < (*contadorProdutos); i++) { //lista os produtos disponiveis no estoque

        if(produtosDisponiveis[i].id >= 0) {

            printf("%s: %d\n", produtosDisponiveis[i].nomeProd, produtosDisponiveis[i].quantidade);

        }

    }
}

void adicionarEstoque(Produtos* produtosDisponiveis, int* contadorProdutos) {

    int idSelecionado, quantidadeSelecionada;

    printf("\nSelecione o ID do produto que deseja acrescentar: "); //usuario escolhe produto
    scanf("%d", &idSelecionado);

    printf("\nDigite a quantidade que deseja adicionar ao estoque: "); //usuario escolhe quantidade
    scanf("%d", &quantidadeSelecionada);

    produtosDisponiveis[idSelecionado].quantidade += quantidadeSelecionada; //acrescenta quantidade

}

void removerEstoque(Produtos* produtosDisponiveis, int* contadorProdutos) {

    int idSelecionado, quantidadeSelecionada;

    printf("\nSelecione o ID do produto que deseja remover: ");
    scanf("%d", &idSelecionado);

    printf("\nDigite a quantidade que deseja remover do estoque: ");
    scanf("%d", &quantidadeSelecionada);

    produtosDisponiveis[idSelecionado].quantidade -= quantidadeSelecionada; //retira quantidade

}

void adicionarCatalogo(Produtos* produtosDisponiveis, int* contadorProdutos) {

    char nomeProduto[40];
    int quantidadeProd = 0, idProdutoSob = -1;
    float precoProd;

    getchar();
    printf("\nEscreva o nome do produto que deseja adicionar: ");
    scanf("%[^\n]", nomeProduto);
    getchar();
    printf("\nEscreva a quantidade ja disponivel do produto: ");
    scanf("%d", &quantidadeProd);
    //getchar();
    printf("\nEscreva o preco do produto: ");
    scanf("%f", &precoProd);

    for(int i = 0; i < (*contadorProdutos); i++) {

        if(produtosDisponiveis[i].id == -1) {//caso algum produto tenha sido removido, seu id estara como menos 1 e a variavel ira pegar qual o index desse produto

            idProdutoSob = i;
            break;

        }

    }

    if(idProdutoSob != -1){ //caso a variavel que foi iniciada como -1 esteja diferente, e pois um produto foi sobrescrito

        produtosDisponiveis[idProdutoSob].id = idProdutoSob;
        produtosDisponiveis[idProdutoSob].quantidade = quantidadeProd;
        produtosDisponiveis[idProdutoSob].preco = precoProd;
        strcpy(produtosDisponiveis[idProdutoSob].nomeProd, nomeProduto);

    }
    else { //caso nao tenha produto a ser sobrescrito, ele escreve normalmente

        produtosDisponiveis[*contadorProdutos].id = (*contadorProdutos);
        produtosDisponiveis[*contadorProdutos].quantidade = quantidadeProd;
        produtosDisponiveis[*contadorProdutos].preco = precoProd;
        strcpy(produtosDisponiveis[*contadorProdutos].nomeProd, nomeProduto);
        (*contadorProdutos)++;

    }

}


void removerCatalogo(Produtos* produtosDisponiveis, int* contadorProdutos) {

    int idProdutoRemover;

    printf("Digite o ID do produto que deseja remover: ");
    scanf("%d", &idProdutoRemover);
    produtosDisponiveis[idProdutoRemover].id = -1;

}

int alterarCatalogo(Produtos* produtosDisponiveis, int* contadorProdutos) {

    int idProdutoAlterar, quantidadeProd, opcao;
    char nomeProduto[40];
    char desejaAlterar;
    float precoProd;

    do {

        printf("Selecione o ID do produto que deseja alterar: ");
        scanf("%d", &idProdutoAlterar);

        printf("-------------------------\n");
        printf("Selecione o que deseja alterar:\n");
        printf("1 - Nome\n");
        printf("2 - Quantidade\n");
        printf("3 - Preco\n");
        printf("4 - Cancelar\n");
        scanf("%d", &opcao);
        printf("-------------------------\n");

        switch(opcao) {

            case 1:
                getchar();
                printf("\nEscreva o nome do produto que deseja alterar: ");
                scanf("%[^\n]s", nomeProduto);
                getchar();
                strcpy(produtosDisponiveis[idProdutoAlterar].nomeProd, nomeProduto);
                break;

            case 2:
                printf("\nEscreva a quantidade ja disponivel do produto: ");
                scanf("%d", &quantidadeProd);
                produtosDisponiveis[idProdutoAlterar].quantidade = quantidadeProd;
                break;

            case 3:
                printf("\nEscreva o preco do produto: ");
                scanf("%f", &precoProd);
                produtosDisponiveis[idProdutoAlterar].preco = precoProd;
                break;

            case 4:
                return 0;
                break;

        }

        printf("\n-------------------------\n");
        printf("\nDeseja alterar mais uma mercadoria ( Y - sim / N - nao ) ? ");
        scanf("%c", &desejaAlterar);

    } while(toupper(desejaAlterar) != 'N');

    return 0;

}

//--------------------------------------------------------
//--------------- Função Listar Catalogo -----------------
//--------------------------------------------------------
void listarCatalogo(Produtos *produtosDisponiveis, int *contadorProdutos) {

    for ( int i = 0; i < (*contadorProdutos); i++) {

        if(produtosDisponiveis[i].id >= 0){

            printf("Nome: %s - ID: %d\n", produtosDisponiveis[i].nomeProd, produtosDisponiveis[i].id);
            printf("Preco: %.2f\n", produtosDisponiveis[i].preco);
            printf("-------------------------\n");

        }
    
    }

}
