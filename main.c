#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<conio.h>
#define Max 100
#include "functions.h"
#include "types.h"

int main ()
{
    //testuser
    struct users *puser, current_user;
    puser=&current_user;
    struct clientes *pcliente, cliente ;
    pcliente= &cliente;
    struct pedidos *pcu_pedido,cu_pedido;
    pcu_pedido=&cu_pedido;
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
		char cpf[Max];
		switch(step){
			case 1:
			    cadastrar_pedido(puser, pcliente, pcu_pedido);
			break;
			case 2:

			    printf("O Cliente esta cadastrado?\n inserir CPF: ");
                scanf("%s", cpf);
                check_cliente(cpf, pcliente);
                check_for_pedido(pcliente);

			break;
			case 3:
			    show_menu();//change
			break;
			case 4:
			    get_clientes();
			break;
			case 5:
			    show_R_S();
			break;
            case 6:
                show_estoque();
			break;
			case 7:
				printf("voce saio do sistema");
				logout=0;
			break;
		}
	   }

    return 0;
}


