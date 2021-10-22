#include <iostream>
#include <cstdlib>
#include <time.h>
#include <typeinfo>
#include <windows.h>
#include <math.h>
#include <cstdio>
//#include <stack>

using std::cout;
using std::endl;
//using std::stack;

#define M_MATRIZES

static long long int Memory()
{
#ifdef WIN32
	MEMORYSTATUS memory;
	memset(&memory, 0, sizeof(MEMORYSTATUS));
	memory.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memory);
	return memory.dwTotalPhys;
#endif
#ifndef WIN32
	return 11180 * 16;
#endif
}

#define MAX_MATRIZ_LINHA (unsigned int)sqrt(Memory() / 16)
#define MAX_MATRIZ_COLUNA MAX_MATRIZ_LINHA
#define M_MATRIZ_SEED time(NULL)

//65535 * 65535 = 4294836225 células
//4294836225 * 8(long long) = 34358689800 bytes
//4294836225 * 4(int) = 17179344900 bytes
//4294836225 * 2(short) = 8589672450 bytes
//4294836225 * 1(char) = 4294836225 bytes
//linha 11180 padrão
//coluna 11180 padrão

enum Fila
{
	LINHA, COLUNA
};

class Misto
{
public:
	int coeficiente;
	unsigned int linha;
	unsigned int coluna;
	unsigned int linha_array;
};

template<class Tipo>
class Fracao
{
private:
	Tipo numerador;
	Tipo denominador;
public:
	Fracao() : numerador(0), denominador(1) {}
	~Fracao() {}
	Tipo resutado()
	{
		return numerador / denominador;
	}
	void inserir(Tipo par_numerador, Tipo par_denominador)
	{
		numerador = par_numerador;
		denominador = par_denominador;
	}
	Tipo operator*(Tipo valor)
	{
		return (numerador *= valor) / denominador;
	}
	bool divisaoineteira(Tipo valor)
	{
		if(typeid(Tipo) == typeid(int))
		{
			if(typeid(valor) == typeid(int))
			{
				return ((numerador * valor) % 2 == 0);
			}
		}
	}
};

template<typename Tipo>
inline static Tipo FuncaoPotenciaUm(unsigned int expoente)
{
	if(expoente % 2 == 0)
	{
		return 1;
	}
	return -1;
}

static bool Extract(const float& value)
{
	if(value == 1.0 || value == -1.0 || value == 0.0)
		return true;
	int exponent = 0;
	int mantissa = 0;
	int inteira = 0;
	int fracionaraia = 0;
	float partef = 0;
	float value1 = value;
	float value2 = value;
	unsigned int* point;
	unsigned int mask = 0x7F800000;
	unsigned int mask2 = 0;
	point = reinterpret_cast<unsigned int*>(&value1);
	*point = *point & mask;
	*point >>= 23;
	if(*point == 255)//is impossible
	{
		return false;
	}
	exponent = *point - 127;
	mask = 0X7FFFFF;
	point = reinterpret_cast<unsigned int*>(&value2);
	*point = *point & mask;
	mantissa = *point ;
	mask = 0x800000;
	inteira = mantissa;
	inteira |= mask;
	if(exponent > 0)
		inteira >>= (23 - exponent);
	else
		return false;
	fracionaraia = mantissa;
	mask2 = static_cast<unsigned int>(pow(2 , 23 - exponent - 1));
	for(int i = (23 - exponent) - 1, k = 1; i >= 0; i--)
	{
		partef += ((fracionaraia & mask2) >> i) / static_cast<float>(pow(2, k));
		k++;
		mask2 >>= 1;
	}
	if(partef == 0.0)
		return true;
	return false;
}

template<class Tipo> class FilasParaChio
{
public :
	unsigned int linha;
	unsigned int coluna;
	unsigned int largura;
	Tipo* array_da_linha;
	Tipo* array_da_coluna;
	FilasParaChio()
	{
		linha = coluna = 0;
		array_da_linha = NULL;
		array_da_coluna = NULL;
	}
	~FilasParaChio()
	{
		//delete[] array_da_linha;
		//delete[] array_da_coluna;
	}
	FilasParaChio<Tipo> operator=(FilasParaChio<Tipo>* filas)
	{
		this->linha = filas->linha;
		this->coluna = filas->coluna;
		this->largura = filas->largura;
		if(this->array_da_linha != NULL && array_da_coluna != NULL)
		{
			delete[] this->array_da_linha;
			delete[] this->array_da_coluna;
		}
		this->array_da_linha = new Tipo[filas->largura];
		this->array_da_coluna = new Tipo[filas->largura];
		for(unsigned int i = 0; i < filas->largura; i++)
		{
			this->array_da_linha[i] = filas->array_da_linha[i];
			this->array_da_coluna[i] = filas->array_da_coluna[i];
		}
		return *this;
	}
	//friend void operator delete (void* pointfila);
	/*void Inicializa(unsigned int linha, unsigned int coluna, unsigned int largura, Tipo* array_da_linha, Tipo* array_da_coluna)
	{
		this->linha = linha;
		this->coluna = coluna;
		this->largura = largura;
		this->array_da_linha = array_da_linha;
		this->array_da_coluna = array_da_coluna;
	}*/
};

/*template<> class FilasParaChio<class Tipo*>
	{
	public :
		unsigned int linha;
		unsigned int coluna;
		const unsigned int* largura;
		Tipo* array_da_linha;
		Tipo* array_da_coluna;
		FilasParaChio()
		{
			linha = coluna = 0;
			largura = NULL;
			array_da_linha = array_da_coluna = NULL;
		}
		~FilasParaChio()
		{
			//delete linha, delete coluna;
			delete largura;
			//delete array_da_linha, delete array_da_coluna;
		}
		FilasParaChio operator=(FilasParaChio fila)
		{
			largura = new unsigned int;
			array_da_linha = new Tipo[fila.largura];
			array_da_coluna = new Tipo[fila.largura];
		}
	};*/

