#ifndef DATABASE_IMPLEMENTATION_H_INCLUDED
#define DATABASE_IMPLEMENTATION_H_INCLUDED
#include <unistd.h>

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


#endif // DATABASE_IMPLEMENTATION_H_INCLUDED
