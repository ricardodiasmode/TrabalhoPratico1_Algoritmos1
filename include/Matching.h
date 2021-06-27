#ifndef MATCHING_H
#define MATCHING_H

#pragma once
#include <Pessoa.h>
#include <Posto.h>

class Matching
{
public:
	static Posto* PrimeiroPostoDePreferenciaNaoProposto(Pessoa PessoaRef, Posto* ArrayDePostos, int QuantidadeDePostos, bool* VetorPropostas);
	static void ColocarPessoaNoPosto(Pessoa* PessoaRef, Posto* PostoRef);
	static void TrocarPessoaDePosto(Pessoa* PessoaRef, Posto* PostoRef, Pessoa* PessoaSaindoDoPosto);
	static int TodosEstaoEmPostos(Pessoa* ArrayDePessoas, int QuantidadeDePessoas);
	// Checa se posto prefere p1 a qualquer pessoa dentro dele. Se prefere p1, retornta true
	static bool ChecarPreferenciaPosto(Posto* PostoRef, Pessoa* p1, Pessoa** p2);
};

#endif // !MATCHING_H
