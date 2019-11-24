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

int get_entrycount(int opt){
   //opt will be db enter
   int  entryCount;

  char db_names[8][25]={
    "./db/dbUsers.txt", "./db/dbItems.txt","./db/dbSede.txt","./db/dbMotoqueiros.txt",
    "./db/dbProdutos.txt","./db/dbClientes.txt","./db/dbPedidos.txt","./db/dbFeedback.txt"
    };

     FILE *pdbs;

      if(access(db_names[opt],F_OK)==0){
        //db open
        pdbs=fopen(db_names[opt],"r");
        //printf("File %s open\n", db_names[opt]);
      }

      fscanf(pdbs, "%i", &entryCount);
      fclose(pdbs);
      return entryCount;
}

void get_users(users *test, int *n){
    int i, entryCount;
    char db_name[25]="./db/dbUsers.txt";
    FILE *pdbs;

    if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }

    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    users *pusers=NULL;
    pusers=(users *)calloc(entryCount ,(entryCount * sizeof(users)));
    users dbusers[entryCount];
    pusers=&dbusers;


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

void get_clientes_db(clientes *test ,int *n){
    int i,entryCount;
    char db_name[25]="./db/dbClientes.txt";
    FILE *pdbs;

     if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }


    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    clientes *pclientes=NULL, dbclientes[entryCount];
    pclientes=&dbclientes;
    pclientes=(clientes *)calloc(entryCount ,(entryCount * sizeof(clientes)));

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

void get_motoqueiros_db(motoqueiros *test ,int *n){
    int i, entryCount;
    char db_name[25]="./db/dbMotoqueiros.txt";
    FILE *pdbs;


     if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
       // printf("\n%s was open! \n", db_name);
    }



    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    motoqueiros *pmotos=NULL, dbmotos;
    pmotos=&dbmotos;
    pmotos=(motoqueiros *)calloc(entryCount ,(entryCount * sizeof(motoqueiros)));

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
        fscanf(pdbs, "%s %i %i",pmotos[i].telefone,(int *)&pmotos[i].sede,(int *) &pmotos[i].disponivel);

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

void get_produtos_db(produtos *test ,int *n){

    int i,entryCount;
    char db_name[25]="./db/dbProdutos.txt";
    FILE *pdbs;

     if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }



    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    produtos *pprodutos=NULL, dbprodutos[entryCount];
    pprodutos=&dbprodutos;
    pprodutos=(produtos *)calloc(entryCount ,(entryCount * sizeof(produtos)));

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

void add_clientes_db(clientes *newCliente){
    int entryCount;
    char db_name[2][25]={"./db/dbClientes.txt", "./db/dbClientes_temp.txt"};
    FILE *pdbs;
    FILE *pdbs_temp;
     if(access(db_name[0],F_OK)==0){
        pdbs=fopen(db_name[0],"r");
        pdbs_temp=fopen(db_name[1],"w");
        //printf("\n%s was open! \n", db_name[0]);
        //printf("\n%s was created! \n", db_name[1]);
    }
    //gets entry count in original file
    fscanf(pdbs, "%i", &entryCount);
    //allocates memory for database info
    clientes*dbClientes= calloc(entryCount+1,sizeof(clientes)* entryCount+1);
    if( dbClientes ==NULL){
        printf("Vetor n�o alocado");
    }

    for(int i=0;i<entryCount;i++){
         //gets users id
        fscanf(pdbs, "%i",&dbClientes[i].id);
        int cpfLen, nomeLen, endLen, tlfLen;

        //gets CPF length, allocates memory, gets value and nome length
        fscanf(pdbs, "%i", &cpfLen);
        dbClientes[i].CPF= calloc(1,sizeof(char)*(cpfLen+1));
        fscanf(pdbs, "%s %i",dbClientes[i].CPF ,&nomeLen);

        //gets nome length, allocates memory, gets value and endere�� length
        dbClientes[i].nome= calloc(1,sizeof(char)*(nomeLen+1));
        fscanf(pdbs, "%s %i",dbClientes[i].nome ,&endLen);

        //gets enderezo length, allocates memory, gets value and telefone length
        dbClientes[i].enderezo= calloc(1,sizeof(char)*(endLen+2));
        fgets(dbClientes[i].enderezo,endLen+2, pdbs);
        fscanf(pdbs, "%i",&tlfLen);
         //gets telefone length, allocates memory and gets value
        dbClientes[i].telefone= calloc(1,sizeof(char)*(tlfLen+1));
        fscanf(pdbs, " %s", dbClientes[i].telefone);
        //printf("%i. %i- %s - %s -", i+1, dbClientes[i].id, dbClientes[i].CPF, dbClientes[i].nome );
        //printf(" %s - %s\n", dbClientes[i].enderezo, dbClientes[i].telefone);
    }

    newCliente[0].id= entryCount+1;
    dbClientes[entryCount]= *newCliente;

    for(int i=0;i<entryCount+1; i++){
       printf("%i. %i- %s - %s -", i+1, dbClientes[i].id, dbClientes[i].CPF, dbClientes[i].nome );
    printf(" %s - %s\n", dbClientes[i].enderezo, dbClientes[i].telefone);
    }
    //printf(" %i- %s - %s -", newCliente[0].id, newCliente[0].CPF, newCliente[0].nome );
    //printf(" %s - %s\n", newCliente[0].enderezo, newCliente[0].telefone);
    fprintf(pdbs_temp,"%i\n", entryCount+1);

    for(int i=0;i<entryCount+1; i++){
        fprintf(pdbs_temp,"%i %i %s %i %s %i %s %i %s\n",dbClientes[i].id, strlen(dbClientes[i].CPF), dbClientes[i].CPF, strlen(dbClientes[i].nome), dbClientes[i].nome, strlen(dbClientes[i].enderezo), dbClientes[i].enderezo, strlen(dbClientes[i].telefone), dbClientes[i].telefone);
    }


    close_db(pdbs);
    close_db(pdbs_temp);
    remove(db_name[0]);
    rename(db_name[1], db_name[0]);
    free(dbClientes);
    printf("success!");
}