/*
void operator delete (void* elementofila)//aff
{

}
*/

template<class Tipo> class Elemento
{
public :
	unsigned int linha;
	unsigned int coluna;
	Tipo valor;
	Elemento()
	{
		linha = coluna  = 0;
		valor = 0;
	}
	~Elemento()
	{
	}
	bool haumvalor()
	{
		return valor != 0 ? true : false;
	}
	operator bool(void) const//não funciona
	{
		return haumvalor();
	}
};

template<class Tipo> class Matriz
{
	bool teste_de_intervalo(unsigned int linhas, unsigned int colunas)
	{
		bool retorno = false;
		retorno = (linhas > 0 && colunas > 0);
		retorno = retorno && (linhas <= MAX_MATRIZ_LINHA && colunas <= MAX_MATRIZ_COLUNA);
		return retorno;
	}
private:
	unsigned int linhas;
	unsigned int colunas;
	Tipo** valores;
public:
	Matriz()
	{
		linhas = colunas = 0;
		valores = NULL;
	}
	Matriz(unsigned int ordem)//quadradas
	{
		Cria(ordem, ordem);
	}
	Matriz(unsigned int linhas, unsigned int colunas)
	{
		Cria(linhas, colunas);
	}
	~Matriz() {}
	template<class Dado> friend Dado FuncaoRegraDeSarrus(Matriz<Dado>* matriz_sarrus);
	template<class Dado> friend Matriz<Dado>* FuncaoRegraDeChio(Matriz<Dado>* matriz_analise, unsigned int* lin = NULL, unsigned int* col = NULL);
	const Tipo** Cria(unsigned int linhas, unsigned int colunas)//aloca memória
	{
		if(valores == NULL && teste_de_intervalo(linhas, colunas))
		{
			this->linhas = linhas;
			this->colunas = colunas;
			valores = reinterpret_cast<Tipo**>(new Tipo[linhas]);
			//valores = (Tipo**)new Tipo[linhas];
			//this->valores = (Tipo**)malloc(sizeof(Tipo) * linhas);
			for(register unsigned int i = 0; i < linhas; i++)
			{
				valores[i] = new Tipo[colunas];
				//this->valores[i] = (Tipo*)malloc(sizeof(Tipo) * colunas);
			}
			for(register unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					valores[i][j] = static_cast<Tipo>(0);
				}
			}
			return const_cast<const Tipo**>(valores);
		}
		return const_cast<const Tipo**>(valores);
	}
	const Tipo** Destroi()//libera memória
	{
		if(valores != NULL)
		{
			for(register unsigned int i = 0; i < linhas; i++)
			{
				//free(valores[i]);
				delete valores[i];
			}
			linhas = 0;
			colunas = 0;
			delete reinterpret_cast<Tipo**>(&valores);
			//delete (Tipo**)&valores;
			//free((Tipo**)&valores);
			valores = NULL;
		}
		return const_cast<const Tipo**>(valores);
	}
	unsigned int AdicionaLinearmente(Tipo valor)
	{
		static unsigned int conta = 0;
		if(linhas != 0 && colunas != 0)
		{
			unsigned int max = linhas * colunas;
			if(conta < max)
			{
				static unsigned int i = 0;
				static unsigned int j = 0;
				valores[i][j] = valor;
				j++;
				if(j == colunas)
				{
					j = 0;
					i++;
				}
				if(i == linhas)
				{
					i = 0;
					j++;
				}
			}
		}
		conta++;
		return conta;
	}
	void InicializaCom(Tipo value)//depois de alocada define valor para elementos
	{
		if(linhas != 0 && colunas != 0)
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					valores[i][j] = value;
				}
			}
	}
	bool PreencheMatrizIdentidade() //preenche matriz identidade
	{
		if(linhas != 0 && linhas == colunas)
		{
			InicializaCom(0);
			for(unsigned int k = 0; k < linhas; k++)
			{
				valores[k][k] = 1;
			}
			return true;
		}
		return false;
	}
	bool GeraMatrizIdentidade(unsigned int ordem) //gera matriz identidade
	{
		if(this->valores != NULL)
		{
			this->Destroi();
		}
		this->Cria(ordem, ordem);
		return this->PreencheMatrizIdentidade();
	}
	Tipo Acessa(unsigned int pos_i, unsigned int pos_j)const //retorna elemento
	{
		if(pos_i <= linhas && pos_j <= colunas)
			if(linhas >= 1 && colunas >= 1)
				return valores[pos_i - 1][pos_j - 1];
		return -0;
	}
	void Altera(unsigned int pos_i, unsigned int pos_j, Tipo valor) //altera elemento
	{
		if(pos_i <= linhas && pos_j <= colunas)
			if(linhas >= 1 && colunas >= 1)
				this->valores[pos_i - 1][pos_j - 1] = valor;
	}
	void Altera(Elemento<Tipo>* elemento) //altera elemento passando classe
	{
		Altera(elemento->linha, elemento->coluna, elemento->valor);
	}
	Elemento<Tipo>* PesquisaElemento(Tipo valor) //encontra elemento
	{
		Elemento<Tipo>* elementodamatriz = new Elemento<Tipo>;//é melhor ser automático
		if(linhas >= 1 && colunas >= 1)
		{
			unsigned int i = 0;
			unsigned int j = 0;
			for(i = 0; i < linhas; i++)
			{
				for(j = 0; j < colunas; j++)
				{
					if(valores[i][j] == valor)
					{
						elementodamatriz->linha = i + 1;
						elementodamatriz->coluna = j + 1;
						elementodamatriz->valor = valor;
						break;
					}
				}
				/*if(valores[i][j] == valor)//adicionado
					break;*/
			}
		}
		return elementodamatriz;
	}
	Matriz<Tipo>* MatrizTransposta() const //retorna a matriz MatrizTransposta
	{
		Matriz<Tipo>* matriztransposta = new Matriz;
		if(colunas != 0 && linhas != 0)
		{
			matriztransposta->Cria(colunas, linhas);
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					matriztransposta->valores[j][i] = valores[i][j];
				}
			}
		}
		return matriztransposta;
	}
	Matriz<Tipo>* MatrizOposta() const //retorna matriz MatrizOposta
	{
		Matriz<Tipo>* matrizoposta = new Matriz<Tipo>;
		if(colunas != 0 && linhas != 0)
		{
			matrizoposta->Cria(linhas, colunas);
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					matrizoposta->valores[i][j] = (-1) * valores[i][j];
				}
			}
		}
		return matrizoposta;
	}
