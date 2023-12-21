#define _CRT_SECURE_NO_WARNINGS
#define BASE_SIZE (sizeof(BASE)*8)
#define MAX_VAL (USHRT_MAX)

#include <iostream>
#include <ctime>
#include <stdbool.h>
#include <string.h>
#include <type_traits> 
#include <string>
#include <bitset>
#include <algorithm>
#include <tuple>
#include <vector>
#include <map>

using namespace std;
typedef unsigned char BASE;
typedef unsigned short DBASE;

class BigNum {
	int len, maxlen;
	BASE* coef;
public:
	BigNum(); // constructor
	BigNum(const BASE);
	BigNum(int size, bool flag = false); // constructor
	BigNum(const BigNum&); // copy constructor

	~BigNum() { // destructor
		if (coef) delete[] coef; coef = NULL;
	}

	void NormalLen() {
		for (len = maxlen; coef[len - 1] == 0 && len > 0; len--);
		if (len == 0) len = 1;
	}

	BigNum& operator = (const BigNum&);
	bool operator == (const BigNum&);
	bool operator != (const BigNum&);
	bool operator < (const BigNum&) const;
	bool operator <= (const BigNum&);
	bool operator > (const BigNum&);
	bool operator >= (const BigNum&);

	friend istream& operator >> (istream&, BigNum&); // input 16
	friend ostream& operator << (ostream&, BigNum&); // output 16

	BigNum operator + (const BigNum&);
	BigNum& operator +=(const BigNum&);
	BigNum operator + (const BASE);
	BigNum& operator +=(const BASE);

	BigNum operator -(const BigNum&);
	BigNum& operator -=(const BigNum&);
	BigNum operator - (const BASE);
	BigNum& operator -=(const BASE);

	BigNum operator *(const BASE);
	BigNum& operator *=(const BASE);
	BigNum operator *(const BigNum&);
	BigNum& operator *=(const BigNum&);

	BigNum operator /(const BASE);
	BigNum& operator /=(const BASE);
	BigNum operator /(const BigNum&);
	BigNum& operator /=(const BigNum&);

	BigNum operator %(const BASE);
	BigNum& operator %=(const BASE);
	BigNum operator %(const BigNum&);
	BigNum& operator %=(const BigNum&);

	BigNum normalPow(const BigNum&);
	BigNum pow(const BigNum&, const BigNum&);

	void Input();
	void Output();

	BigNum sqrt();
	BigNum nsqrt(const BASE);

	BigNum alway_meth();
	BigNum raiseToThePowerTwo();
	BigNum raiseToThePower(int);
	BigNum module(const BigNum&, const BigNum&);

	BigNum eulerTotient();
	bool fermatTest(int);
	bool solovStrassenTest(int);

	vector<BigNum> small_devisor();

	tuple<BigNum,BigNum> f3rma();

	BigNum floyd(BigNum);
	BigNum gcd(BigNum, BigNum);
	BigNum polard1();

	BigNum log(BigNum);
	BigNum polard2();

	BigNum gelfond(BigNum, BigNum);

	BigNum inv(BigNum);
	BigNum polard3(BigNum, BigNum);

};

//---------------------

BigNum BigNum::normalPow(const BigNum& y) {
	if (y.len == 1 && y.coef[0] == 0)
	{
		BigNum result;
		result += 1;
		return result;
	}

	BigNum result(*this);
	if (y.len == 1 && y.coef[0] == 1) return result;
	if (y.len == 1 && y.coef[0] == 2) return result.raiseToThePowerTwo();

	BigNum mask = y;
	int n = 0;

	while (mask.len > 1 || mask.coef[0] != 0)
	{
		mask = mask / 2;
		n++;
	}

	for (int i = n - 2; i >= 0; i--)
	{
		result = result.raiseToThePowerTwo();
		if ((1 << (i % BASE_SIZE)) & y.coef[i / BASE_SIZE]) result = (result * *this);
	}

	return result;
}

//---------------------
BigNum BigNum::sqrt()
{
        BigNum x(*this), x0;
        do
        {
                x0 = x;
                x = (*this / x + x) / 2;
        } while (x < x0);
        return x0;
}

BigNum BigNum::nsqrt(BASE n) {
	BigNum x(*this), x0;
	do
	{
		x0 = x;
		x = (((*this) / x.raiseToThePower(n - 1)) + (x * (n - (BASE)1))) / n;
	} while (x < x0);
	return x0;
}

