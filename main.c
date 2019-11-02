#include <stdio.h>
#include <stdlib.h>

// a struct to read and write
struct person
{
    int id;
    char nome[100];
    char endereco[100];
	float valorpizza[20];
};

main ()
{
    FILE *arq;

    // open file for writing
    arq = fopen ("person.dat", "w");
    if (arq == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }
    struct person dados;
    printf("Digite o numero do pedido");
    scanf("%d",&dados.id);
    while (dados.id != 0)
       {
        printf("Digite nome e sobrenome");
        scanf("%s%s%f",&dados.nome);
        printf("Digite o Endere�o");
        scanf("%s",&dados.endereco);
        printf("Digite o Valor da Pizza");
        scanf("%F",&dados.valorpizza);
        fwrite(&dados,sizeof(struct person),1,arq);
		printf("Digite o numero do Pedido");
        scanf("%d",&dados.id);
       }

    if(fwrite != 0)
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (arq);

 //    FILE *arq;

}
