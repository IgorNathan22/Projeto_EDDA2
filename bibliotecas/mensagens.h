void msg_erro_alocacao (void) {
	system ("cls"); system ("color 04"); system ("mode 70,3");
	printf("\n\t\tMalloc devolveu NULL!");
	getch();
	exit(1);
}

void msg_arq_inexistente (void) {
	system ("cls"); system ("color 04"); system ("mode 70,3");
	printf("\n\t\tARQUIVO MEDICOSCREMESP.DAT INEXISTENTE!");
	getch();
	exit(1);
}

void msg_erro_login (void) {
	system ("cls"); system ("color 40"); system ("mode 70,5");
	printf("\n\n\t\tERRO: M�DICO E/OU CRM INV�LIDO!");
	getch();
	exit(1);
}

void msg_olhas_vazias (void) {
	system ("cls"); system ("color 40"); system ("mode 70,3");
	printf("\n\t\tATEN��O! N�O H� VACINAS DISPON�VEIS!");
	getch();
}

void msg_usu_inativo (void) {
	system ("cls"); system ("color 40"); system ("mode 70,3");
	printf("\n\t\tUSU�RIO INATIVO!");
	getch();
	exit(1);
}