BigNum BigNum::alway_meth()
{
	BigNum n(*this);

	if (n % (BASE)2 == (BASE)0) {
		std::cout << "even number" << endl;
		return (BASE)0;
	} 

	BigNum d = n.nsqrt((BASE)3) * (BASE)2 + (BASE)1;

	if(d % (BASE)2 == (BASE)0) {
		d += (BASE)1;
	}

	if(fermatTest(10)) {
		return *this;
	}

	BigNum r;
	BigNum r1 = n % d;
	BigNum r2 = n % (d - (BASE)2);
	BigNum q = ((n / (d - (BASE)2)) - (n / d)) * (BASE)4;
	BigNum s = n.sqrt();

	while(true) 
	{
		d += (BASE)2;

		if(d > s) {
			std::cout << "there is no devisor" << std::endl;
			return BASE(0);
		}

		if ((r1 * BASE(2) + q) >= r2) {
			r = r1 * BASE(2) + q - r2;
		}
		else {
			r = r1 * BASE(2) + q + d - r2;
			q += BASE(4);
		}

		r2 = r1;
		r1 = r;

		if(r1 < (BASE)0) {
			r1 += d;
			q += (BASE)4;
		}

		while(r1 >= d) {
			r1 -= d;
			q -= (BASE)4;
		}

		if(r1 == (BASE)0) {
			return d;
		}
	}
}

tuple<BigNum,BigNum> BigNum::f3rma() {
	BigNum n(*this);

	if(fermatTest(10)) {
		cout << "n - primal" << endl;
		return make_tuple(n, (BASE)0);
	}

	if (n % (BASE)2 == (BASE)0) {
		std::cout << "even number" << endl;
		return make_tuple((BASE)0, (BASE)0);
	} 

	BigNum x = n.sqrt();
	if(x.raiseToThePowerTwo() == n) {
		return make_tuple(x,x);
	} 

	BigNum z, y;

	while(true) {
		x += (BASE)1;
		if(x == ((n + (BASE)1)/(BASE)2)) {
			cout << "n - primal" << endl;
			return make_tuple((BASE)0, n);
		} 
		else {
			z = x.raiseToThePowerTwo() - n;
			y = z.sqrt();
		}

		if(y.raiseToThePowerTwo() == z) {
			return make_tuple(x - y, x + y);
			}
	}
}


BigNum BigNum::pow(const BigNum& y, const BigNum& mod) {
	if (mod.len == 1 && mod.coef[0] < 2)
	{
		BigNum result;
		return result;
	}

	if (y.len == 1 && y.coef[0] == 0)
	{
		BigNum result;
		result += 1;
		return result;
	}

	BigNum result(*this);
	if (y.len == 1 && y.coef[0] == 1) return result % mod;
	if (y.len == 1 && y.coef[0] == 2) return result.raiseToThePowerTwo() % mod;

	BigNum mask = y;
	int n = 0;

	while (mask.len > 1 || mask.coef[0] != 0)
	{
		mask = mask / 2;
		n++;
	}

	for (int i = n - 2; i >= 0; i--)
	{
		result = result.raiseToThePowerTwo() % mod;
		if ((1 << (i % BASE_SIZE)) & y.coef[i / BASE_SIZE]) result = (result * *this) % mod;
	}

	return result;
}

BigNum BigNum::eulerTotient() {
	BigNum n = *this;

	//Iterating till the sqaure root of 'n'
	for (BigNum i((BASE)2); i*i <= n; i += (BASE)1) {

		//If 'i' is a factor of 'n'
		if (n % i == BigNum((BASE)0)) {
			while (n % i == BigNum((BASE)0)) {
				n /= i;
			}
			*this -= *this / i;
		}
	}
	if (n > 1) {
		*this -= *this / n;
	}

	return *this;
}

bool BigNum::fermatTest(int t) {
	if (*this == BigNum((BASE)3) || *this == BigNum((BASE)2)) {
		return true;
	}
	
	if (*this% BigNum((BASE)2) == BigNum((BASE)0)) {
		return false;
	}

	while (t > 0) {
		BigNum a(len, 1);
		if (BigNum((BASE)2) > a || a > *this - BigNum((BASE)2)) {
			continue;
		}

		BigNum r = a.pow(*this - BigNum((BASE)1), *this);
		r.NormalLen();
		if (r != BigNum((BASE)1)) {
			return false;
		}

		t -= 1;
	}
	return true;
}

bool BigNum::solovStrassenTest(int t) {
	if (*this == BigNum((BASE)3) || *this == BigNum((BASE)2)) {
		return true;
	}

	if (*this % BigNum((BASE)2) == BigNum((BASE)0)) {
		return false;
	}

	while (t > 0) {
		BigNum a(len, 1);
		if (BigNum((BASE)2) > a || a > *this - BigNum((BASE)2)) {
			continue;
		}

		BigNum r = a.pow((*this - BigNum((BASE)1))/BigNum((BASE)2), *this);
		r.NormalLen();
		if (r != BigNum((BASE)1) || r != (*this - BigNum((BASE)1))) {
			return false;
		}

		BigNum s = a / *this;

		if (r != s.pow(BigNum((BASE)1), *this)) {
			return false;
		}

		t -= 1;
	}
	return true;
}

BigNum::BigNum() {
	maxlen = 1;
	len = 1;
	coef = new BASE[maxlen];
	coef[0] = 0;
}

