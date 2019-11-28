#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "types.h"
#include "faturamento.h"
#include "functions.h"
#include "database_implementation.h"

void  clear_pedido( pedidos *pedido){

    pedidos void_pedido;

    *pedido=void_pedido;
}

void get_time_pedido(pedidos *pedido){
    time_t now;

    struct tm *c_time;

    time(&now);
    c_time= localtime(&now);

    pedido->time=c_time;
}

void get_time(feedback *fb){
    time_t now;

    struct tm *c_time;

    time(&now);
    c_time= localtime(&now);

    fb->time=c_time;
}

void print_date(struct tm *ptime){

    char date_to_print[50];
    strftime(date_to_print, sizeof(date_to_print), "%x", ptime);

    printf("%s", date_to_print);
}

bool check_user(users *current_user, int *logout){
    int *plen,i, lenght;
    plen=&lenght;
    //gets information from database;

    users *dbUsers,Users[get_entrycount(0)] ;
    dbUsers=&Users;
    get_users(dbUsers,plen);

    //testing receive data
     /*for(i=0; i<lenght; i++){
        printf("%i. login: %s - pass: %s - class: %i \n",dbUsers[i].id, dbUsers[i].login, dbUsers[i].password, dbUsers[i].user_permissions );
     }
     printf("%s, %s\n",current_user->login,current_user->password);
     */
     for(i=0;i<lenght;i++){
       if(strcmp(current_user->login, dbUsers[i].login)==0 && strcmp(current_user->password, dbUsers[i].password)==0 ){
            *current_user=dbUsers[i];
            *logout=1;
            return 1;
        }
     }
    printf("not found!");
     return 0;
}

bool check_cliente(char cpf[], clientes *pcliente){
    int *plen, i, length;
    plen=&length;

    clientes *dbClientes,Clientes[get_entrycount(5)] ;
    dbClientes=&Clientes;
    //getting clientes from database
    get_clientes_db(dbClientes,plen);

    for(i=0;i<length-1;i++ ){
            if(strcmp(cpf,dbClientes[i].CPF)==0){
                printf("cliente no sistema!\n");
                *pcliente= dbClientes[i];
                return true;
            }
    }
    printf("cliente sem registro\n");
 return false;
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
    return 0;
}

