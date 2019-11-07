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
    struct users test_user={1,"a","1",0};
    printf("%s \n%s ",  current_user->login, test_user.login);

   if(current_user->login == "a"){
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
        printf("User found %d ", check_user(puser) );



//        scanf("%s%s%f",&dados.nome);
//        printf("Digite o Endere�o");
//        scanf("%s",&dados.endereco);
//        printf("Digite o Valor da Pizza");
//        scanf("%F",&dados.valorpizza);
//        fwrite(&dados,sizeof(struct person),1,arq);
//		printf("Digite o numero do Pedido");
//        scanf("%d",&dados.id);
       }
//
//    if(fwrite != 0)
//        printf("contents to file written successfully !\n");
//    else
//        printf("error writing file !\n");

    // close file
//    fclose (arq);

 //    FILE *arq;
return 1;
}
