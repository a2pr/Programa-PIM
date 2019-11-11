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
void cadastrar_pedido(struct users *atendente, struct clientes *pcliente){
    char cpf[Max];
    struct pedidos *ppedido, pedidos;
    ppedido=&pedidos;
    printf("O Cliente esta cadastrado?\n inserir CPF: ");
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
