#ifndef FATURAMENTO_H_INCLUDED
#define FATURAMENTO_H_INCLUDED
#include "types.h"
#include "database_implementation.h"

double get_multiplier_fat(int i){
     switch(i){
        case 1:
           return 1;
        break;
        case 2:
            return 1.15;
        break;
        case 3:
            return 1.3;
        break;
    }
    return 0;
}
struct tm * get_time_faturamento(){

    time_t now;

    struct tm *c_time;

    time(&now);
    c_time= localtime(&now);

    return c_time;
}

void faturamento(){

    int *plen, length, i, opt,sedeId, tempo, length_items, optSabor, maiorInd=0, maior=NULL ;
    plen=&length;

    pedidos *dbPedidos, Pedidos[get_entrycount(6)];
    dbPedidos=&Pedidos;

    int *plenI,lenItem[get_entrycount(1)];
    plenI=&lenItem;
    get_pedidos(dbPedidos, plen, plenI);

    int *plen_s,length_sabores;
    plen_s= &length_sabores;

    items *dbItems, Items[ get_entrycount(1)];

    dbItems=&Items;
    get_items_db(dbItems, plen_s, 3);

    int maiorT[length_sabores];
    double total=0;
    printf("\n Faturamento total, por sede ou por pizza mais pedida?\n1-  Total\n2- Sede\n3- Sabor\n\n");
    scanf("%d", &opt);
    switch(opt){
        case 1:
            printf("Qual tempo:\n1-Mensal\n2- Diario\n");
            scanf("%d", &tempo);
        break;
        case 2:
            printf("Qual Sede:\n0-Central\n1- Iranduba\n2-Secundaria\n");
            scanf("%d", &sedeId);
             printf("Cual tempo:\n1-Mensal\n2- Diario\n");
            scanf("%d", &tempo);
            break;
        case 3:
            printf("\nPela sede ou total?\n1- Sede\n2- Total\n");
            scanf("%d", &optSabor);
            switch(optSabor){
                case 1:
                    printf("Qual Sede:\n0-Central\n1- Iranduba\n2-Secundaria");
                    scanf("%d", &sedeId);
                    printf("Qual tempo:\n1-Mensal\n2- Diario\n");
                    scanf("%d", &tempo);
                break;
                case 2:
                    printf("Qual tempo:\n1-Mensal\n2- Diario\n");
                    scanf("%d", &tempo);
                    break;
                default:
                    printf("Op��o nao aceitada!");
                    break;
            }
            break;

        default:
            printf("Op��o nao aceitada!");
            break;

    }


    //char time_s[50];

    struct tm *now= get_time_faturamento();

    //clear maiorT
    for(i=0;i<length_sabores;i++){
         maiorT[i]=(int)NULL;
    }
    //checks in database
    for(i=0;i<length; i++){
    //check for sede or total
        if(opt<3){
                int j;
            //check total
            if(opt==1){

                                //Check for the day
            if( tempo==2 && dbPedidos[i].cliente.id!=0 && dbPedidos[i].time->tm_mday==now->tm_mday && dbPedidos[i].time->tm_mon ==now->tm_mon && dbPedidos[i].time->tm_year == now->tm_year ){

                length_items=plenI[i];
                printf("Pedido: %d\n",i+1 );
                for(j=0; j<length_items; j++){

                       if( dbPedidos[i].items_pedido[j].id){
                                    printf("Items:\n %s ------> %.2f--->tamanho: %i---->total: %.2f\n", dbPedidos[i].items_pedido[j].nome, dbPedidos[i].items_pedido[j].prize,  dbPedidos[i].items_pedido[j].tamanho,  dbPedidos[i].items_pedido[j].prize * get_multiplier_fat( dbPedidos[i].items_pedido[j].tamanho) );
                                }
                }
                total+=dbPedidos[i].prize;
                printf("\n----------------\n");
            }
            //checks for mensal
            if(tempo==1 && dbPedidos[i].cliente.id && dbPedidos[i].time->tm_mon ==now->tm_mon && dbPedidos[i].time->tm_year == now->tm_year){
                printf("Pedido: %d\n",i+1 );
                length_items=plenI[i];
                for(j=0; j<length_items; j++){

                       if( dbPedidos[i].items_pedido[j].id){
                                    printf("Items:\n %s ------> %.2f--->tamanho: %i---->total: %.2f\n", dbPedidos[i].items_pedido[j].nome, dbPedidos[i].items_pedido[j].prize,  dbPedidos[i].items_pedido[j].tamanho,  dbPedidos[i].items_pedido[j].prize * get_multiplier_fat( dbPedidos[i].items_pedido[j].tamanho) );
                                }
                }
                total+=dbPedidos[i].prize;
                printf("\n----------------\n");
            }
            }
            //check for sede
            else{

                //Check for the day
                if( tempo==2 && dbPedidos[i].cliente.id!=0 && dbPedidos[i].time->tm_mday==now->tm_mday && dbPedidos[i].time->tm_mon ==now->tm_mon && dbPedidos[i].time->tm_year == now->tm_year ){

                    length_items=plenI[i];
                    //check if pedido is from sede
                    if(dbPedidos[i].sede==sedeId ){
                            printf("Pedido: %d\n",i+1 );
                            for(j=0; j<length_items; j++){

                               if( dbPedidos[i].items_pedido[j].id){
                                    printf("Items:\n %s ------> %.2f--->tamanho: %i---->total: %.2f\n", dbPedidos[i].items_pedido[j].nome, dbPedidos[i].items_pedido[j].prize,  dbPedidos[i].items_pedido[j].tamanho,  dbPedidos[i].items_pedido[j].prize * get_multiplier_fat( dbPedidos[i].items_pedido[j].tamanho) );
                                }
                        }
                        total+=dbPedidos[i].prize;
                        printf("\n----------------\n");
                    }

                }
                //checks for mensal
                if(tempo==1 && dbPedidos[i].cliente.id!=0 && dbPedidos[i].time->tm_mon ==now->tm_mon && dbPedidos[i].time->tm_year == now->tm_year){
                    length_items=plenI[i];
                    if(dbPedidos[i].sede==sedeId ){
                            printf("Pedido: %d\n",i+1 );
                             for(j=0; j<length_items; j++){

                                if( dbPedidos[i].items_pedido[j].id){
                                    printf("Items:\n %s ------> %.2f--->tamanho: %i---->total: %.2f\n", dbPedidos[i].items_pedido[j].nome, dbPedidos[i].items_pedido[j].prize,  dbPedidos[i].items_pedido[j].tamanho,  dbPedidos[i].items_pedido[j].prize * get_multiplier_fat( dbPedidos[i].items_pedido[j].tamanho) );
                                }
                        }
                        total+=dbPedidos[i].prize;
                        printf("\n----------------\n");
                    }

                }
            }

        }

        else{
        break;
        }
    }

    //checks in database
    //check for sabores
    for(i=0;i<length; i++){
                int j, k;

                int maiorl[length_sabores];

                //Pela sede
                if(optSabor==1){
                    // quantidade de items do pedido
                    length_items=plenI[i];

                    //assign counter for sabores
                    int counter[length_sabores] ;
                    for(j=0;j<length_sabores;j++){
                        counter[j]=(int)NULL;
                        maiorl[j]=(int)NULL;
                    }

                        //checking quantidade de sabores pedidos
                        for(j=0; j<length_items; j++){
                                //pelo mes
                                if(tempo==1){
                                    if(dbPedidos[i].items_pedido[j].id && dbPedidos[i].sede==sedeId && dbPedidos[i].time->tm_mon ==now->tm_mon && dbPedidos[i].time->tm_year == now->tm_year ){
                                        for(k=0; k<length_sabores; k++){
                                           if(dbPedidos[i].items_pedido[j].id == dbItems[k].id){
                                                    counter[k]++;
                                           }
                                        }
                                    }
                                }else{
                                    //pelo dia
                                    if(dbPedidos[i].items_pedido[j].id && dbPedidos[i].sede==sedeId && dbPedidos[i].time->tm_mday==now->tm_mday && dbPedidos[i].time->tm_mon ==now->tm_mon && dbPedidos[i].time->tm_year == now->tm_year){
                                        for(k=0; k<length_sabores; k++){
                                           if(dbPedidos[i].items_pedido[j].id== dbItems[k].id){
                                                    counter[k]++;
                                           }
                                        }
                                    }
                                }
                        }


                        for(j=0;j<length_sabores;j++){
                                maiorl[j]+=counter[j];
                        }


                }
                //pelo total
                else{
                     // quantidade de items do pedido
                    length_items=plenI[i];
                    //assign counter for sabores
                    int counter[length_sabores] ;
                    for(j=0;j<length_sabores;j++){
                        counter[j]=(int)NULL;
                        maiorl[j]=(int)NULL;
                    }

                     for(j=0; j<length_items; j++){
                         //pelo mes
                            if(tempo==1){
                                   if(dbPedidos[i].items_pedido[j].id && dbPedidos[i].time->tm_mon ==now->tm_mon && dbPedidos[i].time->tm_year == now->tm_year ){
                                        for(k=0; k<length_sabores; k++){
                                           if(dbPedidos[i].items_pedido[j].id== dbItems[k].id){
                                                    counter[k]++;
                                           }
                                        }
                                    }
                            }
                            //pelo dia
                            else{
                                 if(dbPedidos[i].items_pedido[j].id  && dbPedidos[i].time->tm_mday==now->tm_mday && dbPedidos[i].time->tm_mon ==now->tm_mon && dbPedidos[i].time->tm_year == now->tm_year ){
                                        for(k=0; k<length_sabores; k++){
                                           if(dbPedidos[i].items_pedido[j].id== dbItems[k].id){
                                                    counter[k]++;
                                           }
                                        }
                                    }
                            }

                     }
                      for(j=0;j<length_sabores;j++){
                                maiorl[j]+=counter[j];
                        }

                }
                for(j=0;j<length_sabores;j++){
                                maiorT[j]+=maiorl[j];
                        }

    }

    if(opt==3){
            int j;
            for(j=0;j<length_sabores;j++){
                if(maior<maiorT[j]){
                    maior=maiorT[j];
                    maiorInd=j;
                }
            }
        printf("Sabor mais pedido mensalmente: %s ------- quantidade vendida: %d", dbItems[maiorInd].nome, maior );
    }

    if(opt<3){
        printf("\n Total-----> %.2f", total );
    }
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");

    //strftime(time_s, sizeof(time_s), "%x", now);

};

