#include <iostream>
using namespace std;

class TreeNode {
  int value;
  TreeNode *prev, *left, *right;
  TreeNode(int m = 0) { value = m; prev = left = right = NULL; }
  friend class Tree;
};

class Tree {
	private:

		int N;

		TreeNode *root;
		TreeNode *DirectSearch(int x, TreeNode *curr);
		void Udal(TreeNode *pos);
		void ShowUD(TreeNode *pos);
		void ShowDU(TreeNode *pos);
		void ShowHoriz(TreeNode *pos, int level);

	public:

		Tree();
		~Tree();
		int RootValue(int *);
		int AddElement(int);
		int DeleteElement(int);
		void Search(int);
		void ShowUD( ) {ShowUD(root); cout<<endl;}
		void ShowDU( ) {ShowDU(root); cout<<endl;}

		int distance(int a, int b);

};

Tree::Tree() { root = NULL; N = 0; }

Tree::~Tree() { Udal(root); }

void Tree::Udal(TreeNode *Curr) {
	if (!Curr) return;
	Udal(Curr->left);
	Udal(Curr->right);
	delete(Curr);
}

int Tree::RootValue(int *u) {
	if (root) {*u = root-> value; return 1;}
	else {cout << "void tree" << endl; return 0;}
}

int Tree::AddElement(int x) {
	if (!root) {
		root = new TreeNode(x);
		N++;
		return 1;
	}
	TreeNode *pos, *pos_before;
	int dir;
	pos = root;
	while (pos) {
		pos_before = pos;
			 if (x < pos->value) { pos = pos->left; dir=0; }
		else if (x > pos->value) { pos = pos->right; dir=1; }
		else					 { cout << x << " already is in the tree" << endl; return 0;}
	}
	pos = new TreeNode(x);
	if (dir==0) pos_before->left = pos;
	else		pos_before->right = pos;
	pos->prev = pos_before;
	N++;
	return 1;
}

int Tree::DeleteElement(int x) {
	TreeNode *pos=NULL, *pos_of_x=NULL;
	pos_of_x = DirectSearch(x, root);
	if ( !pos_of_x ) {cout << x << " is absent" << endl; return 0;}

																		
	cout << "Deleting " << x << endl;
	pos = pos_of_x;
	if((pos->left != NULL) && (pos->right != NULL))		
	{ pos=pos->left;													
	  while (pos->right) pos=pos->right;								
      pos_of_x->value=pos->value;										
    }

    if (pos->left == NULL && pos->right == NULL)						
    {   if(pos->prev->left==pos) pos->prev->left=NULL;					
		else pos->prev->right=NULL;										

	}
	else if (pos->left != NULL) {										
			if (pos->prev->left == pos) pos->prev->left = pos->left;	
			else pos->prev->right = pos->left;							
			pos->left->prev = pos->prev;								
		}
	else if (pos->right != NULL) {										
			if (pos->prev->right == pos) pos->prev->right = pos->right;	
			else pos->prev->left = pos->right;							
			pos->right->prev = pos->prev;								
		}
	delete pos;															
	N--;
	return 1;															
}


void Tree::ShowUD(TreeNode *pos) {
	if (!pos) {
		return;
	}
	cout << pos->value << " ";
	ShowUD(pos->left);
	ShowUD(pos->right);
}

void Tree::ShowDU(TreeNode *pos) {
	if (!pos) {
		return;
	}
	ShowDU(pos->left);
	ShowDU(pos->right);
	cout << pos->value << " ";
}


void Tree::Search(int x) {
	TreeNode *Searched = DirectSearch(x, root);
	if (Searched!=NULL) cout << "Searched=" << Searched->value << endl;
	else cout << "Searched=NULL" << endl;
}

TreeNode *Tree::DirectSearch(int x, TreeNode *start) {
	while ( start ) {
		if (x == start->value) break;
		start = (x < start->value) ?
			start->left : start->right; 
	}
	return start;
}

int Tree::distance(int a, int b) {
    TreeNode *aa=root, *bb=root;
    int ka=0, kb=0, flag=0;
    while ( 1 ) {
		if(a==aa->value){flag=1; bb = (b < bb->value) ? bb->left : bb->right; break;}
		if(b==bb->value){flag=2; aa = (a < aa->value) ? aa->left : aa->right; break;}
		aa = (a < aa->value) ? aa->left : aa->right;
		bb = (b < bb->value) ? bb->left : bb->right;
		if(aa != bb) break;
	}
	while( 1 ) {if(flag!=1){
		ka++;}
        if (a == aa->value) break;
		aa = (a < aa->value) ? aa->left : aa->right;
	}
	cout<<ka<<endl;
	while( 1 ) {if(flag!=2){
        kb++;}
        if (b == bb->value) break;
		bb = (b < bb->value) ? bb->left : bb->right;
	}
	cout<<kb<<endl;
	return ka+kb;
}

int main() {
	Tree d;
	cout<<"chisla na vvod"<<endl;
	for (int i=1;i<=16;i++) {d.AddElement( (5*i + 3)%16 + 1 ); cout<<(5*i + 3)%16 + 1<<" ";}
	cout<<endl<<endl;
	d.ShowUD();
	d.ShowDU();
	int a=412, b=124;
	if(a==b){ cout<<" 0 "; return 0;}
    cout << "distance between "<<a<<" and "<<b<<" = " << d.distance(a,b);
	return 0;
}

