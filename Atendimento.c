/* --------------------------------------- Bibliotecas -------------------------------------- */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <locale.h>
#include "bibliotecas\\funcoes_gerais.h"
#include "bibliotecas\\mensagens.h"

/* ------------------------------------ HEAP SORT ------------------------- */
/* variáveis globais */
long int     TAMANHO_VETOR;
long int     qtd_registros;
/* Fila */
#define  true  1      
#define false -1
typedef  int   bool; 


/* Definindo o ELEMENTO */
typedef struct aux
{  
   Cidadao reg;
   struct 	    aux * PROX; 
}                                            
ELEMENTO;

/* Definindo a fila */
typedef ELEMENTO  *PONT;

typedef struct 
{
   PONT inicio;   
   PONT fim;       
} 
fila;

/*------------------Funções específicas para o teste de ordenação: heapsort -----------------*/
int esquerdo(int i) 
{
  return (2*i+1);
}

int direito(int i) 
{
  return (2*i+2);
}

int pai(int i) 
{
  return (i/2);
}

void troca (Cidadao *A, Cidadao *B) 
{
  Cidadao aux = *A; 
  *A = *B; 
  *B = aux;
}

void BuildHeap (Cidadao	* vet_reg)
{
   long int i, atual;
   for(i=1; i<qtd_registros; i++) 
   {
      atual = i;
      
      while(atual > 0 && vet_reg[atual].idade > vet_reg[pai(atual)].idade) 
      {
      	troca(  &vet_reg[atual], &vet_reg[pai(atual)] );
        atual = pai(atual);
      }
   }
}

void heap_sort	(Cidadao	* vetor)
{   long int i, atual;

    for(i=qtd_registros-1; i>0; i--) 
    { 
        troca(  &vetor[0], &vetor[i]  );

        atual = 0;
        while ( direito(atual) <= (i-1) 
                &&
			    ( vetor[atual].idade < vetor[esquerdo(atual)].idade
				  ||
                  vetor[atual].idade < vetor[direito(atual)].idade  ) 
			  )
        {
            if ( vetor[esquerdo(atual)].idade > vetor[direito(atual)].idade ) 
            {
            	troca(  &vetor[atual], &vetor[esquerdo(atual)]  ); 
                atual = esquerdo(atual);
            } 
			else 
			{
				troca(  &vetor[atual], &vetor[direito(atual)]  ); 
                atual = direito(atual);
            }
        }

        if ( esquerdo(atual) <= i-1 
		     && 
		     vetor[atual].idade < vetor[esquerdo(atual)].idade )
        {
            troca(  &vetor[atual], &vetor[esquerdo(atual)]  ); 
            atual = esquerdo(atual);
        }
    }
}

/*------------------Funções específicas para a conversão do .CSV em .DAT --------------------*/

void consulta_dat(void)
{
	FILE 				* ArqDat;
	Cidadao		reg;
	long int 			cont=0;
	
	system ("cls"); system ("mode 230, 100"); system ("color 03");

	TAMANHO_VETOR = findSize("MUNICIPES.DAT");
	qtd_registros = TAMANHO_VETOR/sizeof(Cidadao);

	ArqDat = fopen ("MUNICIPES.DAT", "rb+");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo MUNICIPES.DAT");
		getch();
		exit(0);
	}
	
	printf ("______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	printf ("#         IDADE	         NOME                                                                                                   \n");
	printf ("______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	while ( !feof(ArqDat) )
	{	
		memset(reg.nome,        '\0', sizeof(reg.nome));
		reg.idade = 0;
		cont++;
		fread (&reg, sizeof(reg), 1, ArqDat);
		if ( !feof(ArqDat) )
			printf ("\n%5i->[%8i]\t[%s]", 
			(int)cont, reg.idade, reg.nome);	
		if (feof(ArqDat)) break;
	}
    fclose(ArqDat);
    getch();
}

void consulta_dat_em_relatorio(void)
{
	FILE 				* ArqDat, *Relat;
	Cidadao		reg;
	long int 			cont=0;
	
	system ("cls"); 

	TAMANHO_VETOR = findSize("MUNICIPES.DAT");
	qtd_registros = TAMANHO_VETOR/sizeof(Cidadao);

	ArqDat = fopen ("MUNICIPES.DAT", "rb+");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo MUNICIPES.DAT");
		getch();
		exit(0);
	}
	
	Relat = fopen ("RELAT_MUNICIPES.TXT", "wt");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo RELAT_MUNICIPES.TXT");
		getch();
		exit(0);
	}
	
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf (Relat, "#         IDADE	         NOME                                                                                                   \n");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	while ( !feof(ArqDat) ) {
	
		memset(reg.nome,     '\0', sizeof(reg.nome));
		reg.idade = 0;
		cont++;
		fread (&reg, sizeof(reg), 1, ArqDat);
   	
		if ( !feof(ArqDat) )
			fprintf (Relat,"\n%5i->[%8i]\t[%-100s]", 
			(int)cont, reg.idade, reg.nome);
		
		if (feof(ArqDat)) break; 		
	}
    fclose(ArqDat);
    fclose(Relat);