//public:
	Matriz<Tipo>* MatrizCofator() //retorna matriz cofator
	{
		Matriz<Tipo>* matrizcof = new Matriz<Tipo>;
		matrizcof->Cria(linhas, colunas);
		//////////////////////////////////////////////////
		return matrizcof;
	}
	bool MatrizRandomica(long seed = time(NULL), int intervalo_a = 0, int intervalo_b = 255)
	{
		if(valores != NULL)
		{
			unsigned int k = 1; //gera uma matriz randômica
			unsigned int diferenca = dynamic_cast<unsigned int>(fabs(intervalo_b - intervalo_a));//analisar
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					srand(seed * k );
					valores[i][j] = dynamic_cast<Tipo>(intervalo_a + rand() % diferenca);
					k++;
				}
			}
			return true;
		}
		return false;
	}
	Matriz<Tipo>* MenorComplementar(unsigned int linha, unsigned int coluna) const //retornar a matriz cofator
	{
		Matriz<Tipo>* matrizcofator = new Matriz<Tipo>;
		linha -= 1;
		coluna -= 1;
		if(linhas > 1 && colunas > 1)
		{
			if(linha <= linhas && coluna <= colunas)
			{
				matrizcofator->Cria(linhas - 1, colunas - 1);
				unsigned int i = 0;
				unsigned int j = 0;
				unsigned int k = 0;
				unsigned int l = 0;
				for(i = 0, k = 0; i < linhas; i++)
				{
					if(i != linha)
					{
						for(j = 0, l = 0; j < colunas; j++)
						{
							if(j != coluna)
							{
								matrizcofator->valores[k][l] = valores[i][j];
								l++;
							}
						}
						k++;
					}
				}
			}
		}
		return matrizcofator;
	}
	Tipo RegraDoisPorDois() //determinante de matriz 2X2
	{
		Tipo retorno = -0;
		if(linhas == colunas && linhas == 2)
		{
			retorno = valores[0][0] * valores[1][1] - valores[0][1] * valores[1][0];
		}
	}
	Tipo RegraDeSarrus()	//detreminante de matriz 3X3
	{
		return FuncaoRegraDeSarrus(this);
	}
	Tipo LeiDeLaplace()//retorna determinante////////////////////////////////
	{
		Tipo determinante = -0;
		Matriz<Tipo>* matrizmenor = new Matriz<Tipo>;
		Matriz<Tipo>* matrizabaixada = new Matriz<Tipo>;
		matrizmenor->Cria(linhas, colunas);
		matrizabaixada->Cria(3, 3);
		unsigned int k = 0;
		unsigned int l = 1;
		for(; k < linhas; k++)
		{
			matrizmenor = MenorComplementar(1, l);
			matrizabaixada = matrizmenor->AbaixaOrdem();
			if(valores[0][k] != 0)
			{
				determinante += valores[0][k] * FuncaoPotenciaUm<Tipo>(k + 1) * matrizabaixada->RegraDeSarrus();
			}
			matrizabaixada->Destroi();
			matrizmenor->Destroi();
			l++;
			//delete matrizmenor;
		}
		return determinante;
	}
	Matriz<Tipo>* RegraDeChio()//abaixa um nível
	{
		return FuncaoRegraDeChio(this);
	}
	Matriz<Tipo>* TeoremaDeJacobi(Fila fila, unsigned int origem, unsigned int aplicacao, Tipo numero)
	{
		Matriz<Tipo>* matrizjocobi = new Matriz<Tipo>;// ver retorno e aplicar intervalo
		matrizjocobi->Cria(linhas, colunas);
		*matrizjocobi = *this;
		Tipo* arrayfila = PegaFila(fila, origem);
		aplicacao -= 1;
		for(unsigned int i = 0; i < linhas; i++)
		{
			arrayfila[i] *= numero;
		}
		if(fila == LINHA)
		{
			for(unsigned int j = 0; j < colunas; j++)
			{
				matrizjocobi->valores[aplicacao][j] += arrayfila[j];
			}
		}
		if(fila == COLUNA)
		{
			for(unsigned int i = 0; i < linhas; i++)
			{
				matrizjocobi->valores[i][aplicacao] += arrayfila[i];
			}
		}
		delete[] arrayfila;
		return matrizjocobi;
	}
	Tipo Determinante() const//calcula determinante //ajustar
	{
		Tipo retorno = -0;
		if(linhas == colunas && colunas == 1)//matriz 1X1
		{
			retorno = valores[0][0];
		}
		if(linhas == colunas && colunas == 2)//matriz 2X2
		{
			retorno = valores[0][0] * valores[1][1] - valores[0][1] * valores[1][0];
		}
		if(linhas == colunas && colunas == 3)//regra de Sarrus, matriz 3X3
		{
			return RegraDeSarrus();
		}
		if(linhas == colunas && E_triangular())//se for uma matriz diagonal
		{
			retorno = 1;
			for(unsigned int i = 0; i < linhas; i++)
			{
				retorno *= valores[i][i];
			}
		}
		return retorno;///////////////depois se for valdemor
	}
	void Mostra() const //exibe matrizes
	{
		if(linhas != 0 && colunas != 0)
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					cout << valores[i][j] << ' ';
				}
				cout << endl;
			}
	}
	Matriz<Tipo> operator+(Matriz matriz) const //soma duas matrizes
	{
		if(linhas == matriz.linhas && colunas == matriz.colunas)
		{
			Matriz<Tipo> matrizsoma;
			matrizsoma.Cria(linhas, colunas);
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					matrizsoma.valores[i][j] = valores[i][j] + matriz.valores[i][j];
				}
			}
			return matrizsoma;
		}
	}
	Matriz<Tipo> operator-(Matriz matriz) const //subtrai duas matrizes
	{
		if(linhas == matriz.linhas && colunas == matriz.colunas)
		{
			Matriz<Tipo> matrizsubtracao;
			matrizsubtracao.Cria(linhas, colunas);
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					matrizsubtracao.valores[i][j] = valores[i][j] - matriz.valores[i][j];
				}
			}
			return matrizsubtracao;
		}
	}
	Matriz<Tipo> operator*(Tipo valor) const //ops
	{
		Matriz retorno;
		if(linhas != 0 && colunas != 0)
		{
			Matriz<Tipo> matrizmultiplicacao;
			matrizmultiplicacao.Cria(linhas, colunas);
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					matrizmultiplicacao.valores[i][j] = valor * valores[i][j];
				}
			}
			return matrizmultiplicacao;
		}
		return retorno;
	}
	Matriz<Tipo> operator*(Matriz martz) const //adicionar solução 2X2
	{
		Matriz<Tipo> matrizretorno;
		if(colunas == martz.linhas)
		{
			Matriz<Tipo> matrizmultiplicacao;//o que é isso
			matrizmultiplicacao.Cria(linhas, martz.colunas);
			Tipo resultado = 0;
			for(unsigned int i = 0; i < matrizmultiplicacao.linhas; i++)
			{
				for(unsigned int j = 0; j < matrizmultiplicacao.colunas; j++)
				{
					for(unsigned int k = 0; k < colunas; k++)
					{
						resultado += valores[i][k] * matrizmultiplicacao.valores[k][j];
					}
					matrizmultiplicacao.valores[i][j] = resultado;
					resultado = 0;
				}
			}
			matrizretorno = matrizmultiplicacao;
		}
		return matrizretorno;
	}
	Matriz<Tipo> operator=(Matriz matriz) //atribui matrizes
	{
		if(linhas != matriz.linhas && colunas != matriz.colunas)
		{
			Destroi();
			linhas = matriz.linhas;
			colunas = matriz.colunas;
			valores = matriz.valores;
		}
		else
		{
			if(linhas != 0 && colunas != 0)
			{
				for(unsigned int i = 0; i < linhas; i++)
				{
					for(unsigned int j = 0; j < colunas; j++)
					{
						valores[i][j] = matriz.valores[i][j];
					}
				}
			}
		}
		return *this;
	}
	bool operator==(Matriz matriz)//verdadeiro se esta matriz e iagual à outra
	{
		if(linhas == matriz.linhas && colunas == matriz.colunas)
		{
			unsigned int k = 1;
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					if(valores[i][j] == matriz.valores[i][j])
					{
						k++;
					}
				}
			}
			if(k == linhas * colunas)
			{
				return true;
			}
		}
		return false;
	}
	bool E_invertivel(Matriz matriz) const//testa se uma matriz e a inversa da outra
	{
		if(this->E_quadrada() && matriz.E_quadrada())//podemos implementar
		{
			if(this->linhas == matriz.linha)
			{
				Matriz matriz_resuldado = (*this) * matriz;
				Matriz matriz_identidade;
				matriz_identidade.GeraMatrizIdentidade(this->linhas);
				if(matriz_resuldado == matriz_identidade)
				{
					matriz_resuldado.Destroi();
					matriz_identidade.Destroi();
					return true;
				}
				matriz_resuldado.Destroi();
				matriz_identidade.Destroi();
			}
		}
		return false;
	}
	bool E_singular(Matriz matriz) const//verdadeiro se matriz não é invertivel
	{
		return !E_invertivel(matriz);
	}
	bool E_nao_singular(Matriz matriz) const//verdadeiro se matriz é invertivel
	{
		return E_invertivel(matriz);
	}
	bool E_multiplicavel(Matriz matriz) const //verdadeiro se duas matrizes são multiplicáveis
	{
		return colunas == matriz.linhas && colunas != 0;
	}
	bool E_igual(Matriz matriz) const //verdadeiro se duas matrizes são iguais
	{
		return *this == matriz;
	}
	bool E_comutavel(Matriz matriz)//tanto faz se multiplica ou é multiplicada
	{
		if(this->E_multiplicavel(matriz))
		{
			if(this->E_quadrada() && matriz.E_quadrada())
			{
				Matriz<Tipo>* MatrizA = new Matriz();
				MatrizA = (*this) * matriz;
				Matriz<Tipo>* MatrizB = new Matriz();
				MatrizB = matriz * (*this);
				if(MatrizA == MatrizB)
				{
					MatrizA.Destroi();
					MatrizB.Destroi();
					delete MatrizA;
					delete MatrizB;
					return true;
				}
				MatrizA->Destroi();
				MatrizB->Destroi();
				delete MatrizA;
				delete MatrizB;
			}
		}
		return false;
	}
	bool E_oposta(Matriz matriz) const //verdadeiro se duas matrizes diferentes são opostas
	{
		if(this->linhas == matriz.linhas && this->colunas == matriz.colunas)
		{
			if(this->linhas == this->colunas && this->linhas == 1)
			{
				return (valores[0][0] == -matriz.valores[0][0]);
			}
			unsigned int k = 1;
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					if(this->valores[i][j] == -matriz.valores[i][j])
					{
						k++;
					}
				}
			}
			if(k == linhas * colunas)
			{
				return true;
			}
		}
		return false;
	}
	bool E_simetrica() const //é simetrica quando é igual a sua MatrizTransposta
	{
		Matriz MatrizTransposta = this->MatrizTransposta();
		bool verifica = (*this == MatrizTransposta);
		MatrizTransposta.Destroi();
		return verifica;
	}
	bool E_antissimetrica() const //é antissimetrica quando a MatrizTransposta é iagual a MatrizOposta
	{
		Matriz antisimetrica = this->MatrizTransposta();
		Matriz MatrizOposta = this->MatrizOposta();
		bool verifica = (antisimetrica == MatrizOposta);
		antisimetrica.Destroi();
		MatrizOposta.Destroi();
		return verifica;
	}
	bool E_linha() const //verdadeiro se matriz é linha
	{
		if(valores != NULL)
		{
			return (linhas == 1) && (colunas > 1);
		}
		return false;
	}
	bool E_coluna() const //verdadeiro se matriz é coluna
	{
		if(valores != NULL)
		{
			return (colunas == 1) && (linhas > 1);
		}
		return false;
	}
	bool E_quadrada() const //verdadeiro se matriz é quadrada
	{
		if(valores != NULL)
		{
			return linhas == colunas;
		}
		return false;
	}
	bool E_retangular() const //verdadeiro se matriz é retangular
	{
		return !E_quadrada();
	}
	bool E_nula() const //verdadeiro se todos os elementos da matriz são 0
	{
		unsigned int k = 1;
		if(linhas >= 1 && colunas >= 1)
		{
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					if(valores[i][j] == 0)
						k++;
				}
			}
			if(k == linhas * colunas)
				return true;
		}
		return false;
	}
	bool E_identidade() const //verdadeiro se somente os elementos da diagonal principal são 1 e damis 0
	{
		if(E_quadrada())
		{
			if(E_diagonal() && linhas >= 2)
			{
				unsigned contador = 1;
				for(unsigned int i = 0; i < linhas; i++)
				{
					if(valores[i][i] == 1)
					{
						contador++;
					}
				}
				return (contador == linhas - 1); //lógica alterada
			}
		}
		return false;
	}
	bool E_triangular() const //verdadeiro se os elementos abaixo ou acima da diagonal principasl são 0
	{
		if(E_quadrada() && linhas >= 2)
		{
			unsigned int comparador = (linhas * colunas - linhas) / 2;
			unsigned int conta_abaixo = 0;
			unsigned int conta_acima = 0;
			unsigned int conta_diagonal = 0;
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < i; j++)
				{
					if(valores[i][j] == 0)
					{
						conta_abaixo++;
					}
				}
			}
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = i; j < colunas; j++)
				{
					if(valores[i][j] == 0)
					{
						conta_acima++;
					}
				}
			}
			for(unsigned int i = 0; i < linhas; i++)
			{
				if(valores[i][i] != 0)
				{
					conta_diagonal++;
				}
			}
			return (conta_abaixo == comparador || conta_acima == comparador) && conta_diagonal != 0; //cuidar da lógica quando diagonal só possuir elementos nulos
		}
		return false;
	}
	bool E_diagonal() const //verdadeiro se os elementos da diagonal principal são quais quer números reais e demais 0
	{
		if(E_quadrada() && linhas >= 2)
		{
			unsigned int conta_abaixo = 0;
			unsigned int conta_abaixo_diferente = 0;
			unsigned int conta_acima = 0;
			unsigned int conta_acima_diferente = 0;
			unsigned int conta_diagonal = 0;
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = 0; j < i; j++)
				{
					if(valores[i][j] == 0)
					{
						conta_abaixo++;
					}
					else
					{
						conta_abaixo_diferente++;
					}
				}
			}
			for(unsigned int i = 0; i < linhas; i++)
			{
				for(unsigned int j = i; j < colunas; j++)
				{
					if(valores[i][j] == 0)
					{
						conta_acima++;
					}
					else
					{
						conta_abaixo_diferente++;
					}
				}
			}
			for(unsigned int i = 0; i < linhas; i++)
			{
				if(valores[i][i] != 0)
				{
					conta_diagonal++;
				}
			}
			if(conta_diagonal != 0 && conta_abaixo == conta_acima)
			{
				if(conta_abaixo_diferente == conta_acima_diferente && conta_abaixo_diferente == 0)
				{
					return true;
				}
			}//lógica corrigida!!!
		}
		return false;
	}
	Tipo TracoDaMatriz() const //soma dos elementos da diagonal principal
	{
		Tipo valor = -0;
		if(E_quadrada())
		{
			for(unsigned int i = 0; i < linhas; i++)
			{
				valor += valores[i][i];
			}
		}
		return valor;
	}
	unsigned long long int QuantidadeDeMemoriaBytes()
	{
		return linhas * colunas * sizeof(Tipo);
	}
	FilasParaChio<Tipo>* FilaParaChio(unsigned int pos_linha, unsigned int pos_coluna)//extrai fila para a regra de Chio
	{
		FilasParaChio<Tipo>* filasparachio = new FilasParaChio<Tipo>;
		if(E_quadrada() && linhas >= 4)
		{
			pos_linha -= 1;
			pos_coluna -= 1;
			unsigned int k = 0;
			filasparachio->linha = pos_linha;
			filasparachio->coluna = pos_coluna;
			filasparachio->largura = colunas - 1;
			filasparachio->array_da_linha = new Tipo[colunas - 1];
			filasparachio->array_da_coluna = new Tipo[linhas - 1];
			for(unsigned int j = 0; j < colunas; j++)
			{
				if(j != pos_coluna)
				{
					filasparachio->array_da_linha[k] = valores[pos_linha][j];
					k++;
				}
			}
			k = 0;
			for(unsigned int i = 0; i < linhas; i++)
			{
				if(i != pos_linha)
				{
					filasparachio->array_da_coluna[k] = valores[i][pos_coluna];
					k++;
				}
			}
		}
		return filasparachio;
	}
	Matriz<Tipo>* AbaixaOrdem() const //abaixa ordem até 3X3
	{
		if(E_quadrada())//tem que ser diferente de três
		{
			Matriz<Tipo>* regraA = FuncaoRegraDeChio(const_cast<Matriz<Tipo>*>(this));
			Matriz<Tipo>* regraAtemp = new Matriz<Tipo>;
			int i = regraA->Linhas() - 3;
			while(i > 0)
			{
				regraAtemp->Cria(i + 3, i + 3);
				regraAtemp = FuncaoRegraDeChio(regraA);
				regraA->Destroi();
				regraA->Cria(i + 2, i + 2);
				*regraA = *regraAtemp;
				regraAtemp->Destroi();
				i--;
			}
			delete regraAtemp;
			return regraA;
		}
		return NULL;
	}
	//bool MultiplicaFila(Fila fila, Tipo numero, unsigned int pos_linha, unsigned int pos_coluna)
	bool MultiplicaFila(Fila fila, Tipo numero, unsigned int origem)//multiplica fila
	{
		if(origem > 0 && origem <= linhas && E_quadrada())
		{
			origem -= 1;
			if(fila == LINHA)
			{
				for(unsigned int j = 0; j < colunas; j++)
				{
					valores[origem][j] *= numero;
				}
			}
			if(fila == COLUNA)
			{
				for(unsigned int i = 0; i < linhas; i++)
				{
					valores[i][origem] *= numero;
				}
			}
			return true;
		}
		return false;
	}
	Tipo* PegaFila(Fila fila, unsigned int origem)//retorna array com fila
	{
		Tipo* arraydafila;
		if(linhas > 0 && colunas > 0)
		{
			origem -= 1;
			if(fila == LINHA)
			{
				arraydafila = new Tipo[colunas];
				for(unsigned int j = 0; j < colunas; j++)
				{
					arraydafila[j] = valores[origem][j];
				}
			}
			if(fila == COLUNA)
			{
				arraydafila = new Tipo[linhas];
				for(unsigned int i = 0; i < linhas; i++)
				{
					arraydafila[i] = valores[i][origem];
				}
			}
			return arraydafila;
		}
		return NULL;
	}
	unsigned int Linhas() const  //retorna o número de linhas
	{
		return linhas;
	}
	unsigned int Colunas() const //retorna o número de colunas
	{
		return colunas;
	}
	Matriz<Tipo>* ForcaElementoUm(unsigned int* lin = NULL, unsigned int* col = NULL)//incluir decimais
	{
		Misto base;
		FilasParaChio<Tipo>* filas;
		Matriz<Tipo>* temp;
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int k = 0;
		unsigned int l = 0;
		float tipo = 0;
		bool acendeA = false;
		bool acendeB = false;
		for(i = 1; i <= colunas; i++)
		{
			for(j = 1; j <= linhas; j++)
			{
				filas = this->FilaParaChio(i, j);
				if(j != linhas && i != colunas)
				{
					for(l = 0; l < linhas - 1; l++)
					{
						tipo = 1 - static_cast<float>(valores[i - 1][j - 1]);
						if(filas->array_da_coluna[l] != 0)
						{
							tipo = (tipo / static_cast<float>(filas->array_da_coluna[l]));
						}
						else
						{
							tipo = 0;
						}
						if(Extract(tipo))
						{
							base.coeficiente = static_cast<int>(tipo);
							base.linha = i;
							base.coluna = j;
							base.linha_array = l + 1;
							if(lin != NULL && col != NULL)
							{
								*lin = i;
								*col = j;
							}
							temp = TeoremaDeJacobi(LINHA, base.linha_array + 1, base.linha, base.coeficiente);
							acendeA = true;
							break;
						}
					}
					if(acendeA)
					{
						delete[] filas->array_da_coluna;
						delete[] filas->array_da_linha;
						delete filas;
						break;
					}
					for(l = 0; l < colunas - 1; l++)
					{
						tipo = 1 - static_cast<float>(valores[i - 1][j - 1]);
						if(filas->array_da_linha[l] != 0)
						{
							tipo = (tipo / static_cast<float>(filas->array_da_linha[l]));
						}
						else
						{
							tipo = 0;
						}
						if(Extract(tipo))
						{
							base.coeficiente = static_cast<int>(tipo);
							base.linha = i;
							base.coluna = j;
							base.linha_array = l + 1;
							if(lin != NULL && col != NULL)
							{
								*lin = i;
								*col = j;
							}
							temp = TeoremaDeJacobi(COLUNA, base.linha_array + 1, base.coluna, base.coeficiente);
							acendeB = true;
							break;
						}
					}
					if(acendeB)
					{
						delete[] filas->array_da_coluna;
						delete[] filas->array_da_linha;
						delete filas;
						break;
					}
				}
				delete[] filas->array_da_coluna;
				delete[] filas->array_da_linha;
				delete filas;
				k++;
			}
			if(acendeA || acendeB)
			{
				break;
			}
		}
		return temp;
	}
};

