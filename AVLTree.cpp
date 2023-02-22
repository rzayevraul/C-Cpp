#include <iostream>
#include <fstream>

using namespace std;
void Test_1();
void Test_2();
void Test_3();

class Tree_Node{
  public:
	int value;
	int balance;
	Tree_Node* left;
	Tree_Node* right;
	Tree_Node() {left = right = NULL; value = balance = 0;}
};

class Tree{
	public:
		Tree_Node* root;
		Tree() {root = NULL;}
		~Tree() {Cut(root);}
		void up_down(Tree_Node *n);
		void Cut(Tree_Node *n);
		Tree_Node* Left_Left_Rotate(Tree_Node* A);
		Tree_Node* Big_Left_Rotate(Tree_Node* A);	
		Tree_Node* Right_Right_Rotate(Tree_Node* A);	
		Tree_Node* Big_Right_Rotate(Tree_Node* A);
		Tree_Node* Insert_Element(int v, Tree_Node* root, int* grow);		
		Tree_Node* Delete_Element(int v, Tree_Node* root, int* grow);
};

void Tree::up_down(Tree_Node* n){
	if(n==NULL) return;
	cout << " " << n->value ;
	up_down(n->left);
	up_down(n->right);
}

void Tree::Cut(Tree_Node* n){
	if(n==NULL) return;
	Cut(n->left);
	Cut(n->right);
	delete n;
}

Tree_Node* Tree::Left_Left_Rotate(Tree_Node* A){
	Tree_Node* B;
	B = A->left;
	A->left = B->right;
	B->right = A;
	if(B->balance){
		A->balance = 0;
		B->balance = 0;
	}
	else{
		A->balance = -1;
		B->balance = 1;
	}
	return B;
}

Tree_Node* Tree::Big_Left_Rotate(Tree_Node* A){
	Tree_Node* B;
	Tree_Node* C;
	B = A->left;
	C = B->right;
	A->left = C->right;
	B->right = C->left;
	C->left = B;
	C->right = A;
	switch(C->balance){
		case-1: A->balance = 1; B->balance = 0; break;
		case 0: A->balance = 0; B->balance = 0; break;
		case 1: A->balance = 0; B->balance = -1;
	}
	C->balance = 0;
	return C;
}

Tree_Node* Tree::Right_Right_Rotate(Tree_Node* A){
	Tree_Node *B;
	B = A->right;
	A->right = B->left;
	B->left = A;
	if(B->balance){
		A->balance = 0;
		B->balance = 0;
	}
	else{
		A->balance = 1;
		B->balance = -1;
	}
	return B;
}

Tree_Node* Tree::Big_Right_Rotate(Tree_Node* A){
	Tree_Node* B;
	Tree_Node* C;
	B = A->right;
	C = B->left;
	B->left = C->right;
	A->right = C->left;
	C->left = A;
	C->right = B;
	switch(C->balance){
		case-1: A->balance = 0; B->balance = 1; break;
		case 0: A->balance = 0; B->balance = 0; break;
		case 1: A->balance = -1; B->balance = 0;
	}
	C->balance = 0;
	return C;
}

Tree_Node* Tree::Insert_Element(int v, Tree_Node* root, int* grow){
	int incr;
	*grow = 0;
	if(!root){
	    root = new Tree_Node;
		root->value = v; 
		root->left=root->right = NULL; 
		root->balance=0; 
		*grow = 1;
		return root;
	}
	if(v<root->value){
		root->left = Insert_Element(v, root->left, &incr);
		if(incr){
			switch(root->balance){
				case -1:
					switch(root->left->balance){
						case -1: root = Left_Left_Rotate(root); break;
						case  1: root = Big_Left_Rotate(root);
					}
					break;
				case 0: root->balance = -1; *grow = 1; break;
				case 1: root->balance = 0;
			}
		}
		return root;
	}
	if(v>root->value){
		root->right = Insert_Element(v, root->right, &incr);
		if(incr){
			switch(root->balance){
				case-1: root->balance = 0; break;
				case 0: root->balance = 1; *grow = 1; break;
				case 1:
					switch(root->right->balance){
						case-1: root = Big_Right_Rotate(root); break;
						case 1: root = Right_Right_Rotate(root);
					}
			}
		}
	}
	return root;
}

