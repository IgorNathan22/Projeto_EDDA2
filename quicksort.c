#include "quicksort.h"

int particiona (float * vetor, int ini, int pivo) 
{    
    int   i;
    int   p_maior = ini; /* a posi��o do maior � a do in�cio do vetor */    
    
    for ( i=ini; i<pivo; i++ ) /* percorre o vetor da posi��o ini at� a do piv� */
    {        
       if ( vetor[i] < vetor[pivo] ) /*se o elemento da posi��o atual for menor que o piv�...*/
       {            
            troca(  &vetor[i], &vetor[p_maior] ); /*...troca o atual com o maior */
            p_maior++; /* o maior avan�a uma posi��o */
       }    
   }     
   /* percorrido o vetor, o piv� troca de posi��o com a do maior elemento... */
   troca(  &vetor[p_maior], &vetor[pivo] ); 
   return p_maior; /* ... e o maior elemento passa a ser o novo piv� */ 
}


/* Efetua as trocas necess�rias */
void troca (float *A, float *B) 
{
  float aux = *A; 
  *A = *B; 
  *B = aux;
}

void quick_sort	(float * vetor, int ini, int fim) 
{    
   int pivo;
   if ( ini<fim ) /* Caso base */ 
   {        
        pivo = particiona ( vetor, ini, fim ); /* Particiona o vetor*/ 
        quick_sort( vetor, ini,    pivo-1 );    /* Ordena do in�cio do vetor at� antes do piv� */
        quick_sort( vetor, pivo+1, fim);      /* Ordena desde ap�s o piv� at� o fim do vetor */
   } 
}

void mostra_notas (float *notas, int tamanho) {
	int i;
  for(i = 0; i<tamanho; i++) {
  	printf("[%.2f] ", notas[i]);
	}
	printf("\n");
}
