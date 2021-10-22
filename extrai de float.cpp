//code to extract the float binary parts
#include <iostream>
#include <math.h>
#include <basetsd.h>
//#define pos_inf 0x7F800000
//#define neg_inf 0xFF800000
//#define nan 0xFF800000

//UINT64_MAX

using namespace std;

static void extract_float_partes(float& value)
{
	float valuec1 = value;
	float valuec2 = value;
	float valuec3 = value;

	unsigned int* point = (unsigned int*)&valuec1;
	unsigned int mask = 0x80000000;
	*point = *point & mask;
	*point >>= 31;
	bool signal = *point ? true : false;
	int exponent = 0;
	int mantissa = 0;
	int inteira = 0;
	int fracionaraia = 0;

	mask = 0x7F800000;
	point = (unsigned int*)&valuec2;
	*point = *point & mask;
	*point >>= 23;
	exponent = *point - 127;

	mask = 0X7FFFFF;
	point = (unsigned int*)&valuec3;
	*point = *point & mask;
	mantissa = *point ;

	cout << signal << endl;
	cout << exponent << endl;
	cout << mantissa << endl;

	mask = 0x800000;
	inteira = mantissa;
	inteira |= mask;

	if(exponent > 0)
		inteira >>= (23 - exponent);
	else
		return;
	cout << inteira << endl;

	fracionaraia = mantissa;
	float partef = 0;
	int mask2 = (int)pow(2 , 23 - exponent - 1);
	for(int i = (23 - exponent) - 1, k = 1; i >= 0; i--)
	{
		partef += ((fracionaraia & mask2) >> i) / (float)pow(2, k);
		k++;
		mask2 >>= 1;
	}
	cout << partef << endl;
	cout << value << endl;
}

static bool extract_float(const float& value)
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
	//point = (unsigned int*)&value1;
	*point = *point & mask;
	*point >>= 23;
	if(*point == 255)//is impossible
	{
		return false;
	}
	exponent = *point - 127;
	mask = 0X7FFFFF;
	point = reinterpret_cast<unsigned int*>(&value2);
	//point = (unsigned int*)&value2;
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
	//mask2 = (int)pow(2 , 23 - exponent-1);
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

static void extract_double_partes(double& value)
{
	double valuec1 = value;
	double valuec2 = value;
	double valuec3 = value;

	unsigned long long* point = (unsigned long long*)&valuec1;
	unsigned long long mask = 0x8000000000000000ULL;
	*point = *point & mask;
	*point >>= 63;
	bool signal = *point ? true : false;
	unsigned long long exponent = 0;
	unsigned long long mantissa = 0;
	unsigned long long inteira = 0;
	unsigned long long fracionaraia = 0;

	mask = 0x7FF0000000000000ULL;
	point = (unsigned long long*)&valuec2;
	*point = *point & mask;
	*point >>= 52;
	exponent = *point - 1024;

	mask = 0XFFFFFFFFFFFFFULL;
	point = (unsigned long long*)&valuec3;
	*point = *point & mask;
	mantissa = *point ;

	cout << "signal " << signal << endl;
	cout << "exponent " << exponent << endl;
	cout << "mantissa " << mantissa << endl;

	mask = 0x8000000000000ULL;
	inteira = mantissa;
	inteira |= mask;

	if(exponent > 0)
		inteira >>= (52 - exponent);
	else
		return;
	cout << "interger " << inteira << endl;

	fracionaraia = mantissa;
	double partef = 0;
	unsigned long long mask2 = (unsigned long long)pow(2 , 52 - exponent - 1);
	for(int i = (52 - exponent) - 1, k = 1; i >= 0; i--)
	{
		partef += ((fracionaraia & mask2) >> i) / pow(2, k);
		k++;
		mask2 >>= 1;
	}
	cout << "frac " << partef << endl;
	cout << "value " << value << endl;
}

static bool extract_double(const double &value)
{
	if(value == 1.0 || value == -1.0 || value == 0.0)
		return true;
	long long exponent = 0;
	long long mantissa = 0;
	long long inteira = 0;
	long long fracionaraia = 0;
	double partef = 0;
	double value1 = value;
	double value2 = value;
	unsigned long long * point;
	unsigned long long mask = 0x7FF0000000000000ULL;
	unsigned long long mask2 = 0;
	point = reinterpret_cast<unsigned long long*>(&value1);
	*point = *point & mask;
	*point >>= 52;
	if(*point == 2047)//is impossible
	{
		return false;
	}
	exponent = *point - 1023;//mechido
	mask = 0XFFFFFFFFFFFFFULL;
	point = reinterpret_cast<unsigned long long*>(&value2);
	*point = *point & mask;
	mantissa = *point ;
	mask = 0x8000000000000ULL;
	inteira = mantissa;
	inteira |= mask;
	if(exponent > 0)
		inteira >>= (52 - exponent);
	else
		return false;
	fracionaraia = mantissa;
	mask2 = static_cast<unsigned long long>(pow(2 , 52 - exponent - 1));
	for(int i = (52 - exponent) - 1, k = 1; i >= 0; i--)
	{
		partef += ((fracionaraia & mask2) >> i) / (pow(2, k));
		k++;
		mask2 >>= 1;
	}
	if(partef == 0.0)
		return true;
	return false;
}

int main(int argc, char** argv)
{
	cout << sizeof(unsigned long long) << endl;
	cout << sizeof(long double) << endl;
	double valor = 0;
	int i = 0;
	cin >> valor;
	extract_double_partes(valor);
	cin.ignore();
	while(i < 10)
	{
		cin >> valor;
		if(extract_double(valor))
		{
			cout << "inteiro" << endl;
		}
		else
		{
			cout << "nao inteiro" << endl;
		}
		cout << "verdadeiro" << valor << endl;
		i++;
	}
	return 0;
}
