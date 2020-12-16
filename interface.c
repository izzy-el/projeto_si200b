#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "estoque.h"
#include "vendas.h"
#include "interface.h"
#include "clientes.h"


//--------------------------------------------------------
//--------------- Função Menu Principal ------------------
//--------------------------------------------------------

void limparTela() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //funcao para limpar tela
    //system("clear");
}

void menu(FILE* produtos, FILE* pedidos, FILE* clientes, Produtos *produtosDisponiveis, Pedidos *pedidosCadastrados, Clientes *clientesCadastrados, int *contadorProdutos, int *contadorClientes, int *contadorPedidos, int *pedidosSobrescritos, int *contadorSobrescritos) {

    int opcaoMenu, opcao;

    do {

        printf("-------------------------\n");
        printf("Ecolha uma opcao abaixo:\n");
        printf("1 - Clientes\n");
        printf("2 - Produtos/Vendas\n");
        printf("3 - Estoque\n\n");

        printf("10 - Sair\n");
        printf("-------------------------\n");

        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {

            case 1:
                do {

                    printf("Voce escolheu: Clientes \n");
                    printf("Escolha uma opcao: \n");
                    printf("1 - Visualizar clientes cadastrados\n");
                    printf("2 - Cadastrar um novo cliente\n");
                    printf("3 - Voltar\n");
                    scanf("%d", &opcaoMenu);
                    printf("-------------------------\n");

                    switch (opcaoMenu) {

                        case 1:
                            visualizarClientesCadastrados(clientesCadastrados, contadorClientes); // chama funcao que lista clientes
                            break;

                        case 2:
                            cadastrarCliente(clientesCadastrados, contadorClientes); //chama funcao de cadastrar clientes
                            break;

                        case 3: // assim que o usuario seleciona a opcao de encerrar o cadastramento de clientes, os novos dados sao salvos no arquivo
                            clientes = fopen("arq_clientes.dat", "wb");
                            if(clientes == NULL) {
                                printf("Erro na abertura do arquivo.\n\n");
                                break;
                            }
                            else {
                                fwrite(contadorClientes, sizeof(int),1,clientes);
                                fwrite(clientesCadastrados, sizeof(Clientes), *contadorClientes, clientes);
                                fclose(clientes);
                            }
                            break;

                        default:
                            printf("Escolha uma opcao valida.\n"); // caso o usuario selecione uma opcao inexistente
                            break;
                    }

                } while(opcaoMenu != 3); // se repete ate o usuario querer encerrar essa funcionalidade
                break;

            case 2:

                do{

                    interfaceVendas();
                    scanf("%d", &opcao);

                    switch (opcao) {

                        case 1:
                            listarCatalogo(produtosDisponiveis, contadorProdutos); //Função para verificar produtos do cardapio
                            break;

                        case 2:
                            if((interfaceCadastrarVendas(produtosDisponiveis, pedidosCadastrados, clientesCadastrados, contadorProdutos, contadorPedidos, pedidosSobrescritos, contadorSobrescritos, contadorClientes)) == 0) { //Função para cadastrar venda
                                break;
                            }

                        case 3:
                            listarPedidos(pedidosCadastrados, contadorPedidos); //Função para verificar pedidos em andamento
                            break;

                        case 4:
                            finalizarPedido(pedidosCadastrados, contadorPedidos, pedidosSobrescritos); //Funcao para finalizar um pedido
                            break; 

                        case 5: //assim que o usuario seleciona para finalizar essa funcionalidade, os pedidos e novos clientes sao cadastrados nos arquivos
                            pedidos = fopen("arq_pedidos.dat", "wb");
                            if(pedidos == NULL) {
                                printf("Erro na abertura do arquivo.\n\n");
                                break;
                            }
                            else {
                                fwrite(contadorPedidos, sizeof(int), 1, pedidos);
                                fwrite(contadorSobrescritos, sizeof(int), 1, pedidos);
                                fwrite(pedidosSobrescritos, sizeof(int), 1, pedidos);
                                fwrite(pedidosCadastrados, sizeof(Pedidos), *contadorPedidos, pedidos);
                                fclose(pedidos);
                            }

                            clientes = fopen("arq_clientes.dat", "wb");
                            if(clientes == NULL) {
                                printf("Erro na abertura do arquivo.\n\n");
                                break;
                            }
                            else {
                                fwrite(contadorClientes, sizeof(int),1,clientes);
                                fwrite(clientesCadastrados, sizeof(Clientes), *contadorClientes, clientes);
                                fclose(clientes);
                            }
                            break; 

                        default:
                            printf("Por favor, selecione uma opção válida\n");
                            break;
                    }

                } while(opcao != 5); //repete ate o usuario sair
                break;

            case 3:
                interfaceEstoque(produtos, produtosDisponiveis, contadorProdutos); //chama funcao de estoque
                break;

            default:
                break;
            }

    } while (opcaoMenu != 10); //menu se repete ate usuario digitar 10 para finalizar programa

}

