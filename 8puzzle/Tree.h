/*
Developed by:
name:			Onur Ozuduru
github page:	https://github.com/onurozuduru
twitter:		https://twitter.com/OnurOzuduru

This work is licensed under the Creative Commons Attribution 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.
*/

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node
{
	vector<int> state;
	string moves;
	vector<Node *> children;
	Node(vector<int> &s, string m = "", Node *c = NULL) {
		moves = m;
		state = s;
		
		addChild(c);
	}
	Node(Node *c = NULL) {
		addChild(c);
	}
	void addChild(Node *c) {
		if(c != NULL)
			children.push_back(c);
	}
};

class Tree
{
private:
	Node *root;
public:
	Tree(Node *r) {
		root = r;
	}
	
	Node* getRoot() {return root;}
};

#endif
