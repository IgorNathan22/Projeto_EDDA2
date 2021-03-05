#include "bibliotecas\\funcoes_gerais.h"
#include "bibliotecas\\mensagens.h"

FILE *arqDat;
MEDICO medico;
int tamanhovetor;
int qntregistros;

//int busca_binaria(int crmlogin, char nomemedico[43], MEDICO *vetormedico) // 
int busca_binaria(int crmlogin, char usuario[43], MEDICO *vetormedico) // 
{    
	int ini=0, fim=qntregistros, meio;    
	//printf("\nCRM PASSADO: %i\nCRM MEDICO VETOR: %i, NOME PASSADO = [%s]\n", crmlogin, vetormedico[crmlogin].crm, usuario);
	//printf("CRM PASSADO: %i qntregistros: %i", crmlogin, qntregistros);
	while (ini<=fim)    
	{        
		meio=(ini+fim)/2; 
		
		/*
		if ( (vetormedico[meio].crm==crmlogin) 
		     && 
		     (strcmp(vetormedico[meio].nome,nomemedico)==0 ) )
		*/
		if ( (vetormedico[meio].crm==crmlogin) && (strcmp(vetormedico[meio].nome,usuario)==0 ) ){	
		    //para debug 
		    //printf("\nO string comparation está retornando, primeiro if: %i\n", strcmp(vetormedico[meio].nome,usuario));
			//printf ("\nACHOU! CRM = %i NOME DO MÉDICO = %s \n\tTAMANHO DA STRING DO MEDICO %i \t TAMANHO DA STRING PASSADA %i\n", 
			//vetormedico[meio].crm, vetormedico[meio].nome, strlen(vetormedico[meio].nome), strlen(usuario));
			//printf ("\nPressione qualquer tecla.");
			//getch();
			return meio; 
		}    
		if(vetormedico[meio].crm>crmlogin ){
			fim=meio-1;
		}
		else
			ini=meio+1;
	}    
	return false;
}

void abastecervetor(MEDICO *vetormedico){
	arqDat = fopen("MEDICOSCREMESP.DAT", "rb");
	if (arqDat == NULL){
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO MEDICOSCREMESP.DAT  ");
		getch();
		exit(0);
	}
	i = 0;
	while( !feof(arqDat)){
		fread(&vetormedico[i], sizeof(vetormedico[i]), 1, arqDat);
		if ( ferror(arqDat) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO MEDICOSCREMESP.DAT  ");
			getch();
			exit(0);
		}
		if (feof(arqDat))
		{
			break;
		} 
		i++;
	}
}

int main(){
	char 	usuario[42+1];
	int 	crmlogin;
	MEDICO 	* vetormedico;

	setlocale (LC_ALL, "");
	printf("-----------LOGIN DO MÉDICO---------\n\n");
	printf("\nCRM:     \t");
	fflush(stdin); 
	scanf("%i", &crmlogin);
	printf("NOME:	   \t");
	fflush(stdin);
	scanf("%[^\n]s", &usuario); //	scanf("%[^\n]s", &usuario);
	tamanhovetor = findSize("MEDICOSCREMESP.DAT");
	qntregistros = tamanhovetor/sizeof(MEDICO);
	vetormedico = (MEDICO *) malloc (qntregistros * sizeof (MEDICO)); 
    if (vetormedico == NULL)
    {
        printf ("malloc devolveu NULL!\nNão foi possível alocar %ld bytes.", 
		(qntregistros * sizeof (MEDICO)) );
        getch();
        exit (EXIT_FAILURE);
    }
	abastecervetor(vetormedico);
	if(busca_binaria(crmlogin, usuario, vetormedico) == false){
		//getch();
		msg_erro_login();
	}
	printf("\nUSUARIO LOGADO COM SUCESSO!");
	free(vetormedico);
	return(0);
}
