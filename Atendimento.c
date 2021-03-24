typedef  int   bool; 
/* --------------------------------------- Bibliotecas -------------------------------------- */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include "bibliotecas\\funcoes_gerais.h"
#include "bibliotecas\\mensagens.h"

/* variáveis globais */
long int     TAMANHO_VETOR;
long int     qtd_registros;
/* Fila */
#define  true  1      
#define false -1

void consultaFila(void);

/* Definindo o ELEMENTO */
typedef struct auxC
{  
   Cidadao reg;
   struct 	    auxC * PROX; 
}                                            
ELEMENTOC;

/* Definindo a fila */
typedef ELEMENTOC  *PONTC;

typedef struct 
{
   PONTC inicio;   
   PONTC fim;       
} 
fila;

/* ------------------------------------ PILHA ----------------------------- */
int verificaVacina(char file_name[]) {
	SUPORTE suporte;
	FILE *DAT = fopen (file_name, "rb+");
	if(DAT==NULL) {
		return 0;
	}
	int tamanho = ((int) findSize(file_name) ) /sizeof(suporte);
	fclose(DAT);
	return tamanho;
}

void suporteMemoria(char file_name[], PILHA *p, fila * f) {
	SUPORTE suporte;
	FILE *DAT = fopen (file_name, "rb+");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO %s", file_name);
		getch();
		exit(0);
	}
	
	while (!feof(DAT))
	{
		/* lê o DAT */
		fread (&suporte, sizeof(suporte), 1, DAT);
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO %s.DAT  ", file_name);
			getch();
			exit(0);
		}
		
		if (feof(DAT)) break; 

    if ( inserirElemPilha(p, suporte) == true ) {
			
    }else
			printf("Vacina %i - %s - %i não colocado!", suporte.id_frasco, suporte.nome, suporte.id_lote);
	  }
	   
	fclose (DAT);
}

void atualizaArquivos(fila *f, PILHA *p, char file_name[]) {
	
	FILE *DATP = fopen(file_name, "wb+");
	FILE *DATM = fopen("MUNICIPES.DAT", "wb+");
	
	while (estaVazia(p) != true) {
		excluiDaPilha(p, DATP);
	}
	fclose(DATP);
	
	FILE *DATF = fopen("FILAVACINA.DAT", "wb+");
	
	while (estaVaziaF(f) != true) {
		filaMunicipeNoDat(f, DATF, DATM);
	}
	fclose(DATF);
	fclose(DATM);
	
	consultaFila();
//	consultaSuporte(file_name);
}
/* ------------------------------------ HEAP SORT ------------------------- */
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
//    getch();
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
//    getch();
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
    } 
    vet_reg = (Cidadao *) malloc (qtd_registros * sizeof (Cidadao)); 
    if (vet_reg == NULL)
    {
        printf ("malloc devolveu NULL!\nNão foi possível alocar %ld bytes.", 
		(qtd_registros * sizeof (Cidadao)) );
        exit (EXIT_FAILURE);
    }
    abastece_vetor(vet_reg);  		

	BuildHeap (vet_reg);      	

	envia_vet_ordenado_dat (vet_reg);
    consulta_dat_em_relatorio();
}
/* -------------------------- FILA -------------------- */

void inicializarfila (fila * p)
{
  p->inicio = NULL;
  p->fim    = NULL;
}

int tamanhoF (fila* p) 
{  
	PONTC    end = p->inicio;  
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
   PONTC end = p->inicio;  
   system ("cls");
   printf("fila: \" ");  
   while (end != NULL) 
   {
	printf("%i ", end->reg.idade);  
	end = end->PROX;
   }
   printf("\"\n");
}

bool estaVaziaF(fila* p) 
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
	i = 1;
	while (!feof(DAT))
	{
		
		/* lê o DAT */

		fread (&reg, sizeof(reg), 1, DAT);
		reg.pos_fila = i;
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO .DAT  ");
			getch();
			exit(0);
		}
		
		if (feof(DAT)) break;
		
   PONTC novo = (PONTC) malloc(sizeof(ELEMENTOC));  
   novo->reg = reg;
   novo->PROX = NULL;
   if (f->inicio==NULL) 
      f->inicio = novo;  
   else 
      f->fim->PROX = novo;
   f->fim = novo;
   
   i++;
  }
  
}