void vendas(){
        system("@cls||clear");

        int *plen,length;
        plen=&length;

        pedidos *dbPedidos, Pedidos[ get_entrycount(6)];
        dbPedidos=&Pedidos;
        int *plenI,lenItem[get_entrycount(6)];
        plenI=&lenItem;
        get_pedidos(dbPedidos, plen,plenI);

        int i, j, length_item, maiorInd;
        double  maior=0, sedes[3];

        for(i=0;i<3;i++){
         sedes[i]=(int)NULL;
        };

        //Pedidos
        for(i=0; i< length;i++){
            sedes[dbPedidos[i].sede]+=dbPedidos[i].prize;
        };

        for(j=0;j<3;j++){
            if(maior<sedes[j]){
                maior=sedes[j];
                maiorInd=j;
            }
        }

        switch(maiorInd){
        case 0:
            printf("Manaus com ingresos de %.2f R$\n", maior);
            length_item=sizeof(dbPedidos[maiorInd].items_pedido)/sizeof(dbPedidos[maiorInd].items_pedido[0]);
            for(i=0;i<length_item;i++){
                if(dbPedidos[i].sede==maiorInd){
                     printf("\nPedido %d:\n ",i+1);
                     for(j=0;j<3;j++){
                          if(dbPedidos[i].items_pedido[j].id){
                                printf("\nItem %d: %s:\n ", j, dbPedidos[i].items_pedido[j].nome);

                        }
                     }
                   printf("--------------\n");
                }
            }
            break;
        case 1:
            printf("Iranduba com ingresos de %.2f R$\n", maior);
            length_item=sizeof(dbPedidos[maiorInd].items_pedido)/sizeof(dbPedidos[maiorInd].items_pedido[0]);
            for(i=0;i<length_item;i++){
                if(dbPedidos[i].sede==maiorInd){
                     printf("\nPedido %d:\n ",i+1);
                     for(j=0;j<3;j++){
                          if(dbPedidos[i].items_pedido[j].id){
                                printf("\nItem %d: %s:\n ", j, dbPedidos[i].items_pedido[j].nome);

                        }
                     }
                   printf("--------------\n");
                }
            }
            break;
        case 2:
           printf("Secundario com ingresos de %.2f R$\n", maior);
            length_item=sizeof(dbPedidos[maiorInd].items_pedido)/sizeof(dbPedidos[maiorInd].items_pedido[0]);
            for(i=0;i<length_item;i++){
                if(dbPedidos[i].sede==maiorInd){
                     printf("\nPedido %d:\n ",i+1);
                     for(j=0;j<3;j++){
                          if(dbPedidos[i].items_pedido[j].id){
                                printf("\nItem %d: %s:\n ", j, dbPedidos[i].items_pedido[j].nome);

                        }
                     }
                   printf("--------------\n");
                }
            }
            break;
        }
        printf("\nPress ENTER key to go back to the menu\n");
        getch();
        system("@cls||clear");

}

void previsao(){
    system("@cls||clear");

     int *plen,length;
        plen=&length;

        pedidos *dbPedidos, Pedidos[ get_entrycount(6)];

        int *plenI,lenItem[get_entrycount(6)];
        *plenI=&lenItem;
        get_pedidos(dbPedidos, plen,plenI);


}

#endif // FATURAMENTO_H_INCLUDED
