/* Feito por Leonardo Fonseca Pinheiro
 * para aula de Algoritmos avancados no
 * segundo semestre de 2020 no ICMC da USP */

#include <stdio.h>
#include <stdlib.h>

/* Funcao auxiliar que verifica se um numero n
 * esta contido no vetor vet de tamanho tam. 
 * Retorna 1 se esta e 0 se nao. */

int novet(int* vet, int n, int tam){
	for(int i = 0; i < tam; i++){
		if(vet[i] == n){
			return 1;
		}
	}
	return 0;
}

/* Funcao que executa a recursao.
 * Recebe como parametros o vetor com as duracoes, o tempo limite,
 * um vetor com o melhor caminho, o endereco da melhor soma, o numero 
 * de musicas, o endereco para quantidade de musicas no melhor caminho,
 * um endereco para soma atual e a posicao atual.
 * Tem retorno void */

void recursao(int* tempo, int limite, int* melhor_caminho, int* melhor_soma, 
			  int n, int* qtd, int* soma_atual, int atual, int* caminho_atual, int* posicao){
	
	*soma_atual += tempo[atual];
	caminho_atual[*posicao] = atual;
	*posicao = *posicao + 1;

	//Caso o caminho atual tenha soma melhor que a melhor soma, vira o melhor caminho
	if(*soma_atual > *melhor_soma){
		*melhor_soma = *soma_atual;
		for(int i = 0; i < *posicao; i++){
			melhor_caminho[i] = caminho_atual[i];
		}
		*qtd = *posicao;
	}


	for(int i = 0; i < n; i++){
		//Verifica se o elemento pode ser inserido, verificando seu tempo, se nao eh ele mesmo e se ele ja se encontra no vetor
		if(*soma_atual + tempo[i] <= limite && i != atual && (novet(caminho_atual, i, *qtd) == 0)){ 
			recursao(tempo, limite, melhor_caminho, melhor_soma, n, qtd, soma_atual, i, caminho_atual, posicao);
		}
	}
}

/* Funcao que inicia a recursao.
 * Recebe como parametros o vetor com as duracoes, o tempo 
 * limite, um vetor com o melhor caminho, o numero de musicas 
 * e o endereco para quantidade de musicas no melhor caminho.
 * Tem como retorno a melhor soma */

int comando(int* tempo, int limite, int* melhor_caminho, int n, int* qtd){

	int melhor_soma = 0;
	int soma_atual = 0;
	int caminho_atual[100];
	int posicao;

	for(int i = 0; i < n; i++){
		soma_atual = 0;
		posicao = 0;
		for(int j = 0; j < *qtd; j++){
			caminho_atual[j] = -1;
		}
		recursao(tempo, limite, melhor_caminho, &melhor_soma, n, qtd, &soma_atual, i, caminho_atual, &posicao);

	}

	return melhor_soma;
}

/* Funcao auxiliar para concertar a ordem de impressao,
 * que estava incorreta para alguns casos.
 * Ordena o vetor vet de tamanho tam e tem retorno void */

void ordenavet(int* vet, int tam){
	int aux;
	for(int i = 0; i < tam; i++){
		for(int j = i+1; j < tam; j++){
			if(vet[i] > vet[j]){
				aux = vet[i];
				vet[i] = vet[j];
				vet[j] = aux;
			}
		}
	}
}

int main(void){
	int n;
	int tempo[100];
	int limite;
	int qtd = 0;
	int melhor_caminho[100];
	int total;

	while(scanf("%d", &limite) != -1){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%d", &tempo[i]);
		}
		total = comando(tempo, limite, melhor_caminho, n, &qtd);
		ordenavet(melhor_caminho, qtd);

		for(int i = 0; i < qtd; i++){
			printf("%d ", tempo[melhor_caminho[i]]);
		}
		printf("sum:%d\n", total);
	}

	return 0;
}