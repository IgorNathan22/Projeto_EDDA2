/* --------------------------------------- Bibliotecas -------------------------------------- */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include "bibliotecas\\quicksort_lotes.h"
/* ------------------------------- Constantes pr?-definidas --------------------------------- */
#define MAX       2  /* tamanho m?ximo do vetor est?tico */ 
#define INVALIDO -1

#define false    -1  
#define true      1

/* --------------------- Tipos de dados definidos pelo programador -------------------------- */

/* defini??o do tipo booleano */
typedef int 	bool;
/* defini??o do tipo chave utilizado:  a chave da nossa implementa??o ser? um n?mero inteiro */

/* defini??o do registro*/

FILE *lotes;
FILE *sup;
FILE *sup2;
FILE *sup3;
FILE *sup4;
FILE *sup5;

typedef struct   
{          
  int 	id_vacina;
  char 	id_lote[8+1];
  int 	id_frasco;
} 
SUPORTE;

SUPORTE sups;

typedef struct aux
{  
	SUPORTE 	reg;
	struct 		aux	* PROX; /* prox APONTA para o endere?o de mem?ria  */
}                           /* de um elemento com essa mesma estrutura */
ELEMENTO;

typedef ELEMENTO * PONT;  

typedef struct 
{
	PONT topo; /* topo APONTA para o endere?o do ELEMENTO do TOPO da PILHA */
} 
PILHA;

/* --------------------------- Prot?tipos das fun??es --------------------------------------- */
void inicializarPilha 	(PILHA* p);
int  tamanho 			(PILHA* p);
void exibirPilha 		(PILHA* p);
bool inserirElemPilha	(PILHA* p, SUPORTE reg);
bool excluirElemPilha	(PILHA* p, SUPORTE *reg); 
void reinicializarPilha (PILHA* p);

void 		insereNaPilha 	(PILHA* p);
//void 		excluiDaPilha 	(PILHA* p);

/* ----------------------- Rotinas de gerenciamento da Pilha -------------------------------- */

/* 
Para inicializar uma pilha j? criada pelo usu?rio,  precisamos apenas acertar o valor do 
campo topo.
J? que o topo conter? o endere?o do elemento que est? no topo da pilha e apilha est? vazia,  
iniciaremos esse campo com valor NULL. 
*/
void inicializarPilha (PILHA* p)
{
  p->topo = NULL;
}

/* J? que n?o temos um campo com o n?mero de elementos na pilha, 
   precisaremos percorrer todos os elementos para contar quantos s?o.
*/
int tamanho (PILHA* p) 
{  
   PONT end = p->topo;  
   int tam = 0;
   while (end != NULL) 
   {  
      tam++;
      end = end->PROX;
   }  
   return tam;
}

/* Se topo est?  armazenando o endere?o NULL, significa que a pilha est? vazia. */
bool estaVazia(PILHA* p) 
{
   if (p->topo == NULL) 
      return true;  
   return false;
}

/* Para exibir os elementos da estrutura precisaremos  percorrer os elementos
(iniciando pelo elemento do topo da pilha) e, por exemplo, imprimir suas chaves. */
void exibirPilha (PILHA* p) 
{  
   PONT end = p->topo;  
   system ("cls");
   printf("Pilha: \" ");  
   while (end != NULL) 
   {
		printf("[%i-%s-%i]", end->reg.id_vacina, end->reg.id_lote, end->reg.id_frasco);  
		end = end->PROX;
   }
   printf("\"\n");
   getch();
}

/* 
Inser??o de um elemento (push)
O usu?rio passa como par?metro um registro a ser inserido na pilha
O elemento ser? inserido no topo da pilha, ou  melhor, 
?acima? do elemento que est? no topo da  pilha.
O novo elemento ir? apontar para o elemento que estava no topo da pilha
*/
bool inserirElemPilha(PILHA* p, SUPORTE reg) 
{  
   PONT novo  = (PONT) malloc(sizeof(ELEMENTO));  
   novo->reg  = reg;
   novo->PROX = p->topo;  
   p->topo    = novo;  
   return true;
}

