typedef int bool;

#include "funcoes_gerais.h"
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_SUPORTE 250
FILE * arqDat;

Registro_lote lote;

int tamanhovetor;
int qntregistros;

void envia_vet_ordenado_dat(Registro_lote * vetorlote);

void troca (Registro_lote *A, Registro_lote *B) 
{
  Registro_lote aux = *A; 
  *A = *B; 
  *B = aux;
}

int particiona (Registro_lote * vetor, int ini, int pivo) 
{    
    int   i;
    int   p_maior = ini; /* a posi��o do maior � a do in�cio do vetor */    
    
    for ( i=ini; i<pivo; i++ ) /* percorre o vetor da posi��o ini at� a do piv� */
    {        
       if ( vetor[i].ven_prox > vetor[pivo].ven_prox ) /*se o elemento da posi��o atual for menor que o piv�...*/
       {            
            troca(  &vetor[i], &vetor[p_maior]); /*...troca o atual com o maior */
            p_maior++; /* o maior avan�a uma posi��o */
       }    
   }     
   /* percorrido o vetor, o piv� troca de posi��o com a do maior elemento... */
   troca(  &vetor[p_maior], &vetor[pivo]); 
   return p_maior; /* ... e o maior elemento passa a ser o novo piv� */ 
}

void quick_sort	(Registro_lote * vetor, int ini, int fim) 
{    
   int pivo;
   if ( ini<fim ) /* Caso base */ 
   {        
        pivo = particiona ( vetor, ini, fim ); /* Particiona o vetor*/ 
        quick_sort( vetor, ini,    pivo-1 );    /* Ordena do in�cio do vetor at� antes do piv� */
        quick_sort( vetor, pivo+1, fim);      /* Ordena desde ap�s o piv� at� o fim do vetor */
   } 
}

void ordenarLotes(void){
	Registro_lote * vetorlote;
	char nomeArquivo[100] = "LOTESVACINA.DAT";
	tamanhovetor = findSize(nomeArquivo);
	qntregistros = tamanhovetor/sizeof(Registro_lote);
	vetorlote = (Registro_lote *) malloc (qntregistros * sizeof (Registro_lote)); 
    if (vetorlote == NULL)
    {
        printf ("malloc devolveu NULL!\nN�o foi poss�vel alocar %ld bytes.", 
		(qntregistros * sizeof (Registro_lote)) );
        getch();
        exit (EXIT_FAILURE);
    }

	arqDat = fopen("LOTESVACINA.DAT", "rb+");
	if (arqDat == NULL){
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO LOTESVACINA.DAT  ");
		getch();
		exit(0);
	}
	i = 0;
	while( !feof(arqDat)){
		fread(&vetorlote[i], sizeof(vetorlote[i]), 1, arqDat);
		if ( ferror(arqDat) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO LOTESVACINA.DAT  ");
			getch();
			exit(0);
		}
		if (feof(arqDat))
		{
			break;
		} 
		i++;
	}

	quick_sort(vetorlote, 0, qntregistros-1);
	envia_vet_ordenado_dat(vetorlote);
}


void envia_vet_ordenado_dat (Registro_lote	* vetorlote)
{
    long int i;
	arqDat = fopen ("LOTESVACINA.DAT", "wb+");
	if ( arqDat==NULL )
	{	system ("cls");
		printf ("Erro ao gerar arquivo LOTESVACINA.DAT ordenado!");
		getch();
		exit(0);
	}
    for (i=0; i<qntregistros; i++)
    {
    	fwrite (&vetorlote[i], sizeof(vetorlote[i]), 1, arqDat);
    	if ( ferror(arqDat) )
   	    {  system ("cls");
		   printf ("Erro ao gravar no arquivo LOTESVACINA.DAT no registro %li!", i);
		   getch();
		   exit(0);	
		}
	}
	fclose(arqDat);
//	printf ("\nLOTESVACINA.DAT ordenado com sucesso!");
	free(vetorlote);
//	getch();
}


