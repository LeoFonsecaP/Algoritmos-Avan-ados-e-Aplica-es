/* Feito por Leonardo Fonseca Pinheiro
 * para aula de Algoritmos avancados no
 * segundo semestre de 2020 no ICMC da USP */

#include <stdio.h>
#include <stdlib.h>


 int main(void){
	 int testes;
	 int moedas;
	 int cont;
	 int vetor[100];
	 int soma;

	 scanf("%d", &testes);

	 for(int i = 0; i<testes; i++){
		 scanf("%d", &moedas);
		 for(int j = 0; j<moedas; j++){
			 scanf("%d", &vetor[j]);
		 }
		 cont = 1;
		 soma = vetor[0];
		 for(int j = 1; j<moedas-1; j++){
			 if(soma + vetor[j] < vetor[j+1]){
				 soma += vetor[j];
				 cont++;
			 }
		 }
		 cont++;
		 printf("%d\n", cont);
	 }
 }