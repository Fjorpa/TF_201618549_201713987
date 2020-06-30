#ifndef __ARBOL_H__
#define __ARBOL_H__
#include <functional>
using namespace std;

#define max(a, b) (a > b? a : b)

template <typename T, typename R=T>
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
	Arbol() : root(nullptr), len(0) {}
	/*Arbol(function<R(T)> key = [](T a) {return a; }) : key(key),
		root(nullptr), len(0) {}*/
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
	T find(R val) {
		return find(root, val);
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
	T find(Node* node, R val) {
		if (node == nullptr)
			return 0;
		else if (val == key(node->elem))
			return node->elem;
		else if (val < key(node->elem))
			return find(node->left, val);
		else
			return find(node->right, val);
	}
	T greaterThan(Node* node, R val) {
		if (node == nullptr)
			return 0;
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