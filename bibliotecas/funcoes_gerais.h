#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#define false -1
#define true 1

FILE      *DAT;
FILE *lotes;
FILE *sup;
FILE *sup2;
FILE *sup3;
FILE *sup4;
FILE *sup5;
long int       i, cont;

typedef struct   
{          
  int 	id_vacina;
  char 	id_lote[8+1];
  int 	id_frasco;
} 
SUPORTE;

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


SUPORTE sups;

typedef struct{
	int crm;
	char nome[42+1];
	char status[2];
	char dt_admicao[10+1];
	char dt_final[10+1];
	char cidade[37+1];
	char estado[2+1];
	char especializacao[200+1];
}MEDICO;

typedef struct{
	char nome[50+1];
	char nasc[10+1];
	int idade;
	char cpf[11+1];
	char pais[20+1];
	char estado[25+1];
	char munic[50+1];
	char lograd[50+1];
	char nro[6+1];
	char comp[15+1];
	char bairro[25+1];
	char cep[10+1];
	char email[50+1];
	char tel[15+1];
}Cidadao;

typedef struct {
	int 	id_vacina;
	char 	id_lote[8+1];
	int 	qtd_frascos;
	char 	data_fab[10+1];
	char 	data_ven[10+1];
  	double 	ven_prox;
} Registro_lote;

int opcoes (int controle) {
	printf("\n\t\t\tADM VACINA");
	printf("\n\n ---------------------------------------------------------------------");
	printf("\n\t\t1. Pré-cadastro de cidadãos");
	printf("\n\t\t2. Cadastro de vacinas");
	printf("\n\t\t3. Atendimento");
	printf("\n\t\t0. ENCERRAR");
	printf("\n\n\t\t Opção desejada: ");
	scanf("%i", &controle);
	switch(controle)
	{
		case 1 :
			system("PreCadastroCidadao.exe");
			return controle = 1;
		break;
		
		case 2 :
			system("CadastroVacinaLote.exe");
			return controle = 2;
		break;
			
		case 3 :
			system("Atendimento.exe");
			return controle = 3;
		break;
		
		case 0 : 
			return controle = 0;
		default :
			printf("\nValor inválido\n");
			getch();
	}
}

long int findSize(char file_name[]) 
{ 
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "r");   
    // checking if the file exist or not 
    if (fp == NULL) { 
        system ("cls"); system ("color 04"); system ("mode 70,3");
		printf("\n\t\tARQUIVO %s INEXISTENTE!", file_name);
		getch();
		exit(1);
		return -1;
    } 
    fseek(fp, 0L, SEEK_END); 
    // calculating the size of the file 
    long int res = ftell(fp); 
    // closing the file 
    fclose(fp); 
    return res; 
}

/* --------------------------- FUNÇÕES DA PILHA ------------------------ */
Registro_lote reg_lote;

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

bool estaVazia(PILHA* p) 
{
   if (p->topo == NULL) 
      return true;  
   return false;
}

bool inserirElemPilha(PILHA* p, SUPORTE reg) 
{  
   PONT novo  = (PONT) malloc(sizeof(ELEMENTO));  
   novo->reg  = reg;
   novo->PROX = p->topo;  
   p->topo    = novo;  
   return true;
}

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

