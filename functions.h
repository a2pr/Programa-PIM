#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "types.h"

bool check_user(struct users *current_user, int *logout){
    //gets information from database;
    //for now just a variable
 struct users test_user={1,"andres","123456",0};

   if(strcmp(current_user->login, test_user.login)==0 && strcmp(current_user->password, test_user.password)==0 ){
		*logout=1;
		return 1;
    }else{
    	return 0;
    }
}

bool check_cliente(char cpf[], struct clientes *pcliente){
    int i=0;
    int length;
    //for testing purpose
    struct clientes test_cliente[3]= {
    {1,"789456","andres","Manaus","987456123"},
    {1,"123456","simon","Peru","987456111"}
    };

    length= sizeof(test_cliente)/sizeof(test_cliente[0]);
    for(;i<length-1;i++ ){
            if(strcmp(cpf,test_cliente[i].CPF)==0){
                printf("cliente no sistema!\n");
                *pcliente= test_cliente[i];
                return true;
            }
    }
    printf("cliente sem registro\n");
 return false;
}

double get_multiplier(int i){
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

void choose_pizza(struct pedidos *ppedido){
    int i, opt, Qtd, tamanho, lenght;
    //test pizzas
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
    struct items test_pizzas[]={
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
            .id=12,
            .nome= "Pizza 4 queijos",
            .prize= 15,
            .produto= {test_producto[0],test_producto[2]},
            .quantidade=4,
            .promotion= false
        },
         {
            .id=14,
            .nome= "Pizza Doce",
            .prize= 50,
            .produto= {test_producto[0],test_producto[2]},
            .quantidade=0,
            .promotion= false
        }
    };

    lenght= sizeof(test_pizzas)/sizeof(test_pizzas[0]);
    system("@cls||clear");
    printf("----------Nossas pizzas disponivels-----\n");
    for(i=0; i<lenght; i++){

        if(test_pizzas[i].quantidade!=0){
            printf(" %d-> %s , prize: %.2f \n", i+1, test_pizzas[i].nome, test_pizzas[i].prize);
        }
    }
        printf("Escolha sua pizza: ");
        scanf("%d", &opt);
        printf("\nTamanho da pizza?");
        printf("\n1- Pequena\n");
        printf("\n2- Mediana\n");
        printf("\n3- Grande\n\n");
        scanf("%d", &tamanho);
        printf("\nQuantidade desejada?");
        scanf("%d", &Qtd);


    if(opt && Qtd!=0){
        double total=0;
        test_pizzas[opt-1].tamanho=tamanho;
        double multiplier= get_multiplier(test_pizzas[opt-1].tamanho);
        for(i=0; i<Qtd; i++){
            ppedido->items_pedido[i]= test_pizzas[opt-1];
            ppedido->items_pedido[i].quantidade=1;
            total+= test_pizzas[opt-1].prize*multiplier;

        }
        ppedido->prize=total;
    }
    printf("\n%d pizzas adicionadas\n", Qtd);
}

