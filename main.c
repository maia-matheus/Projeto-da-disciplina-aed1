/*
ChangeLOG:
-------------12/06: ---------------------
-Adicionada função para ler quantidade de strings de um arquivo (contastrings)
-Matriz de Poltronas feita (poltronasvazias)
Faltando: 
-Atualizar conteudo cadastrado pelo programa, e por sua vez alterar as funçoes que precisam do numero dessas informaçoes
-Cancelamento de Cadastro
----------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
	float rg, tel, valor;
	char nome[100], data[9], horario[5];  //
}cliente;

int contastrings(){
  
  int nstrings=1;
  FILE *lista = fopen("Lista_de_clientes.txt", "r");  
  if (lista == NULL){
		  printf("ERRO! O arquivo não foi aberto! As linhas não foram contadas.\n");
	}else	{		
      char c;
   		do{
		    c = getc(lista);   
        if(c=='\n') nstrings++;
      }while (c != EOF);
      fclose (lista);
  }
  return nstrings;
}

void poltronasvazias(){
  
  FILE *poltronas = fopen("Lista_de_clientes.txt", "r");
  if (poltronas==NULL){
    printf ("ERRO AO ABRIR ARQUIVO\n");
  }else{

    char temp[100], polt[4], skip, t1, t2, t3;
    char marcador[]="---------------------------------------------------\n";
    int i, j, repeticoes, c, f;
    repeticoes=contastrings()/8;  // o 8 corresponde ao numero de informaçoes
    int lugar[34][5];
    for (i=0; i<=33; i++){
      for (j=0; j<=4; j++){
        lugar[i][j]=0;
      }
    }
    while (repeticoes--){
      do{
        fgets(temp, 100, poltronas);
      }while (strcmp(temp, marcador));
      
      for (i=0; i<9; i++){   //
        skip = fgetc(poltronas) ;
      }
      
      fgets(polt, 4, poltronas);
      
      t1=polt[0];
      t2=polt[1];
      t3=polt[2];
      c=t1-64;
      t2-=48;
      t3-=48;
      f=(t2*10) + t3;

    for (i=1; i<=33; i++){
      for (j=1; j<=4; j++){
        if (i==f && j==c) lugar[i][j]=((100*c)+f);
      }
    }


    }  
     
    printf("\t    A\t       B\t            C          D");
    for(i=1; i<=33; i++){
      printf("\n%d\t", i);
      for (j=1; j<=4; j++){
          if (j==3) printf("\t\t");
          if (lugar[i][j]==0){
           if(i<=9){
             printf("|   0%d   | ", i);
           }else{
             printf("|   %d   | ", i);
             }
          }else {
            printf("|OCUPADO!| ", lugar[i][j]%10);
          }
      }
    }    
    fclose(poltronas);
  }
}


void novo_cliente() {  //
	

	poltronasvazias();
  printf("\n\n");
  char cadeira[4], numcadeira[2], fileira[2];

	FILE *lista = fopen ("Lista_de_clientes.txt", "a");
	
  if (lista == NULL)
		{
  			  printf("ERRO! O arquivo não foi aberto!\n");
		}else{
   			printf("Escolha a coluna da poltrona (A, B, C, OU D):\n-->");
			  scanf (" %s", fileira);
        fileira[0]=toupper(fileira[0]);   			
   			getchar ();
			  printf("Escolha o numero da poltrona com 2 dígitos:\n:");
			  scanf (" %[^\n]s", numcadeira);
			  getchar ();
			  strcpy(cadeira, fileira);
			  cadeira[1]=numcadeira[0];
			  cadeira[2]=numcadeira[1];
			  cadeira[3]='\0';
			  fprintf(lista, "---------------------------------------------------\nCADEIRA: %s\n", cadeira); 	

        cliente cadeira; 	
  		
      	printf("Digite o Nome do cliente:\n");
   			scanf (" %[^\n]s", cadeira.nome);
		  	getchar ();
   			printf("Digite o RG do cliente:\n");
   			scanf ("%f", &cadeira.rg);
   			printf("Digite o TELEFONE do cliente (somente numeros): \n");
   			scanf ("%f", &cadeira.tel);
   			printf("Digite a DATA da compra (DDMMAAAA):\n");
   			scanf (" %[^\n]s", cadeira.data);
 			  getchar();
 			  printf("Digite o HORARIO da compra (HHMM):\n");
   			scanf (" %[^\n]s", cadeira.horario);
 			  getchar();
 			  printf("Digite o valor pago:\n");
   			scanf ("%f", &cadeira.valor);
   			fprintf(lista, "%s\nRG: %.0f\nTEL: %.0f\nVALOR PAGO: %.0f\nDATA DA COMPRA: %s\nHORARIO DA COMPRA: %s\n", cadeira.nome, cadeira.rg, cadeira.tel, cadeira.valor, cadeira.data,  cadeira.horario);
			  
        fclose (lista);
			}		
 }

void verlista (){

	FILE *lista = fopen ("Lista_de_clientes.txt", "r");
	
  if (lista == NULL){
  			  printf("ERRO! O arquivo não foi aberto!\n");
	
  }else	{		
      char c;
   		do{
		    c = getc(lista);
		    printf("%c" , c);    
			}while (c != EOF);
      fclose (lista);
  }
}

void vercliente_poltrona(void) {

  FILE *lista = fopen("Lista_de_clientes.txt", "r");
  
  if (lista==NULL){
    printf ("ERRO");
  }else{
    
    char c, poltronaalvo[20], poltrona[100], poltronafinal[5];
  
    strcpy(poltronaalvo, "CADEIRA: ");
    printf ("Digite a poltrona (Ex:A9):\n");
    fgets(poltronafinal, sizeof(poltronafinal), stdin);
    
    int i, j=0;
    
    for (i=9; i<14; i++){
        poltronaalvo[i]=poltronafinal[j];
        j++;
    }
    
    while ((strcmp(poltrona, poltronaalvo))!=0){
          fgets(poltrona, sizeof(poltrona), lista);
    } 
  
    if(0){
        printf ("CLIENTE NÃO ENCONTRADO!!!\n");
    }else{
      for (i=0; i<6; i++){  //
            fgets(poltrona, sizeof(poltrona), lista);
            printf ("%s", poltrona);
      }
    }
    
    fclose (lista);
    printf ("\n"); 
  }
}

void vercliente_nome(){
  
  FILE *lista = fopen("Lista_de_clientes.txt", "r");  

  if (lista==NULL){
    printf ("ERRO");
  }else{
      char c, nomealvo[100], nome[100];
      
      printf("Digite o nome completo do cliente:\n");
      fgets(nomealvo, sizeof(nomealvo), stdin);
    
      while ((strcmp(nome, nomealvo))!=0){
            fgets(nome, sizeof(nome), lista);
      }
      
      for (int i=0; i<5; i++){   //
            fgets(nome, sizeof(nome), lista);
            printf ("%s", nome);
      }
      
      fclose (lista);
      printf ("\n");
  }   
}



void vercliente (){
   
   int opcao=11;
   
    while(opcao!=0){
      printf("Pesquisar cliente por:\n ---> (1) Nome Completo\n ---> (2) Poltrona\n ---> (0) Sair\n");
      scanf("%d", &opcao);
      getchar();
      if (opcao==1) vercliente_nome();
      if (opcao==2) vercliente_poltrona();
    }
}

int menu () {
  
  int opcao;
	
  printf ("\n\t\t\tBem Vindo!!\n\tEscolha uma opção:\n");
	printf("--> 1 Cadastramento\n");
	printf("--> 2 Cancelamento do Cadastro\n");
	printf("--> 3 Visualizar Lista de Clientes\n");
  printf("--> 4 Buscar Clientes\n");
	printf("--> 0 Sair\n");

	scanf ("%d", &opcao);
		switch (opcao){
			case 1:
				novo_cliente ();
				break;
			case 2:

				break;
			case 3:
				verlista ();
				break;
      case 4:
        vercliente();
    } 
	
  return opcao;
}

int main () {
	
  int flag=1;
	
  while (flag!=0){
  	flag=menu ();
  }

 
	
  return 0;
}