/*
Exclus?o de um elemento (pop)
O usu?rio solicita a exclus?o do elemento do topo da pilha:
Se a pilha n?o estiver vazia, al?m de excluir esse elemento da pilha 
iremos copi?-lo para um local indicado pelo usu?rio.
*/
//bool excluirElemPilha(PILHA* p, SUPORTE* reg) 
//{  
//
//	SUPORTE sups;
//	sup = fopen ("SUPORTE_1.DAT", "w");
//	
//	for (i = 0; i<tamanho(p); i++) {
////		if ( p->topo == NULL) 
////		    return false;
//		 *reg        = p->topo->reg;  
//		 
//		 sups.id_frasco = reg->id_frasco;
//		 strcpy(sups.id_lote, reg->id_lote);
//		 sups.id_vacina = reg->id_vacina;
//		 fwrite(&sups, sizeof(sups),1,sup);
//		 
//		 printf("\n%i",tamanho(p));
//		 printf("\n[%i\t%s\t%i]", sups.id_vacina, sups.id_lote, sups.id_frasco);
//		 getch();
//		 
//		 PONT apagar = p->topo;
//		 p->topo     = apagar->PROX; 
//		 
//		 
//		 
//		 free(apagar);
//	}
//	 fclose(sup);
//	 return true;
//}

bool excluirElemPilha(PILHA* p, SUPORTE* reg) 
{  
   if ( p->topo == NULL) 
      return false;
   *reg        = p->topo->reg;  
   PONT apagar = p->topo;
   p->topo     = apagar->PROX; 
   free(apagar);
   return true;
}

bool excluiDaPilha (PILHA* p, FILE *sup)
{	SUPORTE regExcluido;
	
 	if ( excluirElemPilha(p, &regExcluido) == true ) {
//	   printf("\n[%i\t%s\t%i]", regExcluido.id_vacina, regExcluido.id_lote, regExcluido.id_frasco);
	   
		 fwrite(&regExcluido, sizeof(regExcluido),1, sup);
		 
		 if ( ferror(sup) ){
			printf("\nErro de gravação no lote!\n");
			getch();
			fclose(sup);
		}
	   
	} else {
//	   printf ("\nNao foi possivel excluir o registro.");
	   return false;
	 }
	 
	 return true;
}

/* 
S? tem sentido, se a pilha foi inicializada alguma vez.
Para reinicializar a pilha, precisamos excluir todos os seus elementos 
e colocar NULL no campo topo 
*/
void reinicializarPilha (PILHA* p) 
{  
   PONT apagar;
   PONT posicao = p->topo;  
   while (posicao != NULL) 
   {
      apagar  = posicao;  
      posicao = posicao->PROX;  
      free(apagar);
   }
   p->topo = NULL;
}
/*------------------*/
/* Fun??es de apoio */
/*------------------*/

Registro_lote reg_lote;

//void excluiDaPilha (PILHA* p)
//{	SUPORTE regExcluido;
// 	if ( excluirElemPilha(p, &regExcluido) == true )
//	   printf ("\nRegistro: [%i-%s-%i] excluido com sucesso.", regExcluido.id_vacina, regExcluido.id_lote, regExcluido.id_frasco );
//	else
//	   printf ("\nNao foi possivel excluir o registro.");
//}

void consultaLote(void) 
{
	system ("cls"); system ("color 37"); system ("mode 80,25");

	FILE *DAT = fopen ("LOTESVACINA.DAT", "r");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO LOTESVACINA.DAT  ");
		getch();
		exit(0);
	}

	printf ("__________________________________________________________________________");
	printf ("\n\n%s %-10s %-10s %-12s %-12s %-12s", "ID", "LOTE", "FRASCOS", "DATA_FAB", "DATA_VENC", "ANOS_VENC" );
	printf ("\n________________________________________________________________________");
	while ( !feof(DAT) )
	{
		/* lê o DAT */
		fread (&reg_lote, sizeof(reg_lote), 1, DAT);
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO LOTESVACINA.DAT  ");
			getch();
			exit(0);
		}
		if (feof(DAT)) break;
		/* Mostra registro lido */
		printf ("\n %i %-10s %i\t %-12s %-12s %f", reg_lote.id_vacina, reg_lote.id_lote, reg_lote.qtd_frascos, reg_lote.data_fab, reg_lote.data_ven, reg_lote.ven_prox);
	}
	fclose (DAT);
	getch();
}

