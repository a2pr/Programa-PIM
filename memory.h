#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
#include "types.h"

void create_cu_user(users *pusers, char login[10], char pass[10]){
    users *values;
    int length_login=0,length_pass=0;
    length_login=strlen(login);
    length_pass=strlen(pass);

    values=(users *)malloc(sizeof(users));
    values->login=(char*)malloc(sizeof(char)*length_login);
    values->password=(char*)malloc(sizeof(char)*length_pass);
    strcpy(values->login,login);
    strcpy(values->password,pass);
    printf("%s,%s\n",values->login,values->password );

    *pusers=*values;

}

void create_item(items *newItem, int qtd, items db[],int opt ){
    int i=0,j=0,nomeLen, prodLen=10;
    newItem= (items *)calloc(qtd, sizeof(items)*qtd);

    for(i=0;i<qtd; i++){
        nomeLen=strlen(db[opt-1].nome);
        //prodLen=sizeof(db[opt-1].produto)/sizeof(produtos);
        newItem[i].nome=(char *)malloc(sizeof(char)*nomeLen);
        newItem[i].produto=(produtos *)calloc(prodLen, sizeof(produtos)*prodLen);
        newItem[i].tamanho=(int *)malloc(sizeof(int));
    }

}

#endif // MEMORY_H_INCLUDED
