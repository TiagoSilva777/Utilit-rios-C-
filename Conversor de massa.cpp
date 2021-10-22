#include <iostream>
#include <cstdlib>

using namespace std;

int nomes(void)
{
	string grandeza;
	int valor;
	cin >> grandeza;
	if(grandeza == "kg")
	{
		valor = -3;
	}
	else if(grandeza == "hg")
	{
		valor = -2;
	}
	else if(grandeza == "dag")
	{
		valor = -1;
	}
	else if(grandeza == "g")
	{
		valor = 0;
	}
	else if(grandeza == "dg")
	{
		valor = 1;
	}
	else if(grandeza == "cg")
	{
		valor = 2;
	}
	else if(grandeza == "mg")
	{
		valor = 3;
	}
	else
	{
		valor = 0;
		cout << "Valor desconhecido passado, saindo do programa" << endl;
		exit(true);
	}
	return valor;
}

int main(int argc, char *argv[])
{
	double valor = 0, resultado;
	double j = 1;
	int rep1, rep2;
	cout << "-----------------Conversor de massa--------------------" << endl;
	cout << "Escolha entre kg, hg, dag, g, dg, cg, mg" << endl;
	cout << "Converte de ";
	rep1 = nomes();
	cout << "para ";
	rep2 = nomes();
	cout << "Digite o valor " << endl;
	cin >> valor;
	if(rep1 < rep2)
	{
		for(int i = rep1; i < rep2; i++)
		{
			j = j * 10;
		}
		resultado = valor * j;
		cout << resultado << endl;
	}
	else if(rep1 > rep2)
	{
		for(int i = rep1; i > rep2; i--)
		{
			j = j / 10;
		}
		resultado = valor * j;
		cout << resultado << endl;
	}
	system("pause");
	return 0;
}
