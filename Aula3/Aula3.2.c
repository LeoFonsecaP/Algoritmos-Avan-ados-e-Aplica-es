/* Feito por Leonardo Fonseca Pinheiro
 * para aula de Algoritmos avancados no
 * segundo semestre de 2020 no ICMC da USP */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função recursiva que faz a verificação dos pixels na ordem cima, direita, baixo, esquerda.
 * Recebe como parâmetros a matriz auxiliar, uma matriz com as regioes, a dimensao da matriz,
 * a posição de verificação e o endereco da variavel para o total de caminhos diferentes. */

void check(int** matriz, int** caminho, int N, int x, int y, int* total){

	//Verifica se esta no ponto final
	if(x == N-1 && y == N-1){
		*total = *total + 1;
	}
	else{
		//definição das variáveis cima, baixo, esquerda e direita para facilitar o uso posterior
		int cima = x-1;
		int baixo =x+1;
		int direita = y+1;
		int esquerda = y-1;

		matriz[x][y] = 1;//coloca o pixel inicial como parte da região

		if(cima >= 0){//evita que a verificação seja feita em uma região fora da matriz
			if(caminho[cima][y] == 0 && matriz[cima][y] == 0){//verifica se o pixel esta disponivel
				check(matriz, caminho, N, cima, y, total);
				matriz[cima][y] = 0;
			}
		}
		if(direita < N){
			if(matriz[x][direita] == 0 && caminho[x][direita] == 0){
				check(matriz, caminho, N, x, direita, total);
				matriz[x][direita] = 0;
			}
		}
		if(baixo < N){//evita que a verificação seja feita em uma região fora da matriz
		if(matriz[baixo][y] == 0 && caminho[baixo][y] == 0){
				check(matriz, caminho, N, baixo, y, total);
				matriz[baixo][y] = 0;
			}
		}
		//evita que a verificação seja feita em uma região fora da matriz
		if(esquerda>= 0){
			if(matriz[x][esquerda] == 0 && caminho[x][esquerda] == 0){
				check(matriz, caminho, N, x, esquerda, total);
				matriz[x][esquerda] = 0;
			}
		}
	}
}
int main(void){

    int n; //Tamanho da matriz quadrada
	int total = 0;
    scanf("%d", &n);

    //aloca a matriz que recebe os valores da imagem
    int** caminho = malloc(n * sizeof(int*));
	int** matriz = malloc(n * sizeof(int*)); //Evita que fique indo e voltando nas mesmas regioes
    for(int i = 0; i<n; i++){
        caminho[i] = malloc(n * sizeof(int));
		matriz[i] = malloc(n * sizeof(int));

    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &caminho[i][j]);//coloca os valores na matriz
			matriz[i][j] = 0; //Zera a matriz auxiliar
        }
    }

    check(matriz, caminho, n, 0, 0, &total);

	printf("%d", total);

    for(int i = 0; i<n; i++){
        free(matriz[i]);
    }
    free(matriz);    
    return 0;
}