BigNum::BigNum(const BASE num) {
	maxlen = 1;
	len = 1;
	coef = new BASE[maxlen];
	coef[0] = num;
}

BigNum::BigNum(int size, bool flag) {
	if (size < 1)
		exit(0);

	maxlen = size;
	len = size;
	coef = new BASE[maxlen];

	if (flag) {
		for (int i = 0; i < maxlen; i++) {
			coef[i] = (rand() << 16) + rand();
		}
		for (int i = maxlen - 1; i > 0 && coef[i] == 0; i++) {
			len = len - 1;
		}
	}
	else {
		len = 1;
		for (int i = 0; i < maxlen; i++) {
			coef[i] = 0;
		}
	}
}

BigNum::BigNum(const BigNum& Big) {
	if (!Big.coef || Big.maxlen < 1 || Big.len < 1)
		exit(0);

	maxlen = Big.maxlen;
	len = Big.len;
	coef = new BASE[maxlen];
	for (int i = 0; i < maxlen; i++) {
		coef[i] = Big.coef[i];
	}
}

BigNum& BigNum::operator=(const BigNum& Big) {
	if (this == &Big)
		return *this;
	if (Big.maxlen < 1 || Big.len < 1 || !Big.coef)
		exit(0);

	delete[] coef;
	maxlen = Big.maxlen;
	len = Big.len;
	coef = new BASE[maxlen];
	for (int i = 0; i < maxlen; i++) {
		coef[i] = Big.coef[i];
	}
	return *this;
}

bool BigNum::operator == (const BigNum& Big) {
	if (len != Big.len) return false;
	for (int i = len - 1; i >= 0; i--) {
		if (coef[i] != Big.coef[i]) return false;
	}
	return true;
}

bool BigNum::operator != (const BigNum& Big) {
	if (len != Big.len) return true;
	for (int i = len - 1; i >= 0; i--) {
		if (coef[i] != Big.coef[i]) return true;
	}
	return false;
}

bool BigNum::operator < (const BigNum& Big) const {
	if (len < Big.len) return true;
	if (len > Big.len) return false;
	for (int i = len - 1; i >= 0; i--) {
		if (coef[i] < Big.coef[i]) return true;
		else
			if (coef[i] > Big.coef[i]) return false;
	}
	return false;
}

bool BigNum::operator <= (const BigNum& Big) {
	if (len < Big.len) return true;
	if (len > Big.len) return false;
	for (int i = len - 1; i >= 0; i--) {
		if (coef[i] < Big.coef[i]) return true;
		else
			if (coef[i] > Big.coef[i]) return false;
	}
	return true;
}

bool BigNum::operator > (const BigNum& Big) {
	if (len > Big.len) return true;
	if (len < Big.len) return false;
	for (int i = len - 1; i >= 0; i--) {
		if (coef[i] > Big.coef[i]) return true;
		else
			if (coef[i] < Big.coef[i]) return false;
	}
	return false;
}

bool BigNum::operator >= (const BigNum& Big) {
	if (len > Big.len) return true;
	if (len < Big.len) return false;
	for (int i = len - 1; i >= 0; i--) {
		if (coef[i] > Big.coef[i]) return true;
		else
			if (coef[i] < Big.coef[i]) return false;
	}
	return true;
}

ostream& operator<<(ostream& out, BigNum& Big) {
	if (!Big.coef) return out;

	for (int j = Big.len - 1; j >= 0; j--) {
		cout.width(BASE_SIZE / 4);
		cout.fill('0');
		cout << hex << (unsigned int)Big.coef[j];
	}
	return out;
}

istream& operator >> (istream& in, BigNum& Big) {
	char* s = new char[1000];
	cout << "Enter 16CC:";
	cin >> s;

	int size = (strlen(s) - 1) / (BASE_SIZE / 4) + 1;

	BigNum Big1(size);
	Big1.len = size;

	int j = 0, k = 0;
	unsigned int tmp;
	bool flag = true;

	for (int i = strlen(s) - 1; i >= 0; i--) {
		flag = false;
		if ('0' <= s[i] && s[i] <= '9') {
			tmp = s[i] - '0';
			flag = true;
		}
		if ('a' <= s[i] && s[i] <= 'f') {
			tmp = s[i] - 'a' + 10;
			flag = true;
		}
		if ('A' <= s[i] && s[i] <= 'F') {
			tmp = s[i] - 'A' + 10;
			flag = true;
		}
		if (!flag) {
			puts("Error");
			exit(0);
		}

		Big1.coef[j] |= tmp << (k * 4);
		k++;
		if (k >= BASE_SIZE / 4) {
			k = 0;
			j++;
		}
	}

	Big1.NormalLen();

	Big = Big1;
	delete[] s;
	return in;
}

