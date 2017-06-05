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
		}
		else
		{
			(prev->key > newNode->key ? prev->left_child : prev->right_child) = newNode;
			newNode->parent = prev;
		}
		// balancing tree

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
	for (int i = 0; i < 3000; i++)
	{
		int elem = rand() % 300;
		tree.add_element(i);
		arr.push_back(elem);
	}
	std::sort(arr.begin(), arr.end(), cmp);
	/*printf("Array: \n");
	for (int i = 0; i < arr.size(); i++)
	{
		printf("%4d", arr[i]);
	}
	printf("\nFrom tree:\n");
	tree.print_sorted(tree.get_root());
	printf("\n");*/
	printf("Count nodes: %4d log(count_nodes): %4.1f\n", tree.get_count_nodes(), log2(tree.get_count_nodes()));
	printf("Tree high: %4d\n", tree.get_high(tree.get_root())-1);
	system("pause");
	return 0;
}