//--------------------------------------------------------
//----------------- Função Menu Vendas -------------------
//--------------------------------------------------------
void interfaceVendas() {

    printf("-------------------------\n");
    printf("Voce selecionou Produtos.\n");
    printf("-------------------------\n");
    printf("Escolha uma opcao abaixo:\n");
    printf("1 - Verificar Produtos\n");
    printf("2 - Cadastrar Venda\n");
    printf("3 - Em Andamento\n");
    printf("4 - Finalizar Pedido\n");
    printf("5 - Voltar\n");
    printf("-------------------------\n");

}

//--------------------------------------------------------
//---------- Função Interface Cadastrar Vendas -----------
//--------------------------------------------------------
int interfaceCadastrarVendas(Produtos *produtosDisponiveis, Pedidos *pedidosCadastrados, Clientes *clientesCadastrados, int *contadorProdutos, int *contadorPedidos, int *pedidosSobrescritos, int *contadorSobrescritos, int* contadorClientes){

    int opcao = 0, id = 0,  opcaoProduto = 0, quantidade = 0;
    char data[12];

    printf("-------------------------\n");
    printf("Voce selecionou Cadastrar Venda.\n");
    printf("-------------------------\n");
    printf("Voce deseja: \n");
    printf(" 1 - Escolher um cliente existente\n");
    printf(" 2 - Cadastrar novo cliente \n");
    printf(" 3 - Voltar\n");
    printf("-------------------------\n");
    scanf("%d", &opcao);

    do {

        if (opcao > 3) {

            printf("-------------------------\n");
            printf("!!!Selecione uma opcao valida!!!\n");
            scanf("%d", &opcao);

        }

    } while (opcao > 3);

    switch (opcao) {

    case 1:

        printf("-------------------------\n");
        printf("Você selecionou 'Escolher cliente existente'.\n");
        printf("Esses são os clientes atuais: \n");
        printf("-------------------------\n");

        visualizarClientesCadastradosVendas(clientesCadastrados, contadorClientes); //Chama função de clientes.c para visualizar clientes

        printf("-------------------------\n");
        printf("Digite o ID do cliente: "); //Anota o ID do cliente que será utilizado para cadastrar pedido
        scanf("%d", &id);

        break;

    case 2:

        printf("-------------------------\n");
        printf("Você selecionou 'Cadastrar Novo Cliente'.\n");
        printf("-------------------------\n");
        cadastrarCliente(clientesCadastrados, contadorClientes); //Chama função de clientes.c para cadastrar novo cliente
        printf("-------------------------\n");
        printf("Esses são os clientes atuais: \n");
        printf("-------------------------\n");
        visualizarClientesCadastradosVendas(clientesCadastrados, contadorClientes); //Chama função de clientes.c para visualizar clientes

        printf("-------------------------\n");
        printf("Digite o ID do cliente: "); //Anota o ID do cliente que será utilizado para cadastrar pedido
        scanf("%d", &id);

        break;

    default:
        return 0; //Caso selecione outra opção, sai da função
        break;
    }

    printf("-------------------------\n");
    printf("Insira a data atual (dd/mm/yyyy): "); //usuario digita a data atual
    scanf("%s", data);

    do {

        printf("\n-------------------------\n");
        printf("Os seguintes produtos estao disponiveis: \n"); 
        listarCatalogo(produtosDisponiveis, contadorProdutos);

        printf("Informe o ID do produto que deseja: "); //usuario informa produto que deseja
        scanf("%d", &opcaoProduto);

        if (opcaoProduto > (*contadorProdutos)) {
            printf("\nPor favor, selecione uma opcao valida.\n");
        }

    } while (opcaoProduto > (*contadorProdutos));

    printf("\n-------------------------\n");
    printf("\nInforme a quantidade que deseja: "); //usuario informa quantidade que deseja
    scanf("%d", &quantidade);

    if (quantidade > produtosDisponiveis[opcaoProduto].quantidade) { //caso nao haja quantidade suficiente no estoque

        printf("\nQuantidade insuficiente, por favor, reponha o estoque.\n");
        return 0;

    }

    cadastrarPedido(produtosDisponiveis, pedidosCadastrados, clientesCadastrados, id, data, opcaoProduto, quantidade, contadorPedidos, pedidosSobrescritos, contadorSobrescritos);

    return 0;

}

//--------------------------------------------------------
//----------------- Função Menu Estoque ------------------
//--------------------------------------------------------

