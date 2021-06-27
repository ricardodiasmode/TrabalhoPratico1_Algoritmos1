#ifndef POSTO_H
#define POSTO_H
#pragma once

#include <Pessoa.h>

class Pessoa;

class Posto
{
public:
	Posto(int InitID, int InitCapacidade, int InitX, int InitY);
	Posto();
public:
	int ID = -1;
	int QuantidadeDentro = 0;
	// Quantidade de pessoas que podem entrar no posto
	int Capacidade = -1;
	int X = -1;
	int Y = -1;
public:
	// Vetor que segura a referencia de cada pessoa
	Pessoa** PessoasDentro = nullptr;
};

#endif // !POSTO_H
