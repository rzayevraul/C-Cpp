#include <iostream>
#include <cstdlib>
using namespace std;

void test_1(); //Adding and removing test, printing and clearing
void test_2(); //Constructor, Destructor, print size, list itself and clear
void test_3(); //Copy constructor
void test_4(); //Other methods

class node{
	int data;
	node *prev, *next;
	public:
		node(int a = 0) {data = a; prev = NULL; next = NULL;}
	friend class lst;
};

class lst{
	private:
		node *ptr_node;
		int size;
	public:
		lst() {ptr_node = NULL; size = 0;}
		lst(const lst &l);
		~lst();
		void Insert_Prev(int v);
		void Insert_Next(int v);
		void ptr_node_prev(); //
		void ptr_node_next();
		void Remove_node();
		void Show();
		void Clear();
		void Change_Prev(int v);
		void Change_Next(int v);
		void Change_Current(int v);
		int Size() {cout << size << endl; return size;}
		void Read_Prev(int *x);
		void Read_Next(int *x);
		void Read_Current(int *x);
};

lst::lst(const lst &l){
	if(l.ptr_node == NULL) ptr_node = NULL;
	node *a1, *a2, *a3;
	ptr_node = new node(l.ptr_node->data);
	a1 = l.ptr_node->next;
	a3 = ptr_node;
	for(; a1!=l.ptr_node; a1 = a1->next){
		a2 = new node(a1->data);
		a2->prev = a3;
		a3->next = a2;
		a3 = a3->next;
	}
	a2->next = ptr_node;
	ptr_node->prev = a2;
}

lst::~lst(){
	if(ptr_node == NULL) return;
	else{
		node *tmpd;
		tmpd = ptr_node->next;
		while(tmpd!=ptr_node){
			tmpd = tmpd->next;
			delete tmpd->prev;
		}
		delete ptr_node;
		ptr_node = tmpd = NULL;
	}
}

void lst::Insert_Prev(int v){
	if(ptr_node == NULL){
		ptr_node = new node(v);
		ptr_node->next = ptr_node->prev = ptr_node;
		size++;
		return;
	}
	else{
		node *n;
		n = new node(v);
		n->next = ptr_node;
		n->prev = ptr_node->prev;
		ptr_node->prev->next = n;
		ptr_node->prev = n;
		size++;
	}
}

void lst::Insert_Next(int v){
	if(ptr_node == NULL){
		ptr_node = new node(v);
		ptr_node->next = ptr_node->prev = ptr_node;
		size++;
		return;
	}
	else{
		node *n;
		n = new node(v);
		n->prev = ptr_node;
		n->next = ptr_node->next;
		ptr_node->next->prev = n;
		ptr_node->next = n;
		size++;
	}
}

void lst::Change_Prev(int v){
	if (size < 2) {cout << "ERROR: NOT ENOUGH MEMBERS OF LISTp" << endl; exit(EXIT_FAILURE);}
	else{
		ptr_node->prev->data = v;
		return;
	}
}

void lst::Change_Next(int v){
	if (size < 2) {cout << "ERROR: NOT ENOUGH MEMBERS OF LISTn" << endl; exit(EXIT_FAILURE);}
	else{
		ptr_node->next->data = v;
		return;
	}
}

void lst::Change_Current(int v){
	if (size < 2) {cout << "ERROR: NOT ENOUGH MEMBERS OF LISTc" << endl; exit(EXIT_FAILURE);}
	else{
		ptr_node->data = v;
		return;
	}
}

void lst::ptr_node_prev(){
	if(ptr_node!=NULL) ptr_node = ptr_node->prev;
}

void lst::ptr_node_next(){
	if(ptr_node!=NULL) ptr_node = ptr_node->next;
}

void lst::Remove_node(){
	if(ptr_node == NULL) {size = 0; return;}
	else if(ptr_node == ptr_node->next){
		delete ptr_node;
		ptr_node = NULL;
		return;
	}
	else{
		ptr_node->next->prev = ptr_node->prev;
		ptr_node->prev->next = ptr_node->next;
		node *tmp = ptr_node;
		ptr_node_next();
		delete tmp;
		size--;
		return;
	}
}

