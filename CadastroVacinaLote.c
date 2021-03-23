/* Bibliotecas */
#include "bibliotecas\\funcoes_gerais.h"

#define true 1
#define false -1

/* Tipos pré-definidos */
typedef struct
{
   int    id;
   char   nome[15+1];
   char   fab[28+1];
   char   tipo[43+1];
   int    doses;
   char   eficacia[9+1];
   char   arm[50+1];
}
registro_vacina;

typedef struct {
	int id_vacina;
	char id_lote[8+1];
	int qtd_frascos;
	char data_fab[10+1];
	char data_ven[10+1];
  double ven_prox;
} Registro_lote;

/* Variáveis globais */

registro_vacina  reg;
Registro_lote reg_lote;

#define MAX_DEFAULT  5
#define MAX_LOTE_DEFAULT 6

int verificaIdVacina(int id_vacina) {
	DAT = fopen ("VACINAS.DAT", "r");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO VACINAS.DAT  ");
		getch();
		exit(0);
	}	
	
	while ( !feof(DAT) )
	{
		fread (&reg, sizeof(reg), 1, DAT);
		
		if(id_vacina == reg.id) {
			fclose (DAT);
			return true;
		}
		if (feof(DAT)) break;
	}
	
	fclose (DAT);
	return false;
	
}

int cadastraLote() {
	
	char dia_aux[2+1];
	char mes_aux[2+1];
	char ano_aux[4+1];
	float dia;
	float mes;
	float ano;
		
	system("cls"); system ("color 80");

	FILE 	*DAT = fopen ("LOTESVACINA.DAT", "a");
	Registro_lote reg_lote;
	
	printf("\nId da vacina: "); scanf("%d", &reg_lote.id_vacina);
	
	while (verificaIdVacina(reg_lote.id_vacina) == false) {
		printf("\n Não existe vacina com esse id!");
		printf("\n\n Id da vacina: "); scanf("%d", &reg_lote.id_vacina);
	}

	printf("\nId do lote: "); fflush(stdin); gets(reg_lote.id_lote);

	printf("\nQuantidade de frascos: "); scanf("%d", &reg_lote.qtd_frascos);

	printf("\nData de fabricação (dd/mm/aaaa): "); fflush(stdin); gets(reg_lote.data_fab);

	printf("\nData de vencimento (dd/mm/aaaa): "); fflush(stdin); gets(reg_lote.data_ven);
	
	for(i= 0; i<3; i++) {
		dia_aux[i] = '\0';
		mes_aux[i] = '\0';
	}
	
	for (i=0;i<5;i++) {
		ano_aux[i] = '\0';
	}
	
	for(i= 0; i<2; i++) {
		dia_aux[i] = reg_lote.data_ven[i];
//		if(reg_lote.data_ven[i] == '/'); break;
	}
	
	for(i= 0; i<2; i++) {
		mes_aux[i] = reg_lote.data_ven[i+3];
//		if(reg_lote.data_ven[i+3] == '/'); break;
	}
	
	for(i= 0; i<4; i++) {
		ano_aux[i] = reg_lote.data_ven[i+6];
//		if(reg_lote.data_ven[i+6] == '/'); break;
	}
	
	printf("Dia: %s Mês: %s Ano: %s", dia_aux, mes_aux, ano_aux);
	
	dia = atof(dia_aux);
	mes = atof(mes_aux);
	ano = atof(ano_aux);
	reg_lote.ven_prox = (double)(dia/365)+(mes/12)+ano;

	fwrite (&reg_lote, sizeof(reg_lote), 1, DAT);
	
	if ( ferror(DAT) ){
		printf("\nErro de gravação no lote!\n");
		getch();
		fclose(DAT);
	} else {
		printf("\nLote cadastrado com sucesso!");
		getch();
		fclose(DAT);
	}

}

void cadastraVacina() {

	system("cls");

	FILE 	*DAT = fopen ("VACINAS.DAT", "a");
	registro_vacina reg;
	int tamanho = ((int) findSize("VACINAS.DAT") ) /sizeof(reg);
	
	reg.id = tamanho +  1; 
	printf("Id: %i", reg.id);

	printf("\nNome da vacina: "); fflush(stdin); gets(reg.nome);

	printf("\nFabricante: "); fflush(stdin); gets(reg.fab);

	printf("\nTipo: "); fflush(stdin); gets(reg.tipo);

	printf("\nDoses: "); scanf("%d", &reg.doses);

	printf("\nEficácia: "); fflush(stdin); gets(reg.eficacia);

	printf("\nArmazenamento: "); fflush(stdin); gets(reg.arm);
	
	fwrite (&reg, sizeof(reg), 1, DAT);
		
	if ( ferror(DAT) ){
		printf("\nErro de gravação!\n");
		getch();
		exit(0);

	} else {
		printf("\nNova vacina cadastrada com sucesso!");
		getch();
	}		
	
	fclose(DAT);
}