BigNum BigNum::operator + (const BigNum& Big) {
	int min, max;
	BASE* MaxBig;
	DBASE tmp;
	bool k = 0;

	if (len > Big.len) {
		min = Big.len;
		max = len + 1;
		MaxBig = coef;
	}
	else {
		min = len;
		max = Big.len + 1;
		MaxBig = Big.coef;
	}

	BigNum SUM(max, 0);

	for (int i = 0; i < min; i++) {
		tmp = (DBASE)Big.coef[i] + (DBASE)coef[i] + k;
		SUM.coef[i] = (BASE)tmp;
		k = (bool)(tmp >> BASE_SIZE);
	}

	for (int i = min; i < max - 1; i++) {
		tmp = (DBASE)MaxBig[i] + k;
		SUM.coef[i] = (BASE)tmp;
		k = (bool)(tmp >> BASE_SIZE);
	}

	SUM.coef[max - 1] = k;
	SUM.NormalLen();
	return SUM;
}

BigNum& BigNum::operator +=(const BigNum& Big) {
	*this = *this + Big;
	return *this;
}

BigNum BigNum::operator + (const BASE Number) {
	DBASE tmp;
	bool k = 0;
	int size = maxlen;

	if (len + 1 > maxlen) size = len + 1;
	BigNum SUM(size, 0);

	tmp = (DBASE)coef[0] + (DBASE)Number;
	k = (bool)(tmp >> BASE_SIZE);
	SUM.coef[0] = tmp;

	for (int i = 1; i < len; i++) {
		tmp = coef[i] + k;
		k = bool(tmp >> BASE_SIZE);
		SUM.coef[i] = tmp;
	}

	SUM.coef[len] = k;
	SUM.NormalLen();
	return SUM;
}

BigNum& BigNum::operator +=(const BASE Number) {
	*this = *this + Number;
	return *this;
}

BigNum BigNum::operator - (const BigNum& Big) {
	if (*this < Big) {
		cout << '\n' << "First value smaller than second" << '\n';
		exit(0);
	}

	bool k = 0;
	DBASE tmp;

	BigNum DIFF(maxlen, 0);

	for (int i = 0; i < Big.len; i++) {
		tmp = ((DBASE)1 << BASE_SIZE) | coef[i];
		tmp = tmp - Big.coef[i] - k;
		DIFF.coef[i] = (BASE)tmp;
		k = !(tmp >> BASE_SIZE);
	}

	for (int i = Big.len; i < maxlen; i++) {
		tmp = ((DBASE)1 << BASE_SIZE) | coef[i];
		tmp -= k;
		DIFF.coef[i] = (BASE)tmp;
		k = !(tmp >> BASE_SIZE);
	}

	DIFF.NormalLen();
	return DIFF;
}

BigNum& BigNum::operator -=(const BigNum& Big) {
	*this = *this - Big;
	return *this;
}

BigNum BigNum::operator - (const BASE Number) {
	if (*this < Number) {
		throw invalid_argument("first value should be bigger than second to subtract");
	}
	DBASE tmp;
	bool k = 0;
	BigNum A(*this);
	tmp = A.coef[0] + ((DBASE)1 << BASE_SIZE) - Number;
	A.coef[0] = (BASE)tmp;
	k = !((tmp) >> BASE_SIZE);
	for (int i = A.len; k && i <= A.len; i++) {
		tmp = A.coef[i] + ((DBASE)1 << BASE_SIZE) - k;
		A.coef[i] = (BASE)tmp;
		k = !((tmp) >> BASE_SIZE);
	}
	A.NormalLen();
	return A;
}

BigNum& BigNum::operator -= (const BASE Number) {
	*this = *this - Number;
	return *this;
}

BigNum BigNum::operator *(BASE Number) {
	DBASE tmp;
	BASE k = 0;

	BigNum MUL(maxlen + 1, 0);

	for (int i = 0; i < len; i++) {
		tmp = (DBASE)coef[i] * Number + k;
		k = (BASE)(tmp >> BASE_SIZE);
		MUL.coef[i] = (BASE)tmp;
	}

	MUL.coef[len] = k;
	MUL.NormalLen();
	return MUL;
}

BigNum& BigNum::operator*= (const BASE Number) {
	*this = *this * Number;
	return *this;
}

BigNum BigNum::operator*(const BigNum& Big) {
	DBASE tmp;
	BASE k;
	BigNum MUL(len + Big.len, 0);

	for (int i = 0; i < len; i++) {
		if (coef[i] != 0) {
			k = 0;
			for (int j = 0; j < Big.len; j++) {
				tmp = (DBASE)coef[i] * (DBASE)Big.coef[j] + (DBASE)MUL.coef[i + j] + (DBASE)k;
				MUL.coef[i + j] = (BASE)tmp;
				k = (BASE)(tmp >> BASE_SIZE);
			}
			MUL.coef[i + Big.len] = k;
		}
	}

	MUL.NormalLen();
	return MUL;
}

