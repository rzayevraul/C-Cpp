#include <iostream>
#include <cstdlib>
using namespace std;

void test_1();
void test_2();
void test_3();
void test_4();
void test_5();
void test_6();

class DEK{
	private:
		int l, r, *mem_s;
		int size, maxsize;
	public:
		DEK(int N = 10);
		DEK(const DEK &c);
		~DEK();
		void Push_l(int v);
		void Pop_l(int *x);
		void Push_r(int v);
		void Pop_r(int *x);
		int Size() {cout << size; return size;}
		void Show();
		DEK operator +(DEK &x);
		DEK& operator =(DEK &x);
		friend ostream& operator <<(ostream &dekout, DEK &dekin);
};

ostream& operator <<(ostream &dekout, DEK &dekin){
	int i;
	if (dekin.size > 0){
		for(i = 0; i < dekin.size; i++)
			dekout << dekin.mem_s[(dekin.l + i + 1)%dekin.maxsize] << " ";
	}
	else dekout << "EMPTY DEQUE";
	return dekout;
}

DEK::DEK(int N){
	maxsize = N;
	mem_s = new int[maxsize];
	r = 0;
	l = maxsize - 1;
	size = 0;
}

DEK::DEK(const DEK &c){
	int i;
	maxsize = c.maxsize;
	size = c.size;
	l = c.l;
	r = c.r;
	mem_s = new int[maxsize];
	for(i = 0; i < maxsize; i++)
		mem_s[i] = c.mem_s[i];
}

DEK::~DEK(){
	delete mem_s;
	r = 0;
	l = 0;
	size = 0;
	maxsize=0;
}


void DEK::Show(){
	if(size > 0){
		int k, i = (l + 1)%maxsize;
		for(k = 0; k < size; i = (i + 1)%maxsize, k++) 
			cout << mem_s[i] << " ";
		cout << endl;
	}
	else
		cout << "EMPTY DEQUE" << endl;
}

void DEK::Push_l(int v){
	if(size<maxsize){
		mem_s[l] = v;
		l = (maxsize + l - 1)%maxsize;
		size++;
	}
	else
		exit(EXIT_FAILURE);
}

void DEK::Pop_l(int *x){
	if(size>0){
		l = (l + 1)%maxsize;
		*x = mem_s[l];
		size--;
	}
	else
		exit(EXIT_FAILURE);
}

void DEK::Push_r(int v){
	if(size<maxsize){
		mem_s[r] = v;
		r = (r + 1)%maxsize;
		size++;
	}
	else
		exit(EXIT_FAILURE);
}

void DEK::Pop_r(int *x){
	if(size>0){
		r = (maxsize + r - 1)%maxsize;
		*x = mem_s[r];
		size--;
	}
	else
		exit(EXIT_FAILURE);
}

DEK DEK::operator +(DEK &x){
	int i;
	DEK sum_res(maxsize+x.maxsize);
	for(i = 0; i < size; i++){
		sum_res.mem_s[i] = mem_s[(l+i+1)%maxsize];
		sum_res.r=(sum_res.r+1)%sum_res.maxsize;
		sum_res.size++;
	}
	int j = 0;
	for(j = 0; j < x.size; j++){
		sum_res.mem_s[i] = x.mem_s[(x.l+j+1)%x.maxsize];
		sum_res.r=(sum_res.r+1)%sum_res.maxsize;
		sum_res.size++;
		i++;
	}
	return sum_res;
}

DEK& DEK::operator =(DEK &x){
	int i;
	delete mem_s;
	maxsize = x.maxsize;
	size = x.size;
	r = x.r;
	l = x.l;
	mem_s = new int[maxsize];
	for(i = 0; i < maxsize; i++)
		mem_s[i] = x.mem_s[i];
	return *this;
}

int main(){
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	test_6();
	return 0;
}

void test_1(){
	int a;
	cout << "INDEX Test START" << endl;
	DEK *test1;
	test1 = new DEK(100);
	for(int i = 0; i < 5; i++)
		test1->Push_r(i);
	for(int i = 0; i < 1000000; i++){
		test1->Pop_r(&a);
		test1->Push_l(i);
	}
	test1->Show();
	
	for(int i = 0; i < 5; i++)
		test1->Push_r(i);
	for(int i = 0; i < 1000000; i++){
		test1->Pop_r(&a);
		test1->Push_l(i);
	}
	test1->Show();
	cout<< "INDEX Test END" << endl << endl;
}

void test_2(){
	int i, j;
	cout << "DESTRUCTOR Test START" << endl;
	DEK *test2;
	test2 = new DEK(1000);
	for(i = 0; i < 5; i++){
		test2->Push_l(i);
		test2->Push_r(i+1);
	}
	test2->Show();
	
	for(i = 0; i < 1000000; i++){
		delete test2;
		test2 = new DEK(1000);
		for(j = 0; j < 3; j++){
			test2->Push_l(i+j);
			test2->Push_r(i+j+74);
		}
	}
	test2->Show();
	cout << "DESTRUCTOR Test END" << endl << endl;
}

void test_3(){
	cout << "COPY CONSTRUCTOR Test START" << endl;
	int a;
	DEK *test_3;
	test_3 = new DEK(15);
	test_3->Push_r(1);
	test_3->Push_r(2);
	test_3->Push_r(3);
	test_3->Push_r(4);
	test_3->Push_r(5);
	test_3->Pop_l(&a);
	test_3->Push_r(6);
	test_3->Pop_l(&a);
	test_3->Push_r(7);
	test_3->Pop_l(&a);
	test_3->Show();
	DEK test_32 = *test_3;
	test_32.Show();
	cout << "COPY CONSTRUCTOR Test END" << endl << endl;
}

void test_4(){
	cout << "+OPERATOR Test START" << endl;
	DEK tst(3);
	DEK tst1(3);
	tst.Push_r(1);
	tst.Push_r(2);
	//tst.Push_r(3);
	tst.Show();
	tst1.Push_r(4);
	tst1.Push_r(5);
	//tst1.Push_r(6);
	tst1.Show();
	DEK tst2 = tst + tst1;
	tst2.Show();
	//tst2.Size();
	cout << "+OPERATOR Test END" << endl << endl;
}

void test_5(){
	cout << "=OPERATOR Test START" << endl;
	DEK test_51(4);
	DEK test_52(10);
	DEK test_53(10);
	test_51.Push_r(1);
	test_51.Push_r(20);
	test_51.Push_r(2);
	test_51.Push_r(4);
	
	test_53.Push_r(5);
	test_53.Push_r(3);
	test_53.Push_r(1);
	test_53.Push_r(7);
	
	test_51.Show();
	test_52.Show();
	test_53.Show();
	
	test_51 = test_52 = test_53;
	
	test_51.Show();
	test_52.Show();
	test_53.Show();
	cout << "=OPERATOR Test END" << endl << endl;
}

void test_6(){
	cout << "<<OPERATOR Test START" << endl;
	DEK test6(5);
	test6.Push_r(1);
	test6.Push_r(3);
	test6.Push_l(788);
	test6.Push_l(998);
	test6.Show();
	cout << test6 << endl;
	cout << "<<OPERATOR Test END" << endl << endl;
}
