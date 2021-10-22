#define BEGN_EXTERN_CPP extern "C++" {
#define END_EXTERN_CPP }

BEGN_EXTERN_CPP

#include <cstdlib>
#include <iostream>
#include <bitset>
#include <string.h>
#include <math.h>
#include <time.h>

using std::bitset;
using std::string;
#ifdef _GLIBCXX_IOSTREAM
using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::endl;
#endif

class int512 //signed and big endian;
{
private:
	bool binsum(bool bita, bool bitb);
	bool binsub(bool bita, bool bitb);
public:
	bitset<512> bits;
	int512();
	int512(const long long int &value);
	~int512();
	friend int512 mod512(int512 value);
	friend int512 neg512(int512 value);
	bool operator==(const int512 &value);
	bool operator!=(const int512 &value);
	bool operator>(const int512 &value);
	bool operator<(const int512 &value);
	bool operator>=(const int512 &value);
	bool operator<=(const int512 &value);
	bool operator!();
	bool operator[](int index);
	int512 operator&(const int512 &value);
	int512 operator|(const int512 &value);
	int512 operator=(const int512 &value);
	int512 operator=(const long long int &value);
	int512 operator+(const int512 &value);
	int512 operator+(const long long int &value);
	int512 operator+=(const int512 &value);
	int512 operator+=(const long long int &value);
	int512 operator++();
	int512 operator++(int);
	int512 operator-(const int512 &value);
	int512 operator-(const long long int &value);
	int512 operator-=(const int512 &value);
	int512 operator-=(const long long int &value);
	int512 operator--();
	int512 operator--(int);
	int512 operator*(int512 &value);
	int512 operator*=(int512 &value);
	int512 operator/(int512 &value);
	int512 operator%(int512 &value);
	int512 operator<<(unsigned short value);
	int512 operator>>(unsigned short value);
	int512 operator<<=(unsigned short value);
	int512 operator>>=(unsigned short value);
	int512 operator~();
	int512 operator^(const int512 &value);
#ifdef _GLIBCXX_IOSTREAM
	friend ostream &operator<<(ostream &output, int512 &value);
	friend istream &operator>>(istream &input, int512 &value);
#endif
	int512 ConvertToint512(const long long int &value);
	void InvertSignal();
	bool Signal();
	short BitsLenght(void);
	long long int ConvertToLongLongInt(void);
	string ConvertToStringBin(void);
	bool ConvertToBool(void);
};
bool int512::binsum(bool bita, bool bitb)
{
	if(bita && bitb)
		return false;
	else if(!bita && !bitb)
		return false;
	else if(bita || bitb)
		return true;
	return false;
}
bool int512::binsub(bool bita, bool bitb)
{
	if(bita && bitb)
		return false;
	else if(!bita && !bitb)
		return false;
	else if(bita && !bitb)
		return true;
	else if(!bita && bitb)
		return true;
	return false;
}
int512::int512()
{
	this->bits.reset();
}
int512::int512(const long long int &value)
{
	*this = ConvertToint512(value);
}
int512::~int512()
{
	//destrutor
}
bool int512::operator==(const int512 &value)
{
	short bitpos = 0;
	short comp = 0;
	while(bitpos < 511)
	{
		if(this->bits[bitpos]  == value.bits[bitpos])
			comp++;
		bitpos++;
	}
	if(bitpos == comp && this->bits[511] == value.bits[511])
		return true;
	return false;
}
bool int512::operator!=(const int512 &value)
{
	return !(this->bits == value.bits);
}
bool int512::operator>(const int512 &value)
{
	if(this->bits == value.bits)
		return false;
	else if(this->bits[511] == 0 && value.bits[511] == 1)
		return true;
	else if(this->bits[511] == 1 && value.bits[511] == 0)
		return false;
	else //if(this->bits[511] == 1or0 && value.bits[511] == 1or0)
	{
		short bitpos = 510;
		short lenghta = 0;
		short lenghtb = 0;
		while(bitpos >= 0)
		{
			if(this->bits[bitpos] == 1 && lenghta == 0)
				lenghta = bitpos;
			if(value.bits[bitpos] == 1 && lenghtb == 0)
				lenghtb = bitpos;
			bitpos--;
		}
		if(lenghta > lenghtb)
			return true;
		if(lenghta == lenghtb)
		{
			bitpos = lenghta > lenghtb ? lenghta : lenghtb;
			while(bitpos >= 0)
			{
				--bitpos;
				if(this->bits[bitpos] == 1 && value.bits[bitpos] == 0)
					return true;
				else if(this->bits[bitpos] == 0 && value.bits[bitpos] == 1)
					return false;
				else
					continue;
			}
		}
	}
	return false;
}
bool int512::operator<(const int512 &value)
{
	return !(*this > value);
}
bool int512::operator>=(const int512 &value)
{
	return (*this > value) || (*this == value);
}
bool int512::operator<=(const int512 &value)
{
	return (*this < value) || (*this == value);
}
bool int512::operator!()
{
	return !this->ConvertToBool();
}
bool int512::operator[](int index)
{
	return bits[index];
}
int512 int512::operator&(const int512 &value)
{
	int512 numtoreturn;
	short bitpos = 0;
	while(bitpos < 512)
	{
		numtoreturn.bits[bitpos] = this->bits[bitpos] && value.bits[bitpos];
		bitpos++;
	}
	return numtoreturn;
}
int512 int512::operator|(const int512 &value)
{
	int512 numtoreturn;
	short bitpos = 0;
	while(bitpos < 512)
	{
		numtoreturn.bits[bitpos] = this->bits[bitpos] || value.bits[bitpos];
		bitpos++;
	}
	return numtoreturn;
}
int512 int512::operator=(const int512 &value)
{
	short bitpos = 0;
	while(bitpos < 512)
	{
		this->bits[bitpos] = value.bits[bitpos];
		bitpos++;
	}
	return *this;
}
int512 int512::operator=(const long long int &value)
{
	return *this = ConvertToint512(value);
}
int512 int512::operator+(const int512 &value)
{
	int512 result;
	int512 carry;
	short bitpos = 0;
	while(bitpos < 512)
	{
		if(carry.bits[bitpos])
		{
			if(this->bits[bitpos] && value.bits[bitpos])
			{
				bool temp = binsum(carry.bits[bitpos], this->bits[bitpos]);
				carry.bits[bitpos + 1] = 1;
				result.bits[bitpos] = binsum(temp, value.bits[bitpos]);
			}
			else if(this->bits[bitpos] || value.bits[bitpos])
			{
				bool temp = binsum(carry.bits[bitpos], this->bits[bitpos]);
				carry.bits[bitpos + 1] = 1;
				result.bits[bitpos] = binsum(temp, value.bits[bitpos]);
			}
			else if(!this->bits[bitpos] && !value.bits[bitpos])
			{
				bool temp = binsum(carry.bits[bitpos], this->bits[bitpos]);
				carry.bits[bitpos + 1] = 0;
				result.bits[bitpos] = binsum(temp, value.bits[bitpos]);
			}
		}
		else
		{
			result.bits[bitpos] = binsum(this->bits[bitpos], value.bits[bitpos]);
			carry.bits[bitpos + 1] = this->bits[bitpos] && value.bits[bitpos] ? 1 : 0;
		}
		bitpos++;
	}
	return result;
}
int512 int512::operator+(const long long int &value)
{
	return *this + ConvertToint512(value);
}
int512 int512::operator+=(const int512 &value)
{
	return *this = *this + value;
}
int512 int512::operator+=(const long long int &value)
{
	return *this = *this + ConvertToint512(value);
}
int512 int512::operator++()
{
	return *this = *this + 1;
}
int512 int512::operator++(int)
{
	static short used = 0;
	if(used == 0)
	{
		used++;
		return *this + 1;
	}
	else
	{
		used = 0;
		return *this = *this + 2;
	}
}
int512 int512::operator-(const int512 &value)
{
	int512 copybits;
	int512 carry;
	short bitpos = 0;
	while(bitpos < 511)
	{
		if(!this->bits[bitpos] && !value.bits[bitpos])
		{
			if(carry.bits[bitpos])
			{
				bool temp = binsub(this->bits[bitpos], carry.bits[bitpos]);
				carry.bits[bitpos + 1] = 1;
				copybits.bits[bitpos] = binsub(temp, value.bits[bitpos]);
			}
			else
			{
				copybits.bits[bitpos] = binsub(this->bits[bitpos], value.bits[bitpos]);
			}
		}
		if(this->bits[bitpos] && value.bits[bitpos])
		{
			if(carry.bits[bitpos])
			{
				bool temp = binsub(this->bits[bitpos], carry.bits[bitpos]);
				copybits.bits[bitpos] = binsub(temp, value.bits[bitpos]);
				carry.bits[bitpos + 1] = 1;
			}
			else
			{
				copybits.bits[bitpos] = binsub(this->bits[bitpos], value.bits[bitpos]);
			}
		}

		if(this->bits[bitpos] && !value.bits[bitpos])
		{
			if(carry.bits[bitpos])
			{
				bool temp = binsub(this->bits[bitpos], carry.bits[bitpos]);
				copybits.bits[bitpos] = binsub(temp, value.bits[bitpos]);
			}
			else
			{
				copybits.bits[bitpos] = binsub(this->bits[bitpos], value.bits[bitpos]);
			}
		}

		if(!this->bits[bitpos] && value.bits[bitpos])
		{
			if(carry.bits[bitpos])
			{
				bool temp = binsub(this->bits[bitpos], carry.bits[bitpos]);
				carry.bits[bitpos + 1] = 1;
				copybits.bits[bitpos] = binsub(temp, value.bits[bitpos]);
			}
			else
			{
				carry.bits[bitpos + 1] = 1;
				copybits.bits[bitpos] = binsub(this->bits[bitpos], value.bits[bitpos]);
			}
		}
		bitpos++;
	}
	return copybits;
}
int512 int512::operator-(const long long int &value)
{
	return *this - ConvertToint512(value);
}
int512 int512::operator-=(const int512 &value)
{
	return *this = *this - value;
}
int512 int512::operator-=(const long long int &value)
{
	return *this = *this - ConvertToint512(value);
}
int512 int512::operator--()
{
	return *this = *this - 1;
}
int512 int512::operator--(int)
{
	static short used = 0;
	if(used == 0)
	{
		used++;
		return *this - 1;
	}
	else
	{
		used = 0;
		return *this = *this - 2;
	}
}
int512 int512::operator*(int512 &value)
{
	if(this == 0 || &value == 0)
		return 0;
	int512 result;
	int512 valuea = *this;
	int512 valueb = value;
	int512 auxvalue;
	if(valuea.Signal() || valueb.Signal())
	{
		if(valuea.Signal())
			valuea.InvertSignal();
		if(valueb.Signal())
			valueb.InvertSignal();
	}
	short contb = valueb.BitsLenght();
	short k = 0;
	for(; k < contb; k++)
	{
		if(valueb.bits[k])
		{
			auxvalue = valuea << k;
			result += auxvalue;
			auxvalue = 0;
		}
	}
	if(Signal() && value.Signal())
		return result;
	if(Signal() || value.Signal())
		result.InvertSignal();
	return result;
}
int512 int512::operator*=(int512 &value)
{
	return *this = *this * value;
}
int512 int512::operator/(int512 &value)
{
	int512 quociente = 0;
	if(*this == 0)
	{
		return quociente;
	}
	if(*this == value)
	{
		return quociente = 1;
	}
	if(*this > value)
	{
		int512 subdividendo = *this;
		int512 divisor = value;
		short bitsdividendo = subdividendo.BitsLenght();
		short bitsdivisor = divisor.BitsLenght();
		short diff = bitsdividendo - bitsdivisor;
		subdividendo = subdividendo >> diff;
		while(diff > 0)
		{
			if(subdividendo >= divisor)
			{
				quociente.bits[0] = 1;
				quociente <<= 1;
				subdividendo = subdividendo - divisor;
				subdividendo <<= 1;
				subdividendo.bits[0] = this->bits[diff - 1];
			}
			else
			{
				quociente.bits[0] = 0;
				quociente <<= 1;
				subdividendo <<= 1;
				subdividendo.bits[0] = this->bits[diff - 1];
			}
			diff--;
		}
		if(diff == 0 && subdividendo >= divisor)
		{
			quociente.bits[0] = 1;
			subdividendo = subdividendo - divisor;
		}
	}
	return quociente;
}
int512 int512::operator%(int512 &value)
{
	int512 quociente = 0;
	if(*this == 0)
	{
		return quociente;
	}
	if(*this == value)
	{
		return quociente = 0;
	}
	if(*this > value)
	{
		int512 subdividendo = *this;
		short bitsdividendo = subdividendo.BitsLenght();
		short bitsdivisor = value.BitsLenght();
		short diff = bitsdividendo - bitsdivisor;
		subdividendo = subdividendo >> diff;
		while(diff > 0)
		{
			if(subdividendo >= value)
			{
				subdividendo = subdividendo - value;
				subdividendo <<= 1;
				subdividendo.bits[0] = this->bits[diff - 1];
			}
			else
			{
				subdividendo <<= 1;
				subdividendo.bits[0] = this->bits[diff - 1];
			}
			diff--;
		}
		if(diff == 0 && subdividendo >= value)
		{
			subdividendo = subdividendo - value;
		}
		quociente = subdividendo;
	}
	return quociente;
}
int512 int512::operator<<(unsigned short value)
{
	int512 temp;
	short i = 0;
	while(i + value < 512)
	{
		temp.bits[i + value] = this->bits[i];
		i++;
	}
	return temp;
}
int512 int512::operator>>(unsigned short value)
{
	int512 temp;
	short i = 511;
	while(i - value >= 0)
	{
		temp.bits[i - value] = this->bits[i];
		i--;
	}
	return temp;
}
int512 int512::operator<<=(unsigned short value)
{
	return *this = *this << value;
}
int512 int512::operator>>=(unsigned short value)
{
	return *this = *this >> value;
}
int512 int512::operator~()
{
	int512 valuecopy;
	short bitpos = 511;
	while(bitpos >= 0)
	{
		if(this->bits[bitpos])
			valuecopy.bits[bitpos] = 0;
		else
			valuecopy.bits[bitpos] = 1;
		bitpos--;
	}
	return valuecopy;
}
int512 int512::operator^(const int512 &value)
{
	int512 copy;
	short bitpos = 0;
	while(bitpos < 512)
	{
		if(this->bits[bitpos] && value.bits[bitpos])
			copy.bits[bitpos] = 0;
		else if(!this->bits[bitpos] && !value.bits[bitpos])
			copy.bits[bitpos] = 0;
		else
			copy.bits[bitpos] = 1;
		bitpos++;
	}
	return copy;
}
#ifdef _GLIBCXX_IOSTREAM
ostream &operator<<(ostream &output, int512 &value)
{
	output << value.ConvertToLongLongInt();
	return output;
}
istream &operator>>(istream &input, int512 &value)
{
	long long int val;
	input >> val;
	value = val;
	return input;
}
#endif
int512 int512::ConvertToint512(const long long int &numbertoconvert)
{
	int512 copy;
	if(numbertoconvert == 0)
		return copy;
	long long int extra = 0;
	long long int mask = 1;
	short i = 0;
	while(i < short(8 * sizeof(long long int)))
	{
		extra = numbertoconvert & mask;
		mask = mask << 1;
		extra = extra >> i;
		copy.bits[i] = extra;
		i++;
	}
	bool signal = numbertoconvert < 0;
	if(signal)
	{
		i = copy.BitsLenght();
		while(i < 512)
		{
			copy.bits[i] = 1;
			i++;
		}
	}
	return copy;
}
void int512::InvertSignal()
{
	if(this->bits == 0)
		return;
	if(this->bits[511])
		*this = ++(~(*this));
	else
		*this = ~(--(*this));
}
bool int512::Signal()
{
	return this->bits[511];
}
short int512::BitsLenght(void)
{
	short bitslenght = 510;
	while(!this->bits[511] ? !this->bits[bitslenght] : this->bits[bitslenght])
	{
		if(bitslenght == 0)
			break;
		bitslenght--;
	}
	return bitslenght += 1;
}
long long int int512::ConvertToLongLongInt(void)
{
	if(BitsLenght() > 64)
		return 0;
	long long int valueexit = 0;
	short i = 0;
	long long int extra = 0;
	//long long int mask = 1;
	while(i < short(8 * sizeof(long long int)))
	{
		extra = this->bits[i];
		extra = extra << i;
		valueexit = valueexit | extra;
		i++;
	}
	if(this->bits[i])
	{
		extra = this->bits[i];
		extra = extra << i;
		valueexit = valueexit | extra;
	}
	return valueexit;
}
string int512::ConvertToStringBin(void)
{
	string stringretun;
	if(this->Signal())
		return stringretun = this->bits.to_string();
	short bitslenght = BitsLenght();
	short i = 0;
	short k = 0;
	char stringblock[bitslenght + 1];
	char stringformat[bitslenght + 1];
	while(k < bitslenght)
	{
		stringblock[k] = char(48 + this->bits[k]);
		k++;
	}
	stringblock[bitslenght] = '\0';
	stringformat[bitslenght] = '\0';
	while(k > 0)
	{
		stringformat[i] = stringblock[k - 1];
		k--;
		i++;
	}
	stringretun = stringformat;
	return  stringretun;
}
bool int512::ConvertToBool(void)
{
	short bitpos = 0;
	while(bitpos < 512)
	{
		if(this->bits[bitpos])
			return true;
		bitpos++;
	}
	if(bitpos == 512)
		return false;
	return false;
}
int512 neg512(int512 value)
{
	if(value.Signal())
		return value;
	else
	{
		value.InvertSignal();
		return value;
	}
	return false;
}
int512 mod512(int512 value)
{
	if(value.Signal())
	{
		value.InvertSignal();
		return value;
	}
	else
		return value;
}
int512 rand512(time_t seed)
{
	int512 copy;
	int512 move;
	move = 1;
	short i = 1;
	while(i != 512)
	{
		srand(i * seed);
		move = (unsigned char)(rand() % 255);
		move = move << i - 1;
		copy += move;
		i *= 8;
	}
	return copy;
}
int512 ConvertToint512(const long long int &value)
{
	int512 retorno;
	return retorno = retorno.ConvertToint512(value);
}

int main(int argc, char** argv)
{
	int512 number1;
	int512 number2;
	int512 number3;
	int512 number4;
	int512 number5;
	int512 number6;
	int512 number7;
	int512 number8;
	int512 number9;
	number1 = 54545465;
	number2 = 454578;
	number3 = number1 + number2;
	number4 = number1 - number2;
	number5 = number1 * number2;
	number1 = 5454546546566594ll;
	number2 = 454578;
	number6 = number1 / number2;
	number7 = ~number1;
	number8 = rand512(time(NULL));
	cout << number1 << endl;
	cout << number2 << endl;
	cout << number3 << endl;
	cout << number4 << endl;
	cout << number5 << endl;
	cout << number6 << endl;
	cout << number7 << endl;
	number7 = number1 % number2;
	cout << "resto " << number7 << endl;;
	cout << number8.ConvertToStringBin() << endl;
	cout << number9[3];
	return 0;
}
END_EXTERN_CPP