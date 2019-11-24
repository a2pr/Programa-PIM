#ifndef DATABASE_IMPLEMENTATION_H_INCLUDED
#define DATABASE_IMPLEMENTATION_H_INCLUDED
#include "functions.h"
#include <unistd.h>
#include "types.h"
#include <time.h>


void close_db(FILE *db){
    fclose(db);

}

void check_for_databases(){
    int i;
    char db_names[8][25]={
    "./db/dbUsers.txt", "./db/dbItems.txt","./db/dbSede.txt","./db/dbMotoqueiros.txt",
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

bool check_cliente_db(char cpf[], clientes *pcliente){
    int *plen, i, length;
    plen=&length;

    clientes *dbClientes,Clientes[get_entrycount(5)] ;
    dbClientes=&Clientes;
    //getting clientes from database
    get_clientes_db(dbClientes,plen);

    for(i=0;i<length-1;i++ ){
            if(strcmp(cpf,dbClientes[i].CPF)==0){
                printf("cliente no sistema!\n");
                *pcliente= dbClientes[i];
                return true;
            }
    }
    printf("cliente sem registro\n");
 return false;
}


void add_clientes_db(clientes *newCliente){
    if(check_cliente_db(newCliente->CPF, newCliente)){
        return;
    }

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
    items *pitems, dbitems[entryCount];
    pitems=&dbitems;

    //pitems=(items *)calloc(entryCount ,(entryCount * sizeof(items)));
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
     }else if(opt==2){
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


void get_motoqueiros(motoqueiros *test ,int *n){
    int i;
    char db_name[25]="./db/dbMotoqueiros.txt";
    FILE *pdbs;
    int entryCount;
    motoqueiros *pmotos=NULL, dbmotos;

     if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }

    pmotos=&dbmotos;

    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);

    pmotos=(motoqueiros *)calloc(entryCount ,(entryCount * sizeof(motoqueiros)));
    //printf("entryCount: %i\n",entryCount);
    //printf("size of motoqueiros struct:%i\nsize of pmotos: %i\n\n",sizeof(motoqueiros),sizeof(pmotos));
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
        //printf(" %s - %s\n", pclientes[i].enderezo, pclientes[i].telefone);
    }

    for(i=0; i<entryCount;i++){
            test[i]=pmotos[i];
     }
    *n=entryCount;
    close_db(pdbs);
    free(pmotos);
}

motoqueiros get_motoqueiros_by_id(int id){
    int *plen=NULL,len,i;
    plen=&len;
    motoqueiros *ptest=NULL, test[get_entrycount(3)], fail;
    ptest=&test;

    get_motoqueiros(ptest,plen);
    for(i=0; i<len;i++){
        if(test[i].id==id ){
           return  test[i];
        }
    }
    printf(" item not found with that id!\n");
    return fail;

}

