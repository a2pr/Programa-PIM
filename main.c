#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
    char login[100];
    char email[100];
    char password[20];
    enum permissions user_permissions;
};

bool check_user(char *login , char *password){

    //gets information from database;
    //for now just a variable
    struct users test_user;
    test_user.id=1;
    strcpy(test_user.login, "andres");
    strcpy(test_user.password, "123456");
    test_user.user_permissions=1;

    printf("%s and %s \n", login, password);
    if(login==test_user.login && password==test_user.password){

        return true;
    }else{
    return false;
    }


}
void main ()
{
    //testuser
    struct users current_user;
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
        scanf("%s",&current_user.login);
        printf("Password: \n");
        scanf("%s",&current_user.password);

        printf("User found %d ", check_user(*current_user.login, *current_user.password) );



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

}