void inserirNaFilaVac(fila *f, FILE *DAT) {
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
		fread (&reg, sizeof(reg), 1, DAT);
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO .DAT  ");
			getch();
			exit(0);
		}
		
		if (feof(DAT)) break;
		
   PONTC novo = (PONTC) malloc(sizeof(ELEMENTOC));  
   novo->reg = reg;
   novo->PROX = NULL;
   if (f->inicio==NULL) 
      f->inicio = novo;  
   else 
      f->fim->PROX = novo;
   f->fim = novo;
   
   i++;
	}
}

bool excluiDaFila(fila * f, Cidadao* reg) {
		
		if (f->inicio==NULL) 
      return false;
   *reg = f->inicio->reg;  
   PONTC apagar = f->inicio;
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

bool filaMunicipeNoDat(fila * f, FILE *DAT, FILE *DATM) {
	Cidadao regExcluido;
	
	if ( excluiDaFila(f, &regExcluido) == true ) {
	   
	fwrite(&regExcluido, sizeof(regExcluido),1, DAT);
	fwrite(&regExcluido, sizeof(regExcluido),1, DATM);
		
	if ( ferror(DAT) || ferror(DATM) ){
		printf("\nErro de gravação no lote!\n");
		getch();
		fclose(DAT);
		fclose(DATM);
	}
	   
	} else {
	   return false;
	 }
	 return true;
}

bool insereElemFila(fila * f, Cidadao reg) {
	PONTC novo = (PONTC) malloc(sizeof(ELEMENTOC));  
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

	FILE *DAT = fopen ("FILAVACINA.DAT", "rb+");
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
			printf ("\n  ERRO AO LER ARQUIVO FILAVACINA.DAT  ");
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

void geraRelatorioVacina(Cidadao regExcluido , SUPORTE supExcluido) {
	int tamanho = ((int) findSize("FILAVACINA.DAT") ) /sizeof(regExcluido);
	time_t t = time(NULL);
  struct tm tm = *localtime(&t);
	
	FILE *Relat = fopen("COMPROVANTE.TXT", "wb+");
	if ( Relat==NULL )
	{
		system ("cls");
		printf ("Erro ao gerar arquivo COMPROVANTE.TXT");
		getch();
		exit(0);
	}
	
	fprintf(Relat, "\n\t\t\t    ATENDIMENTO");
	fprintf(Relat, "\n________________________________________________________________________");
	fprintf(Relat, "\n\n  NOME: %-50s", &regExcluido.nome);
	fprintf(Relat, "[%i/%i]", regExcluido.pos_fila, tamanho);
	fprintf(Relat, "\n\n  CPF: %s", &regExcluido.cpf);
	fprintf(Relat, "\n\n  %s [Lote: %s/Frasco: %i]", &supExcluido.nome, supExcluido.id_lote, supExcluido.id_frasco);
	fprintf(Relat, "\n\n  Primeira dose: %02d/%02d/%d", tm.tm_mday, tm.tm_mon +1, tm.tm_year + 1900);
	fprintf(Relat, "\n\n  Segunda dose:  %02d/%02d/%d", tm.tm_mday, tm.tm_mon +2, tm.tm_year + 1900);
	
	fclose(Relat);
	system("notepad COMPROVANTE.TXT");
//	getch();
}

void removerFilaExibir(fila * f, PILHA * p, char file_name[]) {
	
	time_t t = time(NULL);
  struct tm tm = *localtime(&t);
	
	Cidadao regExcluido;
	SUPORTE supExcluido;
	
	int tamanho = ((int) findSize("FILAVACINA.DAT") ) /sizeof(regExcluido);
	
	if(estaVaziaF(f) == true) {
		msg_fila_vazia();
		exit(0);
	}
	
	char opc;
	
		 do {
		 	
		 	if(estaVaziaF(f) == true) {
				msg_fila_vazia();
				exit(0);
			}
		 	
			if ( excluiDaFila(f, &regExcluido) == true && excluirElemPilha(p, &supExcluido)) {
				system("cls"); system("mode 73,15");
				printf("\n\t\t\t    ATENDIMENTO");
				printf("\n________________________________________________________________________");
				printf("\n\n  NOME: %-50s", regExcluido.nome);
				printf("[%i/%i]", regExcluido.pos_fila, tamanho);
				printf("\n\n  CPF: %s", regExcluido.cpf);
				printf("\n\n  %s [Lote: %s/Frasco: %i]", supExcluido.nome, supExcluido.id_lote, supExcluido.id_frasco);
				printf("\n\n  Primeira dose: %02d/%02d/%d", tm.tm_mday, tm.tm_mon +1, tm.tm_year + 1900);
				printf("\n\n  Segunda dose:  %02d/%02d/%d", tm.tm_mday, tm.tm_mon +2, tm.tm_year + 1900);
				geraRelatorioVacina(regExcluido, supExcluido);
				printf("\n\n\n\t Atender mais uma pessoa? SIM[s] / NAO [n]: ");
				fflush(stdin); opc = getche();
			}
		} while(opc != 'n' && opc != 'N');
		
		if(estaVazia(p) == true) {
			msg_sem_vacina();
			exit(0);
		}
	
	atualizaArquivos(f, p, file_name);

}

void reinicializarFila(fila * f) 
{  
   PONTC end = f->inicio;
   PONTC apagar;
   while (end != NULL) 
   {  
      apagar = end;  
	  end = end->PROX;  
	  free(apagar);
   }
   f->inicio = NULL;  
   f->fim = NULL;
}

void HeapFila(fila * F, PILHA * pil, char file_name[]) {
	DAT = fopen ("MUNICIPES.DAT", "rb+");
	inserirNaFila(F, DAT);
	fclose(DAT);
	
	DAT = fopen("FILAVACINA.DAT", "wb+");
	
	while(estaVaziaF(F) != true) {
		filaNoDat(F, DAT);	
	}
	
	fclose(DAT);
	
	DAT = fopen("FILAVACINA.DAT", "rb+");
	inserirNaFilaVac(F, DAT);
	fclose(DAT);
	
	removerFilaExibir(F, pil, file_name);
}

/* ---------------------------------- CORPO DO PROGRAMA ------------------------------------ */
int main ()
{	
	setlocale (LC_ALL, "");  
	
	/* PILHA */
	PILHA *pil; 
	pil = (PILHA *)malloc(sizeof(PILHA));
	inicializarPilha (pil);
	
	if (pil==NULL )
	{
		printf ("\nErro ao alocar pilha! (pil=%p)", pil);
		getch();
		exit(0);
	}	
	
	/* HEAP E FILA */
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
	
	if(verificaVacina("SUPORTE_1.DAT") > 0) {
		suporteMemoria("SUPORTE_1.DAT", pil, F);
		HeapFila(F, pil, "SUPORTE_1.DAT");
		
	} else if (verificaVacina("SUPORTE_2.DAT") > 0) {
		suporteMemoria("SUPORTE_2.DAT", pil, F);
		HeapFila(F, pil, "SUPORTE_2.DAT");
		
	} else if (verificaVacina("SUPORTE_3.DAT") > 0) {
		suporteMemoria("SUPORTE_3.DAT", pil, F);
		HeapFila(F, pil, "SUPORTE_3.DAT");
		
	} else if (verificaVacina("SUPORTE_4.DAT") > 0) {
		suporteMemoria("SUPORTE_4.DAT", pil, F);
		HeapFila(F, pil, "SUPORTE_4.DAT");
		
	} else if (verificaVacina("SUPORTE_5.DAT") > 0) {
		suporteMemoria("SUPORTE_5.DAT", pil, F);
		HeapFila(F, pil, "SUPORTE_5.DAT");
	} else {
		msg_sem_vacina();
	}
	
 	return 0;
} 
