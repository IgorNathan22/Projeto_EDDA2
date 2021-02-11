#include "quicksort.h"

int particiona (float * vetor, int ini, int pivo) 
{    
    int   i;
    int   p_maior = ini; /* a posição do maior é a do início do vetor */    
    
    for ( i=ini; i<pivo; i++ ) /* percorre o vetor da posição ini até a do pivô */
    {        
       if ( vetor[i] < vetor[pivo] ) /*se o elemento da posição atual for menor que o pivô...*/
       {            
            troca(  &vetor[i], &vetor[p_maior] ); /*...troca o atual com o maior */
            p_maior++; /* o maior avança uma posição */
       }    
   }     
   /* percorrido o vetor, o pivô troca de posição com a do maior elemento... */
   troca(  &vetor[p_maior], &vetor[pivo] ); 
   return p_maior; /* ... e o maior elemento passa a ser o novo pivô */ 
}


/* Efetua as trocas necessárias */
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
        quick_sort( vetor, ini,    pivo-1 );    /* Ordena do início do vetor até antes do pivô */
        quick_sort( vetor, pivo+1, fim);      /* Ordena desde após o pivô até o fim do vetor */
   } 
}

void mostra_notas (float *notas, int tamanho) {
	int i;
  for(i = 0; i<tamanho; i++) {
  	printf("[%.2f] ", notas[i]);
	}
	printf("\n");
}
