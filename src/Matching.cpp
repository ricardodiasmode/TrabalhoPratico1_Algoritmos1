#include <Matching.h>
#include <cmath>
#include <iostream>

using namespace std;

float DistanciaEntrePontos(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((x1 - x2), 2.f) + pow((y1 - y2), 2.f));
}

Posto* Matching::PrimeiroPostoDePreferenciaNaoProposto(Pessoa PessoaRef, Posto* ArrayDePostos, int QuantidadeDePostos, bool* VetorPropostas)
{
	// Declarando variaveis auxiliares
	float MenorDistancia = 99999.f;
	int IndexDoPostoMaisProximo = -1;
	// Verifica o posto mais proximo
	for (int i = 0; i < QuantidadeDePostos; i++)
	{
		// Declarando variaveis auxiliares
		int x1 = ArrayDePostos[i].X;
		int y1 = ArrayDePostos[i].Y;
		int x2 = PessoaRef.X;
		int y2 = PessoaRef.Y;
		float DistanciaAtual = DistanciaEntrePontos(x1, y1, x2, y2);
		// Verifica se a distancia do posto atual eh menor que a do anterior
		if (MenorDistancia > DistanciaAtual)
		{
			// Verifica se ja propos pra esse posto
			if (!(VetorPropostas[i]))
			{
				MenorDistancia = DistanciaAtual;
				IndexDoPostoMaisProximo = i;
			}
		}
		// Se distancia for igual
		else if (MenorDistancia == DistanciaAtual)
		{
			// Desempate por ID de cada posto
			if (ArrayDePostos[IndexDoPostoMaisProximo].ID > ArrayDePostos[i].ID)
			{
				// Verifica se ja propos pra esse posto
				if (!(VetorPropostas[i]))
				{
					MenorDistancia = DistanciaAtual;
					IndexDoPostoMaisProximo = i;
				}
			}
		}
	}
	if (IndexDoPostoMaisProximo != -1)
		return &ArrayDePostos[IndexDoPostoMaisProximo];
	else
		return nullptr;
}

void Matching::ColocarPessoaNoPosto(Pessoa* PessoaRef, Posto* PostoRef)
{
	// Verifica se ha alguma posicao vazia
	if (PostoRef->QuantidadeDentro < PostoRef->Capacidade)
	{
		// Verifica que posicao do posto esta vazia
		for (int i = 0; i < PostoRef->Capacidade; i++)
		{
			// Checa se a posicao 'i' esta vazia
			if (PostoRef->PessoasDentro[i]->ID == -1)
			{
				// Finalmente coloca a pessoa dentro do posto
				PostoRef->PessoasDentro[i] = PessoaRef;
				PessoaRef->MeuPosto = PostoRef;
				PostoRef->QuantidadeDentro = PostoRef->QuantidadeDentro + 1;
				return;
			}
		}
	}
}

void Matching::TrocarPessoaDePosto(Pessoa* PessoaRef, Posto* PostoRef, Pessoa* PessoaSaindoDoPosto)
{
	for (int i = 0; i < PostoRef->QuantidadeDentro; i++)
	{
		if (PostoRef->PessoasDentro[i]->ID == PessoaSaindoDoPosto->ID)
		{
			// Remove a pessoa do posto
			PessoaSaindoDoPosto->MeuPosto = nullptr;
			// Coloca a outra pessoa no posto
			PostoRef->PessoasDentro[i] = PessoaRef;
			PessoaRef->MeuPosto = PostoRef;
			return;
		}
	}
}

int Matching::TodosEstaoEmPostos(Pessoa* ArrayDePessoas, int QuantidadeDePessoas)
{
	bool ProposParaTodos = true;
	for (int i = 0; i < QuantidadeDePessoas; i++)
	{
		// Checa se a pessoa em questao ja esta em um posto
		if (ArrayDePessoas[i].MeuPosto == nullptr)
		{
			// Checa se ja propos para todos
			for (int j = 0; j < ArrayDePessoas[i].QuantidadeDePostos; j++)
			{
				if (ArrayDePessoas[i].Propostas[j] == false)
					ProposParaTodos = false;
			}
			// Se a 'ProposParaTodos' eh falso, entao nao propos para 'i'
			if (!ProposParaTodos)
				return i;
		}
	}
	// Se saiu do loop eh pq todas as pessoas
	// ja proporam para todos os postos ou estao em um
	return -1;
}

bool Matching::ChecarPreferenciaPosto(Posto* PostoRef, Pessoa* p1, Pessoa** p2)
{
	int IndexDeMenorIdade = -1;
	int MenorIdade = 99999;
	// Iteracao nos postos para verificar qual a pessoa
	// dentro do posto tem a menor idade
	for (int i = 0; i < PostoRef->QuantidadeDentro; i++)
	{
		if (MenorIdade > PostoRef->PessoasDentro[i]->Idade)
		{
			IndexDeMenorIdade = i;
			MenorIdade = PostoRef->PessoasDentro[i]->Idade;
		}
		else if (MenorIdade == PostoRef->PessoasDentro[i]->Idade)
		{
			if (PostoRef->PessoasDentro[i]->ID > PostoRef->PessoasDentro[IndexDeMenorIdade]->ID)
			{
				IndexDeMenorIdade = i;
				MenorIdade = PostoRef->PessoasDentro[i]->Idade;
			}
		}
	}
	// Verificando se idade eh maior
	if (p1->Idade > PostoRef->PessoasDentro[IndexDeMenorIdade]->Idade)
	{
		*p2 = PostoRef->PessoasDentro[IndexDeMenorIdade];
		return true;
	}
	// Verificando se idade eh igual
	else if (p1->Idade == PostoRef->PessoasDentro[IndexDeMenorIdade]->Idade)
	{
		if (p1->ID < PostoRef->PessoasDentro[IndexDeMenorIdade]->ID)
		{
			*p2 = PostoRef->PessoasDentro[IndexDeMenorIdade];
			return true;
		}
	}
	return false;
}
