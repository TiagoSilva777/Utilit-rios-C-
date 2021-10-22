#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	string resposta;
	double resultado, valor;
	cout << "---------------Conversor de temperatura------------------" << endl;
	cout << "Escolha entre øC, øF, K" << endl;
	cout << "Converter de " << endl;
	cin >> resposta;
	if (resposta == "C")
	{
		cout << "digite o valor" <<endl; 
		cin>>valor;
		resultado = valor * 1.8 + 32;
		cout << "valor em F " << resultado << endl;
	}
	return 0;
}
