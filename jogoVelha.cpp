/*
	Representação de bola: 30
	Representação de X: 1
*/

#include <iostream>

using namespace std;

const int sizeTab = 3;
const int contGanhaBola = 30, contGanhaX = 3;
const int ganhaBola = 1, ganhaX = 2;
const int bola = 1, xis = 2;

int tab[sizeTab][sizeTab] = {{1, 1, 10},
														 {10, 1, 1},
														 {10, 10, 1}};

/*
	Verifica se nao existem mais casas para jogar
*/
bool impossivel() {
	int cont;
	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (tab[i][j]) cont++;
		}
	}
	return cont == sizeTab*sizeTab ? true : false;
}


/*
	Verifica se existe algumm ganhador, caso nao exista retorna 0
*/
int verificaGanhador() {
	// verifica linhas e colunas
	for (int i = 0; i < sizeTab; i++) {
		int contLinha = 0, contColuna;
		for (int j = 0; j < sizeTab; j++) {
			contLinha += tab[i][j];
			contColuna += tab[j][i];
		}
		if (contLinha == contGanhaBola || contColuna == contGanhaBola) return ganhaBola;
		if (contLinha == contGanhaX || contColuna == contGanhaX) return ganhaX;
	}

	// verifica diagonais
	int contPrincipal = 0, contSecundaria = 0;
	for (int i = 0; i < sizeTab; i++) {
		cout << tab[i][sizeTab-i-1] << ' ';
		contPrincipal += tab[i][i];
		contSecundaria += tab[i][sizeTab-i-1];
		cout << contSecundaria << endl;
	}

	if (contPrincipal == contGanhaBola || contSecundaria == contGanhaBola) return ganhaBola;
	if (contPrincipal == contGanhaX || contSecundaria == contGanhaX) return ganhaX;

	return 0;
}

void constroiTree(int v[sizeT][], int jogador) {
	int estado = verificaGanhador();
	if (estado == ganhaBola) return 1;
	if (estado == ganhaX) return -1;
	if (impossivelJogar()) return 0;

	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (!tab[i][j]) {
				
			}
		}
	}

}

int main () {
	
	

	return 0;
}
