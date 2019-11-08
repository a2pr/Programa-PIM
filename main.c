#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define Max 100
//Not working with files yet.

// a struct to read and write
//struct person
//{
//    int id;
//    char nome[100];
//    char endereco[100];
//	float valorpizza[20];
//};
enum permissions{ADMIN,ATENDENTE};

struct users{
    int id;
    char login[Max];
    char password[Max];
    int user_permissions;
};

bool check_user(struct users *current_user){

    //gets information from database;
    //for now just a variable
  struct users test_user={1,"andres","1",0};
   if(strcmp(current_user->login, test_user.login)==0){
        printf("User found! \n");
		*logout=1;
		return 1;
    }else{
    	return 0;
    }
}
int main ()
{
    //testuser
    struct users *puser, current_user;
    puser=&current_user;
    int i=1;
	int step=0;
	int *plogout, logout=0;
	plogout = &logout;
////    FILE *arq;
//
//    // open file for writing
//    arq = fopen ("person.dat", "w");
//    if (arq == NULL)
//    {
//        fprintf(stderr, "\nError opend file\n");
//        exit (1);
//    }
//    struct person dados;
//    printf("Digite o numero do pedido");
//    scanf("%d",&dados.id);
    while (i != 0)
       {
         printf("Login: \n");
        scanf("%s",puser->login);
        printf("Password: \n");
        scanf("%s", puser->password);

        puser->id=1;
        puser->user_permissions= 0;
        if(check_user(puser, plogout)){
        	i=0;
		}

       }
      while(logout==1){
       	printf("1- opcao \n");
		printf("2- opcao \n");
		printf("3- opcao \n");
		printf("4- opcao \n");
		printf("5- opcao \n");
		printf("6- sair \n");
		scanf("%d", &step);
		switch(step){
			case 1:
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
				printf("vc saio");
				logout=0;
			break;
		}
	   }
	
return 1;
}