void choose_pizza(pedidos *ppedido, int *qtd_T){
    int *plen, i, opt, Qtd, tamanho, lenght;
    plen=&lenght;

    items *dbPizzas, Pizzas[get_entrycount(1)];
    dbPizzas=&Pizzas;
    //getting pizzas from db
    get_items_db(dbPizzas,plen,1);

    system("@cls||clear");
    printf("----------Nossas pizzas disponivels-----\n");
    for(i=0; i<lenght; i++){

        if( dbPizzas[i].quantidade!=0){
            printf(" %d-> %s , prize: %.2f \n", i+1,  dbPizzas[i].nome,  dbPizzas[i].prize);
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
         dbPizzas[opt-1].tamanho=tamanho;
        double multiplier= get_multiplier((int) dbPizzas[opt-1].tamanho);

        for(i=0; i<Qtd; i++){
            create_item(ppedido->items_pedido, Qtd, Pizzas, opt);
            ppedido->items_pedido[i]=  dbPizzas[opt-1];
            ppedido->items_pedido[i].quantidade=1;
            total+=  dbPizzas[opt-1].prize*multiplier;

        }
        ppedido->prize=total;
        *qtd_T=Qtd;
    }
    printf("%i %s,  %i , %f, %i", ppedido->items_pedido[0].id,  ppedido->items_pedido[0].nome,ppedido->items_pedido[0].quantidade, ppedido->prize, *qtd_T);
    printf("\n%d pizzas adicionadas\n", Qtd);
}

void choose_bebida(pedidos *ppedido, int *qtd_T ){
    int *plen, i,j,used, opt, Qtd, tamanho,  lenght,lenght_total;
    plen=&lenght;

    items *dbBebidas, Bebidas[get_entrycount(6)];
    dbBebidas=&Bebidas;
    get_items_db(dbBebidas,plen,2);

    lenght_total= *qtd_T;
    printf("\n----------Nossas bebidas disponivels-----\n");

    for(i=0; i<lenght; i++){

        if(dbBebidas[i].quantidade!=0){
            printf(" %d-> %s , prize: %.2f \n", i+1, dbBebidas[i].nome, dbBebidas[i].prize);
        }
    }
    printf("Escolha sua bebida: ");
    scanf("%d", &opt);
    printf("\nTamanho da pizza?");
    printf("\n1- Pequena\n");
    printf("\n3- Grande\n\n");
    scanf("%d", &tamanho);
    printf("\nQuantidade desejada?");
    scanf("%d", &Qtd);

    //checks pedido last added space index
    used=*qtd_T;

    //checks if opt and qtd not null
    if(opt && Qtd!=0){
        double total=0;
        dbBebidas[opt-1].tamanho=tamanho;
        double multiplier= get_multiplier((int) dbBebidas[opt-1].tamanho);
        int check=Qtd+used;
        //starts loop in first unsued space in pedido
        for(i=used; i<check; i++){
                    ppedido->items_pedido[i]= dbBebidas[opt-1];
                    ppedido->items_pedido[i].quantidade=1;
                    total+= dbBebidas[opt-1].prize*multiplier;
        }
        ppedido->prize+=total;
        *qtd_T+=Qtd;
    }
    printf("\n%d Bebidas adicionadas\n", Qtd);
}


bool check_en_estoque(pedidos *ppedido, int *itemsL){
    int *plen,i,j,length_e, length_p, counterProd,k,l;
    plen=&length_e;

    items *dbEstoques, Estoques[get_entrycount(1)];
    dbEstoques=&Estoques;
    //getting pizzas from db
    get_items_db(dbEstoques,plen,3);

    length_p=*itemsL;

    for(i=0; i<length_p;i++){
        for(j=0; j<length_e;j++){
            if(ppedido->items_pedido[i].id == dbEstoques[j].id){
                dbEstoques[j].quantidade-=ppedido->items_pedido[i].quantidade;
                if(dbEstoques[j].quantidade<=0 ){
                    return false;
                }
            }
        }
    }
    update_items_db(dbEstoques, plen);
    items *retire, retireItems[*itemsL];
    retire= &retireItems;
    for(i=0; i<length_p;i++){
        retire[i]=ppedido->items_pedido[i];
    }
    update_produtos_db(retire, itemsL);
    return true;

}

void cadastrar_cliente(clientes *pcliente, char cpf[]){
    int *plen, length;
    char temp_nome[15], temp_end[50], temp_tel[15];
     plen=&length;

     clientes *dbClientes,Clientes[20] ;
    dbClientes=&Clientes;
    //getting clientes from database
    get_clientes_db(dbClientes,plen);

    pcliente->CPF=malloc(sizeof(char)*(strlen(cpf)+1));
    strcpy(pcliente->CPF, cpf);
    printf("\n Cliente n�o cadastrado!\nPress ENTER key para cadastrar\n");
    getch();
    system("@cls||clear");

    printf("\nNome do cliente: \n");
    scanf("%s", temp_nome);
    pcliente->nome=malloc(sizeof(char)*(strlen(temp_nome)+1));
    strcpy(pcliente->nome, temp_nome);

    printf("\nEndere�� do cliente: \n");
    scanf("%s",  temp_end);
    pcliente->enderezo=malloc(sizeof(char)*(strlen(temp_end)+1));
    strcpy(pcliente->enderezo, temp_end);

    printf("\nTelefone do cliente: \n");
    scanf("%s", temp_tel);
    pcliente->telefone=malloc(sizeof(char)*(strlen(temp_tel)+1));
    strcpy(pcliente->telefone, temp_tel);

    //adding to database
    add_clientes_db(pcliente);

    printf("cliente cadastrado !\n");

}

void set_motoqueiro( pedidos *ppedido){
    int *plen,length, j;
    bool opt=false;
    plen=&length;
    //gets information from database;
    motoqueiros *dbMotoqueiros, Motoqueiros[get_entrycount(3)];
    dbMotoqueiros=&Motoqueiros;
    get_motoqueiros_db(dbMotoqueiros,plen);

    while(!opt){
        //pseudo random number assign
        j=rand()%length;
        //missing condition for sede
        if(dbMotoqueiros[j].id && dbMotoqueiros[j].disponivel){
            ppedido->motoqueiro=dbMotoqueiros[j];
            opt=true;
        }
    }
    printf("motoqueiro %s assinado\n ",ppedido->motoqueiro.nome );

}

void set_time( pedidos *ppedido){
    int i,length, multiplier,qtd, j=0;
    double time;
    length=sizeof(ppedido->items_pedido)/sizeof(ppedido->items_pedido[0]);
    //another logic for this should be added
    for(i=0;i<length;i++){
        if(ppedido->items_pedido[i].id){
                multiplier=get_multiplier((int)ppedido->items_pedido[i].tamanho);
                qtd=ppedido->items_pedido[i].quantidade;
                j+=(multiplier*qtd);
        }

    }
    time= (j*20); //min; formula= soma de cada item(quantidade de item * multiplier de tamanho) *20 min
    if(time>=60){
        if((int)time%60 != 0){
            int hours= (int)time/60;
            printf("Demorara %d horas para chegar seu pedido\n",hours);
        }
    }else{
        printf("Demorara %.0f minutos para chegar seu pedido\n", time);
    }


}

void cadastrar_pedido(users *atendente, clientes *pcliente,  pedidos *ppedido){
    bool pedido_ok=false;
    int *lenqtd, qtd;
    lenqtd=&qtd;
    while(!pedido_ok){
        int  length,i;


        get_time_pedido(ppedido);
        //choose from menu
        choose_pizza(ppedido, lenqtd);
        choose_bebida(ppedido, lenqtd);
        ppedido->cancelado=0;
        //showing results
        length=sizeof(ppedido->items_pedido)/sizeof(ppedido->items_pedido[0]);
        for(i=0;i< length;i++){
            if(ppedido->items_pedido[i].id!=NULL){
                printf("\n %s quantidade de items: %d ; custo-> %.2f\n",ppedido->items_pedido[i].nome, ppedido->items_pedido[i].quantidade, ppedido->items_pedido[i].prize );
            }else{
                break;
            }

        }
        printf("-------------------\n");
        printf("Conta ate agora: %.2f \n",ppedido->prize);
        // check in estoque if values are available

        if(!check_en_estoque(ppedido, lenqtd)){

                    memset(ppedido->items_pedido,0,10*sizeof(items));

            printf("\n Items de pedido fora de estoque\nPress ENTER key to go back to menu\n");
            getch();
        }else{
            pedido_ok= true;
        }
    }

    //adding cliente to pedido
    char cpf[Max];
    printf("\nO Cliente esta cadastrado?\n inserir CPF: ");
    scanf("%s", cpf);
    if( check_cliente(cpf, pcliente) ){
        ppedido->cliente= *pcliente;
        printf("Cliente %s asignado !\n", ppedido->cliente.nome);
    }else{
        cadastrar_cliente(pcliente, cpf);
        printf("\n cliente: %s cpf: %s \n", pcliente->nome, pcliente->CPF);

    }


    set_motoqueiro(ppedido);

    set_time(ppedido);
    //set sede by global variable

    //Pedido vai ser mandado para a base de dados;
    add_pedidos(ppedido, lenqtd);
    //clear variable
    clear_pedido(ppedido);
    printf("\n\n Pedido Cadastrado !");
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");
}

//needs to return pedidos by client
void check_for_pedido(clientes *pcliente, char cpf[]){
    int *plen, i,k,length_p, length_i;
    plen=&length_p;

    pedidos *dbPedidos, Pedidos[get_entrycount(6)];
    dbPedidos=&Pedidos;

    int *plenI,lenItem[get_entrycount(6)];
    for(i=0;i<get_entrycount(6);i++){
        lenItem[i]=0;
    };
    plenI=&lenItem;
    //getting info from db
    get_pedidos(dbPedidos, plen, plenI);
    printf("\n Para esse cpf temos os siguientes pedidos feitos\n");
    for(i=0; i<length_p;i++){
        if(strcmp(cpf,dbPedidos[i].cliente.CPF)==0){
                length_i=plenI[i];

                printf("\n Pedido %d: \n",i+1);
                for(k=0;k<length_i;k++){
                    if(dbPedidos[i].items_pedido[k].id){
                        printf("%s ----> prize: %.2f\n", dbPedidos[i].items_pedido[k].nome,dbPedidos[i].items_pedido[k].prize );
                    }

                }
                printf("-----------");

        }
    }
    free(plenI);
    free(dbPedidos);
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");
}

/* void get_menu(items (*menu)[Max]){
    //for testing purpose
    produtos test_produto[2]={{1,"item A", 5, 10}};

    items test_items[]={
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
}*/

void cadastrar_pedido_promotion(users *atendente, clientes *pcliente,  pedidos *ppedido, int *qtd){
    bool pedido_ok=false;
    get_time_pedido(ppedido);
    ppedido->cancelado=0;
    while(!pedido_ok){
       int length,i;
        //showing results
        length=*qtd;
        for(i=0;i< length;i++){
            if(ppedido->items_pedido[i].id!=NULL){
                printf("\n %s quantidade de items: %d ; custo-> %.2f\n",ppedido->items_pedido[i].nome, ppedido->items_pedido[i].quantidade, ppedido->items_pedido[i].prize );
            }else{
                break;
            }
        }
        printf("-------------------\n");
        printf("Conta ate agora: %.2f \n",ppedido->prize);
        // check in estoque if values are available

        if(!check_en_estoque(ppedido, qtd)){

                    memset(ppedido->items_pedido,0,10*sizeof(items));

            printf("\n Items de pedido fora de estoque\nPress ENTER key to go back to menu\n");
            getch();
        }else{
            pedido_ok= true;
        }
    };

    //adding cliente to pedido
    char cpf[Max];
    printf("\nO Cliente esta cadastrado?\n inserir CPF: ");
    scanf("%s", cpf);
    if( check_cliente(cpf, pcliente) ){
        ppedido->cliente= *pcliente;
        printf("Cliente %s asignado !\n", ppedido->cliente.nome);
    }else{
        cadastrar_cliente(pcliente, cpf);
        printf("\n cliente: %s cpf: %s \n", pcliente->nome, pcliente->CPF);

    }


    set_motoqueiro(ppedido);

    set_time(ppedido);
    //set sede by global variable

    //Pedido vai ser mandado para a base de dados;

    add_pedidos(ppedido, qtd);
    //clear variable
    clear_pedido(ppedido);

    printf("\n\n Pedido Cadastrado !");
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");
}

void show_promotion( users *atendente, clientes *pcliente,  pedidos *ppedido){
    system("@cls||clear");
    int *plen, opt,i, length,tamanho;
    plen=&length;
    int *lenQtd,  Qtd;
    lenQtd=&Qtd;

    //getting info db
    items *dbPromotions, Promotions[get_entrycount(1)];
    dbPromotions=&Promotions;
    get_items_db(dbPromotions,plen,3);

    printf("\n----------Nossas Promo��es disponivels-----\n");

    for(i=0; i<length; i++){
        if(dbPromotions[i].quantidade!=0 && dbPromotions[i].promotion==true ){
            printf(" %d-> %s , prize: %.2f \n", i+1, dbPromotions[i].nome, dbPromotions[i].prize);
        }
    }

    printf("Escolha sua promo��o: ");
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
        dbPromotions[opt-1].tamanho=tamanho;
        double multiplier= get_multiplier(dbPromotions[opt-1].tamanho);
        for(i=0; i<Qtd; i++){
            create_item(ppedido->items_pedido, Qtd, Promotions, opt);
            ppedido->items_pedido[i]= dbPromotions[opt-1];
            ppedido->items_pedido[i].quantidade=1;
            total+= dbPromotions[opt-1].prize*multiplier;

        }
        ppedido->prize=total;
    }

    cadastrar_pedido_promotion(atendente,pcliente, ppedido, lenQtd );
}

 void get_clientes(){
     system("@cls||clear");
     int *plen, i, length;
     plen=&length;

     clientes *dbClientes,Clientes[20] ;
     dbClientes=&Clientes;

     //get clientes from database
     get_clientes_db(dbClientes,plen);

     /*testing data obtain
     for(i=0; i<length; i++){
        printf("%i. %i- %s - %s -", i+1,dbClientes[i].id, dbClientes[i].CPF,dbClientes[i].nome );
        printf(" %s - %s\n", dbClientes[i].enderezo, dbClientes[i].telefone);
     }*/

    printf("getting clientes.... \n");
     for(i=0;i<length;i++){
        printf("\n %d ) %s CPF: %s \n", i+1, dbClientes[i].nome,  dbClientes[i].CPF );
     };
    printf("\nQuantidade de clientes cadastrados: %d\n\n", i+1);
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");
 }

 void get_or_do_feedback( clientes *pcliente){
    int opt, i, length, type_of_comment;
    char cpf[100];

    int *plen,length_clientes;
    plen=&length_clientes;

    clientes *dbClientes,Clientes[20] ;
    dbClientes=&Clientes;

     //get clientes from database not really necesary
      /*testing data obtain
    get_clientes_db(dbClientes,plen);
    for(i=0; i<length_clientes; i++){
        printf("%i. %i- %s - %s -", i+1,dbClientes[i].id, dbClientes[i].CPF,dbClientes[i].nome );
        printf(" %s - %s\n", dbClientes[i].enderezo, dbClientes[i].telefone);
     }*/

    feedback test_fb[]={
        {
            .cliente= dbClientes[0],
            .description="lorem impsom",
            .type=1,
            .sede=0
        },
        {
            .cliente= dbClientes[1],
            .description="lorem impsomqhbdwfubqrweyfveqr",
            .type=0,
            .sede=1
        }

    };

    printf("\n1- Cadastra uma Reclama��es ou sugest�o\n");
    printf("\n2- Feedback disponivel\n");
    scanf("%d", &opt);
    switch(opt){
        case 1:
            system("@cls||clear");
            feedback *pfb,fb, clear_fb;
            pfb=&fb;

            printf("Inserir o CPF do cliente: \n");
            scanf("%s", cpf);
            if(check_cliente(cpf,pcliente)){
                pfb->cliente=*pcliente;
            }else{
               cadastrar_cliente(pcliente,cpf);
            }
            printf("Inserir o feedback: \n");
            scanf("%s",  pfb->description);

            printf("Tipo de feedback. \n1= reclama��o\n0=suggestao: \n");
            scanf("%d", &type_of_comment);

            pfb->type= type_of_comment;

            get_time(pfb);

            //sede will be set by global variable

            //set feeback in database

            printf("feedback registrado!\n");
            *pfb=clear_fb;
            printf("\nPress ENTER key to go back to the menu\n");
            getch();
            system("@cls||clear");
            break;
        case 2:
            //get feedback from database

            length=sizeof(test_fb)/sizeof(test_fb[0]);

            for(i=0;i<length; i++){
                    printf(" %d-> From %s: \n %s\n", i+1, test_fb[i].cliente.nome, test_fb[i].description );
                    printf("-----------\n\n");
            }
            printf("\nPress ENTER key to go back to the menu\n");
            getch();
            system("@cls||clear");
            break;
        default:
            printf("not an option!\n");
            break;

    }
 }

