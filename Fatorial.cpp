#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	static int var=1;//Variaável que retem o valor quando a função é chamada
	long double fat=1, val, i;
	cout<<"Digite um valor para saber o fatorial"<<endl;
	cin>>val;
	for(i=1; i<=val;i++){
		fat=fat*i;
	}
	cout<<fat<<endl;
	cout.precision(0);//casas a ser exibidas apos a virgula
	cout<<fixed<<fat;//exibe valor fixo
	return 0;
}