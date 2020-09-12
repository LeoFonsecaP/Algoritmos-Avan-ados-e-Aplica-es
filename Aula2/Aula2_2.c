/* Feito por Leonardo Fonseca Pinheiro
 * para aula de Algoritmos avancados no
 * segundo semestre de 2020 no ICMC da USP */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Funcao para ordenar o vetor de forma crescente
 * Recebe o vetor e o seu tamanho
 * Tem retorno void */

void ordenar(float* m, int tam){
	int aux;
	for(int i = 0; i < tam; i++){
		for(int j = i; j < tam; j++){
			if(m[i] > m[j]){
				aux = m[i];
				m[i] = m[j];
				m[j] = aux;
			}
		}
	}
}


int main(void){
	int camaras, especime;
	float* vetor;
	float soma = 0;
	float media = 0;
	float imb = 0;
	int set = 0;

	while(scanf("%d", &camaras) != -1){
		scanf("%d", &especime);
		vetor = calloc(2 * camaras, sizeof(float));
		soma = 0;
		imb = 0;
		set++;

		for(int i = 0; i<especime; i++){
			scanf("%f", &vetor[i]);
			soma+= vetor[i];
		}
		ordenar(vetor, 2 * camaras);
		media = soma/camaras;

		printf("Set #%d\n", set);
		
		for(int i = 0; i < camaras; i++){
			soma = 0;
			printf(" %d: ", i);
			if(vetor[i] != 0){
				printf("%.0f ",vetor[i]);
			}
			if(vetor[(2 * camaras) - i - 1] != 0){
				printf("%.0f\n", vetor[(2 * camaras) - i - 1]);
			}
			else{
				printf("\n");
			}
			soma = vetor[i] + vetor[(2 * camaras) - i - 1];
			imb += fabs(soma - media);
		}
		printf("IMBALANCE = %.5f\n\n", imb);
	}
}