void consultaVacina() {
	system ("cls"); system ("color 37"); system ("mode 165,25");

	DAT = fopen ("VACINAS.DAT", "r");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO VACINAS.DAT  ");
		getch();
		exit(0);
	}

	printf ("___________________________________________________________________________________________________________________________________________________________________");
		printf ("\n\n%s %-15s %-32s %-42s %s %-12s %-50s", "ID", "NOME", "FABRICACAO", "TIPO", "DOSES", "EFICACIA", "ARMAZENAMENTO");
	printf ("\n_________________________________________________________________________________________________________________________________________________________________");
	while ( !feof(DAT) )
	{
		/* lê o DAT */
		fread (&reg, sizeof(reg), 1, DAT);
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO VACINAS.DAT  ");
			getch();
			exit(0);
		}
		if (feof(DAT)) break;
		/* Mostra registro lido */
		printf ("\n %i %-15s %-32s %-47s %i %-12s %-50s", reg.id, reg.nome, reg.fab, reg.tipo, reg.doses, reg.eficacia, reg.arm);
	}
	fclose (DAT);
	getch();
}

void consultaLote() {
	system ("cls"); system ("color 37"); system ("mode 80,25");

	DAT = fopen ("LOTESVACINA.DAT", "r");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO LOTESVACINA.DAT  ");
		getch();
		exit(0);
	}

	printf ("__________________________________________________________________________");
		printf ("\n\n%s %-10s %-10s %-12s %-12s", "ID", "LOTE", "FRASCOS", "DATA_FAB", "DATA_VENC");
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
		printf ("\n %i %-10s %i\t %-12s %-12s", reg_lote.id_vacina, reg_lote.id_lote, reg_lote.qtd_frascos, reg_lote.data_fab, reg_lote.data_ven);
	}
	fclose (DAT);
	getch();
}

void cadastraLoteDefault() {
	Registro_lote reg_lote[MAX_LOTE_DEFAULT] =
	{
   {1, "20210001", 50, "10/01/2021", "05/01/2022",2022.09703},
   {1, "20210002", 50, "11/03/2021", "06/03/2022",2022.26644},
   {2, "20200001", 50, "16/12/2020", "11/12/2021",2022.03014},
   {3, "21210001", 25, "15/03/2021", "10/03/2022",2022.2774},
   {4, "21210001", 25, "14/05/2021", "09/05/2022",2022.44132},
   {5, "20200001", 50, "15/12/2020", "10/12/2021",2022.0274},
	};
	
	
	DAT = fopen("LOTESVACINA.dat", "w");
	
	if ( DAT!=NULL) {
		fwrite (&reg_lote, sizeof (reg_lote), 1, DAT);
    fclose(DAT);
	} else {
		printf ("\nERRO AO ABRIR O ARQUIVO LOTES.DAT");
    getch();
	}
	printf("\nArquivo LOTES.DAT gerado!");
	
}

void cadastraDefault() {
	registro_vacina reg[MAX_DEFAULT] =
	{
   {1,"CoronaVac", "SinoVac - Instituto Butantan", "Virus inativado", 2, "50.38%", "2 a 8C, podendo ficar ate 27 dias sem refrigeracao"},
   {2,"Covishield", "Oxford-astraZeneca", "Vetor viral-virus geneticamente modificado", 2, "62% a 90%", "2 a 8C"},
   {3,"mRNA-1273", "Sputnik", "RNA - parte do codigo genetico do virus", 2, "95%", "-20C ate 6 meses"},
   {4,"mRNA BNT162b2", "Pfizer-BioNTech", "RNA", 2, "95%", "-70C"},
   {5,"Sputnik", "Gmaleya", "Vetor viral- virus geneticamente modificado", 2, "92%", "Temperatura normal de refrigerador"},
	};

	DAT = fopen("VACINAS.dat", "w");
	if ( DAT!=NULL) {
		fwrite (&reg, sizeof (reg), 1, DAT);
    fclose(DAT);
	} else {
		printf ("\nERRO AO ABRIR O ARQUIVO VACINA.DAT");
    getch();
	}
	printf("\nArquivo VACINAS.DAT gerado!");
	
	cadastraLoteDefault();
	getch();
}

void acondicionaFrascos() {
	system("SuportesPilha.exe");
}

/* Corpo do programa */
int main()
{
	int resp;
	setlocale (LC_ALL, "");

	do {
		system ("cls"); system ("color D0"); system ("mode 70,15");
		printf("\n\t\t\tCADASTRO DE VACINAS/LOTES");
		printf("\n\n ---------------------------------------------------------------------");
		printf("\n\t\t1. Cadastro default");
		printf("\n\t\t2. Cadastra vacinas");
		printf("\n\t\t3. Consulta vacinas");
		printf("\n\t\t4. Cadastro lotes");
		printf("\n\t\t5. Consulta lotes");
		printf("\n\t\t6. Adicionar frascos no suporte"); // IGOR: ADICIONEI ESTA LINHA E MODIFIQUEI O SWITCH CASE PARA ENCERRAR NO 0, N MEXI NAS FUNCOES
		printf("\n\t\t0. ENCERRAR");
		printf("\n\n\t\t Opção desejada: ");
		scanf("%i", &resp);

		switch(resp) {
			case 1: cadastraDefault(); break;
			case 2: cadastraVacina(); break;
			case 3: consultaVacina(); break;
			case 4: cadastraLote(); break;
			case 5: consultaLote(); break;
			case 6: acondicionaFrascos(); break;
			case 0: resp = 0;
		}

	} while(resp != 0);

	return (0);
}
