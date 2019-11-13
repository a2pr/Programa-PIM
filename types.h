#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

struct users{
    int id;
    char login[Max];
    char password[Max];
    int user_permissions;
};
struct sede{
    int id;
    char nome[Max];
    char enderezo[Max];
};


struct produtos{
    int id;
    char nome[Max];
    double prize;
    int quantidade;
};

struct motoqueiros{
    int id;
    char nome[Max];
    char telefone[Max];
    int sede;
};

struct items{
    int id;
    char nome[Max];
    double prize;
    struct produtos produto[Max];
    int quantidade;
    int tamanho; //1- pequena; 2- mediana; 3- grande;
    bool promotion; // true or false;
};

struct clientes{
    int id;
    char CPF[Max];
    char nome[Max];
    char enderezo[Max];
    char telefone[Max];
};

struct pedidos{
    struct clientes cliente;
    struct items items_pedido[10];
    double prize;
    struct motoqueiros motoqueiro;
    struct users atendente;
    int sede;
};

#endif // TYPES_H_INCLUDED

