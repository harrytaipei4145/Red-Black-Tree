#include<iostream>
// change this to your id
static const char* student_id = "0211261";


void Insert(int *, int);
void Delete(int *, int);
int Select(int *, int);
int Rank(int *, int);



class rbtree
{
public:
	rbtree();
	rbtree(int a, int b,int c);
	~rbtree();
	
	int color;
	int key;
	int set;
	int arr;
	rbtree *right;
	rbtree *left;
	rbtree *parent;
	friend class operate;
};
// do not edit prototype


rbtree::~rbtree()
{

}
rbtree::rbtree()
{
	color = 0;
	key = 0;
	left = NULL;
	right = NULL;
	parent = NULL;
	set = 0;
	arr = 0;
}
rbtree::rbtree(int a,int b,int c)
{
	color = a;
	key = b;
	left = NULL;
	right = NULL;
	parent = NULL;
	set = c;
	arr = 0;
}
class operate
{
public:
	operate();
	void arr_to_node(int*);
	void node_to_arr( int*);
	void newleft(rbtree*, int, int*);
	void newright( rbtree*, int, int*);
	void insert(int *, int);
	void del(int *, int);
	void fixup(int *, rbtree*);
	void d_fixup(int *, rbtree*);
	void left_rotate(int *, rbtree *);
	void right_rotate(int *, rbtree *);
	void transplant(int *, rbtree *, rbtree *);
	int select(rbtree*, int);
	int rank(rbtree*, int);
	int select_void(int*, int);
	int rank_void(int*, int);
	void d(rbtree*);
	rbtree* find(int, rbtree*);
private:
	rbtree *head;
	rbtree *nil;
	rbtree* getleft(rbtree*, int,int*);
	rbtree* getright(rbtree*,  int,int*);

};
operate::operate() {
	head = NULL;
	nil= NULL;
}

//dtor

rbtree* operate::getleft(rbtree* pa, int position,int* tree)
{
	rbtree *l = new rbtree();
	int l_pos = position * 2;
	if (l_pos > *(tree+0))
		return NULL;
	else
	{
		if (*(tree + l_pos - 1) == 0)
			return nil;
		else if (*(tree + l_pos - 1) == -1)
			return NULL;
		else
		{
			l->parent = pa;
			l->color = *(tree + l_pos - 2);
			l->key = *(tree + l_pos - 1);
			l->set = *(tree + l_pos);
			l->arr = l_pos;
			l->left = getleft(l, l_pos, tree);
			l->right = getright(l,  l_pos, tree);
			return l;
		}
	}
	



}
rbtree* operate::getright(rbtree* pa,int position, int* tree)
{
	rbtree *r = new rbtree();
	int r_pos = position * 2+3;
	if (r_pos > *(tree + 0))
		return NULL;
	else
	{
		if (*(tree + r_pos - 1) == 0)
			return nil;
		else if (*(tree + r_pos - 1) == -1)
			return NULL;
		else
		{
			r->parent = pa;
			r->color = *(tree + r_pos - 2);
			r->key = *(tree + r_pos - 1);
			r->set = *(tree + r_pos);
			r->arr = r_pos;
			r->left = getleft(r,r_pos, tree);
			r->right = getright(r, r_pos, tree);
			return r;
		}
	}



}

void operate::arr_to_node(int* tree)
{
			head->color = *(tree+1);
			head->key = *(tree + 2);
			head->set = *(tree + 3);
			head->arr = 3;
			head->left = getleft(head ,3, tree);
			head->right = getright(head, 3, tree);
			head->parent = nil;
			
}
void operate::d(rbtree* a)
{

	if (a->right != NULL && a->right!=nil)
	{
		d(a->right);
	}
		
	if (a->left != NULL  && a->left != nil)
	{
		d(a->left);
	}
	delete a;
}
void  operate::node_to_arr( int* tree)
{
	for (int i = 1; i<(*tree + 0); i++)
	{
		*(tree + i) = -1;
	}
	if (head != NULL)
	{
		
		head->arr = 3;
		*(tree + 3) = head->set;
		*(tree + 2) = head->key;
		*(tree + 1) = head->color;

		if (head->right != NULL)
			newright(head, 3, tree);
		if (head->left != NULL)
			newleft(head, 3, tree);
		d(head);
		delete nil;
	}
	
	

}

