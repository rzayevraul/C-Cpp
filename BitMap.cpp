#include <iostream>
#include <algorithm>

using namespace std;
class cbitset{
	private:
		int min_el, max_el, number, dif;
		unsigned int *arr;
	public:
		cbitset(int minel = 0, int maxel = 32);
		cbitset(const cbitset &c);
		~cbitset() {delete [] arr;}
		bool exist(int n) const;
		cbitset & operator |=(int n);
		cbitset & operator -=(int n);
		cbitset & operator =(const cbitset &c);
		cbitset & clear();
		bool isEmpty();
		friend ostream &operator <<(ostream &out, const cbitset &c);
		void association(const cbitset &a, const cbitset &b);
		void intersection(const cbitset &a, const cbitset &b);
		void complement(const cbitset &a, const cbitset &b);
};

cbitset::cbitset (int minel, int maxel){
	min_el = min(minel, maxel);
	max_el = max(minel, maxel);
	int wh_min, wh_max;
	wh_min = (min_el-((32+(min_el%32))%32))/32;
	wh_max = (max_el-((32+(max_el%32))%32))/32;
	number = wh_max - wh_min + 1;
	dif = abs((min_el - ((32+(min_el%32))%32))/32);
	arr = new unsigned int[number];
	for(int i = 0; i < number; i++){
		arr[i] = 0;
	}
}

cbitset::cbitset(const cbitset &c){
	min_el = c.min_el;
	max_el = c.max_el;
	number = c.number;
	dif = c.dif;
	arr = new unsigned int[number];
	for(int i = 0; i < number; i++)
		arr[i] = c.arr[i];
}

bool cbitset::exist(int n) const{
	if(n > max_el || n < min_el) return false;
	int t1, t2;
	t1 = (32+(n%32))%32;
	t2 = (n-((32+(n%32))%32))/32;
	return (arr[t2 + dif] & (1 << t1)) != 0;
}

cbitset & cbitset::operator |= (int n){
	if(n <= max_el && n >= min_el){
		int t1, t2;
		t1 = (32+(n%32))%32;
		t2 = (n-((32+(n%32))%32))/32;
		arr[t2 + dif] |= (1 << t1);
	}else
		cout << "out of range" << endl;
	return *this;
}

void cbitset::association(const cbitset &a, const cbitset &b){
	min_el = min(a.min_el, b.min_el);
	max_el = max(a.max_el, b.max_el);
	/*int wh_min, wh_max;
	wh_min = (min_el-((32+(min_el%32))%32))/32;
	wh_max = (max_el-((32+(max_el%32))%32))/32;
	number = wh_max - wh_min + 1;
	dif = abs((min_el - ((32+(min_el%32))%32))/32) ;
	delete [] arr;
	arr = new unsigned int[number];
	for(int i = 0; i < number; i++){
		arr[i] = 0;
	}*/
	cbitset k(min_el, max_el);
	*this = k;
	//for(int i = min_el; i <= max_el; i++)
	//	if(a.exist(i) || b.exist(i)) *this |= i;
	int v_kak_yach_a = (a.min_el-((32+(a.min_el%32))%32))/32;
	int v_kak_yach_b = (b.min_el-((32+(b.min_el%32))%32))/32;
	for(int i = 0; i < a.number; i++, v_kak_yach_a++)
		arr[v_kak_yach_a + a.dif] |= a.arr[a.dif + v_kak_yach_a];
	for(int i = 0; i < b.number; i++, v_kak_yach_b++)
		arr[v_kak_yach_b + b.dif] |= b.arr[b.dif + v_kak_yach_b];
	return;
}

