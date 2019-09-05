#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void inicializar_LISTA (lista *L) {
	L->tamanho = 0;
	L->cabeca = NULL;
	L->cauda = NULL;
}



noh * CriaNoh (char x) { 
	noh *novo = (noh *) malloc (sizeof(noh));
	if (novo == NULL){
		printf("NÃO FOI POSSÍVEL ALOCAR O NOVO NÓ! ERRO NA FUNÇÃO CriaNoh OU ESPAÇO INSIFICIENTE.\n");
		exit (0);
	}
	novo->anterior = NULL;
	novo->proximo = NULL;
	novo->conteudo = x;
	return (novo); //retorna o ponteiro para o novo nó
}



void inserir_na_cauda (lista *L, char elem){
	noh *novo = CriaNoh (elem);
	if (L->cabeca == NULL) {
		L->cabeca = novo;
		L->cauda = novo;
	} else {
		L->cauda->proximo = novo;
		novo->anterior = L->cauda;
		L->cauda = novo;
	}
	L->tamanho ++;
}



void inserir_na_cabeca (lista *L, char elem){
	noh *novo = CriaNoh (elem);
		novo->proximo = L->cabeca;
		if (L->cabeca != NULL){
			L->cabeca->anterior = novo;
		}
		else 
			L->cauda = novo;
		L->cabeca = novo;

		L->tamanho ++;
}



short colocar_elementos_lista (lista *L1, lista *L2, char *nome) {
	short controle = 0, contador = 0, cont;
	char ch;
	char caracteres[12] = "-0123456789 "; //usado para verificar os dígitos que irão entrar

	FILE *file; //ponteiro para o tipo arquivo
	file = fopen (nome, "r"); //essa função retorna um PONTEIRO para o ponteiro file

	ch = fgetc(file);
	if (ch == EOF)//1º CASO: arquivo em branco
		return 0;


	while (ch != EOF){
		for (cont = 0; cont < 12; cont++){ //4º CASO - entrada com algum caractere fora do padrão
			if (ch != caracteres[cont])
				contador ++;
		}
		if (contador == 12)
			return 0;
		else {
			contador = 0;
			if (ch == ' ')
				controle ++;
			if (controle == 0){
				if (ch != '-')
				inserir_na_cauda (L1, ch);
			} else if (controle == 1) {
				if (ch != ' ')//IGNORA O ESPAÇO LOGO DEPOIS DO PRIMEIRO NÚMERO
					if (ch != '-')
					inserir_na_cauda (L2, ch);
			} else if (controle > 1)//3º CASO: mais que dois números
				return 0;

		}

	ch = fgetc(file);
	}
	
	if (L2->cabeca == NULL)// 2º CASO: apenas um número
		return 0;

	fclose (file);
	return 1;
}




void insercao_de_zeros (lista *L1, lista *L2){
	unsigned long long diferenca, contador;
	
	if (L1->tamanho > L2->tamanho){
		diferenca = L1->tamanho - L2->tamanho;
		for (contador = 0; contador < diferenca; contador ++)
			inserir_na_cabeca (L2, '0');
	} else {
		diferenca = L2->tamanho - L1->tamanho;
		for (contador = 0; contador < diferenca; contador ++)
			inserir_na_cabeca (L1, '0');
	}
}



void colocar_resultado_arquivo (lista *Lgenerica, char nome_arquivo[]){ //ARRUMAR
	FILE *file;
	noh *aux_impressao;
	char ch;
	short controle = 1;

	aux_impressao = Lgenerica->cabeca;

	file = fopen (nome_arquivo, "a");
	if (file == NULL){
		printf("NÃO FOI POSSÍVEL ABRIR/CRIAR O ARQUIVO! TENTE NOVAMENTE. (ERRO NA FUNÇÃO colocar_resultado_arquivo");
		exit(0);
	}
	
	if (aux_impressao->conteudo == '-'){ // CASO: -000009
		fputc ('-', file);
		aux_impressao = aux_impressao->proximo;
	}
	
	if (aux_impressao->conteudo == '0'){ //CASO: 000008
		if (aux_impressao->proximo == NULL)
			fputc ('0', file);
		controle = 0;
	}
	while (aux_impressao != NULL){
		ch = aux_impressao->conteudo;
		
		if (ch != '0')
			controle = 1;
		
		if (controle == 1)
			fputc(ch, file);
		
		aux_impressao = aux_impressao->proximo;
	}

	fclose (file);
}



void desalocagem (lista *Lgenerica){
	noh *aux1, *aux2;
	aux1 = Lgenerica->cabeca;
	while (aux1 != NULL){
		aux2 = aux1;
		aux1 = aux1->proximo;
		free (aux2);
		aux2 = NULL;
	}
	free (aux1);
	aux1 = NULL;
}



void imprimirLISTA (lista *L){
	noh *aux;
	if (L == NULL){
		printf ("NÃO FOI POSSÍVEL IMPRIMIR A LISTA POIS ELA SE ENCONTRA VAZIA.");
	} else {
		aux = L->cabeca;
		do {
			printf ("%c --> ", aux->conteudo);
			aux = aux->proximo;
		} while (aux != NULL);
	}
	printf("\n");
}
