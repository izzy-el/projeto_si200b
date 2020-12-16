#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "interface.h"

int main() {

    FILE *produtos, *pedidos, *clientes; //Um arquivo para produtos, um para pedidos, um para clientes

    int contadorProdutos = 0, contadorClientes = 0, contadorPedidos = 0, pedidosSobrescritos = 0, contadorSobrescritos = 0;

    Produtos produtosDisponiveis[20]; //declarando vetores de structures para puxar os dados dos arquivos
    Pedidos pedidosCadastrados[40];
    Clientes clientesCadastrados[60];

    produtos = fopen("arq_produtos.dat", "rb"); //puxando os dados de produtos
    if(produtos != NULL) {
        fread(&contadorProdutos, sizeof(int), 1, produtos);
        fread(produtosDisponiveis, sizeof(Produtos), contadorProdutos, produtos);
        fclose(produtos);
    }

    pedidos = fopen("arq_pedidos.dat", "rb"); //puxando os dados de pedidos
    if(pedidos != NULL) {
        fread(&contadorPedidos, sizeof(int), 1, pedidos);
        fread(&contadorSobrescritos, sizeof(int), 1, pedidos);
        fread(&pedidosSobrescritos, sizeof(int), 1, pedidos);
        fread(pedidosCadastrados, sizeof(Pedidos), contadorPedidos, pedidos);
        fclose(pedidos);
    }

    clientes = fopen("arq_clientes.dat", "rb"); //puxando os dados de clientes
    if(clientes != NULL) {
        fread(&contadorClientes, sizeof(int), 1, clientes);
        fread(clientesCadastrados, sizeof(Clientes), contadorClientes, clientes);
        fclose(clientes);
    }


    menu(produtos, pedidos, clientes, produtosDisponiveis, pedidosCadastrados, clientesCadastrados, &contadorProdutos, &contadorClientes, &contadorPedidos, &pedidosSobrescritos, &contadorSobrescritos);

    return 0;

}