BigNum& BigNum::operator *=(const BigNum& Big) {
	*this = *this * Big;
	return *this;
}

BigNum BigNum::operator /(const BASE Number) {
	DBASE tmp;
	BASE r = 0;
	BigNum DIV(len, 0);
	for (int i = len - 1; i >= 0; i--) {
		tmp = ((DBASE)r << BASE_SIZE) + (DBASE)coef[i];
		DIV.coef[i] = (BASE)(tmp / (DBASE)Number);
		r = (BASE)(tmp % (DBASE)Number);
	}

	DIV.NormalLen();
	return DIV;
}

BigNum& BigNum::operator/=(const BASE Number) {
	*this = *this / Number;
	return *this;
}

BigNum BigNum::operator/(const BigNum& Big) {
	if (Big.len == 1 && Big.coef[0] == 0) {
		cout << "Error";
		exit(0);
	}

	if (*this < Big) {
		BigNum q(1);
		return q;
	}

	if (Big.len == 1) return *this / Big.coef[0];

	if (*this == Big) {
		BigNum q(1);
		q.coef[0] = 1;
		return q;
	}

	int m = len - Big.len;
	DBASE b = ((DBASE)1 << BASE_SIZE);
	DBASE d = b / (DBASE)(Big.coef[Big.len - 1] + (BASE)1); // coef
	BigNum q(m + 1); // chastnoe
	q.len = m + 1;

	BigNum U = *this; // delimoe
	BigNum V = Big; // delitel

	// D1
	// narmalization
	U = U * d;
	V = V * d;
	if (U.len == len) {
		if (U.maxlen == U.len) {
			U.len = U.maxlen;
			delete[]U.coef;
			U.coef = new BASE[U.maxlen];
			for (int i = 0; i < len; i++) {
				U.coef[i] = coef[i];
			}
			U = U * d;
			U.coef[U.len - 1] = 0; // add null to begin
		}
		U.coef[len] = 0;// add null to begin
		U.len = len + 1;
	}

	// D2
	for (int j = m; j >= 0; j--) {
		// D3
		DBASE qq = (((DBASE)U.coef[j + Big.len] << BASE_SIZE) + U.coef[j + Big.len - 1]) / V.coef[Big.len - 1];
		DBASE rr = (((DBASE)U.coef[j + Big.len] << BASE_SIZE) + U.coef[j + Big.len - 1]) % V.coef[Big.len - 1];

		// correction
		if (qq == b || ((qq * V.coef[Big.len - 2]) > (b * rr + U.coef[j + Big.len - 2]))) {
			qq--;
			rr = rr + V.coef[Big.len - 1];
			if ((rr < b) && ((qq == b) || (qq * V.coef[Big.len - 2] > b * rr + U.coef[j + Big.len - 2]))) {
				qq--;
				rr = rr + V.coef[Big.len - 1];
			}
		}

		BigNum u(V.len + 1);
		u.len = V.len + 1;
		for (int i = 0; i < V.len + 1; i++) {
			u.coef[i] = U.coef[j + i];
		}
		// D6
		if (u < V * qq) qq--;
		// D4
		u = u - V * qq;
		// D5
		q.coef[j] = qq;
		// D6
		for (int i = 0; i < V.len + 1; i++) {
			U.coef[j + i] = u.coef[i];
		}
		// D7
	}
	// D8
	q.NormalLen();
	return q;
}

BigNum& BigNum::operator/=(const BigNum& Big) {
	*this = *this / Big;
	return *this;
}

BigNum BigNum::operator%(const BASE Number) {
	DBASE tmp = 0;
	BASE r = 0;
	BigNum Rem(1, 0);
	for (int i = 0; i < len; i++) {
		tmp = (((DBASE)r << BASE_SIZE) + (DBASE)coef[len - 1 - i]);
		r = (BASE)(tmp % (DBASE)Number);
	}
	Rem.coef[0] = r;
	return Rem;
}

BigNum& BigNum::operator%=(const BASE Number) {
	*this = *this % Number;
	return *this;
}