rbtree* operate::find(int key, rbtree* f)
{
	rbtree *found;
	if (f != NULL) {
		if (f->key==key) {
			return f;
		}
		else {
			found = find(key, f->left);
			if (found == NULL) {
				found = find(key, f->right);
			}
			return found;
		}
	}
	else {
		return NULL;
	}
}

void operate::newleft(rbtree* pa,  int position, int* tree)
{
	operate *a = new operate();
	int pos = position * 2;
	pa->left->arr = pos;
	*(tree + pos) = pa->left->set;
	*(tree + pos-1) = pa->left->key;
	*(tree + pos-2) = pa->left->color;
	if (pa->left->right != NULL)
		a->newright(pa->left,  pos, tree);
	if (pa->left->left != NULL)
		a->newleft(pa->left, pos, tree);
}
void operate::newright(rbtree* pa, int position, int* tree)
{
	operate *a = new operate();
	int pos = position * 2+3;
	pa->right->arr = pos;
	*(tree + pos) = pa->right->set;
	*(tree + pos - 1) = pa->right->key;
	*(tree + pos - 2) = pa->right->color;
	if (pa->right->right != NULL)
		a->newright(pa->right, position * 2 + 3, tree);
	if (pa->right->left != NULL)
		a->newleft(pa->right,  position * 2 + 3, tree);
}
void operate::del(int * tree, int key) {


	rbtree *use_h =new rbtree();
	rbtree *x;
	rbtree *y;
	rbtree *z = new rbtree();
	rbtree *use_n = new rbtree();
	rbtree* temp;
	use_n->color = 0;
	use_n->key = 0;
	use_n->set = 0;
	nil = use_n;
	use_h->color = *(tree + 1);
	use_h->key = *(tree + 2);
	use_h->set = *(tree + 3);
	use_h->arr = 3;
	head = use_h;
	arr_to_node( tree);
	head->parent = nil;
	z = find(key, head);
	if (z == NULL)
	{
		node_to_arr( tree);
	}
	else
	{
		y = z;
		int y_color = y->color;
		if (z->left == nil)
		{
			x = z->right;
			transplant(tree, z, z->right);
			temp = z->parent;
			while (true)
			{
				if (temp == nil)
					break;
				temp->set = temp->set - 1;
				if (temp == head)
					break;
				else
				{
					temp = temp->parent;
				}
			}

		}
		else if (z->right == nil)
		{
			x = z->left;
			transplant(tree, z, z->left);
			temp = z->parent;
			while (true)
			{
				if (temp == nil)
					break;
				temp->set = temp->set - 1;
				if (temp == head)
					break;
				else
				{
					temp = temp->parent;
				}
			}
		}
		else
		{
			y = z->left;
			while (true)
			{

				if (y->right == nil)
					break;
				else
				{
					y = y->right;
				}

			}
			y_color = y->color;
			x = y->right;
			int check = 0;
			if (y->parent == z)
				x->parent = y;
			else
			{
				check = 1;
				transplant(tree, y, y->right);

				y->right = z->right;
				y->right->parent = y;
			}
			transplant(tree, z, y);

			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
			if (check == 0)
			{
				y->set = y->set + z->set - 1;
				temp = y->parent;
				while (true)
				{
					temp->set = temp->set - 1;
					if (temp == nil)
						break;
					if (temp == head)
						break;
					else
					{
						temp = temp->parent;
					}
				}
			}
			else
			{
				y->set = z->set - 1;
				temp = z->parent;
				while (true)
				{
					if (temp == nil)
						break;
					temp->set = temp->set - 1;
					if (temp == head)
						break;
					else
					{
						temp = temp->parent;
					}
				}
			}
		}

		if (y_color == 0)
			d_fixup(tree, x);


		node_to_arr( tree);
	}
	

}

