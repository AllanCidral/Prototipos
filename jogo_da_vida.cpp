//FUNCAO:
//Gerar uma simulacao do Jogo da Vida. O programa deve criar a
//proxima geracao de seres vivos a partir da geracao anterior, e exibir a cada alteracao o status anterior e
//o atual do "mundo". O mundo e uma matriz quadrada de ordem n (10 <= n <= 30) na qual cada celula contem
//um espaco em branco ou um asterisco. As informacoes iniciais do mundo
//dimensao da matriz e gerada manualmente (lidas do teclado) e o conteudo das celulas sao geradas aleatoriamente.
//Se a celula da matriz contiver um asterisco significa que um organismo (ser vivo) vive na celula; caso
//contrario, a celula esta vazia. Cada celula tem 8 celulas vizinhas, que sao as celulas adjacentes, incluindo as diagonais.
//As mudancas no status da matriz decorrem da aplicacao das seguintes regras:
//I. Reproducao: Um ser vivo nasce numa celula vazia se essa celula vazia tiver exatamente 3 seres
//vivos vizinhos.
//II. Sobrevivencia: Um ser vivo que tenha 2 ou 3 vizinhos sobrevive para a geracao seguinte.
//III. Morte por falta de comida: Um ser vivo com 4 ou mais vizinhos morre porque fica sem comida.
//IV. Morte por solidao: Um ser vivo com 0 ou 1 vizinhos morre de solidao.

#include <iostream>
#include <cctype> // stoi
#include <string> // getline
#include <cstdlib> // isdigit
#include <ctime> // rand
#define TMIN 10 // tamanho minimo do mundo
#define TMAX 30 // tamanho maximo do mundo
using namespace std;

int leiaN(); // responsavel por ler a dimensao do mundo, que sera gerada pela informacao do usuario.
void gerarMundo(int n, bool mundo[][TMAX]); // responsavel por criar o mundo com base na dimensao informada e gerar um conteudo aleatorio para cada celula.
void mostrarMundo(int n, bool mundo[][TMAX]); // exibe o mundo atual na tela.
void contarVizinhos(int n, bool mundo[][TMAX], int vizinhos[][TMAX]); // conta o numero de vizinhos vivos de cada celula do mundo e armazena essas informacoes em uma matriz de vizinhos.
void gerarNovoMundo(int n, bool mundo[][TMAX], int vizinhos[][TMAX], bool novoMundo[][TMAX]); // responsavel por aplicar as regras do Jogo da Vida para cada celula e gerar a proxima geracao de seres vivos.
bool verificarEstagnado(int n, bool mundo[][TMAX], bool novoMundo[][TMAX]); // verifica se o novo mundo gerado e igual ao mundo anterior, indicando que o jogo estagnou.
bool verificarFim(int n, bool mundo[][TMAX]); // verifica se o mundo ficou vazio, indicando que o jogo acabou.
void mostrarNovoMundo(int n, bool novoMundo[][TMAX]); // exibe o novo mundo gerado na tela.
void gerarMundoI(int n, bool novoMundo[][TMAX], bool mundo[][TMAX]); // e utilizada para gerar o mundo inicial a partir do novo mundo gerado na geracao anterior.
int leiaResp(); // e utilizada para ler a resposta do usuario para nova iteracao.

