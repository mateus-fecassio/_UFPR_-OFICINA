#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "subtrai.h"
/*------------------------------------------------------FUNÇÃO PRINCIPAL------------------------------------------------------*/
int main (int argc, char *argv[]){
	lista *L1 = (lista *) malloc (sizeof (lista));	//PONTEIRO QUE VAI APONTAR PARA UMA REGIÃO DA MEMÓRIA QUE CONTÉM AS LISTAS
	lista *L2 = (lista *) malloc (sizeof (lista));
	lista *Lsubtracao = (lista *) malloc (sizeof (lista));
	char nome_arquivo[] = "ResultadoSub.txt";
	short verificador;

	if (argv[1] == NULL){
		printf("ERRO! o formato correto para o funcionamento desde programa é: ./nome_do_programa nome_do_arquivo_de_teste.txt \n");
		exit (0);
	}

	inicializar_LISTA (L1);
	inicializar_LISTA (L2);
	inicializar_LISTA (Lsubtracao);
	
	verificador = colocar_elementos_lista (L1, L2, argv[1]);
	
	if (verificador) {
		
		executar_subtracao (L1, L2, Lsubtracao); //DESALOCAGEM FEITA DENTRO DA FUNÇÃO!

		colocar_resultado_arquivo (Lsubtracao, nome_arquivo);
		//imprimirLISTA (Lsubtracao);
		
		desalocagem (Lsubtracao);
		Lsubtracao = NULL;
		
		return 0;
	} else {
		printf("ARQUIVO NO FORMATO INCORRETO! VERIFIQUE OS DADOS CONTIDOS NO ARQUIVO E TENTE NOVAMENTE. \n");
		return 0;
	}

}



/*---------------------------------------------------------FUNÇÕES------------------------------------------------------------*/
void executar_subtracao (lista *L1, lista *L2, lista *Lsubtracao){
	short verificador = -1;
	noh *auxiliar_V1, *auxiliar_V2;

	if (L1->tamanho > L2->tamanho)
		executar_subtracao_convencional (L1, L2, Lsubtracao); //exemplo: 234 - 29
	else if (L1->tamanho < L2->tamanho){
		executar_subtracao_convencional (L2, L1, Lsubtracao); //exemplo: 1 - 300
		inserir_na_cabeca (Lsubtracao, '-');
	} else if (L1->tamanho == L2->tamanho){

		if (L1->cabeca->conteudo > L2->cabeca->conteudo)
			executar_subtracao_convencional (L1, L2, Lsubtracao); //exemplo: 25 - 12
		else if (L1->cabeca->conteudo < L2->cabeca->conteudo){
			executar_subtracao_convencional (L2, L1, Lsubtracao); //exemplo: 11 - 30
			inserir_na_cabeca (Lsubtracao, '-');
		
		} else if (L1->cabeca->conteudo == L2->cabeca->conteudo){ //CASO DO PRIMEIRO DÍGITO SER IGUAL AO SEGUNDO
			auxiliar_V1 = L1->cabeca;
			auxiliar_V2 = L2->cabeca;

			while (verificador == -1){ // PROCURA OS DÍGITOS SUBSEQUENTES
					if (auxiliar_V1 != NULL) {
						if (auxiliar_V1->conteudo > auxiliar_V2->conteudo)
							verificador = 1; //CASO 2: ALGUM DÍGITO SUBSEQUENTE É MAIOR QUE O SEGUNDO
						else if (auxiliar_V1->conteudo < auxiliar_V2->conteudo)
							verificador = 2; //CASO 3: ALGUM DÍGITO SUBSEQUENTE É MENOR QUE O SEGUNDO
					} else if (auxiliar_V1 == NULL)
						verificador = 0; //CASO 1: TODOS OS NÚMEROS SÃO IGUAIS

				if (auxiliar_V1 != NULL){
					auxiliar_V1 = auxiliar_V1->proximo;
					auxiliar_V2 = auxiliar_V2->proximo;
				}
				}
			if  (verificador == 0){  //TODOS OS NÚMEROS IGUAIS
				inserir_na_cabeca (Lsubtracao, '0');
			} 
			if  (verificador == 1){
				executar_subtracao_convencional (L1, L2, Lsubtracao); //exemplo: 3074 - 3025
			}
			if  (verificador == 2){
				executar_subtracao_convencional (L2, L1, Lsubtracao); //exemplo: 3074 - 3132
				inserir_na_cabeca (Lsubtracao, '-');
			}
		}
	}
}


void executar_subtracao_convencional (lista *L1, lista *L2, lista *Lsubtracao){ 
	noh *aux_L1, *aux_L2, *auxiliar_1d, *auxiliar_2d;
	short numero_1, numero_2, numero_resto;
	char ch, numero_1ch, numero_2ch;

	insercao_de_zeros (L1, L2);
	
	aux_L1 = L1->cauda;
	aux_L2 = L2->cauda;
	
	while (aux_L1 != NULL){
		numero_1ch = aux_L1->conteudo;
		numero_2ch = aux_L2->conteudo;
			
		numero_1 = (int)numero_1ch - 48;//CONVERTE CHAR PARA INTEIRO
		numero_2 = (int)numero_2ch - 48;
		
		if (numero_1 >= numero_2){
			numero_resto = numero_1 - numero_2;

			ch = (char)numero_resto + 48; //CONVERTE INTEIRO PARA CHAR
			inserir_na_cabeca (Lsubtracao, ch);
		} else if (numero_1 < numero_2 && aux_L1->anterior != NULL) {
			busca_doador (L1, aux_L1);
			numero_resto = (numero_1 + 10) - numero_2;
			ch = (char)numero_resto + 48; 
			inserir_na_cabeca (Lsubtracao, ch);
		} else if (aux_L1->anterior == NULL){
			numero_resto = (numero_1 - numero_2) * -1;
			ch = (char)numero_resto + 48;
			inserir_na_cabeca (Lsubtracao, ch);
			inserir_na_cabeca (Lsubtracao, '-');
		}
		aux_L1 = aux_L1->anterior;
		aux_L2 = aux_L2->anterior;


		//DESALOCAGEM GRADUAL DENTRO DO LAÇO
		auxiliar_1d = L1->cauda;
		auxiliar_2d = L2->cauda;


		L1->cauda = L1->cauda->anterior;
		L2->cauda = L2->cauda->anterior;

			
			free (auxiliar_1d);
			auxiliar_1d = NULL;
			if (L1->cauda == NULL){
				L1->cabeca = NULL;
			} else
				L1->cauda->proximo = NULL;

			free (auxiliar_2d);
			auxiliar_2d = NULL;
			if (L2->cauda == NULL){
				L2->cabeca = NULL;
			} else
				L2->cauda->proximo = NULL;
		//FIM DESALOCAGEM
	}

}



void busca_doador (lista *L, noh *aux_L){
	noh *aux_B1;
	short confirmador = 0;
	long long int contador, conta_zeros = 0;


	aux_B1 = aux_L->anterior;

	while (confirmador != 1){
		if (aux_B1->conteudo == '0'){
			conta_zeros ++;
		} else {
			aux_B1->conteudo = aux_B1->conteudo - 1;
			confirmador = 1;
		}
		
		if (confirmador == 0)
			aux_B1 = aux_B1->anterior;
	}
	if (conta_zeros != 0){ //AQUI, COLOCA-SE 9 EM CADA ZERO DO NÚMERO
		for (contador = 0; contador < conta_zeros; contador ++){
			aux_B1 = aux_B1->proximo;
			aux_B1->conteudo = '9';
		}
	}
	//no final, aux_B1 == aux_L1->anterior;
}



