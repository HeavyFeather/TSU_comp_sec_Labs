#include <iostream>
#include <math.h>
#include <string>
#include <string.h>
#include <ctime>
#include <bitset>
#include <random>

using namespace std;

class BF {
private:
	unsigned int *f = NULL;
	unsigned int count; // колво переменных	
	unsigned int nw; // длинна массива

public:		
	BF() {
		f = new unsigned int[1];
		count = 1;
		nw = 1;
	}

	BF(const BF& other) {
		count = other.count;
		nw = other.nw;
		f = new unsigned int[nw];

		for(int i = 0; i < nw; i++) {
			f[i] = other.f[i];
		}
	}

	~BF() {
		if(f) delete[] f; 
		f = NULL;
	}

	BF(int num, int type) {
		count = num; 

		if(count < 2) cout << "[-] Error: count < 2" << endl;
			
		nw = (unsigned int)(1 << count) + 31 >> 5;
		f = new unsigned int[nw];

		if(type == 0) {
			for(int i = 0; i < nw; i++) {
				f[i] = 0;
			}
		}

		//===
		
		else if(type == 1) {
			if(count < 5) {
				f[0] = (unsigned int)((1 << (1 << count)) - 1); 
			}
		
			else {
				for(int i = 0; i < nw; i++) {
					f[i] = ~0;
				}
			}
		}

		//===

		else if(type == 2) {

			srand((unsigned) time(NULL));

			random_device r;
  			default_random_engine e(r());
  			uniform_int_distribution<unsigned int> dist(0, ~0);

			
			unsigned int num;

			if(count < 5) {;
				num = rand()%(unsigned int)((1 << (1 << count)) - 1);
				f[0] = num;
			}

			else {
				for(int i = 0; i < nw; i++) {
					f[i] = dist(e); //dist(e)
				}
			}

		} else {
			cout << "[-] Error: invalid type" << endl;
		}	
	}

	BF(string init) {
		count = log2(init.length());

		if(init.length() != 0 && ((init.length() - 1) & init.length())) {

			nw = (init.length() - 1) / 32 + 1; 
			f = new unsigned int [nw];

			unsigned int mask = 1;
			int j = 0; // block iterator

			for(int i = 0; i < nw;  i++) {
				f[i] = 0;
			}

			for(int i = init.length() - 1; i >= 0; i--) {
				if(mask == 0) {
					mask = 1;
					j++;
				}

				if(init[i] == '1') {
					f[j] |= mask;
				}

				mask = mask << 1;
			}

		}
	}



	void prOut() {
		for(int i = 0; i < nw; i++) {
			cout << bitset<32> (f[i]) << "	===	f[" << i << "]" << endl;
		}
	}

	/*int weigth() {

		unsigned int mask = 1;
		int i = 0; // block iterator
		int weigth = 0; 

		while(i < nw) {

			if(mask == 0) {
				mask = 1;
				i++;
			}

			if((f[i] & mask) == mask) {
				weigth += 1;
			}

			mask = mask << 1;
		}

		return weigth;
	}*/

	int weigth_v2() { // пример из пособия
		int n = 0;

		int i = 0;

		while (i < nw) {
			
			while(f[i] != 0) {
				f[i] = f[i] & (f[i] - 1);
				n += 1;
			}
			
			i++;
		}

		return n;
	}

	int weigth_v3() { // вес немаловесного вектора

		int i = 0;
		unsigned int x;
		int weigth;

		while (i < nw) {
		x = f[i];

		x = x - ((x >> 1) & 0x55555555);
		x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
		x = (x + (x >> 4)) & 0x0f0f0f0f;
		x = x + (x >> 8);
		x = x + (x >> 16);

		i++;
		weigth += x;
		}
		return weigth;
	}


	int getCount() {
		return count;
	}

	bool operator == (const BF& other) {
		if (count != other.count) return false;
		for (int i = 0; i < nw; i++) {
			if (f[i] != other.f[i]) return false;
		}
		return true;
	}

	bool operator != (const BF& other) {
		if(!(this == &other)) return false;
		return true;
	}

	BF& operator = (const BF& other) {
		if(this == &other) return *this;

		delete[] f;
		count = other.count;
		nw = other.nw;
		f = new unsigned int [nw];

		for(int i = 0; i < nw; i++) {
			f[i] = other.f[i];
		}

		return *this;
	}
	
};

// =====================	TESTS	 ===============================================================================

void test_type() { // инициализация по типу
	while(1) {
	int count, type;
	cout << "Count: ";
	cin >> count;
	cout << "Type(0 - void, 1 - full, 2 - random): ";
	cin >> type;
	BF f(count, type);
	f.prOut();
	cout << endl;
	}
}

void test_str() { // инициализация по строке
	while (1) {
	string init;
	cin >> init;
	BF f(init);
	f.prOut();
	}
}

void test_kn() { // Kn
	BF f(10, 2);
	float kn = f.weigth_v3()/(pow(2, f.getCount()));
	cout << kn;
}

void test_weigth() { // Вес

	for(int i = 0; i < 5; i++){
	BF f(5, 2);
	f.prOut();

	cout << "Weigth: " << f.weigth_v3() << endl;
	}

	
}

void test_func() {
	BF f1("1001");
	BF f2("1001");
	BF f3("1111");
	//f3 = f2;
	if(f1 == f2) cout << "True 1" << endl;
	if(f1 == f3) cout << "True 2" << endl;
	if(f1 != f2) cout << "True 3" << endl;
}

void test_lab() {
	for(int n = 5; n <= 32; n++) {
		BF f(n, 2);
		float a = f.weigth_v2();
		unsigned int b = (1 << n);
		float kn = a / b;
		cout << "Kn: " << kn << endl;
	}
}

// =====================	MAIN	 ===============================================================================

int main()
{
	//test_str();
	//test_weigth();
	//test_kn();
	//test_func();
	test_lab();
	//test_type();
	return 0;
}