void consultaSuporte(void)  
{
	system ("cls"); system ("color 37"); system ("mode 80,25");

	sup = fopen ("SUPORTE_1.DAT", "r");
	if (sup==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO SUPORTE_1.DAT  ");
		getch();
		exit(0);
	}

	printf ("__________________________________________________________________________");
	printf ("\n\n%s %-10s %-10s", "ID", "LOTE", "VACINA" );
	printf ("\n________________________________________________________________________");
	while ( !feof(sup) )
	{
		/* lê o DAT */
		fread (&sups, sizeof(sups), 1, sup);
		if ( ferror(sup) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO SUPORTE_1.DAT  ");
			getch();
			exit(0);
		}
		if (feof(sup)) break;
		/* Mostra registro lido */
		printf ("\n %i %-10s %i", sups.id_frasco, sups.id_lote, sups.id_vacina);
	}
	fclose (sup);
	getch();
}

void geraDistribuicao (PILHA* p)
{
	SUPORTE r[TAMANHO_SUPORTE];
	FILE *DAT = fopen ("LOTESVACINA.DAT", "r");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO LOTESVACINA.DAT  ");
		getch();
		exit(0);
	}
	
	while (!feof(DAT))
	{
		/* lê o DAT */
		fread (&reg_lote, sizeof(reg_lote), 1, DAT);
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO LOTESVACINA.DAT  ");
			getch();
			exit(0);
		}
		
		if (feof(DAT)) break; // se leu o EOF, termina o looping de leitura do arquivo
        
		//debug -> Vai começar a montar o suporte para esse lote
//		printf("\nVacina = [%i] Lote = [%s] Frascos = [%i]", 
//		reg_lote.id_vacina, reg_lote.id_lote, reg_lote.qtd_frascos); 
		
		if (reg_lote.qtd_frascos <= TAMANHO_SUPORTE)
		{
		   for ( i=reg_lote.qtd_frascos; i>0; i-- ) 
	 	   {
	 	   	//monta uma ocorrência de frasco ("tripinha")
	 	   	r[i-1].id_vacina = reg_lote.id_vacina;
			r[i-1].id_frasco = i;
			strcpy(r[i-1].id_lote, reg_lote.id_lote);
		    //debug -> Frasco montado para ir para a pilha
//		    printf("\nSUPORTE: Vacina = [%i] Lote = [%s] Frascos = [%i]", 
//		    r[i-1].id_vacina, r[i-1].id_lote, r[i-1].id_frasco);		
		    //insere frasco na pilha
	        if ( inserirElemPilha(p, r[i-1]) == true )
//	          printf ("\nFrasco [%i-%s-%i] inserido com sucesso.", 
			  r[i-1].id_vacina, r[i-1].id_lote, r[i-1].id_frasco);
	        else
	          printf ("\nFrasco [%i] NAO inserido!", r[i-1].id_frasco );
		   }
	    }
	}
	fclose (DAT);
	//debug
	printf ("\nFrascos distribuidos pela pilha de suporte!"); getch();
}