void choose_bebida(struct pedidos *ppedido){
    int i,j,used, opt, Qtd, lenght,lenght_total;
    struct produtos test_producto[]={
        {
            30,"Monster", 2.55, 100
        },
        {
            31,"Coca", 2.55, 20
        },
        {
            35,"pepsi", 4.55, 20
        }
    };

    struct items test_bebidas[]={
        {
            .id=20,
            .nome= "Monster",
            .prize= 8.66,
            .produto[0]= test_producto[0],
            .quantidade=100,
            .tamanho=1,
            .promotion= true
        },
        {
            .id=21,
            .nome= "Coca-Cola",
            .prize= 4.55,
            .produto[0]= test_producto[1],
            .quantidade=20,
            .tamanho=1,
            .promotion= false
        },
        {
            .id=22,
            .nome= "Pepsi",
            .prize= 4.55,
            .produto= {test_producto[2]},
            .quantidade=20,
            .tamanho=1,
            .promotion= false
        }
    };

    lenght= sizeof(test_bebidas)/sizeof(test_bebidas[0]);
    lenght_total= sizeof(ppedido->items_pedido)/sizeof(ppedido->items_pedido[0]);
    printf("\n----------Nossas bebidas disponivels-----\n");

    for(i=0; i<lenght; i++){

        if(test_bebidas[i].quantidade!=0){
            printf(" %d-> %s , prize: %.2f \n", i+1, test_bebidas[i].nome, test_bebidas[i].prize);
        }
    }
    printf("Escolha sua bebida: ");
    scanf("%d", &opt);
    printf("\nQuantidade desejada?");
    scanf("%d", &Qtd);

//checks pedido last added space index
    for(j=0;j<lenght_total;j++){
        if(!ppedido->items_pedido[j].id){
            used=j;
            break;
        }
    }
//checks if opt and qtd not null
    if(opt && Qtd!=0){
        double total=0;
        int check=Qtd+used;
        //starts loop in first unsued space in pedido
        for(i=used; i<check; i++){
                if(check<=lenght_total){
                    ppedido->items_pedido[i]= test_bebidas[opt-1];
                    ppedido->items_pedido[i].quantidade=1;
                    total+= test_bebidas[opt-1].prize;
                }
        }
        ppedido->prize+=total;
    }
    printf("\n%d Bebidas adicionadas\n", Qtd);
}


bool check_en_estoque(struct pedidos *ppedido){
    int i,j,length_e, length_p;

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

    struct items test_estoque[]={
        {
            .id=10,
            .nome= "Pizza portuguesa",
            .prize= 15,
            .produto[0]= test_producto[0],
            .quantidade=5,
            .promotion= true
        },
        {
            .id=11,
            .nome= "Pizza calabresa",
            .prize= 15,
            .produto[0]= test_producto[1],
            .quantidade=3,
            .promotion= false
        },
        {
            .id=12,
            .nome= "Pizza 4 queijos",
            .prize= 15,
            .produto= {test_producto[0],test_producto[2]},
            .quantidade=2,
            .promotion= false
        },
         {
            .id=14,
            .nome= "Pizza Doce",
            .prize= 50,
            .produto= {test_producto[0],test_producto[2]},
            .quantidade=0,
            .promotion= false
        },
        {
            .id=20,
            .nome= "Monster",
            .prize= 8.66,
            .produto[0]= test_producto[0],
            .quantidade=100,
            .tamanho=1,
            .promotion= true
        },
        {
            .id=21,
            .nome= "Coca-Cola",
            .prize= 4.55,
            .produto[0]= test_producto[1],
            .quantidade=20,
            .tamanho=1,
            .promotion= false
        },
        {
            .id=22,
            .nome= "Pepsi",
            .prize= 4.55,
            .produto= {test_producto[2]},
            .quantidade=2,
            .tamanho=1,
            .promotion= false
        }
    };

    length_e=sizeof(test_estoque)/sizeof(test_estoque[0]);
    length_p=sizeof(ppedido->items_pedido)/sizeof(ppedido->items_pedido[0]);

    for(i=0; i<length_p;i++){
        for(j=0; j<length_e;j++){
            if(ppedido->items_pedido[i].id == test_estoque[j].id){
                test_estoque[j].quantidade-=ppedido->items_pedido[i].quantidade;
                if(test_estoque[j].quantidade<=0 ){
                    return false;
                }
            }
        }
    }
    return true;

}

void cadastrar_cliente(struct clientes *pcliente, char cpf[]){
    int i, length;
    //for testing
    struct clientes test_cliente[3]= {
    {1,"789456","andres","Manaus","987456123"},
    {1,"123456","simon","Peru","987456111"}
    };

    length=sizeof(test_cliente)/sizeof(test_cliente[0]);
    for(i=0;i<length;i++){
        if(!test_cliente[i].id){
            pcliente->id=i;
            break;
        }
    }
    strcpy(pcliente->CPF, cpf);
    printf("\n Cliente não cadastrado!\nPress ENTER key para cadastrar\n");
    getch();
    system("@cls||clear");

    printf("\nNome do cliente: \n");
    scanf("%s", pcliente->nome);
    printf("\nEndereçõ do cliente: \n");
    scanf("%s", pcliente->enderezo);
    printf("\nTelefone do cliente: \n");
    scanf("%s", pcliente->telefone);

    /*
        Here should be added to database
    */

    printf("cliente cadastrado !\n");

}