template<class Dado>
Dado FuncaoRegraDeSarrus(Matriz<Dado>* matriz_sarrus)
{
	Dado retorno = -0;
	if(matriz_sarrus->linhas == matriz_sarrus->colunas && matriz_sarrus->linhas == 3)
	{
		Dado determinanteA = -0;
		Dado determinanteB = -0;
		Dado multiplicanteA = 1;
		Dado multiplicanteB = 1;
		Matriz<Dado> *matrizdeterminante = new Matriz<Dado>;
		matrizdeterminante->Cria(3, 5);
		for(short i = 0, k = 0; i < 3; i++)
		{
			for(short j = 0; j < 5; j++)
			{
				if(j < 3)
					matrizdeterminante->valores[i][j] = matriz_sarrus->valores[i][j];
				else
					matrizdeterminante->valores[i][j] = matriz_sarrus->valores[i][k++];
			}
			k = 0;
		}
		for(short i = 0; i < 5;)
		{
			if(i != 0)
				i -= 2;
			for(short j = 0; j < 3; j++)
			{
				multiplicanteA *= matrizdeterminante->valores[j][i];
				i++;
			}
			determinanteA += multiplicanteA;
			multiplicanteA = 1;
		}
		for(short i = 0; i < 5;)
		{
			if(i != 0)
				i -= 2;
			for(short j = 2; j >= 0; j--)
			{
				multiplicanteB *= matrizdeterminante->valores[j][i];
				i++;
			}
			determinanteB += multiplicanteB;
			multiplicanteB = 1;
		}
		matrizdeterminante->Destroi();
		delete matrizdeterminante;
		retorno = determinanteA - determinanteB;
	}
	return retorno;
}