void cbitset::intersection(const cbitset &a, const cbitset &b){
	if(a.min_el > b.max_el || b.min_el > a.max_el){
		cout << "intersection is empty";
		for(int i = 0; i < number; i++)
		arr[i] = 0;
		return;
	}
	int t[4] = {a.min_el, b.min_el, a.max_el, b.max_el};
	sort(t, t + 4);
	min_el = t[1];
	max_el = t[2];
	/*int wh_min, wh_max;
	wh_min = (min_el-((32+(min_el%32))%32))/32;
	wh_max = (max_el-((32+(max_el%32))%32))/32;
	number = wh_max - wh_min + 1;
	dif = abs((min_el - ((32+(min_el%32))%32))/32) ;
	delete [] arr;
	arr = new unsigned int[number];
	for(int i = 0; i < number; i++)
		arr[i] = 0;*/
	cbitset k(min_el, max_el);
	*this = k;
	//for(int i = min_el; i <= max_el; i++)
	//	if(a.exist(i) && b.exist(i)) *this |= i;
	int v_kak_yach_a = (a.min_el-((32+(a.min_el%32))%32))/32;
	int v_kak_yach_b = (b.min_el-((32+(b.min_el%32))%32))/32;
	for(int i = 0; i < a.number; i++, v_kak_yach_a++)
		arr[v_kak_yach_a + a.dif] |= a.arr[a.dif + v_kak_yach_a];
	for(int i = 0; i < b.number; i++, v_kak_yach_b++)
		arr[v_kak_yach_b + b.dif] &= b.arr[b.dif + v_kak_yach_b];
	return;
}

void cbitset::complement(const cbitset &a, const cbitset &b){
	min_el = a.min_el;
	max_el = a.max_el;
	cbitset k(min_el, max_el);
	*this = k;
	//for(int i = min_el; i <= max_el; i++)
	//	if(a.exist(i) == true && b.exist(i) == false) *this |= i;
	int v_kak_yach_a = (a.min_el-((32+(a.min_el%32))%32))/32;
	int v_kak_yach_b = (b.min_el-((32+(b.min_el%32))%32))/32;
	for(int i = 0; i < a.number; i++, v_kak_yach_a++)
		arr[v_kak_yach_a + a.dif] |= a.arr[a.dif + v_kak_yach_a];
	for(int i = 0; i < b.number; i++, v_kak_yach_b++)
		arr[v_kak_yach_b + b.dif] &= ~b.arr[b.dif + v_kak_yach_b];
	return;
}

cbitset & cbitset::operator -=(int n){
	if(n <= max_el && n >= min_el){
		int t1, t2;
		t1 = (32+(n%32))%32;
		t2 = (n-((32+(n%32))%32))/32;
		arr[t2 + dif] &= ~(1 << t1);
	}
	return *this;
}

cbitset & cbitset::clear(){
	for(int i = 0; i < number; i++)
		arr[i] = 0;
	return *this;
}

bool cbitset::isEmpty(){
	for(int i = 0; i < number; i++)
		if(arr[i] != 0) return false;
	return true;
}

cbitset & cbitset::operator =(const cbitset &c){
	min_el = c.min_el;
	max_el = c.max_el;
	number = c.number;
	delete [] arr;
	arr = new unsigned int[number];
	dif = c.dif;
	for(int i = 0; i < number; i++)
		arr[i] = c.arr[i];
	return *this;
}

ostream & operator <<(ostream &out, const cbitset &c){
	int i;
	for(i = c.min_el; i <= c.max_el; i++)
		if(c.exist(i)) out << i << ", ";
	out << endl;
	return out;
}

int main(){
	cbitset a(-20, 40);
	cbitset b(-10, 50);
	a |= -2; a |= -5;  a |= 6; a |= 1; a |= 7; a |= 14;
	cout << a << endl;
	b |= -20; b |= -10; b |= 0; b |= -3; b |= -5; b |= -8; b |= 7; b |= -19;
	cout << b << endl;
	cbitset c, d;
	c.association(a, b);
	d.intersection(a, b);
	cout << "association " << c << endl << "intersection " << d << endl;
	b -= -20;
	cout << b << endl;
	cbitset k = b;
	cout << k << endl;
	b -= 566;
	cout << b << endl;
	cbitset com;
	com.complement(a, b);
	cout << "complement a on b " << com << endl;
}
	
	
	