void operate::insert(int * tree, int key) {
	rbtree *x;
	rbtree *y;
	rbtree *z = new rbtree();
	rbtree *use_n = new rbtree();
	rbtree *use_h = new rbtree();
	use_n->color = 0;
	use_n->key = 0;
	use_n->set = 0;
	nil=use_n;

	if (*(tree+1) == -1)
	{
		head = nil;
		rbtree* temp_r = new rbtree();
		rbtree* temp_l = new rbtree();
		use_h->color = 0;
		use_h->key = key;
		use_h->set = 1;
		use_h->arr = 3;
		use_h->right = nil;
		use_h->left = nil;
		head = use_h;
		nil->parent = head;
		nil->right = NULL;
		nil->left = NULL;
		head->parent = nil;
		node_to_arr( tree);
	}
	else
	{
		use_h->color = *(tree+1);
		use_h->key = *(tree + 2);
		use_h->set = *(tree + 3);
		use_h->arr = 3;
		head = use_h;
		arr_to_node(tree);
		x = head;
		y = nil;
		z->key = key;
		head->parent = nil;
		while (x != nil)
		{
			y = x;
			x->set = x->set + 1;
			if (z->key < x->key)
				x = x->left;
			else
				x = x->right;


		}
		z->parent = y;
		if (y == nil)
			head = z;
		else if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
		z->left = nil;
		z->right = nil;
		z->color = 1;
		z->set = 1;
		fixup(tree, z);

		node_to_arr(tree);
		
	}

}

// data structure : 
// tree is an array with enough space
// tree[0] is the array size
// bundle three attribute as a node data
// First attribute is color, "0" means black, "1" means red , NIL is also "0", "-1" means no data
// Second attribute is key, "0" means NIL, "1"~"999" means data,  "-1" means no data
// Third attribute is size, for Dynamic Order Statistics, "0" means NIL , "-1" means no data
//
// for example,
// if tree[0] is "256" says that the array size is 256
//
// if tree[1] is "1" says that the place of 1 is a red node
//
// if tree[2] is "5" says that the place of 1 is key of 5
//
// if tree[8] is "-1" says that the place of 3 has nothing
//
// if tree[14] is "0" says that the place of 5 is a node of NIL
//
// if tree[19] is "66" says that the place of 7 is key of 66

//
// if there is an ambiguous situation, choose the smaller ( left ) one
//

//
// do your homework here
//