template<class Dado>
Matriz<Dado>* FuncaoRegraDeChio(Matriz<Dado>* matriz_analise, unsigned int* lin = NULL, unsigned int* col = NULL)
{
	Matriz<Dado>* complementar = NULL;
	Elemento<Dado>* valor_encontado = matriz_analise->PesquisaElemento(1);
	FilasParaChio<Dado>* filas = NULL;
	if(valor_encontado->haumvalor())
	{
		complementar = matriz_analise->MenorComplementar(valor_encontado->linha, valor_encontado->coluna);
		filas = matriz_analise->FilaParaChio(valor_encontado->linha, valor_encontado->coluna);
		if(lin != NULL && col != NULL)
		{
			*lin = valor_encontado->linha;
			*col = valor_encontado->coluna;
		}
		if(!valor_encontado)
			delete valor_encontado;
		for(unsigned int i = 0; i < complementar->linhas; i++)
		{
			for(unsigned int j = 0; j < complementar->colunas; j++)
			{
				complementar->valores[i][j] -= filas->array_da_linha[j] * filas->array_da_coluna[i];
			}
		}
		delete[] filas->array_da_linha;
		delete[] filas->array_da_coluna;
		delete filas;
	}
	else
	{
		Matriz<Dado>* matriztemp = NULL;
		if(!valor_encontado)
			delete valor_encontado;
		Elemento<Dado>* valor_encontado = new Elemento<Dado>;
		matriztemp = matriz_analise->ForcaElementoUm(&valor_encontado->linha, &valor_encontado->coluna);
		valor_encontado->valor = 1;
		complementar = FuncaoRegraDeChio(matriztemp);
		matriztemp->Destroi();
		delete matriztemp;
	}
	return complementar;
}

