#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<conio.h>
#define Max 100

struct sede{
    int id;
    char nome[Max];
    char enderezo[Max];
};
struct users{
    int id;
    char login[Max];
    char password[Max];
    int user_permissions;
};

struct produtos{
    int id;
    char nome[Max];
    double prize;
    int quantidade;
};

struct motoqueiros{
    int id;
    char nome[Max];
    char telefone[Max];
    int sede;
};

struct items{
    int id;
    char nome[Max];
    double prize;
    struct produtos produto[Max];
    int quantidade;
};

struct clientes{
    int id;
    char CPF[Max];
    char nome[Max];
    char enderezo[Max];
    char telefone[Max];
};

struct pedidos{
    struct clientes cliente;
    struct items items_pedido[10];
    double prize;
    struct motoqueiros motoqueiro;
    struct users atendente;
    int sede;
};


bool check_user(struct users *current_user, int *logout);
void cadastrar_pedido(struct users *atendente,  struct clientes *cliente);
int check_cliente(char cpf[], struct clientes *cliente);
void show_menu();
void get_menu(struct items (*menu)[Max]);

int main ()
{
    //testuser
    struct users *puser, current_user;
    puser=&current_user;
    struct clientes *pcliente, cliente[Max] ;
    pcliente= &cliente;
    int i=1;
	int step=0;
	int *plogout, logout=0;
	plogout = &logout;
    while (i != 0)
       {
         printf("Login: \n");
        scanf("%s",puser->login);
        printf("Password: \n");
        scanf("%s", puser->password);

        puser->id=1;
        puser->user_permissions= 1;
        if(check_user(puser, plogout)){
        	i=0;
		}
        system("@cls||clear");
       }
      while(logout==1){
        printf("---------Menu------\n");
       	printf("1- Cadastrar Pedido \n");
		printf("2- Pedidos \n");
		printf("3- Promocoes \n");
		if(puser->user_permissions==0){
            printf("4- Clientes cadastrados \n");
            printf("5- Reclamações e sugestoes \n");
            printf("6- Estoque \n");
		}
		printf("7- sair \n");
		scanf("%d", &step);
		switch(step){
			case 1:
			    cadastrar_pedido(puser, pcliente);
			break;
			case 2:
			break;
			case 3:
			    show_menu();
			break;
			case 4:
			break;
			case 5:
			break;
            case 6:
			break;
			case 7:
				printf("vc saio");
				logout=0;
			break;
		}
	   }

    return 0;
}
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

void cadastrar_pedido(struct users *atendente, struct clientes *pcliente){
    char cpf[Max];
    struct pedidos *ppedido, pedidos;
    ppedido=&pedidos;
    printf("O Cliente esta cadastrado?\n inserir CPF: ");
    scanf("%s", cpf);
    if(check_cliente(cpf, pcliente)){
        ppedido->cliente= *pcliente;
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

void get_menu(struct items (*menu)[Max]){
    //for testing purpose
    int i, lenght;
    struct produtos prod1={1,"item A", 5, 10};
    struct items test_user[2]={{.id=1,"pizza A",.prize= 22.5,{prod1},.quantidade=5},{.id= 2,"pizza B",.prize= 22.8,{prod1},.quantidade= 5}};

    lenght= sizeof(test_user)/sizeof(test_user[0]);
    for(i=0;i<=lenght-1;i++){
        //assign items to menu
        menu[i]->id= test_user[i].id;
        strcpy(menu[i]->nome,test_user[i].nome);
        (*menu[i]).prize= test_user[i].prize;
        (*menu[i]).produto->id = prod1.id;
        strcpy((*menu[i]).produto->nome, prod1.nome);
        (*menu[i]).produto->prize= prod1.prize;
        (*menu[i]).produto->quantidade = prod1.quantidade;
        (*menu[i]).quantidade= test_user[i].quantidade;
        //testing values assings
        //printf("Items del menu:\n id: %d \nitem name:%s\nprize: %.2f \n Quantidade: %d\n ",menu[i]->id, menu[i]->nome, (*menu[i]).prize, (*menu[i]).quantidade  );
        //printf("produtos usados:\n id: %d \n item name:%s\nprize: %.2f \n Quantidade: %d\n",(*menu[i]).produto->id, (*menu[i]).produto->nome,(*menu[i]).produto->prize,  (*menu[i]).produto->quantidade  );
    }
    printf("values assign !");
}