void interfaceEstoque(FILE* produtos, Produtos *produtosDisponiveis, int *contadorProdutos) {

    int opcao, opcao1;

    do { // menu de opcoes do estoque//

        printf("-------------------------\n");
        printf("GERENCIAMENTO DE ESTOQUE\n");
        printf("-------------------------\n");
        printf("Escolha uma opcao abaixo:\n");
        printf("1 - Produtos do estoque\n");
        printf("2 - Produtos do catalogo\n");
        printf("3 - Voltar\n"); //sai da funcao de estoque
        printf("-------------------------\n");
        scanf("%d", &opcao1);

        switch (opcao1) {

            case 1:
                printf("-------------------------\n");
                printf("Voce selecionou Produtos do Estoque.\n");
                printf("-------------------------\n");
                printf("Escolha uma opcao abaixo:\n");
                printf("1 - Disponiveis\n");
                printf("2 - Adicionar quantidade\n");
                printf("3 - Remover quantidade\n");
                printf("4 - Voltar\n"); //volta para o menu principal de estoques
                printf("-------------------------\n");
                scanf("%d", &opcao);

                switch (opcao) {

                    case 1: //listar os produtos disponiveis e suas quantidades
                        printf("-------------------------\n");
                        printf("Voce selecionou Disponiveis.\n");
                        printf("-------------------------\n");
                        printf("Produtos disponiveis no estoque:\n");
                        listarEstoque(produtosDisponiveis, contadorProdutos);
                        break;

                    case 2: //selecionar um determinado produto para incrementar
                        printf("-------------------------\n");
                        printf("Voce selecionou Adicionar Quantidade.\n");
                        printf("-------------------------\n");
                        printf("Produtos disponiveis no estoque:\n");
                        listarCatalogo(produtosDisponiveis, contadorProdutos);
                        adicionarEstoque(produtosDisponiveis, contadorProdutos);
                        break;

                    case 3: //selecionar um determinado produto para decrementar
                        printf("-------------------------\n");
                        printf("Voce selecionou Remover Quantidade.\n");
                        printf("-------------------------\n");
                        printf("Produtos disponiveis no estoque:\n");
                        listarCatalogo(produtosDisponiveis, contadorProdutos);
                        removerEstoque(produtosDisponiveis, contadorProdutos);
                        break;

                    case 4: //voltar
                        break;
                    }

                    break;

            case 2: //pensar em algo para adicionar/remover novos produtos do catalogo :(
                printf("-------------------------\n");
                printf("Voce selecionou Produtos do Catalogo.\n");
                printf("-------------------------\n");
                printf("Escolha uma opcao abaixo:\n");
                printf("1 - Disponiveis\n");
                printf("2 - Adicionar produto\n");
                printf("3 - Remover produto\n");
                printf("4 - Alterar produto\n");
                printf("5 - Voltar\n"); //volta para o menu principal de estoques
                printf("-------------------------\n");
                scanf("%d", &opcao);

                switch (opcao) {

                    case 1: //listar os produtos disponiveis e suas quantidades
                        printf("-------------------------\n");
                        printf("Voce selecionou Disponiveis.\n");
                        printf("-------------------------\n");
                        printf("Produtos disponiveis no catalogo:\n");
                        listarCatalogo(produtosDisponiveis, contadorProdutos);
                        break;

                    case 2: //selecionar um determinado produto para incrementar
                        printf("-------------------------\n");
                        printf("Voce selecionou Adicionar Produto.\n");
                        printf("-------------------------\n");
                        printf("Produtos disponiveis no estoque:\n");
                        listarCatalogo(produtosDisponiveis,contadorProdutos);
                        adicionarCatalogo(produtosDisponiveis, contadorProdutos);
                        break;

                    case 3: //selecionar um determinado produto para decrementar
                        printf("-------------------------\n");
                        printf("Voce selecionou Remover Produto.\n");
                        printf("-------------------------\n");
                        printf("Produtos disponiveis no catalogo:\n");
                        listarCatalogo(produtosDisponiveis,contadorProdutos);
                        removerCatalogo(produtosDisponiveis, contadorProdutos);
                        break;

                    case 4:
                        printf("-------------------------\n");
                        printf("Voce selecionou Alterar Produto.\n");
                        printf("-------------------------\n");
                        printf("Produtos disponiveis no catalogo:\n");
                        listarCatalogo(produtosDisponiveis,contadorProdutos);
                        alterarCatalogo(produtosDisponiveis, contadorProdutos);
                        break;

                    case 5:
                        break;
                }

                break;

            case 3: //quando o usuario seleciona para finalizar a funcionalidade, os possiveis novos produtos do catalogo são armazenados no arquivo
                produtos = fopen("arq_produtos.dat", "wb");
                if(produtos == NULL) {
                    printf("Erro na abertura do arquivo.\n\n");
                    break;
                }
                else {
                    fwrite(contadorProdutos, sizeof(int),1, produtos);
                    fwrite(produtosDisponiveis, sizeof(Produtos), *contadorProdutos, produtos);
                    fclose(produtos);
                }
                break;

            default:
                printf("Escolha uma opcao valida!!\n");
                break;

        }
    } while (opcao1 != 3); //repete ate usuario finalizar
}
