#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "multiplica.h"
/*------------------------------------------------------FUNÇÃO PRINCIPAL------------------------------------------------------*/
int main (int argc, char *argv[]){
	lista *L1 = (lista *) malloc (sizeof (lista));	//PONTEIRO QUE VAI APONTAR PARA UMA REGIÃO DA MEMÓRIA QUE CONTÉM AS LISTAS
	lista *L2 = (lista *) malloc (sizeof (lista));
	lista *Lmultiplicacao = (lista *) malloc (sizeof (lista));
	char nome_arquivo[] = "ResultadoMult.txt";
	short verificador, negativo;

	if (argv[1] == NULL){
		printf("ERRO! o formato correto para o funcionamento desde programa é: ./nome_do_programa nome_do_arquivo_de_teste.txt \n");
		exit (0);
	}

	inicializar_LISTA (L1);
	inicializar_LISTA (L2);
	inicializar_LISTA (Lmultiplicacao);
	
	verificador = colocar_elementos_lista (L1, L2, argv[1]);
	
	if (verificador) {
		
		executar_multiplicacao (L1, L2, Lmultiplicacao);

		if (Lmultiplicacao->cabeca->conteudo == '0'){ //consertar falha na formatação de saída do arquivo no caso 0 x 0
			if (Lmultiplicacao->cabeca->proximo->conteudo == '0')
				Lmultiplicacao->cabeca = Lmultiplicacao->cabeca->proximo;
		} 
		
		//verificar se algum dos números é negativo
		negativo = verifica_negativo (argv[1]);
		if (negativo == 1){
			inserir_na_cabeca (Lmultiplicacao, '-');
		}

		colocar_resultado_arquivo (Lmultiplicacao, nome_arquivo);
		//imprimirLISTA (Lmultiplicacao);
		

		//DESALOCAGEM FEITA NO FINAL
		desalocagem (L1);
		L1 = NULL;

		desalocagem (L2);
		L2 = NULL;

		desalocagem (Lmultiplicacao);
		Lmultiplicacao = NULL;
		//FIM DESALOCAGEM

		return 0;
	} else {
		printf("ARQUIVO NO FORMATO INCORRETO! VERIFIQUE OS DADOS CONTIDOS NO ARQUIVO E TENTE NOVAMENTE. \n");
		return 0;
	}

}

/*---------------------------------------------------------FUNÇÕES------------------------------------------------------------*/
void executar_multiplicacao (lista *L1, lista *L2, lista *Lmultiplicacao){
	if (L1->tamanho >= L2->tamanho)
		executar_multiplicacao_convencional (L1, L2, Lmultiplicacao); 
	else if (L1->tamanho < L2->tamanho){
		executar_multiplicacao_convencional (L2, L1, Lmultiplicacao); 
	} 
}

void executar_multiplicacao_convencional (lista *L1, lista *L2, lista *Lmultiplicacao) {
	noh *aux_L1, *aux_L2, *marca_segundo, *marcador, *auxiliar_marcador;
	short numero_1, numero_2, numero_resto, numero_auxiliar, colocar_proximo, multiplicacao, soma, vai_um, somatorio, vai_um_externo;
	char ch, numero_1ch, numero_2ch, numero_auxiliarCH;

	insercao_de_zeros (L1, L2);
	
	marca_segundo = L2->cauda;
	

	inserir_na_cabeca (Lmultiplicacao, '0');

	marcador = Lmultiplicacao->cauda; //MARCA A Lmultiplicacao
	
	while (marca_segundo != NULL){
		aux_L1 = L1->cauda;
		auxiliar_marcador = marcador;
		aux_L2 = marca_segundo;
		vai_um = 0;
		vai_um_externo = 0;
		while (aux_L1 != NULL){
			numero_1ch = aux_L1->conteudo;
			numero_2ch = aux_L2->conteudo;

			numero_1 = (int)numero_1ch - 48; //CONVERTE CHAR PARA INTEIRO
			numero_2 = (int)numero_2ch - 48; 
			numero_auxiliarCH = auxiliar_marcador->conteudo; //o que já estava na lista
			numero_auxiliar = (int)numero_auxiliarCH - 48;

			multiplicacao = (numero_1 * numero_2);
			numero_resto = multiplicacao % 10; //resto
			colocar_proximo = multiplicacao / 10; //o que precisa colocar na próxima casa
			
			soma = numero_resto + numero_auxiliar;
			if (soma > 9){
				soma = soma % 10;
				vai_um = 1;

			} //end if(soma > 9)
			
			ch = (char)soma + 48; //CONVERTE INTEIRO PARA CHAR
			auxiliar_marcador->conteudo = ch;

			colocar_proximo = colocar_proximo + vai_um + vai_um_externo;
			if (vai_um_externo == 1)
				vai_um_externo = 0;
			if (vai_um == 1)
				vai_um = 0;


			if (auxiliar_marcador->anterior == NULL){
				ch = (char)colocar_proximo + 48;
				inserir_na_cabeca (Lmultiplicacao, ch);
			} else {
				numero_1ch = auxiliar_marcador->anterior->conteudo;
				numero_1 = (int)numero_1ch - 48;
				somatorio = numero_1 + colocar_proximo;
				if (somatorio > 9){
					somatorio = somatorio % 10;
					vai_um_externo = 1;
				}

				ch = (char)somatorio + 48;
				auxiliar_marcador->anterior->conteudo = ch;
			}
			

			//imprimirLISTA (Lmultiplicacao);
			aux_L1 = aux_L1->anterior;
			auxiliar_marcador = auxiliar_marcador->anterior;
			} //end while (aux_L1 != NULL)
		marca_segundo = marca_segundo->anterior;
		marcador = marcador->anterior;
		} //end while (marca_segundo != NULL)
}//end final da função

short verifica_negativo (char *nome){
	short conta_sinais = 0;
	char ch;

	FILE *file; //ponteiro para o tipo arquivo
	file = fopen (nome, "r"); //essa função retorna um PONTEIRO para o ponteiro file

	while (ch != EOF){
		if (ch == '-')
			conta_sinais ++;
		ch = fgetc(file);
	}
	return conta_sinais;
}