void set_motoqueiro( struct pedidos *ppedido){
    int length, j;
    bool opt=false;
    //for testing
    struct motoqueiros test_list_motoqueiros[5]={
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
        },
        {
          .id=3,
          .nome="Ricardo",
          .telefone="4568456",
          .sede=2,
          .disponivel= false
        },
        {
          .id=4,
          .nome="Pepega",
          .telefone="4568456",
          .sede=1,
          .disponivel= true
        }
    };

    length=sizeof(test_list_motoqueiros)/sizeof(test_list_motoqueiros[0]);

    while(!opt){
        //pseudo random number assign
        j=rand()%length;
        //missing condition for sede
        if(test_list_motoqueiros[j].id && test_list_motoqueiros[j].disponivel){
            ppedido->motoqueiro=test_list_motoqueiros[j];
            opt=true;
        }
    }
    printf("motoqueiro %s assinado\n ",ppedido->motoqueiro.nome );

}

void set_time( struct pedidos *ppedido){
    int i,length, multiplier,qtd, j=0;
    double time;
    length=sizeof(ppedido->items_pedido)/sizeof(ppedido->items_pedido[0]);
    //another logic for this should be added
    for(i=0;i<length;i++){
        if(ppedido->items_pedido[i].id){
                multiplier=get_multiplier(ppedido->items_pedido[i].tamanho);
                qtd=ppedido->items_pedido[i].quantidade;
                j+=(multiplier*qtd);
        }

    }
    time= (j*20); //min; formula= soma de cada item(quantidade de item * multiplier de tamanho) *20 min
    if(time>=60){
        if((int)time%60 != 0){
            int hours= (int)time/60;
            printf("Demorara %d horas para chegar seu pedido\n",hours);
        }
    }else{
        printf("Demorara %.0f minutos para chegar seu pedido\n", time);
    }


}

void cadastrar_pedido(struct users *atendente, struct clientes *pcliente,  struct pedidos *ppedido){
    bool pedido_ok=false;
    while(!pedido_ok){
        int length,i;

        //choose from menu
        choose_pizza(ppedido);
        choose_bebida(ppedido);

        //showing results
        length=sizeof(ppedido->items_pedido)/sizeof(ppedido->items_pedido[0]);
        for(i=0;i< length;i++){
            if(ppedido->items_pedido[i].id){
                printf("\n %s quantidade de items: %d ; custo-> %.2f\n",ppedido->items_pedido[i].nome, ppedido->items_pedido[i].quantidade, ppedido->items_pedido[i].prize );
            }
        }
        printf("-------------------\n");
        printf("Conta ate agora: %.2f \n",ppedido->prize);
        // check in estoque if values are available

        if(!check_en_estoque(ppedido)){

                    memset(ppedido->items_pedido,0,10*sizeof(struct items));

            printf("\n Items de pedido fora de estoque\nPress ENTER key to go back to menu\n");
            getch();
        }else{
            pedido_ok= true;
        }
    }

    //adding cliente to pedido
    char cpf[Max];
    printf("\nO Cliente esta cadastrado?\n inserir CPF: ");
    scanf("%s", cpf);
    if( check_cliente(cpf, pcliente) ){
        ppedido->cliente= *pcliente;
        printf("Cliente %s asignado !\n", ppedido->cliente.nome);
    }else{
        cadastrar_cliente(pcliente, cpf);
        printf("\n cliente: %s cpf: %s \n", pcliente->nome, pcliente->CPF);

    }


    set_motoqueiro(ppedido);

    set_time(ppedido);
    //set sede by global variable

    //Pedido vai ser mandado para a base de dados;

    printf("\n\n Pedido Cadastrado !");
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");
}