void sort_estoque(int n, produtos *prod){

    int i, j ;
    produtos t;

     for (i = 0; i < n; i++) {

        for (j = i + 1; j < n; j++) {
            if ( prod[j].sede < prod[i].sede) {

                t =  prod[i];
                prod[i] = prod[j];
                prod[j] = t;
            }
        }
    }
}

void get_estoque(int opt){
    system("@cls||clear");
    int *plen, i,j, length, optSede=NULL,k=0;
    plen=&length;
    produtos *dbProdutos,Produtos[100] ;
    dbProdutos= &Produtos;
    //get produtos from database
    get_produtos_db(dbProdutos, plen);

    sort_estoque(*plen, dbProdutos);

    if(opt==1){
        printf("Qual sede quer pesqui�ar ?\n 0= sede principal\n 1= sede en iranduba\n 2= sede terciaria\n");
        scanf("%d", &j);
         for (i = 0; i < length; i++)
             if(dbProdutos[i].sede==j){
               printf("%s , quantidade = %d na sede %d\n", dbProdutos[i].nome, dbProdutos[i].quantidade, dbProdutos[i].sede );
             }

    }else if(opt==2){
            for (i = 0; i < length; i++){
                if(optSede==NULL && k==0){
                    optSede=dbProdutos[i].sede;
                    printf("Produtos na sede %i\n\n", optSede);
                    k++;
                }
                if(optSede!=dbProdutos[i].sede){
                    optSede=dbProdutos[i].sede;
                    printf("\n\nProdutos na sede %i\n\n", optSede);
                }

                printf("%s , quantidade = %d \n", dbProdutos[i].nome,dbProdutos[i].quantidade);

        }
    }
    printf("\nPress ENTER key to go back to the menu\n");
    getch();
    system("@cls||clear");
    }

 void show_estoque(){
 int opt;
    system("@cls||clear");
    printf("\n1- Estoque por sede\n");
    printf("\n2- Estoque Total\n");
    scanf("%d", &opt);
     switch(opt){
        case 1:
            get_estoque(opt);
            break;
        case 2:
            get_estoque(opt);
            break;
     }
 }


#endif // FUNCTIONS_H_INCLUDED
