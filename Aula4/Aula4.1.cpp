/* Feito por Leonardo Fonseca Pinheiro
 * para aula de Algoritmos avancados no
 * segundo semestre de 2020 no ICMC da USP */
#include <math.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

typedef struct {
	int resultados[4];
	int movimentos;
	int dist;
}Roleta;

/* Funcao auxiliar que compara duas roletas */
const auto compara = [](const Roleta &x, const Roleta &y) {
	return x.movimentos + x.dist > y.movimentos + y.dist;
};

/* Verifica se chegou na posicao final */
bool ver_final(int num[], int tabela[10][10][10][10]){
	if(tabela[num[0]][num[1]][num[2]][num[3]] == 1){
		return true;
	}
	return false;
}

/* Verifica se a posicao eh proibida */
bool ver_proibido(int num[], int tabela[10][10][10][10]){
	if(tabela[num[0]][num[1]][num[2]][num[3]] == -1){
		return true;
	}
	return false;
}

/* Configura uma posicao como proibida */
void proibe(int num[], int tabela[10][10][10][10]){
	tabela[num[0]][num[1]][num[2]][num[3]] = -1;
}

/* Funcao que roda a roleta para esquerda. */
void roda_roleta_esq(int* roleta){
	*roleta = (*roleta + 1) % 10;
}

/* Funcao que roda a roleta para direita. */
void roda_roleta_dir(int* roleta){
	if(*roleta == 0){
		*roleta = 9;
	}
	else{
		*roleta = (*roleta - 1);
	}
}

/* Funcao que calcula a distancia */
int distancia(int num[], int final[]){
	int d = 0;
	int x, y, z;
	for(int i = 0; i < 4; i++){
		x = abs(final[i] - num[i]);
		y = 10 - num[i] + final[i];
		z = 10 - final[i] + num[i];
        if (x>=y) {
			x = y;
		}
		if(x<z){
			d += x;
		}
		else{
			d += z;
		}
	}
	return d;
}

/* Funcao que verifica as adjacencias
 * Recebe como parametro a roleta, uma tabela que é 
 * na quarta dimensao e o vetor da posicao final.
 * Retorna um vetor */
vector<Roleta> ver_adj(Roleta* atual, int tabela[10][10][10][10], int* final){
	vector<Roleta> adjacentes;
	Roleta aux;

	for(int i = 0; i < 8; i++){
		memcpy(&aux, atual, sizeof(Roleta));
		if(i % 2 == 0){
			roda_roleta_esq(&aux.resultados[i/2]);
		}
		else{
			roda_roleta_dir(&aux.resultados[i/2]);
		}
		if(!ver_proibido(aux.resultados, tabela)){
			++aux.movimentos;
			aux.dist = distancia(aux.resultados, final);
			adjacentes.push_back(aux);
		}
	}
	return adjacentes;
}

/* Funcao que descobre o caminho ate a posicao final.
 * Recebe como parametro a roleta, uma tabela que é 
 * na quarta dimensao e o vetor da posicao final.
 * Retorno booleano. */
bool descobre_caminho(Roleta* roleta, int tabela[10][10][10][10], int* final){
	priority_queue <Roleta, vector<Roleta>, decltype(compara)> proxima(compara);
	vector<Roleta> adjacentes;

	proxima.push(*roleta);
	while(!proxima.empty()){
		*roleta = proxima.top();
		proxima.pop();
		if(ver_final(roleta->resultados, tabela) == true){
			return true;
		}
		adjacentes = ver_adj(roleta, tabela, final);
		for(int i = 0; i < (int)adjacentes.size(); i++){
			proxima.push(adjacentes[i]);
		}
		proibe(roleta->resultados, tabela);
		adjacentes.clear();
	}
	return false;
}


int main(void){
	int n;
	int proibidos;

    scanf("%d", &n);
	for(int i = 0; i < n; i++){
		Roleta roleta = {.resultados = {0}, .movimentos = 0, .dist = 0};
		int tabela[10][10][10][10] = {{{{0}}}};
		int final[4];
		int aux[4];

		for(int j = 0; j < 4; j++){
			scanf("%d", &roleta.resultados[j]);
		}

		for(int j = 0; j < 4; j++){
			scanf("%d", &final[j]);
		}
		tabela[final[0]][final[1]][final[2]][final[3]] = 1;

		cin >> proibidos;
		for(int j = 0; j < proibidos; j++){
			for(int k = 0; k < 4; k++){
				scanf("%d", &aux[k]);
			}
			tabela[aux[0]][aux[1]][aux[2]][aux[3]] = -1;
		}
		
		if (descobre_caminho(&roleta, tabela, final) == true){
			printf("%d\n", roleta.movimentos);
		}
		else{ 
			printf("-1");
		}
	}
}
