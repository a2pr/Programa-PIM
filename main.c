#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<conio.h>
#include <time.h>

#define Max 100
#include "functions.h"
#include "types.h"
#include "functions.h"
#include "database_implementation.h"
#include "memory.h"
#include "perdas.h"

int main ()
{
    char temp_login[10],temp_pass[10];

    users *puser, current_user;
    puser=&current_user;

    clientes *pcliente, cliente ;
    pcliente= &cliente;

    pedidos *pcu_pedido,cu_pedido;
    pcu_pedido=&cu_pedido;

    int i=1, step=0, optG=0;
	int *plogout, logout=0;
	plogout = &logout;
    int *psede, cu_sede;
    psede=&cu_sede;
	check_for_databases(psede);

    while (i != 0)
       {
        system("@cls||clear");
         printf("Login: \n");
        scanf("%s",temp_login);
        printf("Password: \n");
        scanf("%s",temp_pass);

        create_cu_user(puser, temp_login,temp_pass);
        printf("%s,%s",puser->login,puser->password );
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
            printf("5- Reclama��es e sugestoes \n");
            printf("6- Estoque \n");
            printf("7- Gerenciamento\n");
		}
		printf("8- sair \n");
		scanf("%d", &step);
		char cpf[Max];

		switch(step){
			case 1:
                pcu_pedido->atendente=*puser;
                pcu_pedido->sede=cu_sede;
			    cadastrar_pedido(puser, pcliente, pcu_pedido);
			break;

			case 2:
			    printf("O Cliente esta cadastrado?\n Inserir 0 se n�o ou se � cadastrado inserir CPF: ");
                scanf("%s", cpf);
                if(strcmp(cpf,"0")==0){
                    system("@cls||clear");
                    break;
                }

                if(check_cliente(cpf, pcliente)){
                    //Aqui vai trouzer pedido del cliente
                    check_for_pedido(pcliente, cpf);
                }else{
                    printf("\nCliente nao cadastrado na base dados !");
                    printf("\nPress ENTER key to go back to the menu\n");
                    getch();
                    system("@cls||clear");
                }

			break;

			case 3:
                pcu_pedido->atendente=*puser;
                pcu_pedido->sede=cu_sede;
			    show_promotion(puser, pcliente, pcu_pedido);//change
			break;

			case 4:
			    get_clientes(); //for now it will only display clientes
			break;

			case 5:
			    get_or_do_feedback(pcliente);
			break;

            case 6:
                show_estoque();
			break;

			case 7:
			    printf("\n.1 Faturamento\n.2 Sede con mais vendas\n  ");
                scanf("%d", &optG);

                switch(optG){
                    case 1 :
                        faturamento();
                        break;
                    case 2 :
                        vendas();
                        break;
                    case 3:
                        previsao();
                        break;
                    default:
                        printf("op��o nao aceitada\n");
                    break;
                }

			break;

			case 8:
				printf("voce saio do sistema");
				logout=0;
			break;

			default:
                printf("op��o nao aceitada\n");
            break;

		}

    }
return 0;
}


