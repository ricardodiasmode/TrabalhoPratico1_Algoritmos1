#ifndef PESSOA_H
#define PESSOA_H
#pragma once

#include <Posto.h>

class Posto;

class Pessoa
{
public:
	Pessoa(int InitID, int InitIdade, int InitX, int InitY, int QuantidadeDePostos);
	Pessoa(const Pessoa& PessoaRef);
	Pessoa();
public:
	int ID = -1;
	int Idade = 0;
	int X = -1;
	int Y = -1;
	int QuantidadeDePostos = -1;
	// Vetor que segura para qual posto ja propos
	bool* Propostas;
	// Vetor que segura o posto em que esta
	Posto* MeuPosto = nullptr;
};

#endif // !PESSOA_H
