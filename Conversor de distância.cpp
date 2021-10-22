#include <iostream>
#include <cstdlib>
using namespace std;

int nomes(void)
{
	string grandeza;
	int valor;
	//cout << "Digite a graneza" << endl;
	cin >> grandeza;
	if(grandeza == "km")
	{
		valor = -3;
	}
	else if(grandeza == "hm")
	{
		valor = -2;
	}
	else if(grandeza == "dam")
	{
		valor = -1;
	}
	else if(grandeza == "m")
	{
		valor = 0;
	}
	else if(grandeza == "dm")
	{
		valor = 1;
	}
	else if(grandeza == "cm")
	{
		valor = 2;
	}
	else if(grandeza == "mm")
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
	cout << "-----------------Conversor de distancia--------------------" << endl;
	cout << "Escolha entre km, hm, dam, m, dm, cm, mm" << endl;
	cout << "Converte de ";
	rep1 = nomes();
	//cin >> rep1;
	cout << "para ";
	rep2 = nomes();
	//cin >> rep2;
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