//    system ("notepad RELAT_MUNICIPES.TXT");
    getch();
}

/*-------------------------------------------------------------------------------------------*/

void    abastece_vetor (Cidadao	* vet_reg)
{   int i=0;
   	FILE * ArqDat;
	ArqDat = fopen ("MUNICIPES.DAT", "rb+");
	if ( ArqDat==NULL )
	{	system ("cls");
		printf ("Erro ao abrir arquivo MUNICIPES.DAT para leitura");
		getch();
		exit(0);
	}
	
	while ( !feof(ArqDat) )
	{
	    fread (&vet_reg[i], sizeof(vet_reg[i]), 1, ArqDat);
	    
   	    if ( ferror(ArqDat) )
   	    {  system ("cls");
		   printf ("Erro ao ler arquivo MUNICIPES.DAT no registro [%i]",i);
		   getch();
		   exit(0);	
		}
		i++;
		if (feof(ArqDat)) break;
	}
    fclose(ArqDat);
	printf ("\nArquivo MUNICIPES.DAT transferido para vetor em memória com sucesso!");
//	Sleep(2000);
}

void mostra_codigos  (Cidadao	* vet_reg)
{
    long int i;
    printf ("\n_______________________________________________________________________\n");
	for (i=0; i<qtd_registros; i++)
    {
       printf ("%i;%s", 
	   vet_reg[i].idade, vet_reg[i].nome);
	   if (i<qtd_registros-1) printf ("\n");
    }
    printf ("\n_______________________________________________________________________\n");
//		getch();
}

void envia_vet_ordenado_dat (Cidadao	* vet_reg)
{
    long int i;
   	FILE * ArqDat;
	ArqDat = fopen ("MUNICIPES.DAT", "wb+");
	if ( ArqDat==NULL )
	{	system ("cls");
		printf ("Erro ao gerar arquivo MUNICIPES.DAT ordenado!");
		getch();
		exit(0);
	}
    for (i=0; i<qtd_registros; i++)
    {
    	fwrite (&vet_reg[i], sizeof(vet_reg[i]), 1, ArqDat);
    	if ( ferror(ArqDat) )
   	    {  system ("cls");
		   printf ("Erro ao gravar no arquivo MUNICIPES.DAT no registro %li!", i);
		   getch();
		   exit(0);	
		}
	}
	fclose(ArqDat);
	printf ("\nMUNICIPES.DAT ordenado com sucesso!");
}

void teste_heapsort(void)
{
	FILE * ArqDat;
	Cidadao		* vet_reg;

 	TAMANHO_VETOR = findSize("MUNICIPES.DAT");
	qtd_registros = TAMANHO_VETOR/sizeof(Cidadao);
    system ("cls"); system ("mode 160, 1000"); 
	if (TAMANHO_VETOR != -1) 
	{
	    printf("Tamanho do arquivo MUNICIPES.DAT em bytes = %ld e tem %ld registros\n", 
	          TAMANHO_VETOR, qtd_registros );
//        Sleep(2000);
    } 
    vet_reg = (Cidadao *) malloc (qtd_registros * sizeof (Cidadao)); 
    if (vet_reg == NULL)
    {
        printf ("malloc devolveu NULL!\nNão foi possível alocar %ld bytes.", 
		(qtd_registros * sizeof (Cidadao)) );
//        getch();
        exit (EXIT_FAILURE);
    }
    else
    {
    	printf ("\nAlocação de memória bem-sucedida!");
    	printf ("\nmalloc alocou %ld bytes", (qtd_registros * sizeof (Cidadao)) );
    	printf ("\nO arquivo MUNICIPES.DAT possui %ld bytes", TAMANHO_VETOR);
    	printf ("\nO arquivo MUNICIPES.DAT possui %ld registros", qtd_registros);
//    	Sleep(2000);
	}
    
    abastece_vetor(vet_reg);  		
    printf ("\nExibindo o conteúdo do vetor...\n");
    mostra_codigos(vet_reg);  	
	BuildHeap (vet_reg);      	
	printf ("\nExibindo o heap de máximo construído...\n");
    mostra_codigos(vet_reg);  
    
	heap_sort(vet_reg);    
    printf ("\nExibindo o vetor ordenado...\n");
	mostra_codigos(vet_reg);  

	printf ("\nTransferindo o vetor ordenado para MUNICIPES.DAT...");
	envia_vet_ordenado_dat (vet_reg);
    consulta_dat_em_relatorio();
}
/* -------------------------- FILA -------------------- */

