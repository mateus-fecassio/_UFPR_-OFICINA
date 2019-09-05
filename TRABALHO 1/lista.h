#ifndef __LISTA__
#define __LISTA__

typedef struct noh { //contém os nós em particular
	char conteudo;
	struct noh *proximo;
	struct noh *anterior;
} noh;

typedef struct lista { //contém o CONJUNTO de nós
	unsigned long long tamanho;
	struct noh *cabeca;
	struct noh *cauda;
} lista;



void inicializar_LISTA (lista *L); 														
void inserir_na_cauda (lista *L, char elem); 
void inserir_na_cabeca (lista *L, char elem);		
short colocar_elementos_lista (lista *L1, lista *L2, char *nome);
void insercao_de_zeros (lista *L1, lista *L2); 
void colocar_resultado_arquivo (lista *Lgenerica, char nome_arquivo[]);
void desalocagem (lista *Lgenerica);
noh * CriaNoh (char x);
void imprimirLISTA (lista *L);

#endif