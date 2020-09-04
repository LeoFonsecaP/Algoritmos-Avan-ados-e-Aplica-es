/* Feito por Leonardo Fonseca Pinheiro
 * para aula de Algoritmos avancados no
 * segundo semestre de 2020 no ICMC da USP */

#include <stdio.h>
#include <stdlib.h>

/* Funcao que preenche a matriz de opcoes
 * Recebe o numero de pessoas
 * Retorna a matriz */
int** preenche(int n){
	int** matriz = (int**) malloc(n * sizeof(int*));
	for(int i = 0; i < n; i++){
		matriz[i] = (int*) malloc(n * sizeof(int));
	}
	int pos;
	for(int i = 0; i < n; i++){
		scanf("%d", &pos);
		for(int j = 0; j < n; j++){
			scanf("%d", &matriz[pos-1][j]); //Recebe a lista de prioridades
		}
	}
	return matriz;
}
/* Funcao que verifica se alguem ainda esta solteiro
 * Recebe o vetor de casados e o numero de pessoas
 * Retorna 1 se tem alguem solteiro e 0 caso contrario */
int alguem_solteiro(int* c, int n){
	//Percorre o vetor inverso pra aumentar a chance dele ser eficiente
	for(int i = n-1; i >= 0; i--){
		if(c[i] == 0){
			return 1;
		}
	}
	return 0;
}

/* Funcao que descobre a posicao de um homem na lista de preferencia da mulher
 * Recebe a matriz de preferencia das mulheres, a mulher e o homem
 * Retorna a posicao */
int descobrir_posicao(int** matriz, int mulher, int homem){
	int pos = 0;
	while(matriz[mulher][pos] != homem){
		pos++;
	}
	return pos;
}

/* Funcao que gera os casamentos
 * Recebe o numero de pessoas e as matrizes de preferencia
 * Retorna uma matriz dos casais */
int* casa(int** h, int** m, int n){

	int* casados = (int*) calloc(n, sizeof(int));
	int* casadas = (int*) calloc(n, sizeof(int));
	int* casais = (int*) calloc(n, sizeof(int));

	int aux = 0; //Para buscar uma mulher pro homem
	int mulher; //Variavel que recebe a mulher que vai receber o pedido

	//Loop ate nao ter solteiros
	while(alguem_solteiro(casados, n) == 1){
		for(int i = 0; i < n; i++){
			if(casados[i] == 0){ //Se for solteiro
				while(casados[i] == 0){ //Ate casar
					mulher = h[i][aux] - 1; //-1 para ajustar no vetor
					if(casadas[mulher] == 0){ //Se a mulher for solteira
						casadas[mulher] = i+1; //+1 para ajustar ao homem
						casados[i] = 1;
						casais[i] = mulher + 1; //+1 para ajustar ao mulher
						aux = 0;
					}
					//Se for casada verifica se vai trocar o marido
					else if(descobrir_posicao(m, mulher, i+1) < descobrir_posicao(m, mulher, casadas[mulher])){
						casados[casadas[mulher]] = 0; //Deixa o ex solteiro
						casadas[mulher] = i+1;
						casados[i] = 1;
						casais[i] = mulher + 1;
						aux = 0;
					}
					else{
						aux++;
					}
				}
			}
		}
	}
	return casais;
}


int main(void){
	int testes; //Quantidade de testes que serão feitos
	scanf("%d", &testes);
	int n; //Numero de casamentos
	int** homens; //Prioridade dos homens
	int** mulheres; //Priopriedade das mulheres
	int* casais; //Vetor com os casais
	for(int i = 0; i < testes; i++){
		scanf("%d", &n);
		mulheres = preenche(n);
		homens = preenche(n);
		casais = casa(homens, mulheres, n);
		for(int j = 0; j < n; j++){
			printf("%d %d\n", j+1, casais[j]);
		}
	}
}