BigNum BigNum::operator%(const BigNum& Big) {
	if (Big.len == 1 && Big.coef[0] == 0) {
		cout << "Error";
		exit(0);
	}

	if (*this < Big) return *this;

	if (Big.len == 1) return *this % Big.coef[0];

	if (*this == Big) {
		BigNum Rem(1);
		return Rem;
	}

	int m = len - Big.len; // length subtraction
	DBASE b = ((DBASE)1 << BASE_SIZE);
	DBASE d = b / (DBASE)(Big.coef[Big.len - 1] + (BASE)1); // normalization coef

	int k = 0;

	BigNum U = *this;
	BigNum V = Big;

	U = U * d; // normalization
	V = V * d;

	if (U.len == len) {
		if (U.maxlen == U.len) {
			U.maxlen++;
			U.len = U.maxlen;
			delete[]U.coef;
			U.coef = new BASE[U.maxlen];
			for (int i = 0; i < len; i++) {
				U.coef[i] = coef[i];
			}
			U = U * d;
			U.coef[U.len - 1] = 0;
		}
		U.coef[len] = 0;
		U.len = len + 1;
	}

	for (int j = m; j >= 0; j--) {

		DBASE qq = (((DBASE)U.coef[j + Big.len] << BASE_SIZE) + U.coef[j + Big.len - 1]) / V.coef[Big.len - 1];
		DBASE rr = (((DBASE)U.coef[j + Big.len] << BASE_SIZE) + U.coef[j + Big.len - 1]) % V.coef[Big.len - 1];

		if (qq == b || ((qq * V.coef[Big.len - 2]) > (b * rr + U.coef[j + Big.len - 2]))) {
			qq--;
			rr = rr + V.coef[Big.len - 1];
			if ((rr < b) && ((qq == b) || (qq * V.coef[Big.len - 2] > b * rr + U.coef[j + Big.len - 2]))) {
				qq--;
				rr = rr + V.coef[Big.len - 1];
			}
		}

		BigNum u(V.len + 1);
		u.len = V.len + 1;
		for (int i = 0; i < V.len + 1; i++) {
			u.coef[i] = U.coef[j + i];
		}

		if (u < V * qq) qq--;

		u = u - V * qq;

		for (int i = 0; i < V.len + 1; i++) {
			U.coef[j + i] = u.coef[i];
		}

	}

	U = U / d;
	return U;
}

BigNum& BigNum::operator%=(const BigNum& Big) {
	*this = *this % Big;
	return *this;
}

void test() {
	srand(time(NULL));
	int M = 1000;
	int T = 1000;
	BigNum A;
	BigNum B;
	BigNum C;
	BigNum D;
	do {
		int n = rand() % M + 1;
		BigNum E(n, 1);
		int m = rand() % M + 1;
		BigNum F(m, 1);
		A = E;
		B = F;
		C = A / B;
		D = A % B;
		cout << m << " " << n << " ";
		cout << "T: " << T << '\n';
	} while (A == C * B + D && A - D == C * B && D < B && --T);
	cout << T << '\n';
}

void BigNum::Input() {
	string S;
	cout << "Enter 10CC: ";
	cin >> S;

	int LEN = (S.length() - 1) / (BASE_SIZE / 4) + 1;
	BigNum Big(LEN);
	Big.len = LEN;
	for (int i = 0; i < S.length(); i++) {
		char num = 0;
		if ((S[i] >= '0') && (S[i] <= '9')) {
			num = S[i] - '0';
			Big = Big * 10 + num;
		}
		else {
			cout << "Error";
			exit(0);
		}
	}
	*this = Big;
}

void BigNum::Output() {
	BigNum NumToOut = *this;
	string s = "";
	while (NumToOut.coef[0] != 0 || NumToOut.len > 1) {
		BigNum r = NumToOut % 10;
		s += (r.coef[0] + '0');
		NumToOut = NumToOut / 10;
	}
	reverse(s.begin(), s.end());
	cout << "Number: " << s << '\n';
}

BigNum BigNum::raiseToThePowerTwo()  {
	// 1.
	BigNum y(2 * len, 0);
	y.len = y.maxlen;
	DBASE uv = 0; //0
	// 2.
	for (int i = 0; i < len; i++) {
		// 2.1
		uv = (DBASE)(y.coef[2 * i]) + (DBASE)(coef[i]) * (DBASE)(coef[i]);//uv
		y.coef[2 * i] = BASE(uv);//v
		// 2.2
		for (int j = i + 1; j < len; j++) {
			uv = (DBASE)(y.coef[i + j]) + 2 * (DBASE)(coef[i]) * (DBASE)(coef[j]) + (uv >> BASE_SIZE);//cuv = ... + cu
			y.coef[i + j] = BASE(uv);//v
		}
		// 2.3
		y.coef[i + len] += BASE(uv >> BASE_SIZE);//u
		y.coef[i + len + 1] += BASE(uv >> BASE_SIZE * 2);//c
	}
	// 3.
	y.NormalLen();
	return y;
}

BigNum BigNum::raiseToThePower(int y) {
	BigNum z;
	BigNum q(*this);
	// 1.
	if (y & 1) {
		z = *this;
	}
	else {
		z += 1;
	}
	// 2.
	while (y != 0) {
		y = y >> 1;
		// 2.1
		q = q.raiseToThePowerTwo();
		// 2.2
		if (y & 1) {
			z *= q;
		}
	}
	// 3.
	z.NormalLen();
	return z;
}