void lst::Show(){
	if(ptr_node == NULL)
		cout << "EMPTY" << endl;
	else{
		node *tmp;
		tmp = ptr_node->next;
		cout << ptr_node->data << endl;
		while(tmp!=ptr_node){
			cout << tmp->data << endl;
			tmp = tmp->next;
		}
		cout << endl;
	}
}

void lst::Clear(){
	if(ptr_node == NULL) return;
	else{
		node *tmp;
		tmp = ptr_node->next->next;
		while(tmp!=ptr_node){
			delete tmp->prev;
			tmp = tmp->next;
		}
		delete tmp->prev;
		delete tmp;
		ptr_node = NULL;
		size = 0;
		return;
	}
}

void lst::Read_Prev(int *x){
	if(size>1){
		*x = ptr_node->prev->data;
	}
	else{
		cout << "CANT READ PREV" << endl;
		exit(EXIT_FAILURE);
	}
}

void lst::Read_Next(int *x){
	if(size>1){
		*x = ptr_node->next->data;
	}
	else{
		cout << "CANT READ NEXT" << endl;
		exit(EXIT_FAILURE);
	}
}

void lst::Read_Current(int *x){
	if(size>1){
		*x = ptr_node->data;
	}
	else{
		cout << "CANT READ CURRENT" << endl;
		exit(EXIT_FAILURE);
	}
}

int main(){
	test_1();
	test_2();
	test_3();
	test_4();
}

void test_1(){
	cout << "TEST 1" << endl;
	lst test1;
	int i;
	for(i = 0; i < 2000; i++){
		test1.Insert_Prev(i);
		test1.ptr_node_next();
	}
	for(i = 0; i < 2000; i++){
		test1.Insert_Next(i);
		test1.ptr_node_prev();
	}
	test1.ptr_node_next();
	for(i = 0; i < 4000; i++)
		test1.Remove_node();
	test1.Show();
	test1.Clear();
	test1.Show();
	cout << "TEST 1 END" << endl << endl;
}

void test_2(){
	cout << "TEST 2" << endl;
	int i, j;
	lst* test2;
	test2 = new lst;
	for(i = 1; i < 6; i++){
		test2->Insert_Next(i*3);
		test2->ptr_node_next();
	}
	test2->ptr_node_next();
	test2->Show();
	cout << "SIZE = ";
	test2->Size();
	
	for(i = 0; i < 10000; i++){
		delete test2;
		test2 = new lst;
		for(j = 0; j < 4; j++){
			test2->Insert_Next(i*3);
			test2->ptr_node_next();
		}
		test2->ptr_node_next();
	}
	test2->Size();
	test2->Clear();
	cout << "SIZE = ";
	test2->Size();
	test2->Show();
	cout << "TEST 2 END" << endl << endl;
}

void test_3(){
	cout << "TEST 3" << endl;
	lst test31;
	int i;
	for(i = 0; i<5; i++){
		test31.Insert_Next(i);
		test31.ptr_node_next();
	}
	test31.ptr_node_next();
	test31.Show();
	lst test32 = test31;
	test32.Show();
	test32.Clear();
	test32.Show();
	test31.Clear();
	test31.Show();
	cout << "TEST 3 END" << endl << endl;
}

void test_4(){
	cout << "TEST 4 START" << endl;
	lst* test4;
	int i, x;
	test4 = new lst;
	for(i = 0; i<5; i++){
		test4->Insert_Next(i);
		test4->ptr_node_next();
	}
	test4->ptr_node_next();
	test4->Change_Prev(436);
	test4->Show();
	test4->Size();
	test4->Clear();
	test4->Show();
	delete test4;
	test4 = new lst;
	cout << endl << endl;
	test4->Insert_Next(3);
	test4->Insert_Next(5);
	test4->Insert_Next(7);
	test4->Insert_Next(78);
	test4->Read_Next(&x);
	cout << "X = " << x << endl;
	test4->Read_Current(&x);
	cout << "X = " << x << endl;
	test4->Read_Prev(&x);
	cout << "X = " << x << endl;
	test4->Show();
	test4->Change_Next(235);
	test4->Show();
	test4->Change_Prev(3333);
	test4->Show();
	test4->Change_Current(5737);
	test4->Show();
	delete test4;
	test4 = new lst;
	test4->Change_Next(12);
	cout << "TEST 4 END" << endl << endl;
}