int main(int argc, char** argv)
{
	Matriz<int> matrizA;
	Matriz<int> matrizB;
	matrizA.Cria(9, 9);
	matrizB.Cria(4, 4);
	int elementos_a[9][9] = {{3, 3, 7, 2, 9, -4, 3, 0, 2}, {1, 2, 5, 3, 2, 5, -8, 9, 3}, {1, 1, 8, 7, 3, 5, -8, 0, 5}, {1, 3, 7, 3, 4, -3, 7, -1, 1}, {0, 5, 2, 2, 1, -4, 9, 7, -8}, {1, 3, 0, 1, 2, -1, 3, 2, -4}, {0, 6, 7, 4, 7, 8, 0, 4, 3}, { -1, 0, 0, 8, 3, 5, -5, 4, 6}, { -8, 5, 7, -4, -7, 8, -2, 5, 1}};//19775392
	//int elementos_a[8][8] = {{1, 2, 5, 3, 2, 5, -8, 9}, {1, 1, 8, 7, 3, 5, -8, 0}, {1, 3, 7, 3, 4, -3, 7, -1}, {0, 5, 2, 2, 1, -4, 9, 7}, {1, 3, 0, 1, 2, -1, 3, 2}, {0, 6, 7, 4, 7, 8, 0, 4}, { -1, 0, 0, 8, 3, 5, -5, 4}, { -8, 5, 7, -4, -7, 8, -2, 5}};
	//int elementos_a[7][7] = {{1, 2, 5, 3, 2, 5, -8}, {1, 3, 7, 3, 4, -3, 7}, {0, 5, 2, 2, 1, -4, 9}, {1, 3, 0, 1, 2, -1, 3}, {0, 6, 7, 4, 7, 8, 0}, { -1, 0, 0, 8, 3, 5, -5}, { -8, 5, 7, -4, -7, 8, -2}};//110034
	//int elementos_a[5][5] = {{1, 2, 5, 3, 2}, {1, 3, 7, 3, 4}, {0, 5, 2, 2, 1}, {1, 3, 0, 1, 2}, {0, 6, 7, 4, 7}};
	//int elementos_a[6][6] = {{5, 7, 8, 3, 2, 6}, {8, 8, 9, 3, 5, 4}, {2, 7, 6, 4, 8, 4}, {7, 3, 9, 5, 9, 6}, {8, 2, 3, 4, 2, 8}, {3, 7, 5, 8, 4, 8}};
	//long long int elementos_a[6][6] = {{1, 1, 1, 1, 1, 1}, {2, 3, 4, 5, 6, 7}, {4, 9, 16, 25, 36, 49}, {8, 27, 64, 125, 216, 343}, {16, 34, 256, 625, 1296, 2401}, {32, 81, 1024, 3125, 7776, 16807}};
	//int elementos_b[4][4] = {{1, 1, 1, 1}, {2, 3, 4, 5}, {4, 9, 16, 25}, {8, 27, 64, 125}};//12 ok
	//int elementos_a[6][6] = {{0, 0, 0, 0, 0, 6}, {0, 0, 0, 0, 5, 0}, {0, 0, 0, 4, 0, 0}, {0, 0, 3, 0, 0, 0}, {0, 2, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}};
	//int elementos_b[4][4] = {{5, 8, 7, 3}, {2, 5, 9, 3}, {6, 7, 5, 4}, {3, 2, 8, 6}};
	int elementos_b[4][4] = {{1, 3, 2, 1}, {1, 0, -1, 5}, {4, 2, 1, 2}, {2, -1, 2, 0}};//-128
	//int elementos_b[4][4] = {{1, 2, 4, 7}, {2, 2, -1, 0}, { 3, 8, -2, -5}, { 4, -3, 6, 7}};//-584
	//int elementos_a[5][5] = {{1, 0, 0, 0, 0}, {0, 2, 0, 0, 0}, {0, 0, 3, 2, 0}, {0, 0, 1, 4, 0}, {0, 0, 0, 0, 5}};
	//int elementos_a[6][6] = {{0,0,0,0,0,6},{0,0,0,0,5,0},{0,0,0,4,0,0},{0,0,3,0,0,0},{0,2,0,0,0,0},{1,0,0,0,0,0}};
	//int elementos_a[5][5] = {{2, 3, -1, 0, 3}, {1, 4, 2, 1, 7}, {3, 2, 2, 0, 9}, { -1, 2, 3, 2, 0}, {3, 1, 1, 2, 4}};
	//int elementos_b[4][4] = {{3, -3, -4, 0}, {2, 5, 4, 3}, {-4, 0, 2, -2}, {-5, 3, 0, -4}};//-60 ok
	//int elementos_b[4][4] = {{2, 3, -1, 0}, {1, 4, 2, 1}, { 3, 2, 2, 0}, { -1, 2, 3, 2}};//23 ok
	//int elementos_b[4][4] = {{2, 3, 0, 2}, {1, 1, 2, 0}, { -1, 2, 2, 1}, {7, 5, 1, 2}};//-9
	//int elementos_a[2][3] = {{1, 2, 3}, {1, -1, 0}};
	//int elementos_b[3][4] = {{2, 3, 0, 2}, {1, 1, 2, 0}, { -1, 2, 2, 1}};
	//int elementos_c[6][6] = {{0,0,0,0,0,6},{0,0,0,0,5,0},{0,0,0,4,0,0},{0,0,3,0,0,0},{0,2,0,0,0,0},{1,0,0,0,0,0}};
	//int elementos_d[4][4] = {{2, 3, 0, 2}, {1, 1, 2, 0}, { -1, 2, 2, 1}, {7, 5, 1, 2}};
	//int elementos_e[3][3] = {{3, 5, 5}, {5, 0, 5}, { 5, 5, 4}};//d = 75 ok
	//int elementos_f[3][3] = {{4, 5, -3}, {2, 1, 0}, { 3, -1, 1}};//d = 9 ok
	//int elementos_g[3][3] = {{2, 1, -2}, {1, 3, 4}, { 2, 1, 2}};//d = 20 ok
	//int elementos_h[3][3] = {{1, 2, 4}, {3, 2, 1}, { 2, 0, 4}};//d = -28 ok
	for(unsigned int i = 0; i < matrizA.Linhas(); i++)
	{
		for(unsigned int j = 0; j < matrizA.Colunas(); j++)
		{
			matrizA.Altera(i + 1, j + 1, elementos_a[i][j]);
		}
	}
	for(unsigned int i = 0; i < matrizB.Linhas(); i++)
	{
		for(unsigned int j = 0; j < matrizB.Colunas(); j++)
		{
			matrizB.Altera(i + 1, j + 1, elementos_b[i][j]);
		}
	}
	matrizA.Mostra();
	Matriz<int>* regraA = matrizA.MatrizOposta();
	Matriz<int>* regraB = FuncaoRegraDeChio<int>(&matrizB);

	cout << "separaA" << endl;
	cout << regraA->RegraDeSarrus() << endl;
	regraA->Mostra();

	cout << "separaB" << endl;
	cout << regraB->RegraDeSarrus() << endl;
	regraB->Mostra();

	matrizA.Destroi();
	matrizB.Destroi();
	regraA->Destroi();
	regraB->Destroi();
	system("pause");
	return 0;
}

