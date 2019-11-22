#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
#include "types.h"

void create_cu_user(struct users *pusers, char login[10], char pass[10]){
    struct users *values;
    int length_login=0,length_pass=0;
    length_login=strlen(login);
    length_pass=strlen(pass);

    values=(struct users *)malloc(sizeof(struct users));
    values->login=(char*)malloc(sizeof(char)*length_login);
    values->password=(char*)malloc(sizeof(char)*length_pass);
    strcpy(values->login,login);
    strcpy(values->password,pass);
    printf("%s,%s\n",values->login,values->password );

    *pusers=*values;

}

#endif // MEMORY_H_INCLUDED