//needs to return pedidos by client
void check_for_pedido(struct clientes *pcliente, char cpf[]){
    int i,k,length_p, length_i;
    //for testing
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

    struct items test_item[2]={
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

    struct pedidos test_pedidos[] = {
            {
                .cliente= test_cliente[0],
                .items_pedido[0]= test_item[0],
                .prize= 15 ,
                .motoqueiro= test_motoqueiro[0],
                .atendente= 2,
                .sede=1
            },
            {
                .cliente= test_cliente[1],
                .items_pedido[0]= test_item[1],
                .prize= 15 ,
                .motoqueiro= test_motoqueiro[1],
                .atendente= 2,
                .sede=1
            }
        };

    length_p=sizeof(test_pedidos)/sizeof(test_pedidos[0]);
    for(i=0; i<length_p;i++){
        if(strcmp(cpf,test_pedidos[i].cliente.CPF)==0){
                length_i=sizeof(test_pedidos[i].items_pedido)/sizeof(test_pedidos[i].items_pedido[0]);
                printf("\n Para esse cpf temos os siguientes pedidos feitos\n");
                for(k=0;k<length_i;k++){
                    if(test_pedidos[i].items_pedido[k].id){
                        printf("\n Pedido %d: \n%s ----> prize: %.2f\n",k+1, test_pedidos[i].items_pedido[k].nome,test_pedidos[i].items_pedido[k].prize );
                    }

                }
                printf("-----------");

        }
    }
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");
}

void get_menu(struct items (*menu)[Max]){
    //for testing purpose
    struct produtos test_produto[2]={{1,"item A", 5, 10}};

    struct items test_items[]={
        {
            .id=1,
            "pizza A",
            .prize= 22.5,
            .produto= test_produto[0],
            .quantidade=10
        },
        {
            .id= 2,
            "pizza B",
            .prize= 22.8,
            .produto= test_produto[0],
            .quantidade= 5
        }
    };
    int i, lenght;
    lenght= sizeof(test_items)/sizeof(test_items[0]);
    for(i=0;i<=lenght-1;i++){
        //assign items to menu
        menu[i]->id= test_items[i].id;
        strcpy(menu[i]->nome,test_items[i].nome);
        (*menu[i]).prize= test_items[i].prize;
        (*menu[i]).produto->id = test_produto[0].id;
        strcpy((*menu[i]).produto->nome, test_produto[0].nome);
        (*menu[i]).produto->prize= test_produto[0].prize;
        (*menu[i]).produto->quantidade = test_produto[0].quantidade;
        (*menu[i]).quantidade= test_items[i].quantidade;
        //testing values assings
        //printf("Items del menu:\n id: %d \nitem name:%s\nprize: %.2f \n Quantidade: %d\n ",menu[i]->id, menu[i]->nome, (*menu[i]).prize, (*menu[i]).quantidade  );
        //printf("produtos usados:\n id: %d \n item name:%s\nprize: %.2f \n Quantidade: %d\n",(*menu[i]).produto->id, (*menu[i]).produto->nome,(*menu[i]).produto->prize,  (*menu[i]).produto->quantidade  );
    }
    printf("values assign !");
}

void cadastrar_pedido_promotion(struct users *atendente, struct clientes *pcliente,  struct pedidos *ppedido){
     bool pedido_ok=false;
    while(!pedido_ok){
       int length,i;
        //showing results
        length=sizeof(ppedido->items_pedido)/sizeof(ppedido->items_pedido[0]);
        for(i=0;i< length;i++){
            if(ppedido->items_pedido[i].id){
                printf("\n %s quantidade de items: %d ; custo-> %.2f\n",ppedido->items_pedido[i].nome, ppedido->items_pedido[i].quantidade, ppedido->items_pedido[i].prize );
            }
        }
        printf("-------------------\n");
        printf("Conta ate agora: %.2f \n",ppedido->prize);
        // check in estoque if values are available

        if(!check_en_estoque(ppedido)){

                    memset(ppedido->items_pedido,0,10*sizeof(struct items));

            printf("\n Items de pedido fora de estoque\nPress ENTER key to go back to menu\n");
            getch();
        }else{
            pedido_ok= true;
        }
    };

    //adding cliente to pedido
    char cpf[Max];
    printf("\nO Cliente esta cadastrado?\n inserir CPF: ");
    scanf("%s", cpf);
    if( check_cliente(cpf, pcliente) ){
        ppedido->cliente= *pcliente;
        printf("Cliente %s asignado !\n", ppedido->cliente.nome);
    }else{
        cadastrar_cliente(pcliente, cpf);
        printf("\n cliente: %s cpf: %s \n", pcliente->nome, pcliente->CPF);

    }


    set_motoqueiro(ppedido);

    set_time(ppedido);
    //set sede by global variable

    //Pedido vai ser mandado para a base de dados;

    printf("\n\n Pedido Cadastrado !");
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");
}

void show_promotion(struct users *atendente, struct clientes *pcliente,  struct pedidos *ppedido){
    system("@cls||clear");
    int opt,i, length,tamanho, Qtd;

    //for testing
     struct produtos test_producto[]={
        {
            30,"Monster", 2.55, 100
        },
        {
            31,"Coca", 2.55, 20
        },
        {
            35,"pepsi", 4.55, 20
        }
    };

    struct items test_promotions[]={
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
            .id=12,
            .nome= "Pizza 4 queijos",
            .prize= 15,
            .produto= {test_producto[0],test_producto[2]},
            .quantidade=4,
            .promotion= false
        },
         {
            .id=14,
            .nome= "Pizza Doce",
            .prize= 50,
            .produto= {test_producto[0],test_producto[2]},
            .quantidade=0,
            .promotion= false
        },
        {
            .id=20,
            .nome= "Monster",
            .prize= 8.66,
            .produto[0]= test_producto[0],
            .quantidade=100,
            .tamanho=1,
            .promotion= true
        },
        {
            .id=21,
            .nome= "Coca-Cola",
            .prize= 4.55,
            .produto[0]= test_producto[1],
            .quantidade=20,
            .tamanho=1,
            .promotion= false
        },
        {
            .id=22,
            .nome= "Pepsi",
            .prize= 4.55,
            .produto= {test_producto[2]},
            .quantidade=20,
            .tamanho=1,
            .promotion= false
        }
    };

    length= sizeof(test_promotions)/sizeof(test_promotions[0]);
    printf("\n----------Nossas Promoções disponivels-----\n");

    for(i=0; i<length; i++){
        if(test_promotions[i].quantidade!=0 && test_promotions[i].promotion==true ){
            printf(" %d-> %s , prize: %.2f \n", i+1, test_promotions[i].nome, test_promotions[i].prize);
        }
    }

    printf("Escolha sua promoção: ");
    scanf("%d", &opt);
     printf("\nTamanho da pizza?");
    printf("\n1- Pequena\n");
    printf("\n2- Mediana\n");
    printf("\n3- Grande\n\n");
    scanf("%d", &tamanho);
    printf("\nQuantidade desejada?");
    scanf("%d", &Qtd);

     if(opt && Qtd!=0){
        double total=0;
        test_promotions[opt-1].tamanho=tamanho;
        double multiplier= get_multiplier(test_promotions[opt-1].tamanho);
        for(i=0; i<Qtd; i++){
            ppedido->items_pedido[i]= test_promotions[opt-1];
            ppedido->items_pedido[i].quantidade=1;
            total+= test_promotions[opt-1].prize*multiplier;

        }
        ppedido->prize=total;
    }

    cadastrar_pedido_promotion(atendente,pcliente, ppedido);
}



 void get_clientes(){
 printf("getting clientes.... \n");
 }
 void show_R_S(){
 printf("getting reclamações e suggestões..... \n");
 }
 void show_estoque(){
 printf("in the estoque....\n");
 }


#endif // FUNCTIONS_H_INCLUDED