Tree_Node* Tree::Delete_Element(int v, Tree_Node* root, int* grow){
	int incr;
	Tree_Node* n;
	*grow = 0;
	if(!root) return 0;
	if(v==root->value){
		if(root->left==0){
			*grow = -1;
			root = root->right;
			return root;
		}
		if(root->right==0){
			*grow = -1;
			root = root->left;
			return root;
		}
		for(n = root->left; n->right;)
			n = n->right;
		root->value = n->value;
		root->left = Delete_Element(n->value, root->left, &incr);
		if(incr){
			switch(root->balance){
				case-1: root->balance = 0; *grow = -1; break;
				case 0: root->balance = 1; break;
				case 1:
					switch(root->right->balance){
						case-1: root = Big_Right_Rotate(root); *grow = -1; break;
						case 0: root = Right_Right_Rotate(root); break;
						case 1: root = Right_Right_Rotate(root); *grow = -1; 
					}
			}
		}
	}
	else{
		if(v<root->value){
			root->left = Delete_Element(v, root->left, &incr);
			if(incr){
				switch(root->balance){
					case-1: root->balance = 0; *grow = -1; break;
					case 0: root->balance = 1; break;
					case 1:
						switch(root->right->balance){
							case-1: root = Big_Right_Rotate(root); *grow = -1; break;
							case 0: root = Right_Right_Rotate(root); break;
							case 1: root = Right_Right_Rotate(root); *grow = -1;
						}
				}
			}
		}
		else{
			root->right = Delete_Element(v, root->right, &incr);
			if(incr){
				switch(root->balance){
					case 1: root->balance = 0; *grow = -1; break;
					case 0: root->balance = -1; break;
					case-1:
						switch(root->left->balance){
							case-1: root = Left_Left_Rotate(root); *grow = -1; break;
							case 0: root = Left_Left_Rotate(root); break;
							case 1: root = Big_Left_Rotate(root); *grow = -1;
						}
				}
			}
		}
	}
	return root;
}

int main(){
	Tree avl;
	ifstream mytxt("avltrees.txt");
	int grow, v;
	while(mytxt >> v){
		cout << v << endl;
		avl.root = avl.Insert_Element(v, avl.root, &grow);
	}
	avl.up_down(avl.root);
	cout << endl;
	Test_1();
	Test_2();
	Test_3();
}

void Test_1(){
	cout << "Test 1" << endl;
	int grow = 0, i;
	Tree avl;
	for(i = 0; i < 10; i++){
		if (i%2!=0) avl.root = avl.Insert_Element(i, avl.root, &grow);
		else avl.root = avl.Insert_Element(20-i, avl.root, &grow);
		cout << endl << " up-to-down " << endl;
		avl.up_down(avl.root);
	}
	cout << endl << endl;
}

void Test_2(){
	cout << "Test 2" << endl;
	int grow = 0, i, j, k;
	Tree *avl;
	avl = new Tree;
	for(i = 0; i < 10; i++){
		if (i%2!=0) avl->root = avl->Insert_Element(i, avl->root, &grow);
		else avl->root = avl->Insert_Element(20-i, avl->root, &grow);
	}
	avl->up_down(avl->root);
	cout << endl;
	i++;
	for(k = 0; k < 100000; k++){
		delete avl;
		avl = new Tree;
		for(j = 0; j < 3; j++, i++){
			if (i%2!=0) avl->root = avl->Insert_Element(i, avl->root, &grow);
			else avl->root = avl->Insert_Element(-i, avl->root, &grow);
		}
	}
	avl->up_down(avl->root);
	cout << endl;
}

void Test_3(){
	cout << "Test 3" << endl;
	Tree avl;
	int grow = 0, i;
	for(i = 0; i < 100000; i++)
		avl.root = avl.Insert_Element(i, avl.root, &grow);
	for(i = 20; i < 100000; i++)
		avl.root = avl.Delete_Element(i, avl.root, &grow);
	avl.up_down(avl.root);
	cout << endl;
}