/*
private:
	void MenorComplementarRecursiva(unsigned int linha, unsigned int coluna, Matriz<Tipo>* matrizcof)
	{
		Matriz<Tipo>* matrizcofator = new Matriz<Tipo>;
		for(unsigned int i = 0; i < linhas; i++)
		{
			for(unsigned int j = 0; j < colunas; j++)
			{
				matrizcofator = MenorComplementar(i + 1, j + 1);
				if(matrizcofator->linhas > 3)
				{
					matrizcofator->MenorComplementarRecursiva(i, j, matrizcof);
				}
				if(matrizcofator->E_quadrada() && (matrizcofator->linhas == 2))
				{
					Tipo resultado = matrizcofator->RegraDeSarrus() * FuncaoPotenciaUm<Tipo>(i + j);
					matrizcof->AdicionaLinearmente(resultado);
					matrizcofator->Destroi();
					delete matrizcofator;
				}
				matrizcofator->Destroi();
				delete matrizcofator;
			}
		}
	}
	void MenorComplementarRecursiva2(Matriz<Tipo>* matrizcof)
	{
		if(this->linhas == this->colunas && this->colunas > 4)
		{
			--this->linhas;
			--this->colunas;
		}
		Matriz<Tipo>* matrizcofator = new Matriz<Tipo>;
		for(unsigned int i = 1; i <= this->linhas; i++)
		{
			for(unsigned int j = 1; j <= this->colunas; j++)
			{
				matrizcofator = this->MenorComplementar(i, j);
				cout << endl;
				matrizcofator->Mostra();
				cout << endl;
				if(matrizcofator->linhas > 3)
				{
					matrizcofator->MenorComplementarRecursiva2(matrizcof);
				}
				if(matrizcofator->linhas == 3)
				{
					cout << "esta";
					cout << endl;
					cout << matrizcof->AdicionaLinearmente(matrizcofator->RegraDeSarrus() * FuncaoPotenciaUm<Tipo>(i + j));
				}
				matrizcofator->Destroi();
				delete matrizcofator;
			}
		}
	}
*/
