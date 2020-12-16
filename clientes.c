#include "clientes.h"
#include "structs.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void visualizarClientesCadastrados(Clientes* clientesCadastrados, int* contadorClientes) {

    char tecla;
    printf("\n-------------------------\n");
    for( int i = 0; i < (*contadorClientes); i++) { //imprime clientes cadastrados 

        printf("%s\n", clientesCadastrados[i].nome);
        printf("%s\n", clientesCadastrados[i].telefone);
        printf("%s\n", clientesCadastrados[i].endereco);
    }

    printf("-------------------------\n");
    printf("Pressione qualquer tecla para continuar: ");
    tecla = getchar();
    printf("\n-------------------------\n");

}

void visualizarClientesCadastradosVendas(Clientes* clientesCadastrados, int* contadorClientes) {

    for( int i = 0; i < (*contadorClientes); i++) {

        printf("%s - ID: %d\n", clientesCadastrados[i].nome, clientesCadastrados[i].id); //imprime os clientes cadastrados especificamente para vendas (mostrando so id e nome)

    }

}

void cadastrarCliente(Clientes* clientesCadastrados, int* contadorClientes) {

    char stop = 'Y';

    for( int i = *contadorClientes; ; i++) { //realiza cadastro ate usuario dizer que nao quer mais

        getchar();
        clientesCadastrados[i].id = i;
        printf("Insira o nome: ");
        scanf("%[^\n]s", clientesCadastrados[i].nome);
        getchar();
        printf("Insira  telefone (xx-9zzzz-zzzz): ");
        scanf("%[^\n]s", clientesCadastrados[i].telefone);
        getchar();
        printf("Insira o endereco: ");
        scanf("%[^\n]s", clientesCadastrados[i].endereco);
        getchar();

        //perguntar se o usuário deseja cadastrar mais um cliente
        printf("\n Deseja cadastrar mais um cliente? (Y/N)\n");
        scanf("%c", &stop);

        //caso a resposta seja não, executar esse if e quebrar o loop
        if(toupper(stop) == 'N') {

            *contadorClientes = i + 1;

            break;

        }

    }
}
