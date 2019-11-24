#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

struct users{
    int id;
    char *login;
    char *password;
    int user_permissions;
};

struct sede{
    int id;
    char nome[Max];
    char enderezo[Max];
};

struct produtos{
    int id;
    char *nome;
    double prize;
    int quantidade;//kg ou items
    int sede;
};

struct motoqueiros{
    int id;
    char *nome;
    char *telefone;
    int sede;
    bool disponivel;
};

struct items{
    int id;
    char nome[Max];
    double prize;
    struct produtos produto[Max];
    int quantidade;
    int tamanho; //1- pequena; 2- mediana; 3- grande;
    bool promotion; // true or false;
    int type; //1- pizza; 2-bebida;
};

struct clientes{
    int id;
    char *CPF;
    char *nome;
    char *enderezo;
    char *telefone;
};

struct pedidos{
    struct clientes cliente;
    struct items items_pedido[10];
    double prize;
    struct motoqueiros motoqueiro;
    struct users atendente;
    int sede;
    bool cancelado; //cancelado
    struct tm *time;
};

struct feedback{

    struct clientes cliente;
    char description[500];
    int type; //0 suggestao/ 1 reclamação
    struct tm *time; //type struct tm that contains the value of the time; in database we only will save month, day and year
    int sede;
};

#endif // TYPES_H_INCLUDED