/* Consulta de relatório (fiz 5 diferentes, pois não consegui colocar o nome do dat como parametro e ir fazendo a leitura e escrita conforme o nome) */
void consulta_dat_em_relatorio1()
{
	FILE 				* ArqDat, *Relat;
	SUPORTE				suporte;
	long int 			cont=0;
	int 				qtd_registros;
//	char nome_original[14];
//	strcpy(nome_original, nome_arquivo);
//	char dat[] = ".dat";
//	char txt[] = ".txt";
	
	system ("cls"); system ("mode 170,50");

	tamanhovetor  = findSize("SUPORTE_1.dat");
	qtd_registros = tamanhovetor/sizeof(SUPORTE);
  qntregistros  = qtd_registros;
  
//	strcat(nome_arquivo, dat);
	ArqDat = fopen ("SUPORTE_1.dat", "rb+");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo SUPORTE_1.DAT");
		getch();
		exit(0);
	}
//	strcat(nome_original, txt);
	Relat = fopen ("SUPORTE_1.txt", "wt");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo TXT...");
		getch();
		exit(0);
	}
//	printf ("\nGerando relatório...");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf (Relat, "#         ID_VACINA	    ID_LOTE       ID_FRASCO \n");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	
	while ( !feof(ArqDat) )
	{
		// Limpa o registro 
		/*
		memset(suporte.Municipio,       '\0', sizeof(reg.Municipio));
		memset(reg.Nome_Escola,     '\0', sizeof(reg.Nome_Escola));
		reg.PK_COD_ENTIDADE = 0;*/
		cont++;
		fread (&suporte, sizeof(suporte), 1, ArqDat);
				
		if ( !feof(ArqDat) )
			fprintf (Relat,"\n%5i->[%8i]\t[%-8s]\t[%i]", 
			(int)cont, suporte.id_vacina, suporte.id_lote, suporte.id_frasco);
		
		if (feof(ArqDat)) break; 		
	}
    fclose(ArqDat);
    fclose(Relat);
//    system ("notepad SUPORTE_5.TXT");
//		printf("\nRelatório da pilha 1 disponível para visualização!");
}
void consulta_dat_em_relatorio2()
{
	FILE 				* ArqDat, *Relat;
	SUPORTE				suporte;
	long int 			cont=0;
	int 				qtd_registros;
//	char nome_original[14];
//	strcpy(nome_original, nome_arquivo);
//	char dat[] = ".dat";
//	char txt[] = ".txt";
	
	system ("cls"); system ("mode 170,50");

	tamanhovetor  = findSize("SUPORTE_2.dat");
	qtd_registros = tamanhovetor/sizeof(SUPORTE);
  qntregistros  = qtd_registros;
  
//	strcat(nome_arquivo, dat);
	ArqDat = fopen ("SUPORTE_2.dat", "rb+");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo SUPORTE_5.DAT");
		getch();
		exit(0);
	}
//	strcat(nome_original, txt);
	Relat = fopen ("SUPORTE_2.txt", "wt");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo TXT...");
		getch();
		exit(0);
	}
//	printf ("\nGerando relatório...");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf (Relat, "#         ID_VACINA	    ID_LOTE       ID_FRASCO \n");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	
	while ( !feof(ArqDat) )
	{
		// Limpa o registro 
		/*
		memset(suporte.Municipio,       '\0', sizeof(reg.Municipio));
		memset(reg.Nome_Escola,     '\0', sizeof(reg.Nome_Escola));
		reg.PK_COD_ENTIDADE = 0;*/
		cont++;
		fread (&suporte, sizeof(suporte), 1, ArqDat);
				
		if ( !feof(ArqDat) )
			fprintf (Relat,"\n%5i->[%8i]\t[%-8s]\t[%i]", 
			(int)cont, suporte.id_vacina, suporte.id_lote, suporte.id_frasco);
		
		if (feof(ArqDat)) break; 		
	}
    fclose(ArqDat);
    fclose(Relat);