users get_users_by_id(int id){
    int *plen=NULL,len,i;
    plen=&len;
    users *ptest=NULL, test[get_entrycount(0)], fail;
    ptest=&test;

    get_users(ptest,plen);
    for(i=0; i<len;i++){
        if(test[i].id==id ){
           return  test[i];
        }
    }
    printf(" item not found with that id!\n");
    return fail;
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

clientes get_clientes_cpf( char cpf[]){
    int *plen=NULL,len,i;
    plen=&len;
    clientes *ptest=NULL, test[get_entrycount(5)], fail;
    ptest=&test;

    get_clientes_db(ptest,plen);

    //printf("cpf: %s\n",cpf);
    for(i=0; i<len;i++){
        if(strcmp(test[i].CPF,cpf)==0 ){
           return  test[i];
        }
    }
    printf(" client not found with that id!\n");
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

void get_pedidos(pedidos *test ,int *n, int *lenItem[]){
    int i,j,entryCount;
    char db_name[25]="./db/dbPedidos.txt";
    FILE *pdbs;


     if(access(db_name,F_OK)==0){
        pdbs=fopen(db_name,"r");
        //printf("\n%s was open! \n", db_name);
    }


    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    pedidos *ppedidos, dbpedidos[entryCount];
    ppedidos=&dbpedidos;
    if( ppedidos ==NULL){
            printf("Vetor n�o alocado");
    }
    //printf("entryCount: %i\n",entryCount);
    //printf("size of produtos struct:%i\nsize of pprodutos: %i\n\n",sizeof(pedidos),sizeof(*ppedidos));
    for(i=0; i<entryCount;i++){
        int cpfLen, itemsLen,idMoto, idAten;
        struct tm *p, time;
        p=&time;
        char time_s[50];
        //gets cliente
        fscanf(pdbs, "%i",&cpfLen);
        char cpf_temp[cpfLen];
        fscanf(pdbs, "%s",&cpf_temp);
        ppedidos[i].cliente= get_clientes_cpf(cpf_temp);
        //gets items length and assing memory
        fscanf(pdbs, "%i",&itemsLen);
        lenItem[i]=itemsLen;
        ppedidos[i].items_pedido=calloc(itemsLen,sizeof(items));
        //gets pedido prize
        fscanf(pdbs, "%lf",&ppedidos[i].prize);

        //get motoqueiro
        fscanf(pdbs, "%i",&idMoto);
        ppedidos[i].motoqueiro= get_motoqueiros_by_id(idMoto);

        //get atendente
        fscanf(pdbs, "%i",&idAten);
        ppedidos[i].atendente= get_users_by_id(idAten);

        //get sede
        fscanf(pdbs, "%i",&ppedidos[i].sede);

        //get canceledo status
        fscanf(pdbs, "%i",&ppedidos[i].cancelado);

        //get time
        fscanf(pdbs, "%i",&time.tm_mday);
        fscanf(pdbs, "%i",&time.tm_mon);
        fscanf(pdbs, "%i",&time.tm_year);
        ppedidos[i].time=p;
        strftime(time_s, sizeof(time_s),"%x",ppedidos[i].time);

        //printf("%i. cpf: %s - prize: %.2f -motoqueiro:%s -atendente: %s - sede: %i -status:%i- time: %s \n", i+1,  ppedidos[i].cliente.CPF, ppedidos[i].prize, ppedidos[i].motoqueiro.nome, ppedidos[i].atendente.login, ppedidos[i].sede, ppedidos[i].cancelado, time_s );
        for(j=0;j<itemsLen;j++){
            int idItem;
            fscanf(pdbs, "%i",&idItem);
            ppedidos[i].items_pedido[j]=get_items_by_id(idItem);
            fscanf(pdbs, "%i",&ppedidos[i].items_pedido[j].tamanho );
            fscanf(pdbs, "%i",&ppedidos[i].items_pedido[j].promotion );
            fscanf(pdbs, "%i",&ppedidos[i].items_pedido[j].type );

            //printf("%i.%i id:%i-%s- prize: %.2f promotion:%i, qtd: %i , type: %i\n",i+1, j+1, ppedidos[i].items_pedido[j].id ,ppedidos[i].items_pedido[j].nome,ppedidos[i].items_pedido[j].prize, ppedidos[i].items_pedido[j].promotion, ppedidos[i].items_pedido[j].quantidade, ppedidos[i].items_pedido[j].type);
        }
        //printf("\n\n");
  }

      for(i=0;i<entryCount;i++){
        test[i]=ppedidos[i];
      }

    *n=entryCount;
    close_db(pdbs);
    free(ppedidos);
}

void add_pedidos( pedidos *newPedido, int *itemsN){
    int i,j , entryCount;
    char db_name[2][25]={"./db/dbPedidos.txt", "./db/dbPedidos_temp.txt"};
    FILE *pdbs;
    FILE *pdbs_temp;


    if(access(db_name[0],F_OK)==0){
        pdbs=fopen(db_name[0],"r");
        pdbs_temp=fopen(db_name[1],"w");
        //printf("\n%s was open! \n", db_name[0]);
        //printf("\n%s was created! \n", db_name[1]);
    }
    //gets entrys made
    fscanf(pdbs, "%i", &entryCount);
    int itemsLenfinal[entryCount+1];
    pedidos *ppedidos=NULL, dbpedidos[entryCount+1];
    ppedidos=&dbpedidos;
    ppedidos=(pedidos *)calloc(entryCount+1 ,(entryCount+1 * sizeof(pedidos)));
    if( ppedidos ==NULL){
            printf("Vetor n�o alocado");
    }

     for(i=0; i<entryCount;i++){
        int cpfLen, itemsLen,idMoto, idAten;
        struct tm *p, time;
        p=&time;
        char time_s[50];
        //gets cliente
        fscanf(pdbs, "%i",&cpfLen);
        char cpf_temp[cpfLen+2];
        fscanf(pdbs, "%s",&cpf_temp);

        ppedidos[i].cliente= get_clientes_cpf(cpf_temp);
        //gets items length and assing memory
        fscanf(pdbs, "%i",&itemsLen);
        ppedidos[i].items_pedido=calloc(itemsLen,sizeof(items));
        itemsLenfinal[i]=itemsLen;
        //gets pedido prize
        fscanf(pdbs, "%lf",&ppedidos[i].prize);

        //get motoqueiro
        fscanf(pdbs, "%i",&idMoto);
        ppedidos[i].motoqueiro= get_motoqueiros_by_id(idMoto);
        //get atendente
        fscanf(pdbs, "%i",&idAten);
        ppedidos[i].atendente= get_users_by_id(idAten);

        //get sede
        fscanf(pdbs, "%i",&ppedidos[i].sede);

        //get canceledo status
        fscanf(pdbs, "%i",&ppedidos[i].cancelado);

        //get time
        fscanf(pdbs, "%i",&time.tm_mday);
        fscanf(pdbs, "%i",&time.tm_mon);
        time.tm_mon-=1;
        fscanf(pdbs, "%i",&time.tm_year);
        time.tm_year-=1900;
        ppedidos[i].time=p;
        strftime(time_s, sizeof(time_s),"%x",ppedidos[i].time);

        printf("%i. cpf: %s - prize: %.2f -motoqueiro:%s -atendente: %s - sede: %i -status:%i- time: %s \n", i+1,  ppedidos[i].cliente.CPF, ppedidos[i].prize, ppedidos[i].motoqueiro.nome, ppedidos[i].atendente.login, ppedidos[i].sede, ppedidos[i].cancelado, time_s );
        for(j=0;j<itemsLen;j++){
            int idItem;
            fscanf(pdbs, " %d",&idItem);
            ppedidos[i].items_pedido[j]=get_items_by_id(idItem);
            fscanf(pdbs, "%i",&ppedidos[i].items_pedido[j].tamanho );
            fscanf(pdbs, "%i",&ppedidos[i].items_pedido[j].promotion );
            fscanf(pdbs, "%i",&ppedidos[i].items_pedido[j].type );

            printf("%i.%i id:%i-%s- prize: %.2f promotion:%i, qtd: %i , type: %i\n",i+1, j+1, ppedidos[i].items_pedido[j].id ,ppedidos[i].items_pedido[j].nome,ppedidos[i].items_pedido[j].prize, ppedidos[i].items_pedido[j].promotion, ppedidos[i].items_pedido[j].quantidade, ppedidos[i].items_pedido[j].type);
        }
        printf("\n\n");
  }
  printf("%i",*itemsN);
    itemsLenfinal[entryCount]= *itemsN;
    printf("new pedido length %i\n",itemsLenfinal[entryCount] );
    ppedidos[entryCount]=*newPedido;
    printf("%i. cpf: %s - prize: %.2f -motoqueiro:%s -atendente: %s - sede: %i -status:%i- time:  \n", i+1,  ppedidos[3].cliente.CPF, ppedidos[3].prize, ppedidos[3].motoqueiro.nome, ppedidos[3].atendente.login, ppedidos[3].sede, ppedidos[3].cancelado);

    fprintf(pdbs_temp,"%i\n", entryCount+1);

    for(int i=0;i<entryCount+1; i++){
        char time_d[10];
        char time_m[10];
        char time_y[10];
        strftime(time_d, sizeof(time_d), "%d",ppedidos[i].time );
        strftime(time_m, sizeof(time_m), "%m",ppedidos[i].time );
        strftime(time_y, sizeof(time_y), "%Y",ppedidos[i].time);

        fprintf(pdbs_temp,"%i %s %i %.0f",strlen(ppedidos[i].cliente.CPF), ppedidos[i].cliente.CPF, itemsLenfinal[i],  ppedidos[i].prize );
        fprintf(pdbs_temp,"% i %i %i",ppedidos[i].motoqueiro.id,ppedidos[i].atendente.id, ppedidos[i].sede );
        fprintf(pdbs_temp,"% i %s %s %s\n",ppedidos[i].cancelado, time_d, time_m, time_y);

        for(j=0;j< itemsLenfinal[i] ;j++){
            fprintf(pdbs_temp," %i %i ", ppedidos[i].items_pedido[j].id, ppedidos[i].items_pedido[j].tamanho);
            fprintf(pdbs_temp,"%i %i\n", ppedidos[i].items_pedido[j].promotion, ppedidos[i].items_pedido[j].type );
        }
    }

    close_db(pdbs);
    close_db(pdbs_temp);
    remove(db_name[0]);
    rename(db_name[1], db_name[0]);
    free(ppedidos);
    printf("success!");
}

#endif // DATABASE_IMPLEMENTATION_H_INCLUDED