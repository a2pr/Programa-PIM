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
    struct items items[10];
    double prize;
    struct motoqueiros motoqueiro;
    struct users atendente;
    int sede;
};


bool check_user(struct users *current_user, int *logout);
void cadastrar_pedido(struct users *atendente,  struct clientes *cliente);
void check_pedido(char cpf, struct clientes *cliente);
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

void cadastrar_pedido(struct users *atendente, struct clientes *cliente){
    char cpf[Max];
    printf("O Cliente esta cadastrado?\n inserir CPF: ");
    scanf("%s", cpf);
    check_cliente(cpf, cliente);
}


int check_pedido(char cpf, struct clientes *cliente){
    int i=0;
    for(;cliente==0;i++ ){

    }
    return 0;
}