void operate::fixup(int *tree, rbtree*z)
{
	rbtree *y;
	while (z->parent->color == 1)
	{
		if (z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if (y->color == 1)
			{
				z->parent->color = 0;
				y->color = 0;
				z->parent->parent->color = 1;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->right)
				{
					z = z->parent;
					left_rotate(tree, z);
				}
				z->parent->color = 0;
				z->parent->parent->color = 1;
				right_rotate(tree, z->parent->parent);
			}
		}
		else {
			y = z->parent->parent->left;
			if (y->color == 1) {
				z->parent->color = 0;
				y->color = 0;
				z->parent->parent->color = 1; 
				z = z->parent->parent;
			}

			else 
			{
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(tree, z);
				}

				z->parent->color = 0;
				z->parent->parent->color = 1;
				left_rotate(tree, z->parent->parent);
			}
		}
		
	}
	head->color = 0;
}
void operate::d_fixup(int *tree, rbtree*x)
{
	rbtree *w;
	while (x != head && x->color == 0)
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;
			if (w->color == 1)
			{
				w->color = 0;
				x->parent->color = 1;
				left_rotate(tree, x->parent);

				w = x->parent->right;
			}
			if (w->left->color == 0 && w->right->color == 0)
			{
				w->color = 1;
				x = x->parent;
			}
			else
			{
				if (w->right->color == 0)
				{
					w->left->color = 0;
					w->color = 1;
					right_rotate(tree, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 0;
				w->right->color = 0;
				
				left_rotate(tree, x->parent);
				x = head;
			}
			
			
		}
		else
		{
			w = x->parent->left;
			if (w->color == 1)
			{
				w->color = 0;
				x->parent->color = 1;
				right_rotate(tree, x->parent);
				w = x->parent->left;
			}
			if (w->left->color == 0 && w->right->color == 0)
			{
				w->color = 1;
				x = x->parent;
			}
			else
			{
				if (w->left->color == 0)
				{
					w->right->color = 0;
					w->color = 1;
					left_rotate(tree, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 0;
				w->left->color = 0;
				right_rotate(tree, x->parent);
				x = head;
			}
		}
	}
	x->color = 0;
}
void operate::right_rotate(int * tree, rbtree *x)
{
	rbtree *y;
	
	y = x->left;
	int save = x->set;
	x->set = x->set - y->set + y->right->set;
	y->set = save;
	x->left = y->right;

	if (y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		head = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	x->parent = y;
	
	

}
void operate::left_rotate(int * tree, rbtree *x)
{
	rbtree *y;
	
	y = x->right;
	int save = x->set;
	x->set = x->set - y->set + y->left->set;
	y->set = save;
	x->right = y->left;
	if (y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
	{
		head = y;
	}
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	
}

void operate::transplant(int *tree, rbtree *u, rbtree *v)
{
	if (u->parent == nil)
		head = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
	
}
int operate::select_void(int *tree, int i)
{
	if (*(tree + 1) != -1)
	{
		rbtree *use_h = new rbtree();
		rbtree *use_n = new rbtree();
		use_n->color = 0;
		use_n->key = 0;
		use_n->set = 0;
		nil = use_n;
		use_h->color = *(tree + 1);
		use_h->key = *(tree + 2);
		use_h->set = *(tree + 3);
		use_h->arr = 3;
		head = use_h;
		arr_to_node( tree);
		head->parent = nil;
		return select(head, i);
	}
	else
		return 0;
}
int operate::rank_void(int *tree, int i)
{
	if (*(tree + 1) != -1)
	{
		rbtree *use_h = new rbtree();
		rbtree *use_n = new rbtree();
		use_n->color = 0;
		use_n->key = 0;
		use_n->set = 0;
		nil = use_n;
		use_h->color = *(tree + 1);
		use_h->key = *(tree + 2);
		use_h->set = *(tree + 3);
		use_h->arr = 3;
		head = use_h;
		arr_to_node( tree);
		head->parent = nil;
		return rank(head, i);
	}
	else
		return 0;
}
int operate::select(rbtree*a, int i)
{
	if (a->left != NULL)
	{
		int temp = a->left->set;
		if (i == temp)
			return a->key;
		else if (i<temp)
		{
			if (a->left != NULL)
				return  select(a->left, i);
			else
				return 0;
		}

		else
		{
			if (a->right != NULL)
				return select(a->right, i - temp - 1);
			else
				return 0;
		}
	}
	else
		return 0;
	
		
}
int operate::rank(rbtree* a, int i)
{
	rbtree* b;
	if (a->left != NULL)
	{
		int temp = a->left->set + 1;
		b = a;
		while (b != head)
		{
			if (b == b->parent->right)
			{
				temp = temp + b->parent->left->set + 1;

			}
			b = b->parent;
		}
		return temp;
	}
	else
		return 0;
}
void Insert(int * tree, int key) {
	operate *r = new operate();
	r->insert(tree, key);
	delete r;
}

void Delete(int * tree, int key) {
	operate *r = new operate();
	r->del(tree, key);
	delete r;
}

int Select(int * tree, int i) {
	// use Dynamic Order Statistics to return the i'th smallest element
	operate *r = new operate();
	i = i - 1;
	return r->select_void(tree, i);
	delete r;
	
}

int Rank(int * tree, int x) {
	// use Dynamic Order Statistics to return the rank of element x in the tree
	operate *r = new operate();

	return r->rank_void(tree, x);
	delete r;
}
