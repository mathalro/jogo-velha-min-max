/*
	Representação de bola: 30
	Representação de X: 1
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
#include <unistd.h>

using namespace std;

struct Estado {
	string tab;
	int jogador, resultado, i, j;
	Estado() {}
	Estado(string tab, int jogador, int resultado, int i, int j) :  tab(tab), jogador(jogador), resultado(resultado), i(i), j(j) {}
	bool operator < (const Estado &outro) const {
		return tab <= outro.tab;
	}
};

const int sizeTab = 3;
const int contGanhaBola = 30, contGanhaX = 3;
const int ganhaBola = 1, ganhaX = 2;
const int bola = 10, xis = 1;

map<pair<string, int>, Estado> utilidade;

int tab[sizeTab][sizeTab];
/*
	Verifica se nao existem mais casas para jogar
*/
bool impossivelJogar() {
	int cont = 0;
	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (tab[i][j]) cont++;
		}
	}
	return cont == sizeTab*sizeTab ? true : false;
}


/*
	Verifica se existe algum ganhador, caso nao exista retorna 0
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

/*
	Muda o jogador da vez
*/
int trocaJogador(int jogador) {
	if (jogador == xis) return bola;
	return xis;
}


string criaEstado(int y = -1, int x = -1, int jogador = 0) {
	// criar a string que representa o nosso tabuleiro
	string resultado;
	// constroi a string atual
  for(int i = 0; i < sizeTab; i++){
	  for(int j = 0; j < sizeTab; j++){
      if(tab[i][j] == xis) resultado += "x";
      else if(tab[i][j] == bola) resultado += "o";
      else resultado += ".";
    }
  }
  if (y != -1) {
    resultado[y*sizeTab+x] = (jogador == xis) ? 'x' : 'o';
	}

	return resultado;
}

/*
	Imprime o tabuleiro atual
*/
void print() {
	puts("");
	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (tab[i][j] == bola) {
				printf("o ");
			} else if (tab[i][j] == xis){
				printf("x ");
			} else {
				printf(". ");
			}
		}puts("");
	}
}


/*
	Gera os estados com uma arvore de recursao
*/
int constroiTree(int jogador) {
	int resultado, iOtimo, jOtimo, estado;
  
	estado = verificaGanhador();
	if (estado == ganhaBola) {
		//cout << "O ganhou!!" << endl;
		return 1;
	}
	if (estado == ganhaX) {
		//cout << "X ganhou!!" << endl;
		return -1;
	}
	if (impossivelJogar()) {
		return 0;
	}

	string estadoAtual = criaEstado();
	map<pair<string, int>, Estado>::iterator tmp = utilidade.find(make_pair(estadoAtual, jogador));
	if (tmp != utilidade.end()) {
		return tmp->second.resultado;
	}

	if (jogador == xis) {
		resultado = -1;
	} else {
		resultado = 1;
	}

  for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (!tab[i][j]) {
				tab[i][j] = jogador;
				if (jogador == xis) {
					int val = constroiTree(trocaJogador(jogador));
					if (resultado == -1) {
						iOtimo = i;
						jOtimo = j;
						resultado = val;
					} else if (!resultado && val == 1) {
						iOtimo = i;
						jOtimo = j;
						resultado = val;
					}
				} else {
					int val = constroiTree(trocaJogador(jogador));
					if (resultado == 1) {
						iOtimo = i;
						jOtimo = j;
						resultado = val;
				 	} else if (!resultado && val == -1) {
						iOtimo = i;
						jOtimo = j;
						resultado = val;
					}
				}
				constroiTree(trocaJogador(jogador));
				tab[i][j] = 0;
			}
		}
	}

  string novoEstado = criaEstado(iOtimo, jOtimo, jogador);
	utilidade.insert(make_pair(make_pair(estadoAtual, jogador), Estado(novoEstado, trocaJogador(jogador), resultado, iOtimo, jOtimo)));
	return resultado;
}


int jogo(int jogador){
	int i, j, ganhador;
	string estado;
	while(1){
		cout << jogador << endl;
		print();
		ganhador = verificaGanhador();
		if (ganhador) return ganhador == ganhaBola ? ganhaBola : ganhaX;
		if (impossivelJogar()) return 0;			
		if(jogador == 1){	
			cout << "Escolha uma linha e uma coluna do tabuleiro (linha coluna): ";
			cin >> i >> j;
			tab[--i][--j] = bola;
		}else{
			estado = criaEstado();
			map<pair<string, int>, Estado>::iterator tmp = utilidade.find(make_pair(estado, jogador));
			int ii = tmp->second.i; 
			int jj = tmp->second.j;
			cout << ii << ' ' << jj << endl << estado << endl;
			tab[ii][jj] = xis;
		}
		jogador = !jogador;
	}
	
}


int main () {
		

	memset(tab, 0, sizeof tab);
	constroiTree(xis);
	
	jogo(1);

	return 0;
}
