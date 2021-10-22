#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
	unsigned int linhas = 5;
	//alocacao
	unsigned int*** matriz_de_possibilidades = (unsigned int***)new unsigned int[linhas - 1];
	for(unsigned int i = 0; i < linhas - 1; i++)
	{
		matriz_de_possibilidades[i] = (unsigned int**)new int[linhas - 1];
	}
	for(unsigned int i = 0; i < linhas - 1; i++)
	{
		for(unsigned int j = 0; j < linhas - 1; j++)
		{
			matriz_de_possibilidades[i][j] = new unsigned int[linhas - 1];
		}
	}
	for(unsigned int i = 0; i < linhas - 1; i++)
	{
		for(unsigned int j = 0; j < linhas - 1; j++)
		{
			for(unsigned int k = 0; k < linhas - 1; k++)
			{
				//matriz_de_possibilidades[i][j][k] = NULL;
				matriz_de_possibilidades[i][j][k] = 0;
				//cout << matriz_de_possibilidades[i][j][k] << ' ';
			}
			//cout << endl;
		}
		//cout << endl;
	}
	//desalocacao
	for(unsigned int i = 0; i < linhas - 1; i++)
	{
		for(unsigned int j = 0; j < linhas - 1; j++)
		{
			delete[] matriz_de_possibilidades[i][j];
			matriz_de_possibilidades[i][j] = NULL;
		}
	}
	for(unsigned int i = 0; i < linhas - 1; i++)
	{
		delete[] matriz_de_possibilidades[i];
		matriz_de_possibilidades[i] = NULL;
	}
	matriz_de_possibilidades = NULL;
	return 0;
}
