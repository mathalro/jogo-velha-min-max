/*
 =======================================================
|          Engenharia de Computacao - CEFET-MG          |
|                 Inteligencia Artificial               |
| Implementacao do algoritmo MaxMin para Jogo da Velha  |
|	             Higor Coimbra - Matheus Rosa             |
 =======================================================
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
#include <unistd.h>

#define tabulacao printf("\t\t\t\t\t")
#define tabulacao2 printf("\t\t\t\t")

using namespace std;

struct Estado {
	string tab;
	int jogador, resultado, i, j;
	Estado() {}
	Estado(string tab, int jogador, int resultado, int i, int j) :  tab(tab), jogador(jogador), resultado(resultado), i(i), j(j) {}
};

const int sizeTab = 3;
const int contGanhaBola = 30, contGanhaX = 3;
const int ganhaBola = 1, ganhaX = 2;
const int bola = 10, xis = 1;
const int pc = 0, play = 1;

map<pair<int, string>, Estado> utilidade;

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
		int contLinha = 0, contColuna = 0;
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
	system("clear");
	puts("Higor Coimbra ----------------- Jogo da Velha - CEFET-MG -------------------- Matheus Rosa\n");
	for (int i = 0; i < sizeTab; i++) {
		tabulacao;
		for (int j = 0; j < sizeTab; j++) {
			if (tab[i][j] == bola) {
				printf(" o");
			} else if (tab[i][j] == xis){
				printf(" x");
			} else {
				printf("  ");
			}
			if (j < sizeTab-1) {
				printf(" |");		
			}
		}
		puts("");
		if (i < sizeTab-1) {
			tabulacao;
			printf("-----------\n");
		}
	}
	puts("");
}


/*
	Gera os estados com uma arvore de recursao
*/
int cont = 0;
int constroiTree(int jogador) {
	int resultado, iOtimo, jOtimo, ganhador;
  
	if (impossivelJogar()) {
		return 0;
	}

	// Programacao dinamica para otimizar a geracao dos estados. Caso um estado ja tenha sido calculado, usa-se este valor que ja foi calculado
	string estadoAtual = criaEstado();	
	map<pair<int, string>, Estado>::iterator tmp = utilidade.find(make_pair(jogador, estadoAtual));
	if (tmp != utilidade.end()) {
		return tmp->second.resultado;
	}

	if (jogador == xis) {
		resultado = -1;
	} else {
		resultado = 1;
	}

	// Testa todas as escolhas
  for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (!tab[i][j]) {
				tab[i][j] = jogador;
				ganhador = verificaGanhador();
				if (jogador == xis) {
					if (ganhador == ganhaX) {
						resultado = 1;
						iOtimo = i;
						jOtimo = j;
					} else {
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
					}
				} else {
					if (ganhador == ganhaBola) {
						resultado = -1;
						iOtimo = i;
						jOtimo = j;
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
				}
				tab[i][j] = 0;
			}
		}
	}

	// Salva um novo estado com o resultado da melhor escolha para o min ou para o max
	string novoEstado = criaEstado(iOtimo, jOtimo, jogador);
	utilidade.insert(make_pair(make_pair(jogador, estadoAtual), Estado(novoEstado, trocaJogador(jogador), resultado, iOtimo, jOtimo)));
	return resultado;
}

/*
	Funcao que controla um jogo atual
*/
int jogo(int jogadorAtual){
	int ganhador, jogador = xis;
	int i, j;
	char ii, jj;
	string estado;
	while(1){
		print();
		ganhador = verificaGanhador();
		if (ganhador) return ganhador == ganhaBola ? ganhaBola : ganhaX;
		if (impossivelJogar()) return 0;

		if (jogadorAtual == play) {
			bool pode = false;
			while (!pode) {
				tabulacao2;
				cout << "Escolha a linha que deseja marcar: ";
				cin >> ii;
				tabulacao2;
				cout << "Escolha a coluna que deseja marcar: ";
				cin >> jj;
				i = ii-'0';
				j = jj-'0';
				if (i > sizeTab || j > sizeTab || i <= 0 || j <= 0) {
					print();
					tabulacao2;
					cout << "Esta posicao não existe!" << endl;
				} else if (tab[i-1][j-1]) {
					print();
					tabulacao2;
					cout << "Esta posicao ja esta ocupada! " << endl;
				} else {
					pode = true;
				}
			}
		} else {
			tabulacao2;
			cout << "Aguarde sua vez ! " << endl;
			sleep(1);
			estado = criaEstado();
			map<pair<int, string>, Estado>::iterator tmp = utilidade.find(make_pair(jogador, estado));
			i = tmp->second.i;
			j = tmp->second.j;
			i++; j++;
		}
	
		if(jogador == bola) {
			tab[--i][--j] = bola;
		} else {
			tab[--i][--j] = xis;
		}

		jogador = trocaJogador(jogador);
		jogadorAtual = !jogadorAtual;
	}
	
}

/*
	Funcao que comeca um novo jogo
*/
void iniciarJogo() {
	int primeiro, ganhador;
	bool jogando = true;
	char c;
	while (jogando) {
		int aleatorio = rand()%100;
		cout << aleatorio << endl;	
		if (aleatorio >= 50) {
			primeiro = play;
		} else {
			primeiro = pc;
		}

		ganhador = jogo(primeiro);
		tabulacao2;
		if (ganhador == ganhaBola) {
			if (primeiro == pc) {
				cout << "Parabéns! Você venceu. " << endl;
			} else {
				cout << "Você perdeu!" << endl;
			}
		} else if (ganhador == ganhaX) {
			if (primeiro == pc) {
				cout << "Você perdeu!" << endl;
			} else {
				cout << "Parabéns! Você venceu. " << endl;
			}
		} else {
			cout << "Deu Velha!" << endl;
		}
		
		tabulacao2;
		cout << "Deseja jogar novamente? (Y/N): ";
		cin >> c;
		if (c != 'Y' && c != 'y') {
			jogando = false;
		}	
		memset(tab, 0, sizeof tab);
	}
}

int main () {
		
	srand(time(NULL));
	constroiTree(xis);

	iniciarJogo();
	return 0;
}
