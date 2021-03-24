#ifndef JEDINKA
#define JEDINKA
#include <string>

// Model jedinke
struct Jedinka
{
public:
	int getPrilagodjenost();
	std::string getGenotip();

	void setPrilagodjenost(int n);
	void setGenotip(std::string s);

private:
	std::string genotip = "";
	int prilagodjenost = 0;
};

#endif