BigNum BigNum::module(const BigNum& m, const BigNum& z) {
	if (len >= 2 * m.len) {
		cout << "Out of range";
		return 0;
	};
	
	// 1.
	BigNum q;
	q = *this;

	for (int i = 0; i < m.len; i++) { 
		q.coef[i] = q.coef[i + m.len - 1];
	}
	q.len = q.len - (m.len - 1);

	q = q * z;

	for (int i = 0; i < m.len; i++) {
		q.coef[i] = q.coef[i + (m.len + 1)];
	}
	q.len = q.len - (m.len + 1);

	// 2.
	BigNum r1, r2, r;

	r1 = *this;
	for (int i = m.len + 1; i < r1.len; i++) {
		r1.coef[i] = 0;
	}
	r1.len = m.len + 1;

	r2 = q * m;
	for (int i = m.len + 1; i < r2.len; i++) {
		r2.coef[i] = 0;
	}
	r2.len = m.len + 1;

	// 3.
	if (r1 >= r2) {
		r = r1 - r2;
	}
	else
	{
		BigNum b(2, 0);
		b.coef[1] = (BASE)1;
		r = r1 - r2;
		r = r + b.raiseToThePower(m.len + 1);
	}

	// 4.
	while (r >= m)
	{
		r -= m;
	}

	return r;
}

vector<BigNum> BigNum::small_devisor()
{
	BigNum n(*this);
	vector<BigNum> ans;

	if(fermatTest(10) == 1) {
		ans.push_back(n);
		return ans;
	}

	while (n % (BASE)2 == (BASE)0)
	{
		ans.push_back((BASE)2);
		n /= (BASE)2;
	}

	int t = 0, k = 1;

	if(n == (BASE)1) {
		ans.push_back(n);
		return ans;
	}

	BigNum ds = n.sqrt();
	BigNum dk = (BASE)0;
	BigNum dkPrev;
	BigNum q, r;

	while(dk < ds && n != (BASE)1) {

	if(t != k) {
		if(k == 1) {
			dk = (BASE)3;
		} else if(k == 2) {
			dkPrev = dk;
			dk = (BASE)5;
		} else if(k == 3) {
			dkPrev = dk;
			dk = (BASE)7;
		} else {
			BigNum tmp = dk;
			dk = dkPrev + (BASE)6;
			dkPrev = tmp;
		}
	}
		q = n / dk;
		r = n % dk;

		if(r == (BASE)0) {
			ans.push_back(dk);
			n = q;
			t = k;
		} else if (q > dk) {
			k++;
		} else {
			ans.push_back(n);
			break;
		}
	}
	return ans;
}
// extention lab 4 polard 1

BigNum BigNum::floyd(BigNum x) {
	return (x.raiseToThePowerTwo() + 1) % *this;
}

BigNum BigNum::gcd(BigNum x, BigNum y) {
	while (x != (BASE)0 && y != (BASE)0) 
		if (x > y) x = x % y;
		else y = y % x;

	return x + y;
}

BigNum BigNum::polard1() {
	BigNum n(*this);
	BigNum a = (BASE)2;
	BigNum b = (BASE)2;
	BigNum d = (BASE)1;

	while (d == (BASE)1)
	{
		a = floyd(a);
		b = floyd(floyd(b));

		if(a == b) { return (BASE)0; }

		if(a < b) {
			d = gcd(b - a, n);
		} else {
			d = gcd(a - b, n);
		}
	}

	return d;
}

// extension polard 2

BigNum BigNum::log(BigNum q) {
	if (q == BASE(0) || *this == (BASE)0) {
		cout << "[-] error" << endl;
		exit(1);
	}

	BigNum x(*this);
	BigNum x0 = q;
	BigNum log = (BASE)0;
	while (x0 <= x) {
		x0 *= q;
		log += (BASE)1;
	}

	return log;
}

BigNum BigNum::polard2() {
	srand(time(NULL));
	BigNum n(*this);

	if(n.fermatTest(10)) {return *this;}

	BigNum B = BigNum((BASE)(rand() % 100)) + (BASE)2;
	BigNum a = n - (BASE)(rand() % 10);

	while (!(a >= (BASE)2 && a <= n - (BASE)2)) 
	{
		a = n - (BASE)(rand() % 10);
	}

	BigNum e; // log
	BigNum d = gcd(a, n);
	if(d > (BASE)1) {return d;}

	for(BigNum q = (BASE)2; q < B; q += (BASE)1)
	{
		if(!q.fermatTest(10)) {continue;}

		e = n.log(q);
		a = a.pow(q.normalPow(e), n);

		if(a == (BASE)1) {
			a = n - BASE(rand() % 10);
			while (!(a >= (BASE)2 && a <= n - (BASE)2)) 
			{
				a = n - (BASE)(rand() % 10);
			}
		} 
		else {
			d = gcd(a - (BASE)1, n);

			if(d == (BASE)1 || d == n) {
				B += ((BASE)(rand() % 100));
			} else {
				return d;
			}
		}
	}	
	return (BASE)0;
}

// extension lab 5


