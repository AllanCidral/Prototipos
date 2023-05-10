//FUNCAO:
// Implementar um sistema de biblioteca com os seguintes dados: ISBN, Titulo, Autor, Quantidade de Exemplares e Quantidade Disponivel para Emprestimo.
// As seguintes funçoes devem ser chamadas a qualquer momento da execucao do programa:
// 1) Inclusao: Inclusao de um novo livro no acervo, contendo os dados do livro;
// 2) Consulta: Consulta a um determinado livro no acervo;
// 3) Exclusao: Exclusao fisica de um livro no acervo;
// 4) Emprestimo: Gerar um emprestimo de um determinado livro, com os seguintes dados do(a) professor(a)/aluno(a): Matricula, Codigo e Data de devolucao;
// 5) Devolucao: Gerar a devolucao de um determinado emprestimo, excluindo logicamente o emprestimo;
// 6) Relatorio1: Relatorio de todos os livros no acervo;
// 7) Relatorio2: Relatorio de todos os emprestimos ativos ou devolvidos;
// 8) Sair: Encerrar o programa.
// As funcoes devem conter validação de entrada de dados(tipo primitivo), ordenacao por ISBN, verificacao de um livro ja existente,
// verificacao de um livro existente para consulta, verificacao de quantidade de exemplares disponiveis para emprestimo e verificacao de codigo de emprestimo.
// As funçoes de ordenacao e pesquisa no acervo devem ser desenvolvidas de forma recursiva.
// Data e gerada aleatoriamente somente para representacao, nao e manipulada.
#include <iostream>
#include <cctype> // stoi
#include <string> // getline
#include <cstdlib> // isdigit, isalpha
#include <ctime> // rand
#define TMAX 100 // quantidade maxima de livros
#define TISBN 4 // tamanho do codigo de ISBN
#define TMATR 4 // tamanho da matricula
#define ANO 2023 // ano atual da data
using namespace std;

typedef struct {
	string titulo, autor, isbn;
	unsigned short int qntdExemp, qntdDisp;
} Livro;
typedef struct {
	string matricula, isbn, titulo, autor;
	unsigned short int dia, mes, codigo;
} Emprestimo;
unsigned short int menu(); // menu de opcoes
void ordenaISBN(short int i, short int j, Livro acervo[]); // ordena os livros por ISBN.
bool verificaExistente(short int i, short int j, Livro acervo[]); // verifica se ja existe o ISBN.
void inclusao(short int& i, short int& j, Livro acervo[]); // opcao 1: inclusao de livro.
void gerarConsulta(short int i, string pesquisaInc, Livro acervo[]); // pesquisa e mostra os dados do livro, caso o ISBN exista.
void consulta(short int i, string& pesquisaInc, Livro acervo[]); // opcao 2: consulta de livro.
void gerarExclusao(short int i, short int j, bool& excluido, string pesquisaExc, Livro acervo[]); // pesquisa e exclui os dados do livro, caso o ISBN exista.
void exclusao(short int& i, short int& j, bool excluido, string& pesquisaExc, Livro acervo[]); // opcao 3: exclusao de livro.
void gerarEmprestimo(short int i, short int& e, string pesquisaEmp, Livro acervo[], Emprestimo pessoa[]); // pesquisa e gera o emprestimo, caso o ISBN exista e tenha exemplares disponiveis.
void emprestimo(short int i, short int& e, string& pesquisaEmp, Livro acervo[], Emprestimo pessoa[]); // opcao 4: emprestimo de livro.
void gerarDevolucao(short int i, short int e, short int pesquisaDev, Livro acervo[], Emprestimo pessoa[]); // pesquisa e gera a devolucao, caso o codigo e matricula existam e condizem.
void devolucao(short int i, short int e, short int& pesquisaDev, Livro acervo[], Emprestimo pessoa[]); // opcao 5: devolucao de livro.
void relatorio1(short int i, Livro acervo[]); // opcao 6: relatorio dos livros no acervo.
void relatorio2(short int e, Livro acervo[], Emprestimo pessoa[]); // opcao 7: relatorio de emprestimos.