//    system ("notepad SUPORTE_5.TXT");
//		printf("\nRelatório da pilha 2 disponível para visualização!");
}
void consulta_dat_em_relatorio3()
{
	FILE 				* ArqDat, *Relat;
	SUPORTE				suporte;
	long int 			cont=0;
	int 				qtd_registros;
//	char nome_original[14];
//	strcpy(nome_original, nome_arquivo);
//	char dat[] = ".dat";
//	char txt[] = ".txt";
	
	system ("cls"); system ("mode 170,50");

	tamanhovetor  = findSize("SUPORTE_3.dat");
	qtd_registros = tamanhovetor/sizeof(SUPORTE);
  qntregistros  = qtd_registros;
  
//	strcat(nome_arquivo, dat);
	ArqDat = fopen ("SUPORTE_3.dat", "rb+");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo SUPORTE_3.DAT");
		getch();
		exit(0);
	}
//	strcat(nome_original, txt);
	Relat = fopen ("SUPORTE_3.txt", "wt");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo TXT...");
		getch();
		exit(0);
	}
//	printf ("\nGerando relatório...");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf (Relat, "#         ID_VACINA	    ID_LOTE       ID_FRASCO \n");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	
	while ( !feof(ArqDat) )
	{
		// Limpa o registro 
		/*
		memset(suporte.Municipio,       '\0', sizeof(reg.Municipio));
		memset(reg.Nome_Escola,     '\0', sizeof(reg.Nome_Escola));
		reg.PK_COD_ENTIDADE = 0;*/
		cont++;
		fread (&suporte, sizeof(suporte), 1, ArqDat);
				
		if ( !feof(ArqDat) )
			fprintf (Relat,"\n%5i->[%8i]\t[%-8s]\t[%i]", 
			(int)cont, suporte.id_vacina, suporte.id_lote, suporte.id_frasco);
		
		if (feof(ArqDat)) break; 		
	}
    fclose(ArqDat);
    fclose(Relat);
//    system ("notepad SUPORTE_5.TXT");
//		printf("\nRelatório da pilha 3 disponível para visualização!");
}
void consulta_dat_em_relatorio4()
{
	FILE 				* ArqDat, *Relat;
	SUPORTE				suporte;
	long int 			cont=0;
	int 				qtd_registros;
//	char nome_original[14];
//	strcpy(nome_original, nome_arquivo);
//	char dat[] = ".dat";
//	char txt[] = ".txt";
	
	system ("cls"); system ("mode 170,50");

	tamanhovetor  = findSize("SUPORTE_4.dat");
	qtd_registros = tamanhovetor/sizeof(SUPORTE);
  qntregistros  = qtd_registros;
  
//	strcat(nome_arquivo, dat);
	ArqDat = fopen ("SUPORTE_4.dat", "rb+");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo SUPORTE_4.DAT");
		getch();
		exit(0);
	}
//	strcat(nome_original, txt);
	Relat = fopen ("SUPORTE_4.txt", "wt");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo TXT...");
		getch();
		exit(0);
	}
//	printf ("\nGerando relatório...");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf (Relat, "#         ID_VACINA	    ID_LOTE       ID_FRASCO \n");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	
	while ( !feof(ArqDat) )
	{
		// Limpa o registro 
		/*
		memset(suporte.Municipio,       '\0', sizeof(reg.Municipio));
		memset(reg.Nome_Escola,     '\0', sizeof(reg.Nome_Escola));
		reg.PK_COD_ENTIDADE = 0;*/
		cont++;
		fread (&suporte, sizeof(suporte), 1, ArqDat);
				
		if ( !feof(ArqDat) )
			fprintf (Relat,"\n%5i->[%8i]\t[%-8s]\t[%i]", 
			(int)cont, suporte.id_vacina, suporte.id_lote, suporte.id_frasco);
		
		if (feof(ArqDat)) break; 		
	}
    fclose(ArqDat);
    fclose(Relat);
