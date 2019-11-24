#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef struct{
    int id;
    char *login;
    char *password;
    int user_permissions;
}users;

typedef struct{
    int id;
    char nome[Max];
    char enderezo[Max];
}sede;

typedef struct{
    int id;
    char *nome;
    double prize;
    int quantidade;//kg ou items
    int sede;
}produtos;

typedef struct {
    int id;
    char *nome;
    char *telefone;
    int sede;
    bool disponivel;
}motoqueiros;

typedef struct {
    int id;
    char *nome;
    double prize;
    produtos *produto;
    int quantidade;
    int *tamanho; //1- pequena; 2- mediana; 3- grande;
    bool promotion; // true or false;
    int type; //1- pizza; 2-bebida;
}items;

typedef struct{
    int id;
    char *CPF;
    char *nome;
    char *enderezo;
    char *telefone;
}clientes;

typedef struct {
    clientes cliente;
    items items_pedido[10];
    double prize;
    motoqueiros motoqueiro;
    users atendente;
    int sede;
    bool cancelado; //cancelado
    struct tm *time;
}pedidos;

typedef struct {

    clientes cliente;
    char description[500];
    int type; //0 suggestao/ 1 reclama��o
    struct tm *time; //type struct tm that contains the value of the time; in database we only will save month, day and year
    int sede;
}feedback;

#endif // TYPES_H_INCLUDED