BigNum BigNum::gelfond(BigNum g, BigNum a) {
	BigNum h = sqrt() + (BASE)1;
	BigNum b = g.pow(h, *this);
	BigNum x;

	map<BigNum, BASE> u;
	map<BigNum, BASE>::iterator iter;
	vector<BigNum> v;

	for(BASE i = (BASE)1; h >= i; i += (BASE)1) 
	{
		u.insert(make_pair(b.pow(i, *this), i)); 
	}

	for(BASE i = (BASE)1; h >= i; i += (BASE)1) 
	{
		v.push_back((a * g.normalPow(i)) % *this);

		iter = u.find(v[i - (BASE)1]);

		if(iter != u.end()) {
			x = h * iter->second - i;
			break;
		}
	}
	return x % *this;
}

// extension 6 lab (Po-Polard)

void f(BigNum& x, BigNum& u, BigNum& v, BigNum g, BigNum a, BigNum n, BigNum k) {  // F - function(x,u,v) -> (x1, u1, v1)
	if (x % (BASE)3 == (BASE)1)
	{
		x = x * a % n;
		v = (v + (BASE)1) % k;
	} 
	else if (x % (BASE)3 == 2)
	{
		x = x * x % n;
		u = u * (BASE)2 % k;
		v = v * (BASE)2 % k;
	} 
	else if (x % (BASE)3 == 0)
	{
		x = x * g % n;
		u = (u + (BASE)1) % k;
	}
}

BigNum BigNum::inv(BigNum k) {
	if (*this < (BASE)1 or k < (BASE)2)
		return -1;

	BigNum t = *this;

	int u1 = k.coef[0];
	int u2 = (BASE)0;
	int v1 = t.coef[0];
	int v2 = (BASE)1;

	while (v1 != (BASE)0)
	{
		int q = u1 / v1; 
		int t1 = u1 - q * v1;
		int t2 = u2 - q * v2;
		u1 = v1;
		u2 = v2;
		v1 = t1;
		v2 = t2;
	}

	BigNum inv = BASE((u2 + k.coef[0]) % k.coef[0]);

	return inv;
}

BigNum BigNum::polard3(BigNum g, BigNum a) {
	BigNum x1 = (BASE)1, x2 = x1; // x1, x2 - init
	BigNum u1 = (BASE)0, u2 = u1, v1 = u1, v2 = u1; // u1, u2, v1, v2 - init 

	BigNum n = *this;
	BigNum k = n - (BASE)1; // fi(n) = n - 1

	do {
		f(x1, u1, v1, g, a, n, k);
		f(x2, u2, v2, g, a, n, k);
		f(x2, u2, v2, g, a, n, k);
	} while (x1 != x2);

	BigNum r;

	if (v1 >= v2)
	{
		r = (v1 - v2) % k; // or M??
	} else {
		r = (v1 + k - v2)  % k;
	}

	if(r == (BASE)0) // refuse
	{
		cout << "[-] Refuse" << endl;
		return (BASE)0;
	}

	BigNum d = gcd(r, k);

	BigNum resh;

	if (u1 >= u2)
	{
		resh = (u1 - u2) % k;
	} else {
		resh = (u1 + k - u2) % k;
	}

	r /= d;
	k /= d;
	resh /= d;

	BigNum t = r.inv(k);

	BigNum x = (t * resh) % k;

	while (d > (BASE)0) {
		if (g.pow(x, n) == a) {
			break;
		}
		x += k;
		d -= (BASE)1;
	}
	
	return x;
}

// tests -----------------------------

void test1() {
	while(1){
		BigNum A;
		A.Input();
		A.Output();
		vector<BigNum> B = A.small_devisor();

		for(int i = 0; i < B.size(); i++) {
			B[i].Output();
		}
	}
}

void test2(){
	while(1) {
		BigNum A;
		A.Input();
		A.Output();
		BigNum res = A.alway_meth();
		res.Output();
	}
}

void test3() {
	while(1) {
		BigNum A;
		A.Input();
		A.Output();

		BigNum B, C;
		tie(B, C) = A.f3rma();
		cout << "a: ";
		B.Output();
		cout << "b: ";
		C.Output();
	}
}

void test41() {
	while(1) 
	{
		BigNum A;
		A.Input();
		A.Output();

		BigNum d = A.polard1();
		d.Output();
	}
}

void test42() {
	while(1) 
	{
		BigNum A;
		A.Input();
		A.Output();

		BigNum d = A.polard2();
		d.Output();
	}
}

void test5() {
	BigNum x, g, a;

	while(1)
	{
	x.Input();
	g.Input();
	a.Input();

	x.gelfond(g, a).Output();
	}
}

void test6() {
	BigNum x, g, a;

	while(1)
	{
		x.Input();
		g.Input();
		a.Input();

		x.polard3(g, a).Output();
	}
}

int main() {
	//test();
	//test2();
	//test3();
	//test41(); //polard 1
	//test42(); //polard 2
	test5(); // Gelfond
	//test6(); 	// polard Po
}