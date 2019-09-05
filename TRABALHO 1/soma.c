#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "soma.h"
/*------------------------------------------------------FUNÇÃO PRINCIPAL------------------------------------------------------*/
int main (int argc, char *argv[]){
	lista *L1 = (lista *) malloc (sizeof (lista));	//PONTEIRO QUE VAI APONTAR PARA UMA REGIÃO DA MEMÓRIA QUE CONTÉM AS LISTAS
	lista *L2 = (lista *) malloc (sizeof (lista));
	lista *Lsoma = (lista *) malloc (sizeof (lista));
	char nome_arquivo[] = "ResultadoSom.txt";
	short verificador, digito = 0, *PONTdigito;
	noh *auxiliar, *auxiliar_1d, *auxiliar_2d;

	if (argv[1] == NULL){
		printf("ERRO! o formato correto para o funcionamento desde programa é: ./nome_do_programa dados_dos_pokemons.txt mapa.txt \n");
		exit (0);
	}

	inicializar_LISTA (L1);
	inicializar_LISTA (L2);
	inicializar_LISTA (Lsoma);
	
	verificador = colocar_elementos_lista (L1, L2, argv[1]);
	
	if (verificador) {
		insercao_de_zeros (L1, L2);
		
		PONTdigito = &digito;
		auxiliar = L1->cauda;
		while (auxiliar != NULL){
			executar_soma (L1, L2, Lsoma, PONTdigito);
			
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
			
			auxiliar = L1->cauda;
		}
		if (digito) //ÚLTIMO CASO EM QUE O VAI_UM SEJA DIFERENTE DE 0
			inserir_na_cabeca (Lsoma, '1');

		colocar_resultado_arquivo (Lsoma, nome_arquivo);
		//imprimirLISTA (Lsubtracao);
		
		desalocagem (Lsoma);
		Lsoma = NULL;

		return 0;
	} else {
		printf("ARQUIVO NO FORMATO INCORRETO! VERIFIQUE OS DADOS CONTIDOS NO ARQUIVO E TENTE NOVAMENTE. \n");
		return 0;
	}
}



/*---------------------------------------------------------FUNÇÕES------------------------------------------------------------*/
void executar_soma (lista *L1, lista *L2, lista *Lsoma, short *PONTdigito){
	noh *aux_L1, *aux_L2;
	short numero_1, numero_2, numero_soma, numero_resto, vai_um;
	char ch, numero_1ch, numero_2ch;
	
	vai_um = *PONTdigito; //recebe o conteúdo de vai_um
	aux_L1 = L1->cauda;
	aux_L2 = L2->cauda;


	numero_1ch = aux_L1->conteudo;
	numero_2ch = aux_L2->conteudo;
		
	numero_1 = (int)numero_1ch - 48;//CONVERTE CHAR PARA INTEIRO
	numero_2 = (int)numero_2ch - 48;//CONVERTE CHAR PARA INTEIRO
	numero_soma = numero_1 + numero_2 + vai_um;
		
	numero_resto = numero_soma % 10;
	ch = (char)numero_resto + 48; //CONVERTE INTEIRO PARA CHAR
	inserir_na_cabeca (Lsoma, ch);
		

	vai_um = numero_soma / 10;
	*PONTdigito = vai_um;
}