void inicializarfila (fila * p)
{
  p->inicio = NULL;
  p->fim    = NULL;
}

int tamanho (fila* p) 
{  
	PONT    end = p->inicio;  
	int     tam = 0;
	while (end != NULL) 
	{  
  		tam++;
  		end = end->PROX;
	}
	return tam;
}

void exibirfila (fila* p)
{  
   PONT end = p->inicio;  
   system ("cls");
   printf("fila: \" ");  
   while (end != NULL) 
   {
	printf("%i ", end->reg.idade);  
	end = end->PROX;
   }
   printf("\"\n");
}

bool estaVazia(fila* p) 
{
   if (p->inicio == NULL) 
      return true;  
   return false;
}

void inserirNaFila (fila * f, FILE *DAT) 
{  
		
	 system("cls");
	 
	 Cidadao reg;
	 
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO .DAT  ");
		getch();
		exit(0);
	}
	
	while (!feof(DAT))
	{
		/* lê o DAT */
		fread (&reg, sizeof(reg), 1, DAT);
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO .DAT  ");
			getch();
			exit(0);
		}
		
		if (feof(DAT)) break;
		
   PONT novo = (PONT) malloc(sizeof(ELEMENTO));  
   novo->reg = reg;
   novo->PROX = NULL;
   if (f->inicio==NULL) 
      f->inicio = novo;  
   else 
      f->fim->PROX = novo;
   f->fim = novo;
  }
  
}

bool excluiDaFila(fila * f, Cidadao* reg) {
		
		if (f->inicio==NULL) 
      return false;
   *reg = f->inicio->reg;  
   PONT apagar = f->inicio;
   f->inicio = f->inicio->PROX;  
   free(apagar);
   if (f->inicio == NULL) 
      f->fim = NULL;  
   return true;
}

bool filaNoDat(fila * f, FILE *DAT) {
	Cidadao regExcluido;
	
	if ( excluiDaFila(f, &regExcluido) == true ) {
	   
	fwrite(&regExcluido, sizeof(regExcluido),1, DAT);
		 
	 if ( ferror(DAT) ){
		printf("\nErro de gravação no lote!\n");
		getch();
		fclose(DAT);
	}
	   
	} else {
	   return false;
	 }
	 
	 return true;
}

bool insereElemFila(fila * f, Cidadao reg) {
	PONT novo = (PONT) malloc(sizeof(ELEMENTO));  
   novo->reg = reg;
   novo->PROX = NULL;
   if (f->inicio==NULL) 
      f->inicio = novo;  
   else 
      f->fim->PROX = novo;
   f->fim = novo;
   return true;
}

void consultaFila(void) {
	system ("cls"); system ("color 37"); system ("mode 80,25");

	FILE *DAT = fopen ("FILAVACINA.DAT", "r");
	Cidadao reg;
	
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO FILAVACINA.DAT  ");
		getch();
		exit(0);
	}

	printf ("_________________________________________");
	printf ("\n\n%s %s", "NOME", "IDADE");
	printf ("\n_______________________________________");
	while ( !feof(DAT) )
	{
		/* lê o DAT */
		fread (&reg, sizeof(reg), 1, DAT);
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO LOTESVACINA.DAT  ");
			getch();
			exit(0);
		}
		if (feof(DAT)) break;
		/* Mostra registro lido */
		printf ("\n %s %i", reg.nome, reg.idade);
	}
	fclose (DAT);
	getch();
}

void reinicializarFila(fila * f) 
{  
   PONT end = f->inicio;
   PONT apagar;
   while (end != NULL) 
   {  
      apagar = end;  
	  end = end->PROX;  
	  free(apagar);
   }
   f->inicio = NULL;  
   f->fim = NULL;
}



/* ---------------------------------- CORPO DO PROGRAMA ------------------------------------ */
int main ()
{	
	setlocale (LC_ALL, "");  
  teste_heapsort();

	fila * F; 
	Cidadao r;

	
	F = (fila *) malloc (sizeof (fila));
	if (F == NULL) {
	printf("Malloc devolveu NULL\n");
	getch();
	exit (EXIT_FAILURE);
	}
	
	inicializarfila(F);
	
	DAT = fopen ("MUNICIPES.DAT", "rb+");
	inserirNaFila(F, DAT);
	fclose(DAT);
	
//	exibirfila(F);
//	getch();
	
	DAT = fopen("FILAVACINA.DAT", "wb+");
	
	while(estaVazia(F) != true) {
		filaNoDat(F, DAT);	
	}
	
//	fclose(DAT);
//	getch();
	
//	exibirfila(F);
//	getch();
//	consultaFila();
	
	DAT = fopen("FILAVACINA.DAT", "rb+");
	inserirNaFila(F, DAT);
	fclose(DAT);
	
//	exibirfila(F);
	getch();
	
 	return 0;
} 
