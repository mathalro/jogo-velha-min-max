/*
	Representação de bola: 30
	Representação de X: 1
*/

#include <iostream>
#include <cstring>

using namespace std;

const int sizeTab = 3;
const int contGanhaBola = 30, contGanhaX = 3;
const int ganhaBola = 1, ganhaX = 2;
const int bola = 10, xis = 1;

int tab[sizeTab][sizeTab] = {{1, 1, 10},
														 {10, 1, 1},
														 {10, 10, 1}};

/*
	Verifica se nao existem mais casas para jogar
*/
bool impossivelJogar() {
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
		contPrincipal += tab[i][i];
		contSecundaria += tab[i][sizeTab-i-1];
	}
	if (contPrincipal == contGanhaBola || contSecundaria == contGanhaBola) return ganhaBola;
	if (contPrincipal == contGanhaX || contSecundaria == contGanhaX) return ganhaX;

	return 0;
}

int trocaJogador(int jogador) {
	if (jogador == xis) return bola;
	return xis;
}

void print() {
	puts("");
	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (tab[i][j] == bola) {
				printf("o ");
			} else {
				printf("x ");
			}
		}puts("");
	}
}

int constroiTree(int jogador) {
	
	print();	
	
	int estado = verificaGanhador();
	if (estado == ganhaBola) {
		cout << "O ganhou!!" << endl;
		return 1;
	}
	if (estado == ganhaX) {
		cout << "X ganhou!!" << endl;
		return -1;
	}
	if (impossivelJogar()) return 0;

	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (!tab[i][j]) {
				tab[i][j] = jogador;
				constroiTree(trocaJogador(jogador));
				tab[i][j] = 0;
			}
		}
	}
}

int main () {
	

	memset(tab, 0, sizeof tab);
	constroiTree(xis);

	return 0;
}
