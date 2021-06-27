#include <Matching.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	// Declarando variaveis que serao utilizadas
	Posto* Postos = nullptr;
	Pessoa* Pessoas = nullptr;
	string linha;
	int NumeroTotalDePostos = -1;
	int NumeroDePostosLidos = 0;
	int NumeroTotalDePessoas = -1;
	int NumeroDePessoasLidas = 0;

	// Lendo as informacoes
	while (cin >> linha)
	{
		// Verifica se ja sabemos o numero total de postos
		if (NumeroTotalDePostos == -1)
		{
			NumeroTotalDePostos = stoi(linha);
			Postos = new Posto[NumeroTotalDePostos];
		}
		// Verifica se ja leu todos os postos
		else if (NumeroDePostosLidos < NumeroTotalDePostos)
		{
			// Variaves auxiliares
			string XLido;
			string YLido;
			// Le as informacoes
			cin >> XLido;
			cin >> YLido;
			int PostoID = NumeroDePostosLidos;
			int PostoCapacidade = stoi(linha);
			Postos[PostoID] = Posto(PostoID, PostoCapacidade, stoi(XLido), stoi(YLido));
			NumeroDePostosLidos++;
		}
		// Verifica se ja sabemos o numero total de pessoas
		else if (NumeroTotalDePessoas == -1)
		{
			NumeroTotalDePessoas = stoi(linha);
			Pessoas = new Pessoa[NumeroTotalDePessoas];
		}
		// Verifica se ja leu todas as pessoas
		else if (NumeroDePessoasLidas < NumeroTotalDePessoas)
		{
			// Variaves auxiliares
			string XLido;
			string YLido;
			// Le as informacoes
			cin >> XLido;
			cin >> YLido;
			int PessoaID = NumeroDePessoasLidas;
			int PessoaIdade = stoi(linha);
			int PessoaX = stoi(XLido);
			int PessoaY = stoi(YLido);
			Pessoas[PessoaID] = Pessoa(PessoaID, PessoaIdade, PessoaX, PessoaY, NumeroTotalDePostos);
			NumeroDePessoasLidas++;
		}
	}

	// Apos ler o arquivo, aloca cada pessoa para seu posto de saude
	// Declarando variaveis auxiliares
	Pessoa* PessoaSemPosto = nullptr;
	int IndexDaPessoaSemPosto = 0;
	Pessoa* PessoaSaindoDoPosto = nullptr;
	Posto* PostoAux = nullptr;
	IndexDaPessoaSemPosto = Matching::TodosEstaoEmPostos(Pessoas, NumeroTotalDePessoas);
	// Algoritmo baseado no algoritmo de casamento de Gale-Shapley
	while (IndexDaPessoaSemPosto != -1)
	{
		// Pegando pessoa
		PessoaSemPosto = &(Pessoas[IndexDaPessoaSemPosto]);
		// Pegando posto
		PostoAux = Matching::PrimeiroPostoDePreferenciaNaoProposto(Pessoas[IndexDaPessoaSemPosto], Postos, NumeroTotalDePostos, Pessoas[IndexDaPessoaSemPosto].Propostas);
		// Definindo que Pessoa propos para Posto
		Pessoas[IndexDaPessoaSemPosto].Propostas[PostoAux->ID] = true;
		// Verificando se posto desejado esta livre
		if (PostoAux->QuantidadeDentro < PostoAux->Capacidade)
			Matching::ColocarPessoaNoPosto(PessoaSemPosto, PostoAux);
		// Verificando se posto desejado prefere Pessoa
		else if (Matching::ChecarPreferenciaPosto(PostoAux, PessoaSemPosto, &PessoaSaindoDoPosto))
			Matching::TrocarPessoaDePosto(PessoaSemPosto, PostoAux, PessoaSaindoDoPosto);
		IndexDaPessoaSemPosto = Matching::TodosEstaoEmPostos(Pessoas, NumeroTotalDePessoas);
	}

	// Imprimindo saida
	cout << endl;
	for (int i = 0; i < NumeroTotalDePostos; i++)
	{
		if (Postos[i].QuantidadeDentro > 0)
		{
			cout << Postos[i].ID << endl;
			for (int j = NumeroTotalDePessoas - 1; j >= 0; j--)
			{
				if (Pessoas[j].MeuPosto)
				{
					if (Pessoas[j].MeuPosto->ID == Postos[i].ID)
						cout << Pessoas[j].ID << " ";
				}
			}
			cout << endl;
		}
	}
		
	// Deletando variaveis alocadas
	delete Postos;
	delete Pessoas;

	return 0;
}