//    system ("notepad SUPORTE_5.TXT");
//		printf("\nRelatório da pilha 4 disponível para visualização!");
}
void consulta_dat_em_relatorio5()
{
	FILE 				* ArqDat, *Relat;
	SUPORTE				suporte;
	long int 			cont=0;
	int 				qtd_registros;
//	char nome_original[14];
//	strcpy(nome_original, nome_arquivo);
//	char dat[] = ".dat";
//	char txt[] = ".txt";
	
	system ("cls"); system ("mode 170,50");

	tamanhovetor  = findSize("SUPORTE_5.dat");
	qtd_registros = tamanhovetor/sizeof(SUPORTE);
  qntregistros  = qtd_registros;
  
//	strcat(nome_arquivo, dat);
	ArqDat = fopen ("SUPORTE_5.dat", "rb+");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao ler arquivo SUPORTE_5.DAT");
		getch();
		exit(0);
	}
//	strcat(nome_original, txt);
	Relat = fopen ("SUPORTE_5.txt", "wt");
	if ( ArqDat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo TXT...");
		getch();
		exit(0);
	}
//	printf ("\nGerando relatório...");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	fprintf (Relat, "#         ID_VACINA	    ID_LOTE       ID_FRASCO \n");
	fprintf (Relat, "______________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	
	while ( !feof(ArqDat) )
	{
		// Limpa o registro 
		/*
		memset(suporte.Municipio,       '\0', sizeof(reg.Municipio));
		memset(reg.Nome_Escola,     '\0', sizeof(reg.Nome_Escola));
		reg.PK_COD_ENTIDADE = 0;*/
		cont++;
		fread (&suporte, sizeof(suporte), 1, ArqDat);
				
		if ( !feof(ArqDat) )
			fprintf (Relat,"\n%5i->[%8i]\t[%-8s]\t[%i]", 
			(int)cont, suporte.id_vacina, suporte.id_lote, suporte.id_frasco);
		
		if (feof(ArqDat)) break; 		
	}
    fclose(ArqDat);
    fclose(Relat);
//    system ("notepad SUPORTE_5.TXT");
}


/* ---------------------------------- CORPO DO PROGRAMA ------------------------------------ */
int main ()
{
   PILHA *pil; 
   pil = (PILHA *)malloc(sizeof(PILHA));
   inicializarPilha (pil);
   if (pil==NULL )
   {
  		printf ("\nErro ao alocar pilha! (pil=%p)", pil);
  		getch();
  		exit(0);
   }
   
   int *ant;
   char opc;
   int  j;
   
   SUPORTE regExcluido;
   
   ordenarLotes();
   consultaLote();
   
   geraDistribuicao (pil);
   
   sup = fopen  ("SUPORTE_1.dat", "wb+");
   sup2 = fopen ("SUPORTE_2.dat", "wb+");
   sup3 = fopen ("SUPORTE_3.dat", "wb+");
   sup4 = fopen ("SUPORTE_4.dat", "wb+");
   sup5 = fopen ("SUPORTE_5.dat", "wb+");
   
   // Exclui da pilha e coloca no DAT
//   printf("\nTAMANHO: %i", tamanho(pil));
//   getch();
	 for (i= tamanho(pil); i>0; i--) {
	 	
		 for(j = 0; j<50; j++) {
	 		excluiDaPilha(pil, sup);
	 	 }
	 	 fclose(sup);
	 	 
	 	 for(j = 0; j<50; j++) {
	 		excluiDaPilha(pil, sup2);
	 	 }
	 	 fclose(sup2); 
	 	 
	 	 for(j = 0; j<50; j++) {
	 		excluiDaPilha(pil, sup3);
	 	 }
	 	 fclose(sup3);
	 	 
	 	 for(j = 0; j<50; j++) {
	 		excluiDaPilha(pil, sup4);
	 	 }
	 	 fclose(sup4);
	 	
	 	 for(j = 0; j<50; j++) {
	 		excluiDaPilha(pil, sup5);
	 	 }
	 	 fclose(sup5);
	 
	 }
	 
//	 exibirPilha(pil);
   
//   getch();
   consulta_dat_em_relatorio1();
   consulta_dat_em_relatorio2();
   consulta_dat_em_relatorio3();
   consulta_dat_em_relatorio4();
   consulta_dat_em_relatorio5();
   printf("\nRelatorio das pilhas disponivel para visualizacao!");
   getch();
   return 0;
}