int main()
{
	Livro acervo[TMAX];
	Emprestimo pessoa[TMAX];
	short int opcao = 0, i = 0, j = 0, e = 0, pesquisaDev = 0;
	string pesquisaInc = "", pesquisaExc = "", pesquisaEmp = "";
	bool excluido = false;

	srand(time(nullptr)); // semente de gerador de numeros aleatorios com base no tempo atual
	do {
		opcao = menu();
		switch (opcao) {
		case 1:
			inclusao(i, j, acervo);
			break;
		case 2:
			consulta(i, pesquisaInc, acervo);
			break;
		case 3:
			exclusao(i, j, excluido, pesquisaExc, acervo);
			break;
		case 4:
			emprestimo(i, e, pesquisaEmp, acervo, pessoa);
			break;
		case 5:
			devolucao(i, e, pesquisaDev, acervo, pessoa);
			break;
		case 6:
			relatorio1(i, acervo);
			break;
		case 7:
			relatorio2(e, acervo, pessoa);
			break;
		case 8:
			return 0;
		}
	} while (opcao != 8);
}
unsigned short int menu() {
	string info = "";
	bool validado;
	unsigned short int x = 0;
	cout << "-----------------------------------\n";
	cout << "Bem-vindo(a):\n";
	cout << "1) Inclusao de um novo livro.\n";
	cout << "2) Consulta a um livro.\n";
	cout << "3) Exclusao de um livro.\n";
	cout << "4) Emprestimo de um exemplar.\n";
	cout << "5) Devolucao de um exemplar.\n";
	cout << "6) Relatorio de livros no acervo.\n";
	cout << "7) Relatorio de emprestimos ativos.\n";
	cout << "8) Sair.\n";
	cout << "-----------------------------------\n";
	do {
		do {
			validado = true;
			cout << "Informe sua opcao: ";
			getline(cin, info);
			if (info == "") // se a string for vazia
				validado = false;
			else
				for (unsigned short int i = 0; i < info.size(); i++) // verifica posicao a posicao
					if (!isdigit(info.at(i))) { // se nao for digito
						validado = false;
						break;
					}
			if (!validado)
				cout << "Opcao invalida, tente novamente." << endl;
		} while (!validado);
		x = stoi(info.c_str()); // converte string para inteiro
		if (x < 1 or x > 8)
			cout << "Opcao invalida, tente novamente." << endl;
	} while (x < 1 or x > 8);
	system("CLS");
	return x;
}
void ordenaISBN(short int i, short int j, Livro acervo[]) {
	if (i == 0) // primeiro elemento nao precisa de ordenacao
		return;
	if (j == i) // condicao de parada
		return;
	if (acervo[i].isbn < acervo[j].isbn)
		swap(acervo[i], acervo[j]);
	ordenaISBN(i, j + 1, acervo);
}
bool verificaExistente(short int i, short int j, Livro acervo[]) {
	if (i == 0) // primeiro elemento nao precisa de verificacao
		return false;
	if (j < 0) // condicao de parada
		return false;
	if (acervo[i].isbn == acervo[j - 1].isbn)
		return true;
	return verificaExistente(i, j - 1, acervo);
}
void inclusao(short int& i, short int& j, Livro acervo[]) {
	string info = "";
	bool validado;
	if (i == TMAX) { // caso a quantidade maxima for atingida
		cout << "Quantidade maxima de livros (" << TMAX << ") foi atingida." << endl;
		system("PAUSE");
		return;
	}
	do {
		validado = true;
		cout << "Informe o ISBN (" << TISBN << " digitos): ";
		getline(cin, info);
		if (info == "") // se a string for vazia
			validado = false;
		else
			if (info.size() != TISBN)
				validado = false;
			else
				for (unsigned short int i = 0; i < info.size(); i++) // verifica digito por digito
					if (!isdigit(info.at(i))) { // se nao for digito
						validado = false;
						break;
					}
		if (!validado)
			cout << "ISBN invalido, tente novamente." << endl;
	} while (!validado);
	acervo[i].isbn = info;
	j = i;
	if (verificaExistente(i, j, acervo)) {
		system("CLS");
		cout << "ISBN " << acervo[i].isbn << " ja existente." << endl;
		system("PAUSE");
		system("CLS");
		acervo[i].isbn = "";
		return;
	}
	info = "";
	do {
		validado = true;
		cout << "Informe o titulo referente ao ISBN " << acervo[i].isbn << ": ";
		getline(cin, info);
		if (info == "") // se a string for vazia
			validado = false;
		if (!validado)
			cout << "Titulo invalido, tente novamente." << endl;
	} while (!validado);
	acervo[i].titulo = info;
	info = "";
	do {
		validado = true;
		cout << "Informe o nome do(a) autor(a) referente ao ISBN " << acervo[i].isbn << ": ";
		getline(cin, info);
		if (info == "") // se a string for vazia
			validado = false;
		else
			for (unsigned long int i = 0; i < info.size(); i++) // verifica letra por letra
				if (!isalpha(info.at(i)) and info.at(i) != ' ') { // se nao e letra do alfabeto ou branco
					validado = false;
					break;
				}
		if (!validado)
			cout << "Nome invalido, tente novamente." << endl;
	} while (!validado);
	acervo[i].autor = info;
	info = "";
	do {
		validado = true;
		cout << "Informe a quantidade de exemplares referente ao ISBN " << acervo[i].isbn << ": ";
		getline(cin, info);
		if (info == "") // se a string for vazia
			validado = false;
		else
			for (unsigned short int i = 0; i < info.size(); i++) // verifica posicao a posicao
				if (!isdigit(info.at(i))) { // se nao for digito
					validado = false;
					break;
				}
		if (!validado)
			cout << "Quantidade invalida, tente novamente." << endl;
	} while (!validado);
	acervo[i].qntdExemp = stoi(info.c_str()); // converte string para inteiro
	acervo[i].qntdDisp = acervo[i].qntdExemp;
	system("CLS");
	cout << "Inclusao do ISBN " << acervo[i].isbn << " confirmada." << endl;
	system("PAUSE");
	system("CLS");
	j = 0;
	ordenaISBN(i, j, acervo);
	i++;
}
void gerarConsulta(short int i, string pesquisaInc, Livro acervo[]) {
	if (i < 0) { // condicao de parada
		cout << "ISBN " << pesquisaInc << " inexistente." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}
	if (pesquisaInc == acervo[i].isbn) {
		cout << "-------------------------------------------------------\n";
		cout << "ISBN: " << acervo[i].isbn << endl;
		cout << "Titulo: " << acervo[i].titulo << endl;
		cout << "Autor(a): " << acervo[i].autor << endl;
		cout << "Quantidade de exemplares: " << acervo[i].qntdExemp << endl;
		cout << "Quantidade de exemplares disponiveis: " << acervo[i].qntdDisp << endl;
		cout << "Posicao no acervo: " << i << endl;
		cout << "-------------------------------------------------------\n";
		system("PAUSE");
		system("CLS");
		return;
	}
	gerarConsulta(i - 1, pesquisaInc, acervo);
}
void consulta(short int i, string& pesquisaInc, Livro acervo[]) {
	string info = "";
	bool validado;
	do {
		validado = true;
		cout << "Informe o ISBN (" << TISBN << " digitos): ";
		getline(cin, info);
		if (info == "") // se a string for vazia
			validado = false;
		else
			if (info.size() != TISBN)
				validado = false;
			else
				for (unsigned short int i = 0; i < info.size(); i++) // verifica digito por digito
					if (!isdigit(info.at(i))) { // se nao for digito
						validado = false;
						break;
					}
		if (!validado)
			cout << "ISBN invalido, tente novamente." << endl;
	} while (!validado);
	pesquisaInc = info;
	system("CLS");
	gerarConsulta(i, pesquisaInc, acervo);
}
void gerarExclusao(short int i, short int j, bool& excluido, string pesquisaExc, Livro acervo[]) {
	if (i < 0) { // condicao de parada
		cout << "ISBN " << pesquisaExc << " inexistente, impossivel excluir." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}
	if (pesquisaExc == acervo[i].isbn) { // caso tenha devolucoes pendentes
		if (acervo[i].qntdExemp != acervo[i].qntdDisp) {
			cout << "ISBN " << acervo[i].isbn << " possui devolucoes pendentes, nao e possivel excluir." << endl;
			system("PAUSE");
			system("CLS");
			return;
		}
		for (unsigned short int k = i; k < j; k++) {
			acervo[k] = acervo[k + 1];
		}
		acervo[j].isbn = "";
		acervo[j].titulo = "";
		acervo[j].autor = "";
		acervo[j].qntdExemp = 0;
		acervo[j].qntdDisp = 0;
		excluido = true;
		return;
	}
	gerarExclusao(i - 1, j, excluido, pesquisaExc, acervo);
}
void exclusao(short int& i, short int& j, bool excluido, string& pesquisaExc, Livro acervo[]) {
	string info = "";
	bool validado;
	do {
		validado = true;
		cout << "Informe o ISBN (" << TISBN << " digitos): ";
		getline(cin, info);
		if (info == "") // se a string for vazia
			validado = false;
		else
			if (info.size() != TISBN)
				validado = false;
			else
				for (unsigned short int i = 0; i < info.size(); i++) // verifica digito por digito
					if (!isdigit(info.at(i))) { // se nao for digito
						validado = false;
						break;
					}
		if (!validado)
			cout << "ISBN invalido, tente novamente." << endl;
	} while (!validado);
	pesquisaExc = info;
	system("CLS");
	j = i;
	gerarExclusao(i, j, excluido, pesquisaExc, acervo);
	if (excluido) {
		i--;
		cout << "ISBN " << pesquisaExc << " excluido com sucesso." << endl;
		system("PAUSE");
	}
	system("CLS");
}
void gerarEmprestimo(short int i, short int& e, string pesquisaEmp, Livro acervo[], Emprestimo pessoa[]) {
	if (i < 0) { // condicao de parada
		cout << "ISBN " << pesquisaEmp << " inexistente." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}
	if (pesquisaEmp == acervo[i].isbn) { // caso nao tenha exemplares disponiveis
		if (acervo[i].qntdDisp == 0) {
			cout << "Exemplar indisponivel para emprestimo." << endl;
			system("PAUSE");
			system("CLS");
			return;
		}
		else {
			acervo[i].qntdDisp--;
			string info = "";
			bool validado;
			do {
				validado = true;
				cout << "Informe a matricula (" << TMATR << " digitos): ";
				getline(cin, info);
				if (info == "") // se a string for vazia
					validado = false;
				else
					if (info.size() != TMATR)
						validado = false;
					else
						for (unsigned short int i = 0; i < info.size(); i++) // verifica digito por digito
							if (!isdigit(info.at(i))) { // se nao for digito
								validado = false;
								break;
							}
				if (!validado)
					cout << "Matricula invalida, tente novamente." << endl;
			} while (!validado);
			system("CLS");
			pessoa[e].matricula = info;
			pessoa[e].dia = (rand() % 31) + 1; // de 1 a 31
			pessoa[e].mes = (rand() % 12) + 1; // de 1 a 12
			pessoa[e].codigo = (rand() % 900) + 100; // codigo de 3 digitos, superior a 100
			pessoa[e].isbn = acervo[i].isbn;
			pessoa[e].titulo = acervo[i].titulo;
			pessoa[e].autor = acervo[i].autor;
			cout << "-------------------------------------------------------\n";
			cout << "Emprestimo realizado." << endl;
			cout << "Codigo: " << pessoa[e].codigo << endl;
			cout << "Matricula: " << pessoa[e].matricula << endl;
			cout << "Data de devolucao: " << pessoa[e].dia << "/" << pessoa[e].mes << "/" << ANO << endl;
			cout << "ISBN: " << pessoa[e].isbn << endl;
			cout << "Titulo: " << pessoa[e].titulo << endl;
			cout << "Autor(a): " << pessoa[e].autor << endl;
			cout << "-------------------------------------------------------\n";
			system("PAUSE");
			system("CLS");
			e++;
			return;
		}
	}
	gerarEmprestimo(i - 1, e, pesquisaEmp, acervo, pessoa);
}
void emprestimo(short int i, short int& e, string& pesquisaEmp, Livro acervo[], Emprestimo pessoa[]) {
	string info = "";
	bool validado;
	do {
		validado = true;
		cout << "Informe o ISBN (" << TISBN << " digitos): ";
		getline(cin, info);
		if (info == "") // se a string for vazia
			validado = false;
		else
			if (info.size() != TISBN)
				validado = false;
			else
				for (unsigned short int i = 0; i < info.size(); i++) // verifica digito por digito
					if (!isdigit(info.at(i))) { // se nao for digito
						validado = false;
						break;
					}
		if (!validado)
			cout << "ISBN invalido, tente novamente." << endl;
	} while (!validado);
	pesquisaEmp = info;
	system("CLS");
	gerarEmprestimo(i, e, pesquisaEmp, acervo, pessoa);
}
void gerarDevolucao(short int i, short int e, short int pesquisaDev, Livro acervo[], Emprestimo pessoa[]) {
	if (e < 0) { // condicao de parada
		cout << "Registro " << pesquisaDev << " inexistente." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}
	if (pesquisaDev == pessoa[e].codigo and pessoa[e].matricula == "-1") { // caso a devolucao ja foi realizada
		cout << "Devolucao do exemplar do ISBN " << pesquisaDev << " ja realizada." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}
	if (pesquisaDev == pessoa[e].codigo) {
		string info = "";
		bool validado;
		do {
			validado = true;
			cout << "Informe a matricula (" << TMATR << " digitos): ";
			getline(cin, info);
			if (info == "") // se a string for vazia
				validado = false;
			else
				if (info.size() != TMATR)
					validado = false;
				else
					for (unsigned short int i = 0; i < info.size(); i++) // verifica digito por digito
						if (!isdigit(info.at(i))) { // se nao for digito
							validado = false;
							break;
						}
			if (!validado)
				cout << "Matricula invalida, tente novamente." << endl;
		} while (!validado);
		system("CLS");
		if (info != pessoa[e].matricula) {
			cout << "Matricula " << info << " nao condiz com o codigo " << pessoa[e].codigo << endl;
			system("PAUSE");
			system("CLS");
			return;
		}
		pessoa[e].matricula = "-1";
		pessoa[e].dia = 00;
		pessoa[e].mes = 00;
		for (unsigned short int k = 0; k < i; k++) {
			if (pessoa[e].isbn == acervo[k].isbn) {
				acervo[k].qntdDisp++;
				break;
			}
		}
		cout << "Devolucao do exemplar do ISBN " << pessoa[e].isbn << " realizada." << endl;
		system("PAUSE");
		system("CLS");
		return;
	}
	gerarDevolucao(i, e - 1, pesquisaDev, acervo, pessoa);
}
void devolucao(short int i, short int e, short int& pesquisaDev, Livro acervo[], Emprestimo pessoa[]) {
	string info = "";
	bool validado;
	do {
		validado = true;
		cout << "Informe o codigo (3 digitos): ";
		getline(cin, info);
		if (info == "") // se a string for vazia
			validado = false;
		else
			if (info.size() != 3)
				validado = false;
			else
				for (unsigned short int i = 0; i < info.size(); i++) // verifica digito por digito
					if (!isdigit(info.at(i))) { // se nao for digito
						validado = false;
						break;
					}
		if (!validado)
			cout << "Codigo invalido, tente novamente." << endl;
	} while (!validado);
	pesquisaDev = stoi(info.c_str());
	system("CLS");
	gerarDevolucao(i, e, pesquisaDev, acervo, pessoa);
}
void relatorio1(short int i, Livro acervo[]) {
	for (unsigned short int k = 0; k < i; k++) {
		cout << "-------------------------------------------------------\n";
		cout << "ISBN: " << acervo[k].isbn << endl;
		cout << "Titulo: " << acervo[k].titulo << endl;
		cout << "Autor(a): " << acervo[k].autor << endl;
		cout << "Quantidade de exemplares: " << acervo[k].qntdExemp << endl;
		cout << "Quantidade de exemplares disponiveis: " << acervo[k].qntdDisp << endl;
		cout << "Posicao no acervo: " << k << endl;
		cout << "-------------------------------------------------------\n";
	}
	system("PAUSE");
	system("CLS");
}
void relatorio2(short int e, Livro acervo[], Emprestimo pessoa[]) {
	for (unsigned short int k = 0; k < e; k++) {
		if (pessoa[k].matricula == "-1") {
			cout << "-------------------------------------------------------\n";
			cout << "Emprestimo referente ao codigo " << pessoa[k].codigo << " ja foi devolvido." << endl;
			cout << "-------------------------------------------------------\n";
		}
		else {
			cout << "-------------------------------------------------------\n";
			cout << "Codigo: " << pessoa[k].codigo << endl;
			cout << "Matricula: " << pessoa[k].matricula << endl;
			cout << "Data de devolucao: " << pessoa[k].dia << "/" << pessoa[k].mes << "/" << ANO << endl;
			cout << "ISBN: " << pessoa[k].isbn << endl;
			cout << "Titulo: " << pessoa[k].titulo << endl;
			cout << "Autor(a): " << pessoa[k].autor << endl;
			cout << "-------------------------------------------------------\n";
		}
	}
	system("PAUSE");
	system("CLS");
}