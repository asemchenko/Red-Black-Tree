// RedBlackTree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <math.h>
template<typename keyT>
class RedBlackTree
{
	enum NodeColor
	{
		red,
		black
	};
	struct Node
	{
		Node* left_child;
		Node* right_child;
		Node* parent;
		keyT key;
		NodeColor color;
	};
public:
	~RedBlackTree()
	{
		erase_memory(root);
	}
	void erase_memory(Node* start_vertex)
	{
		if (start_vertex)
		{
			erase_memory(start_vertex->right_child);
			erase_memory(start_vertex->left_child);
			if (start_vertex->parent != NULL)
			{
				((start_vertex->parent->left_child == start_vertex) ? start_vertex->parent->left_child : start_vertex->parent->right_child) = NULL;
			}
			else
			{
				root = NULL;
			}
			delete start_vertex;
			count_nodes--;
		}
	}
	Node* get_root()
	{
		return root;
	}
	int get_count_nodes()
	{
		return count_nodes;
	}
	void print_sorted(Node* start)
	{
		if (start)
		{
			print_sorted(start->left_child);
			printf("%4d", start->key);
			print_sorted(start->right_child);
		}
	}
	void add_element(keyT element_key)
	{
		count_nodes++;
		Node* newNode = new Node;
		newNode->key = element_key;
		newNode->left_child = NULL;
		newNode->right_child = NULL;
		newNode->color = red;
		// adding element as in binary search tree
		Node* prev = NULL;
		Node* cur = root;
		while (cur)
		{
			prev = cur;
			cur = ((cur->key > newNode->key) ? cur->left_child : cur->right_child);
		}
		if (prev == NULL) // if we adding element in empty tree
		{
			root = newNode;
			newNode->parent = NULL;
			root->color = black;
			return;
		}
		else
		{
			(prev->key > newNode->key ? prev->left_child : prev->right_child) = newNode;
			newNode->parent = prev;
		}
		// balancing tree
		Node* y;
		Node* x = newNode;
		while ((newNode != NULL)&&(x->parent->color == red))
		{
			// finding uncle (y)
			if (x->parent == x->parent->parent->left_child) // if uncle - right child
			{
				y = x->parent->parent->right_child;
				if ((y != NULL) && (y->color == red)) // if uncle is red
				{
					x->parent->color = black;
					x->parent->parent->color = red;
					y->color = black;
					x = x->parent->parent;
				}
				else // if uncle is black
				{
					if (x == x->parent->right_child) // if x - right child
					{
						x = x->parent;
						LeftRotation(x);
					}
					x->parent->color = black;
					x->parent->parent->color = red;
					RightRotation(x->parent->parent);
				}
			}
			else // if uncle - left child
			{
				y = x->parent->parent->left_child;
				if ((y != NULL) && (y->color == red))
				{
					x->parent->color = black;
					x->parent->parent->color = red;
					y->color = black;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->left_child)
					{
						x = x->parent;
						RightRotation(x);
					}
					x->parent->color = black;
					x->parent->parent->color = red;
					LeftRotation(x->parent->parent);
				}
			}
			root->color = black;
		}
	}
	int get_high(Node* startNode)
	{
		if (startNode)
		{
			int left_high = get_high(startNode->left_child);
			int right_high = get_high(startNode->right_child);
			return (left_high > right_high ? left_high : right_high) + 1;
		}
		return 0;
	}
	void print(Node* start)
	{
		if (start)
		{
			printf("Node: %4d	Parent: %4d		Right: %4d		Left: %4d\n", start->key, (start->parent ? start->parent->key : 0), (start->right_child ? start->right_child->key : 0), (start->left_child ? start->left_child->key : 0));
			print(start->right_child);
			print(start->left_child);
		}
	}
	void RightRotation(Node* x)
	{
		Node* y = x->right_child;
		y->parent = x->parent;
		if (x->parent != NULL)
		{
			((x->parent->left_child == x) ? x->parent->left_child : x->parent->right_child) = y;
		}
		else
		{
			y->parent = NULL;
			root = y;
		}
		x->right_child = y->left_child;
		if (x->right_child != NULL)
		{
			x->right_child->parent = x;
		}
		y->left_child = x;
		x->parent = y;
	}
	void LeftRotation(Node* x)
	{
		Node* y = x->left_child;
		y->parent = x->parent;
		if (x->parent)
		{
			(x->parent->left_child == x ? x->parent->left_child : x->parent->right_child) = y;
		}
		else
		{
			root = y;
		}
		x->left_child = y->right_child;
		if (x->left_child)
		{
			x->left_child->parent = x;
		}
		y->right_child = x;
		x->parent = y;
	}
private:
	Node* root = NULL;
	int count_nodes = 0;
};

bool cmp(int a, int b)
{
	return a < b;
}
int main()
{
	srand(time(NULL));
	RedBlackTree<int> tree;
	std::vector<int> arr;
	int a[] = { 7,3,16,9,25 };
	for (int i = 0; i < 100; i++)
	{
		int elem = rand() % 30;
		tree.add_element(i);
		arr.push_back(elem);
	}
	std::sort(arr.begin(), arr.end(), cmp);
	std::cout << "High tree: " << tree.get_high(tree.get_root()) << std::endl;
	tree.print_sorted(tree.get_root());
	system("pause");
	return 0;
}

