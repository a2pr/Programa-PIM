#ifndef DATABASE_IMPLEMENTATION_H_INCLUDED
#define DATABASE_IMPLEMENTATION_H_INCLUDED
#include <unistd.h>
#include "types.h"

void close_db(FILE *db){
    fclose(db);

}

void check_for_databases(){
    int i;
    char db_names[8][25]={
    "./db/dbUser.txt", "./db/dbItems.txt","./db/dbSede.txt","./db/dbMotoqueiros.txt",
    "./db/dbProdutos.txt","./db/dbClientes.txt","./db/dbPedidos.txt","./db/dbFeedback.txt"
    };

     FILE *pdbs[8];

     for(i=0;i<8;i++){
      if(access(db_names[i],F_OK)==0){
            //db is found
        //printf("File %s exits\n", db_names[i]);

      }else{
          // db is create
            pdbs[i]= fopen(db_names[i],"w");
            fclose(pdbs[i]);
            //printf(" %s created!\n", db_names[i]);

      }
    };
}

void get_users(struct users *test, int *n){
    int i, entryCount;
    char db_name[25]="./db/dbUsers.txt";
    FILE *pdbs;

    if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }

    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    struct users *pusers=NULL, dbusers[entryCount];
    pusers=&dbusers;
    pusers=(struct users *)calloc(entryCount ,(entryCount * sizeof(struct users)));

    if( pusers ==NULL){
        printf("Vetor n�o alocado");
    }

    for(i=0; i<entryCount;i++){
        //gets users id
        fscanf(pdbs, "%i",&pusers[i].id);
        int loginLen, passLen;
        //gets logins length and creates sizes.
        fscanf(pdbs, "%i", &loginLen);
        pusers[i].login= calloc(1,sizeof(char)*(loginLen+1));
        //gets login and passlens. creates sizes of password
        fscanf(pdbs, " %s %i", pusers[i].login,&passLen);
        pusers[i].password= calloc(1,sizeof(char)*(passLen+1));
        //gets pass and permisions
        fscanf(pdbs, " %s %i", pusers[i].password, &pusers[i].user_permissions);
        //printf("%i. %i- %s - %s - %i\n", i+1, pusers[i].id, pusers[i].login, pusers[i].password, pusers[i].user_permissions );
    }

     for(i=0; i<entryCount;i++){
            test[i]=pusers[i];
     }

    *n=entryCount;
    close_db(pdbs);
    free(pusers);
}

void get_clientes_db(struct clientes *test ,int *n){
    int i,entryCount;
    char db_name[25]="./db/dbClientes.txt";
    FILE *pdbs;

     if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }


    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    struct clientes *pclientes=NULL, dbclientes[entryCount];
    pclientes=&dbclientes;
    pclientes=(struct clientes *)calloc(entryCount ,(entryCount * sizeof(struct clientes)));

     if( pclientes ==NULL){
        printf("Vetor n�o alocado");
    }

    for(i=0; i<entryCount;i++){
        //gets users id
        fscanf(pdbs, "%i",&pclientes[i].id);
        int cpfLen, nomeLen, endLen, tlfLen;
        //printf("%i",i);
        //gets CPF length, allocates memory, gets value and nome length
        fscanf(pdbs, "%i", &cpfLen);
        pclientes[i].CPF= calloc(1,(sizeof(char)*(cpfLen+1)));
        fscanf(pdbs, "%s %i",pclientes[i].CPF ,&nomeLen);

        //gets nome length, allocates memory, gets value and endere�� length
        pclientes[i].nome= calloc(1,sizeof(char)*(nomeLen+1));
        fscanf(pdbs, "%s %i",pclientes[i].nome ,&endLen);

        //gets enderezo length, allocates memory, gets value and telefone length
        pclientes[i].enderezo= calloc(1,sizeof(char)*(endLen+3));
        fgets(pclientes[i].enderezo,endLen+3, pdbs);
        fscanf(pdbs, "%i",&tlfLen);
         //gets telefone length, allocates memory and gets value
        pclientes[i].telefone= calloc(1,sizeof(char)*(tlfLen+1));
        fscanf(pdbs, " %s", pclientes[i].telefone);
        //printf("%i. %i- %s - %s -", i+1, pclientes[i].id, pclientes[i].CPF, pclientes[i].nome );
        //printf(" %s - %s\n", pclientes[i].enderezo, pclientes[i].telefone);
    }
    for(i=0; i<entryCount;i++){
            test[i]=pclientes[i];
     }
    *n=entryCount;
    close_db(pdbs);
    free(pclientes);

}

