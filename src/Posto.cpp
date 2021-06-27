#include <Posto.h>
#include <iostream>

Posto::Posto(int InitID, int InitCapacidade, int InitX, int InitY)
{
	this->ID = InitID;
	this->Capacidade = InitCapacidade;
	this->X = InitX;
	this->Y = InitY;
	PessoasDentro = new Pessoa*[this->Capacidade];
	for (int i = 0; i < this->Capacidade; i++)
	{
		PessoasDentro[i] = new Pessoa();
	}
}Posto::Posto()
{
}