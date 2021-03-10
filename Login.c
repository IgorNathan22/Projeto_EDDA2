#include "bibliotecas\\funcoes_gerais.h"
#include "bibliotecas\\mensagens.h"

FILE *arqDat;
MEDICO medico;
int tamanhovetor;
int qntregistros;

void statusmedico(MEDICO medico);

//int busca_binaria(int crmlogin, char nomemedico[43], MEDICO *vetormedico) // 
int busca_binaria(int crmlogin, char usuario[43], MEDICO *vetormedico) // 
{    
	int ini=0, fim=qntregistros, meio;    
	//printf("\nCRM PASSADO: %i\nCRM MEDICO VETOR: %i, NOME PASSADO = [%s]\n", crmlogin, vetormedico[crmlogin].crm, usuario);
	//printf("CRM PASSADO: %i qntregistros: %i", crmlogin, qntregistros);
	
	while (ini<=fim)    
	{        
		meio=(ini+fim)/2; 
		if ( (vetormedico[meio].crm==crmlogin) && (strcmp(vetormedico[meio].nome,usuario)==0 ) ){	
		    //para debug 
		    //printf("\nO string comparation está retornando, primeiro if: %i\n", strcmp(vetormedico[meio].nome,usuario));
			//printf ("\nACHOU! CRM = %i NOME DO MÉDICO = %s \n\tTAMANHO DA STRING DO MEDICO %i \t TAMANHO DA STRING PASSADA %i\n", 
			//vetormedico[meio].crm, vetormedico[meio].nome, strlen(vetormedico[meio].nome), strlen(usuario));
			//printf ("\nPressione qualquer tecla.");
			//getch();
			statusmedico(vetormedico[meio]);
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

void statusmedico(MEDICO medico){
	if(strcmp(medico.status, "I") == 0){
		msg_usu_inativo();
	}
}

void tratarusuario(char usuario[43], int tamanhostring){
	if(tamanhostring >= 43 || tamanhostring == 0){
		system ("color 40");
		printf("\nNome de usuário inválido\n");
		getch();
		exit(0);
	}
	tamanhostring + 1;
	while(tamanhostring != 42){
		usuario[tamanhostring] = ' ';
		tamanhostring++;
	}
	
	/*tamanhostring = strlen(usuario);
	printf("\nTAMANHO DA STRING DO USUARIO PÓS TRATAMENTO = %i\n", tamanhostring); //DEBUG
	getch();*/
}

void abastecervetor(MEDICO *vetormedico){
	arqDat = fopen("MEDICOSCREMESP.DAT", "rb");
	if (arqDat == NULL){
		system ("cls");
		system ("color 40");
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
			system ("color 40");
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
	int tamanhostring;
	MEDICO 	* vetormedico;

	setlocale (LC_ALL, "");
	system("mode 60, 20");
	printf("\t-----------LOGIN DO MÉDICO---------\n\n");
	printf("\nCRM:     \t");
	fflush(stdin); 
	scanf("%i", &crmlogin);
	printf("NOME:	   \t");
	fflush(stdin);
	gets(usuario); //	scanf("%[^\n]s", &usuario);
	tamanhostring = strlen(usuario);
	tratarusuario(usuario, tamanhostring);
	
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
		msg_erro_login();
	}
	free(vetormedico);
	
	system("cls"); system ("color A0"); system("mode 50,5");
	printf("\tUSUARIO LOGADO COM SUCESSO!");
	getch();
	system("AdmVacina.exe");
	return(0);
}
