typedef  int   bool; 
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

/* --------------------------- Prot?tipos das fun??es --------------------------------------- */
void inicializarPilha 	(PILHA* p);
int  tamanho 			(PILHA* p);
void exibirPilha 		(PILHA* p);
bool inserirElemPilha	(PILHA* p, SUPORTE reg);
bool excluirElemPilha	(PILHA* p, SUPORTE *reg); 
void reinicializarPilha (PILHA* p);
void 		insereNaPilha 	(PILHA* p);

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
	 	  strcpy(r[i-1].nome, reg_lote.nome);
	 	  r[i-1].id_vacina = reg_lote.id_vacina;
			r[i-1].id_frasco = i;
			strcpy(r[i-1].id_lote, reg_lote.id_lote);
		    //debug -> Frasco montado para ir para a pilha
//		    printf("\nSUPORTE: Vacina = [%i] Lote = [%s] Frascos = [%i]", 
//		    r[i-1].id_vacina, r[i-1].id_lote, r[i-1].id_frasco);		
		    //insere frasco na pilha
	        if ( inserirElemPilha(p, r[i-1]) == true ) {
//	          printf ("\nFrasco [%i-%s-%i] inserido com sucesso.", 
//			  r[i-1].id_vacina, r[i-1].id_lote, r[i-1].id_frasco);
	        }else
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