void get_motoqueiros_db(struct motoqueiros *test ,int *n){
    int i, entryCount;
    char db_name[25]="./db/dbMotoqueiros.txt";
    FILE *pdbs;


     if(access(db_name,F_OK)==0){
        //pdbs=fopen(db_name,"r");
        printf("\n%s was open! \n", db_name);
    }



    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    struct motoqueiros *pmotos=NULL, dbmotos[entryCount];
    pmotos=&dbmotos;
    pmotos=(struct motoqueiros *)calloc(entryCount ,(entryCount * sizeof(struct motoqueiros)));

    if( pmotos ==NULL){
        printf("Vetor n�o alocado");
    }

    for(i=0; i<entryCount;i++){
        //gets users id
        fscanf(pdbs, "%i",&pmotos[i].id);
        int nomeLen, tlfLen;
        //printf("%i",i);
        //gets nome length, allocates memory, gets value and nome length
        fscanf(pdbs, "%i", &nomeLen);
        pmotos[i].nome= calloc(1,sizeof(char)*(nomeLen+1));
        fscanf(pdbs, "%s %i",pmotos[i].nome ,&tlfLen);

        //gets tlf length, allocates memory, gets value for telefone, sede, disponivel length
        pmotos[i].telefone= calloc(1,sizeof(char)*(tlfLen+1));
        fscanf(pdbs, "%s %i %i",pmotos[i].telefone,&pmotos[i].sede, &pmotos[i].disponivel);

        //printf("%i. %i- %s - %s -sede:%i - %i\n", i+1,  pmotos[i].id, pmotos[i].nome, pmotos[i].telefone, pmotos[i].sede, pmotos[i].disponivel );

    }
    getchar();
    for(i=0; i<entryCount;i++){
            test[i]=pmotos[i];
     }
    *n=entryCount;
    close_db(pdbs);
    free(pmotos);
}

void get_produtos_db(struct produtos *test ,int *n){

    int i,entryCount;
    char db_name[25]="./db/dbProdutos.txt";
    FILE *pdbs;

     if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }



    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    struct produtos *pprodutos=NULL, dbprodutos[entryCount];
    pprodutos=&dbprodutos;
    pprodutos=(struct produtos *)calloc(entryCount ,(entryCount * sizeof(struct produtos)));

    if( pprodutos ==NULL){
        printf("Vetor n�o alocado");
    }

    for(i=0; i<entryCount;i++){
        //gets users id
        fscanf(pdbs, "%i",&pprodutos[i].id);
        int nomeLen;
        //printf("%i",i);
        //gets nome length, allocates memory, gets value
        fscanf(pdbs, "%i", &nomeLen);
        pprodutos[i].nome= calloc(1,sizeof(char)*(nomeLen+3));
        if( pprodutos[i].nome ==NULL){
            printf("Vetor n�o alocado");
        }
        fgets(pprodutos[i].nome,nomeLen+3, pdbs);
        //gets value for pre�o, quantidade, sede
        fscanf(pdbs, "%lf %i %i",&pprodutos[i].prize,&pprodutos[i].quantidade, &pprodutos[i].sede);
        //printf("%i. %i-%s- prize: %f -qtd:%i -sede: %i\n", i+1,  pprodutos[i].id, pprodutos[i].nome, pprodutos[i].prize, pprodutos[i].quantidade, pprodutos[i].sede );
    }

    for(i=0; i<entryCount;i++){
            test[i]=pprodutos[i];
     }

    *n=entryCount;
    close_db(pdbs);
    free(pprodutos);

}
#endif // DATABASE_IMPLEMENTATION_H_INCLUDED
