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
int check_cliente(char cpf[], struct clientes *pcliente){
    int i=0;
    int length;
    //for testing purpose
    struct clientes test_cliente[2]= {
    {1,"789456","andres","Manaus","987456123"},
    {1,"123456","simon","Peru","987456111"}
    };

    length= sizeof(test_cliente)/sizeof(test_cliente[0]);
    for(;i<length-1;i++ ){
            if(strcmp(cpf,test_cliente[i].CPF)==0){
                printf("cliente no sistema!\n");
                *pcliente= test_cliente[i];
                return 1;
            }
    }
    printf("cliente sem registro\n");
 return 0;
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
                    total+= test_bebidas[opt-1].prize;
                }
        }
        ppedido->prize+=total;
    }
    printf("\n%d Bebidas adicionadas\n", Qtd);
}

void cadastrar_pedido(struct users *atendente, struct clientes *pcliente,  struct pedidos *ppedido){
    int length,i;

    choose_pizza(ppedido);
    choose_bebida(ppedido);

    //showing results
    length=sizeof(ppedido->items_pedido)/sizeof(ppedido->items_pedido[0]);
    for(i=0;i< length;i++){
        if(ppedido->items_pedido[i].id){
            printf("\n %s\n",ppedido->items_pedido[i].nome );
        }
    }

    printf("Conta ate agora: %.2f \n",ppedido->prize);
    //adding cliente to pedido
    char cpf[Max];
    printf("\nO Cliente esta cadastrado?\n inserir CPF: ");
    scanf("%s", cpf);
    if( check_cliente(cpf, pcliente) ){
        ppedido->cliente= *pcliente;
    }

}



//needs to return pedidos by client
void check_for_pedido(struct clientes *cliente){
    //for testing
    struct pedidos test[]={
        {
        .cliente= {1,
            "789456",
            "andres",
            "Manaus",
            "987456123"
        },
        .items_pedido[0]= {
            .id=1 ,
            .nome= "pizza A",
            .prize= 22.5 ,
            .produto[0]={
                1,
                "item A",
                5,
                10
            },
            .quantidade=5
         },
        .prize= 22.1 ,
        .motoqueiro={
            1,
            "david",
            "987654",
            1
        },
        2
        }
    };
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
void show_menu(){
    system("@cls||clear");
    int opt,i, length;
    struct items (*pmenu)[Max], menu[Max];
    pmenu= &menu;
    get_menu(pmenu);
    length= sizeof(menu)/sizeof(menu[0]);
    printf("%s", menu[1].nome);
    printf("---------Menu------\n");
    for(i=0;i< length-1; i++){
        printf("%d- %s ->>>>>> %f\n",i, menu[i].nome, menu[i].prize);

    }
    scanf("%d", &opt);

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