int main()
{
	int n = 0, vizinhos[TMIN][TMAX] = { {0} }, contI = 0, resp = 1;
	bool mundo[TMIN][TMAX] = { {false} }, novoMundo[TMIN][TMAX] = { {false} }, vazio = false, estagnado = false;

	srand(time(NULL));
	n = leiaN();
	gerarMundo(n, mundo);
	mostrarMundo(n, mundo);
	contarVizinhos(n, mundo, vizinhos);
	gerarNovoMundo(n, mundo, vizinhos, novoMundo);
	mostrarNovoMundo(n, novoMundo);
	do {
		if (contI > 0) {
			gerarMundoI(n, novoMundo, mundo);
			contarVizinhos(n, mundo, vizinhos);
			gerarNovoMundo(n, mundo, vizinhos, novoMundo);
			estagnado = verificarEstagnado(n, mundo, novoMundo);
			vazio = verificarFim(n, mundo);
			mostrarNovoMundo(n, novoMundo);
		}
		if (estagnado and !vazio) { // caso o novo mundo seja igual ao anterior
			resp = 0;
			cout << "Fim do jogo: o mundo estagnou!" << endl;
		}
		else
			if (vazio) { // caso o mundo fique vazio
				resp = 0;
				cout << "Fim do jogo: todas as celulas estao vazias!" << endl;
			}
			else {
				contI++;
				resp = leiaResp();
			}
	} while (resp != 0);
	return 0;
}
int leiaN() {
	string info = "";
	bool validado;
	int x = 0;
	do {
		do {
			validado = true;
			cout << "Informe o tamanho do mundo (" << TMIN << "-" << TMAX << "): ";
			getline(cin, info);
			if (info == "")
				validado = false;
			else
				for (int i = 0; i < info.size(); i++) {
					if (!isdigit(info.at(i))) {
						validado = false;
						break;
					}
				}
			if (!validado)
				cout << "Tamanho invalido, tente novamente." << endl;
		} while (!validado);
		x = stoi(info.c_str());
		if (x < TMIN or x > TMAX)
			cout << "Tamanho invalido, tente novamente." << endl;
	} while (x < TMIN or x > TMAX);
	return x;
}
void gerarMundo(int n, bool mundo[][TMAX]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mundo[i][j] = rand() % 2; // definido com 50% de chance de gerar um ser vivo
}
void mostrarMundo(int n, bool mundo[][TMAX]) {
	cout << "------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (mundo[i][j])
				cout << "[*]";
			else
				cout << "[ ]";
		cout << endl;
	}
	cout << "------------------------------------------------------------------------------------------\n";
}
void contarVizinhos(int n, bool mundo[][TMAX], int vizinhos[][TMAX]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			vizinhos[i][j] = 0;
			// verificacao das pontas
			if (i == 0 and j == 0) {
				if (mundo[i][j + 1]) vizinhos[i][j]++;
				if (mundo[i + 1][j]) vizinhos[i][j]++; // ponta superior esquerda
				if (mundo[i + 1][j + 1]) vizinhos[i][j]++;
			}
			else
				if (i == n - 1 and j == 0) {
					if (mundo[i][j + 1]) vizinhos[i][j]++;
					if (mundo[i - 1][j]) vizinhos[i][j]++; // ponta inferior esquerda
					if (mundo[i - 1][j + 1]) vizinhos[i][j]++;
				}
				else
					if (i == 0 and j == n - 1) {
						if (mundo[i][j - 1]) vizinhos[i][j]++;
						if (mundo[i + 1][j]) vizinhos[i][j]++; // ponta superior direita
						if (mundo[i + 1][j - 1]) vizinhos[i][j]++;
					}
					else
						if (i == n - 1 and j == n - 1) {
							if (mundo[i][j - 1]) vizinhos[i][j]++;
							if (mundo[i - 1][j]) vizinhos[i][j]++; // ponta inferior direita
							if (mundo[i - 1][j - 1]) vizinhos[i][j]++;
						}
						else // verificacao das bordas extremas
							if (j == 0 and i != 0 and i != n - 1) {
								if (mundo[i][j + 1]) vizinhos[i][j]++;
								if (mundo[i + 1][j]) vizinhos[i][j]++;
								if (mundo[i - 1][j]) vizinhos[i][j]++; // borda esquerda
								if (mundo[i + 1][j + 1]) vizinhos[i][j]++;
								if (mundo[i - 1][j + 1]) vizinhos[i][j]++;
							}
							else
								if (i == n - 1 and j != 0 and j != n - 1) {
									if (mundo[i][j + 1]) vizinhos[i][j]++;
									if (mundo[i][j - 1]) vizinhos[i][j]++;
									if (mundo[i - 1][j]) vizinhos[i][j]++; // borda de baixo
									if (mundo[i - 1][j + 1]) vizinhos[i][j]++;
									if (mundo[i - 1][j - 1]) vizinhos[i][j]++;
								}
								else
									if (j == n - 1 and i != 0 and i != n - 1) {
										if (mundo[i + 1][j]) vizinhos[i][j]++;
										if (mundo[i][j - 1]) vizinhos[i][j]++;
										if (mundo[i - 1][j]) vizinhos[i][j]++; // borda direita
										if (mundo[i + 1][j - 1]) vizinhos[i][j]++;
										if (mundo[i - 1][j - 1]) vizinhos[i][j]++;
									}
									else
										if (i == 0 and j != 0 and j != n - 1) {
											if (mundo[i][j + 1]) vizinhos[i][j]++;
											if (mundo[i][j - 1]) vizinhos[i][j]++;
											if (mundo[i + 1][j]) vizinhos[i][j]++; // borda de cima
											if (mundo[i + 1][j + 1]) vizinhos[i][j]++;
											if (mundo[i + 1][j - 1]) vizinhos[i][j]++;
										}
										else // verificacao do centro
											if (i != 0 and j != 0 and i != n - 1 and j != n - 1) {
												if (mundo[i][j + 1]) vizinhos[i][j]++;
												if (mundo[i][j - 1]) vizinhos[i][j]++;
												if (mundo[i + 1][j]) vizinhos[i][j]++;
												if (mundo[i - 1][j]) vizinhos[i][j]++;
												if (mundo[i + 1][j + 1]) vizinhos[i][j]++;
												if (mundo[i + 1][j - 1]) vizinhos[i][j]++;
												if (mundo[i - 1][j - 1]) vizinhos[i][j]++;
												if (mundo[i - 1][j + 1]) vizinhos[i][j]++;
											}
		}
}
void gerarNovoMundo(int n, bool mundo[][TMAX], int vizinhos[][TMAX], bool novoMundo[][TMAX]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!mundo[i][j] and vizinhos[i][j] == 3) // regra 1 - reproducao
				novoMundo[i][j] = true;
			else
				if (mundo[i][j] and vizinhos[i][j] == 2 or vizinhos[i][j] == 3) // regra 2 - sobrevivencia
					novoMundo[i][j] = true;
				else
					if (mundo[i][j] and vizinhos[i][j] >= 4) // regra 3 - morte por falta de comida
						novoMundo[i][j] = false;
					else
						if (mundo[i][j] and vizinhos[i][j] <= 1) // regra 4 - morte por solidao
							novoMundo[i][j] = false;
}
bool verificarEstagnado(int n, bool mundo[][TMAX], bool novoMundo[][TMAX]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (novoMundo[i][j] != mundo[i][j])
				return false;
	return true;
}
void mostrarNovoMundo(int n, bool novoMundo[][TMAX]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (novoMundo[i][j])
				cout << "[*]";
			else
				cout << "[ ]";
		cout << endl;
	}
	cout << "------------------------------------------------------------------------------------------\n";
}
void gerarMundoI(int n, bool novoMundo[][TMAX], bool mundo[][TMAX]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			mundo[i][j] = false;
			mundo[i][j] = novoMundo[i][j];
		}
}
bool verificarFim(int n, bool mundo[][TMAX]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mundo[i][j])
				return false;
	return true;
}
int leiaResp() {
	string info = "";
	bool validado;
	int resp = 0;
	do {
		do {
			validado = true;
			cout << "Pressione 1 para gerar um novo mundo ou 0 para parar: ";
			getline(cin, info);
			if (info == "")
				validado = false;
			else
				for (int i = 0; i < info.size(); i++)
					if (!isdigit(info.at(i)))
						validado = false;
			if (!validado)
				cout << "Opcao invalida, tente novamente." << endl;
		} while (!validado);
		resp = stoi(info.c_str());
		if (resp < 0 or resp > 1)
			cout << "Opcao invalida, tente novamente." << endl;
	} while (resp < 0 or resp > 1);
	cout << "------------------------------------------------------------------------------------------\n";
	return resp;
}
