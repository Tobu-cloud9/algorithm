// Treap 実装
//https://www.slideshare.net/iwiwi/2-12188757

#include <iostream>
#include <string>

using namespace std;

struct node_t {
	int val; //value
	node_t* ch[2]; //={left, right}
	int pri; //priority
	int cnt; //subtree size
	int sum; //sum of subtree values

	node_t(int v, double p) : val(v), pri(p), cnt(1), sum(v) {
		ch[0] = ch[1] = NULL;
	}
};


// Treap Update
int count(node_t* t) { return !t ? 0 : t->cnt; }
int sum(node_t* t) { return !t ? 0 : t->sum; }

node_t* update(node_t* t) {
	t->cnt = count(t->ch[0]) + count(t->ch[1]) + 1;
	t->sum = sum(t->ch[0]) + sum(t->ch[1]) + t->val;
	return t;
}

// Treap Rotate (insert-erase)
node_t* rotate(node_t* t, int b) {
	node_t* s = t->ch[1 - b];
	t->ch[1 - b] = s->ch[b];
	update(t); update(s);
	return s;
}

/*
* tが根となっている木のk番目に値val, 優先度priのノード挿入
* 根のノードを返す
*/
// Treap Insert (insert-erase)
node_t* insert(node_t* t, int k, int val, double pri) {
	if (!t) return new node_t(val, pri);
	int c = count(t->ch[0]), b = (k > c);
	t->ch[b] = insert(t->ch[b], k = (b ? (c + 1) : 0), val, pri);
	update(t);
	if (t->pri > t->ch[b]->pri) t = rotate(t, 1 - b);
}
