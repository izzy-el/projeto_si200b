//
// Created by izael on 01/12/2020.
//

#ifndef PROJECT_V4_0_STRUCTS_H
#define PROJECT_V4_0_STRUCTS_H

typedef struct {
    int id;
    char nomeCliente[60];
    char produto[40];
    int quantidade;
    char data[20];
    float valor;
} Pedidos;

typedef struct {
    int id;
    char nome[60];
    char telefone[20];
    char endereco[150];
} Clientes;

typedef struct {
    char nomeProd[40];
    float preco;
    int quantidade;
    int id;
} Produtos;


struct aluno  /* defini��o da estrutura */
{
      int numero;
      char nome[20];
	  char curso[15];
};


#endif //PROJECT_V4_0_STRUCTS_H
