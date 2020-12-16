#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "vendas.h"
#include "interface.h"


//----------------------------------------------------------------------------------
//-------------------------Função para Cadastrar o pedido---------------------------
//----------------------------------------------------------------------------------
void cadastrarPedido(Produtos* produtosDisponiveis, Pedidos* pedidosCadastrados, Clientes* clientesCadastrados, int idCliente, char* data, int opcaoProduto, int quantidade, int* contadorPedidos, int* pedidosSobrescritos, int* contadorSobrescritos) {

    int idPedidoSob = 0;

    if(*pedidosSobrescritos > 0) { //caso haja algum pedido para ser sobrescrito

        for( int i = 0; i < (*contadorPedidos); i++) { //percorre os pedidos existentes em busca de um pedido com id -1, se sim, esse pedido sera sobrescrito

            if(pedidosCadastrados[i].id == -1) {

                idPedidoSob = i;
                break;

            }

        }

        pedidosCadastrados[idPedidoSob].id = (*contadorPedidos) + (*contadorSobrescritos);
        strcpy(pedidosCadastrados[idPedidoSob].produto, produtosDisponiveis[opcaoProduto].nomeProd);
        pedidosCadastrados[idPedidoSob].valor = produtosDisponiveis[opcaoProduto].preco * quantidade;
        strcpy(pedidosCadastrados[idPedidoSob].nomeCliente, clientesCadastrados[idCliente].nome);
        pedidosCadastrados[idPedidoSob].quantidade = quantidade;
        strcpy(pedidosCadastrados[idPedidoSob].data, data);
        produtosDisponiveis[opcaoProduto].quantidade -= quantidade;
        (*contadorSobrescritos)++; //como um pedido foi sobrescrito, se incrementa essa variavel para aumentar o id dos pedidos
        (*pedidosSobrescritos)--; //como o pedido foi sobrescrito, essa variavel de pedidos para serem sobrescritos é decrementada

    }
    else {

        pedidosCadastrados[*contadorPedidos].id = *contadorPedidos;
        strcpy(pedidosCadastrados[*contadorPedidos].produto, produtosDisponiveis[opcaoProduto].nomeProd);
        pedidosCadastrados[*contadorPedidos].valor = produtosDisponiveis[opcaoProduto].preco * quantidade;
        strcpy(pedidosCadastrados[*contadorPedidos].nomeCliente, clientesCadastrados[idCliente].nome);
        pedidosCadastrados[*contadorPedidos].quantidade = quantidade;
        strcpy(pedidosCadastrados[*contadorPedidos].data, data);
        produtosDisponiveis[opcaoProduto].quantidade -= quantidade;
        (*contadorPedidos)++;

    }

}

//----------------------------------------------------------------------------------//
//-------------------------Função para Finalizar o pedido---------------------------//
//----------------------------------------------------------------------------------//
void finalizarPedido(Pedidos* pedidosCadastrados, int* contadorPedidos, int* pedidosSobrescritos) {

    int idInserido;

    listarPedidos(pedidosCadastrados, contadorPedidos);

    printf("-------------------------\n");
    printf("Insira o ID do pedido que deseja finalizar: \n");
    scanf("%d", &idInserido);

    for( int i = 0; i < *contadorPedidos; i++) { //o id do produto selecionado sera transformado em 0 e posteriormente sobrescrito

        if(pedidosCadastrados[i].id == idInserido) {

            pedidosCadastrados[i].id = -1;
            (*pedidosSobrescritos)++;
            break;

        }

    }

}


//--------------------------------------------------------
//---------------- Função Listar Pedidos -----------------
//--------------------------------------------------------

void listarPedidos(Pedidos *pedidosCadastrados, int *contadorPedidos) {

    printf("-------------------------\n");
    printf("Pedidos em andamento:\n");

    for ( int i = 0; i < (*contadorPedidos); i++){

        printf("-------------------------\n");

        if (pedidosCadastrados[i].id == -1){

            printf("!!!Pedido finalizado!!!\n");
        }
        else {
            printf("ID do Pedido: %d\n", pedidosCadastrados[i].id);
        }

        printf("Nome do cliente: %s\n", pedidosCadastrados[i].nomeCliente);
        printf("Nome do produto: %s\n", pedidosCadastrados[i].produto);
        printf("Quantidade: %d\n", pedidosCadastrados[i].quantidade);
        printf("Data: %s\n", pedidosCadastrados[i].data);
        printf("Valor: %.2f\n", pedidosCadastrados[i].valor);

    }

    printf("-------------------------\n");

}
