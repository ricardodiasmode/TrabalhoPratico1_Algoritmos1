#include <Pessoa.h>

Pessoa::Pessoa(int InitID, int InitIdade, int InitX, int InitY, int QuantidadeDePostos)
{
	this->ID = InitID;
	this->Idade = InitIdade;
	this->X = InitX;
	this->Y = InitY;
	this->QuantidadeDePostos = QuantidadeDePostos;
	this->Propostas = new bool[QuantidadeDePostos];
	for (int i = 0; i < this->QuantidadeDePostos; i++)
	{
		this->Propostas[i] = false;
	}
}
Pessoa::Pessoa(const Pessoa& PessoaRef)
{
	this->ID = PessoaRef.ID;
	this->Idade = PessoaRef.Idade;
	this->X = PessoaRef.X;
	this->Y = PessoaRef.Y;
	this->QuantidadeDePostos = PessoaRef.QuantidadeDePostos;
	this->Propostas = new bool[QuantidadeDePostos];
	for (int i = 0; i < this->QuantidadeDePostos; i++)
	{
		this->Propostas[i] = false;
	}
}
Pessoa::Pessoa()
{
	this->ID = -1;
	this->Idade = 0;
	this->X = -1;
	this->Y = -1;
	if (this->QuantidadeDePostos != -1)
	{
		for (int i = 0; i < this->QuantidadeDePostos; i++)
		{
			this->Propostas[i] = false;
		}
		this->MeuPosto = nullptr;
	}
}
