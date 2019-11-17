#ifndef FATURAMENTO_H_INCLUDED
#define FATURAMENTO_H_INCLUDED
#include "types.h"
#include "functions.h"

struct tm * get_time_faturamento(){

    time_t now;

    struct tm *c_time;

    time(&now);
    c_time= localtime(&now);

    return c_time;
}

void faturamento(){
    double total=0;
    int length,i, j, opt,sedeId, tempo, length_items, optSabor ;
    printf("\n Faturamento total, por sede ou por pizza mais pedida?\n1-  Total\n2- Sede\n3- Sabor\n\n");
    scanf("%d", &opt);
    switch(opt){
        case 1:
            printf("Cual tempo:\n1-Mensal\n2- Diario\n");
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
                    printf("Opção nao aceitada!");
                    break;
            }
            break;

        default:
            printf("Opção nao aceitada!");
            break;

    }

   struct tm test_dates[10]={
        {
            .tm_mday=17,
            .tm_mon=10,
            .tm_year=2019-1900
        },
        {
            .tm_mday=15,
            .tm_mon=10,
            .tm_year=2019-1900
        },
        {
            .tm_mday=24,
            .tm_mon=10,
            .tm_year=2019-1900
        },
        {
            .tm_mday=10,
            .tm_mon=10,
            .tm_year=2019-1900
        },
        {
            .tm_mday=24,
            .tm_mon=2,
            .tm_year=2019-1900
        },
        {
            .tm_mday=2,
            .tm_mon=2,
            .tm_year=2019-1900
        },
        {
            .tm_mday=10,
            .tm_mon=4,
            .tm_year=2019-1900
        },
        {
            .tm_mday=25,
            .tm_mon=4,
            .tm_year=2019-1900
        },
        {
            .tm_mday=11,
            .tm_mon=4,
            .tm_year=2019-1900
        }
    };

    struct produtos test_producto[]={
        {
            15,"dough", 2.55, 25
        },
        {
            18,"chesse", 2.55, 15
        },
        {
            25,"tomatoes", 4.55, 50
        }
    };

    struct items test_item[3]={
        {
            .id=10,
            .nome= "Pizza portuguesa",
            .prize= 15,
            .produto[0]= test_producto[0],
            .quantidade=4,
            .promotion= true
        },
        {
            .id=11,
            .nome= "Pizza calabresa",
            .prize= 15,
            .produto[0]= test_producto[1],
            .quantidade=4,
            .promotion= false
        },
         {
            .id=101,
            .nome= "Pizza diego",
            .prize= 22,
            .produto[0]= test_producto[1],
            .quantidade=4,
            .promotion= false
        }

    };

    struct clientes test_cliente[2]={
        {
            .id=1,
            .CPF="789456",
            .nome="andres",
            .enderezo="Manaus",
            .telefone="987456123"
        },
        {
            .id=2,
            .CPF="7123456",
            .nome="Simon",
            .enderezo="Peru",
            .telefone="9874565698"
        }

    };

    struct motoqueiros test_motoqueiro[2]={
                  {
                     .id=1,
                    .nome="Julio",
                    .telefone="789456",
                    .sede=1,
                    .disponivel= true

                  },
                   {
                    .id=2,
                  .nome="Manuel",
                  .telefone="4568",
                  .sede=1,
                  .disponivel= true
                }
            };


    struct pedidos test_for_day[10]={
       {
            .cliente= test_cliente[0],
            .items_pedido[0]= test_item[0],
            .prize= 15 ,
            .motoqueiro= test_motoqueiro[0],
            .atendente= 2,
            .sede=0,
            .time= &test_dates[0]
       },
       {
            .cliente= test_cliente[1],
            .items_pedido[0]= test_item[1],
            .prize= 30 ,
            .motoqueiro= test_motoqueiro[0],
            .atendente= 2,
            .sede=1,
            .time= &test_dates[1]
       },
       {
            .cliente= test_cliente[1],
            .items_pedido[0]= test_item[2],
            .prize= 20 ,
            .motoqueiro= test_motoqueiro[1],
            .atendente= 2,
            .sede=2,
            .time= &test_dates[2]
       }
    };

    struct pedidos test_for_month;

    struct pedidos test_for_multiple_sedes_day;
    struct pedidos test_for_multiple_sedes_month;

    char time_s[50];
    struct tm *now= get_time_faturamento();
    length= sizeof(test_for_day)/sizeof(test_for_day[0]);

    //checks in database
    for(i=0;i<length; i++){
    //check for sede or total
        if(opt<3){
            //check total
            if(opt==1){

                                //Check for the day
            if( tempo==2 && test_for_day[i].cliente.id!=0 && test_for_day[i].time->tm_mday==now->tm_mday && test_for_day[i].time->tm_mon ==now->tm_mon && test_for_day[i].time->tm_year == now->tm_year ){

                length_items=sizeof(test_for_day[i].items_pedido)/sizeof(test_for_day[i].items_pedido[0]);

                for(j=0; j<length_items; j++){

                        if( test_for_day[i].items_pedido[j].id){
                            printf("Pedido: %d\nItems:\n %s ------> %.2f\n",i+1, test_for_day[i].items_pedido[j].nome, test_for_day[i].items_pedido[0].prize );
                        }
                }
                total+=test_for_day[i].prize;
                printf("\n----------------\n");
            }
            //checks for mensal
            if(tempo==1 && test_for_day[i].cliente.id!=0 && test_for_day[i].time->tm_mon ==now->tm_mon && test_for_day[i].time->tm_year == now->tm_year){

                length_items=sizeof(test_for_day[i].items_pedido)/sizeof(test_for_day[i].items_pedido[0]);

                for(j=0; j<length_items; j++){

                        if( test_for_day[i].items_pedido[j].id){
                            printf("Pedido: %d\nItems:\n %s ------> %.2f\n",i+1, test_for_day[i].items_pedido[j].nome, test_for_day[i].items_pedido[0].prize );
                        }
                }
                total+=test_for_day[i].prize;
                printf("\n----------------\n");
            }
            }
            //check for sede
            else{

                //Check for the day
                if( tempo==2 && test_for_day[i].cliente.id!=0 && test_for_day[i].time->tm_mday==now->tm_mday && test_for_day[i].time->tm_mon ==now->tm_mon && test_for_day[i].time->tm_year == now->tm_year ){

                    length_items=sizeof(test_for_day[i].items_pedido)/sizeof(test_for_day[i].items_pedido[0]);
                    //check if pedido is from sede
                    if(test_for_day[i].sede==sedeId ){
                            for(j=0; j<length_items; j++){

                                if( test_for_day[i].items_pedido[j].id){
                                    printf("Pedido: %d\nItems:\n %s ------> %.2f\n",i+1, test_for_day[i].items_pedido[j].nome, test_for_day[i].items_pedido[0].prize );
                                }
                        }
                        total+=test_for_day[i].prize;
                        printf("\n----------------\n");
                    }

                }
                //checks for mensal
                if(tempo==1 && test_for_day[i].cliente.id!=0 && test_for_day[i].time->tm_mon ==now->tm_mon && test_for_day[i].time->tm_year == now->tm_year){
                    length_items=sizeof(test_for_day[i].items_pedido)/sizeof(test_for_day[i].items_pedido[0]);
                    if(test_for_day[i].sede==sedeId ){
                             for(j=0; j<length_items; j++){

                                if( test_for_day[i].items_pedido[j].id){
                                    printf("Pedido: %d\nItems:\n %s ------> %.2f\n",i+1, test_for_day[i].items_pedido[j].nome, test_for_day[i].items_pedido[0].prize );
                                }
                        }
                        total+=test_for_day[i].prize;
                        printf("\n----------------\n");
                    }

                }
            }

        }
        //check for sabores
        else{

        }

    }
    printf("\n Total-----> %.2f", total );
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");

    //strftime(time_s, sizeof(time_s), "%x", now);

};
#endif // FATURAMENTO_H_INCLUDED
