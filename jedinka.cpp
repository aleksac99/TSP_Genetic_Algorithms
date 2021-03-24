#include "jedinka.h"


	int Jedinka::getPrilagodjenost()
	{
		return Jedinka::prilagodjenost;
	}
	std::string Jedinka::getGenotip()
	{
		return genotip;
	}

	void Jedinka::setPrilagodjenost(int n)
	{
		prilagodjenost = n;
	}

	void Jedinka::setGenotip(std::string s)
	{
		genotip = s;
	}