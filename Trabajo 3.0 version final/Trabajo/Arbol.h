#ifndef __ARBOL_H__
#define __ARBOL_H__
#include <functional>
#include <vector>
using namespace std;

#define max(a, b) (a > b? a : b)

template <typename T, typename R = T, T NONE = 0>
class Arbol {
	struct Node {
		T elem;
		Node* left;
		Node* right;
		int height;

		Node(T elem) : elem(elem), left(nullptr), right(nullptr), height(0) {}
	};
	Node* root;
	function<R(T)> key;
	int len;
public:
	Arbol(function<R(T)> key = [](T a) {return a; }) : key(key),
		root(nullptr), len(0) {}
	~Arbol() {
		clear(root);
	}
	int height() {
		return height(root);
	}
	int size() {
		return len;
	}
	void clear() {
		clear(root);
		len = 0;
	}
	void add(T elem) {
		add(root, elem);
	}
	void find(R val, vector<T>& v) {
		find(root, val, v);
	}
	void findX(R val, vector<T>& v) {
		findX(root, val, v);
	}
	void findMa(R val, vector<T>& v) {
		findMa(root, val, v);
	}
	void findMi(R val, vector<T>& v) {
		findMi(root, val, v);
	}
	T greaterThan(R val) {
		return greaterThan(root, val);
	}
	void inorder(function<void(T)> proc) {
		inorder(root, proc);
	}
private:
	void clear(Node*& node) {
		if (node != nullptr) {
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
	}
	int height(Node* node) {
		return node == nullptr ? -1 : node->height;
	}
	void add(Node*& node, T elem) {
		if (node == nullptr) {
			node = new Node(elem);
			len++;
		}
		else {
			if (key(elem) < key(node->elem))
				add(node->left, elem);
			else
				add(node->right, elem);
			balance(node);
		}
	}
	void find(Node* node, R val, vector<T>& v) {
		if (node == nullptr)
			return;
		else if (val == key(node->elem)) {
			v.push_back(node->elem);
			find(node->left, val, v);
			find(node->right, val, v);
		}
		else if (val < key(node->elem))
			find(node->left, val, v);
		else
			find(node->right, val, v);
	}
	bool elveinte(string elem, string comp) {
		size_t found = elem.find(comp);
		if (found != string::npos)
			return true;
		return false;
	}
	void findX(Node* node, R val, vector<T>& v) {
		if (node == nullptr)
			return;
		else if (elveinte(key(node->elem), val)) {
			v.push_back(node->elem);
			findX(node->left, val, v);
			findX(node->right, val, v);
		}
		else if (val < key(node->elem))
			findX(node->left, val, v);
		else
			findX(node->right, val, v);
	}
	void findMa(Node* node, R val, vector<T>& v) {
		if (node == nullptr)
			return;
		else if (val == key(node->elem))
			findMa(node->right, val, v);
		else if (val < key(node->elem)) {
			v.push_back(node->elem);
			findMa(node->left, val, v);
			findMa(node->right, val, v);
		}
		else
			findMa(node->right, val, v);
	}
	void findMi(Node* node, R val, vector<T>& v) {
		if (node == nullptr)
			return;
		else if (val == key(node->elem))
			findMi(node->left, val, v);
		else if (val < key(node->elem))
			findMi(node->left, val, v);
		else {
			v.push_back(node->elem);
			findMi(node->left, val, v);
			findMi(node->right, val, v);
		}
	}
	T greaterThan(Node* node, R val) {
		if (node == nullptr)
			return NONE;
		else if (val < key(node->elem))
			return node->elem;
		return greaterThan(node->right, val);
	}
	void inorder(Node* node, function<void(T)> proc) {
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->elem);
			inorder(node->right, proc);
		}
	}
	void updateHeight(Node* node) {
		if (node != nullptr) {
			int hl = height(node->left);
			int hr = height(node->right);

			node->height = max(hl, hr) + 1;
		}
	}
	void rotateLeft(Node*& node) {
		Node* aux = node->right;
		node->right = aux->left;
		updateHeight(node);
		aux->left = node;
		updateHeight(aux);
		node = aux;
	}
	void rotateRight(Node*& node) {
		Node* aux = node->left;
		node->left = aux->right;
		updateHeight(node);
		aux->right = node;
		updateHeight(aux);
		node = aux;
	}
	void balance(Node*& node) {
		int hl = height(node->left);
		int hr = height(node->right);

		if (hr - hl < -1) {
			hl = height(node->left->left);
			hr = height(node->left->right);
			if (hr > hl)
				rotateLeft(node->left);
			rotateRight(node);
		}
		else if (hr - hl > 1) {
			hl = height(node->right->left);
			hr = height(node->right->right);
			if (hl > hr)
				rotateRight(node->right);
			rotateLeft(node);
		}
		else
			updateHeight(node);
	}
};

#endif