void get_items_db(items *test,int *n, int opt){
    int i, j , entryCount;
    char db_name[25]="./db/dbItems.txt";
    FILE *pdbs;

    if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }

    fscanf(pdbs, "%i", &entryCount);
    //printf("entrys: %i \n",entryCount);
    items *pitems=NULL, dbitems[entryCount];
    pitems=&dbitems;

    pitems=(items *)calloc(entryCount ,(entryCount * sizeof(items)));
    if( pitems ==NULL){
        printf("Vetor n�o alocado");
    }
    //printf("sizeof pitems:%i \n",sizeof(pitems));
    for(i=0; i<entryCount; i++){

         //gets users id
        fscanf(pdbs, "%i",&pitems[i].id);
        int nomeLen, prodLen ,  tamanhoLen;

        //gets nome
        fscanf(pdbs, "%i", &nomeLen);
        pitems[i].nome= calloc(1,sizeof(char)*(nomeLen+3));
        if(  pitems[i].nome ==NULL){
            printf("Vetor n�o alocado");
        }
        fgets(pitems[i].nome,nomeLen+3, pdbs);

        //gets prize
        fscanf(pdbs, "%lf", &pitems[i].prize);

        //gets tamanho of produtos
        fscanf(pdbs, "%i", &prodLen );

        pitems[i].produto=calloc(prodLen,sizeof(produtos)*(prodLen));
        if(  pitems[i].produto ==NULL){
            printf("Vetor n�o alocado");
        }
        //gets quantidade
        fscanf(pdbs, "%i", &pitems[i].quantidade);

        //gets tamanho
        fscanf(pdbs, "%i", &tamanhoLen);
        pitems[i].tamanho=calloc(tamanhoLen,sizeof(int)*(tamanhoLen));
        if(  pitems[i].tamanho ==NULL){
            printf("Vetor n�o alocado");
        }
        for(j=0;j<tamanhoLen;j++){
            fscanf(pdbs, "%i", &pitems[i].tamanho[j]);
        }

        //get promotions
        fscanf(pdbs, "%i", &pitems[i].promotion);

        //get types
        fscanf(pdbs, "%i", &pitems[i].type);

        for(j=0; j<prodLen; j++){
             //gets users id
            fscanf(pdbs, " %i",&pitems[i].produto[j].id);
            int nomeLen;
            //gets nome length, allocates memory, gets value
            fscanf(pdbs, "%i", &nomeLen);
            pitems[i].produto[j].nome= calloc(1,sizeof(char)*(nomeLen+3));
            if( pitems[i].produto[j].nome ==NULL){
                printf("Vetor n�o alocado");
            }
            fgets(pitems[i].produto[j].nome,nomeLen+3, pdbs);

            //gets value for pre�o, quantidade, sede
            fscanf(pdbs, "%lf",(float *)&pitems[i].produto[j].prize);
            //printf("%i.%i. id:%i-%s- prize: %.2f\n",i+1, j+1,  pitems[i].produto[j].id, pitems[i].produto[j].nome, pitems[i].produto[j].prize);
        }
        //printf("%i. id:%i-%s- prize: %.2f promotion:%i, qtd: %i , type: %i\n", i+1, pitems[i].id ,pitems[i].nome, pitems[i].prize, pitems[i].promotion, pitems[i].quantidade,  pitems[i].type);
    }

    int entryCountPizza=0, entryCountBebidas=0;
    j=0;
    for(i=0; i<entryCount;i++){
            if(opt==1){
                if(pitems[i].type==1){
                    test[j]=pitems[i];
                    entryCountPizza++;
                    j++;
                }
            }else{
                if(pitems[i].type==2){
                    test[j]=pitems[i];
                    entryCountBebidas++;
                    j++;
                }
            }
     }

     if(opt==1){
        *n=entryCountPizza;
     }else{
        *n=entryCountBebidas;
     }

     if(opt==3){
         for(i=0; i<entryCount;i++){
           test[i]=pitems[i];
        }
        *n=entryCount;
     }
    // id; len of nome; prize; lenofprodutos; qtd; lenoftamanhos; tamanhos;promotion;type

    close_db(pdbs);
    free(pitems);
}


produtos get_produtos_by_id(int id ){
    int *plen=NULL,len,i;
    plen=&len;
    produtos *ptest=NULL, test[100],fail;
    ptest=&test;

    get_produtos_db(ptest,plen);

    for(i=0; i<len;i++){
        if(test[i].id==id){
           return  test[i];
        }
    }
    printf(" item not found with that id!\n");
    return fail;

}

items get_items_by_id(int id ){
    int *plen=NULL,len,i;
    plen=&len;
    items *ptest=NULL, test[get_entrycount(1)], fail;
    ptest=&test;

    get_items_db(ptest,plen,3);

    for(i=0; i<len;i++){
        if(test[i].id==id){
           return  test[i];
        }
    }
    printf(" item not found with that id!\n");
    return fail;


}



#endif // DATABASE_IMPLEMENTATION_H_INCLUDED
