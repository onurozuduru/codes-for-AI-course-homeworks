/*********************************************************************
*File: Tree.h
*Author: Onur Ozuduru
*   e-mail: onur.ozuduru { at } gmail.com
*   github: github.com/onurozuduru
*   twitter: twitter.com/OnurOzuduru
*
*License: This work is licensed under the
*   Creative Commons Attribution-ShareAlike 4.0 International License.
*   To view a copy of this license,
*   visit http://creativecommons.org/licenses/by-sa/4.0/.
***********************************************************************/

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node
{
    vector<char> state;
    int score;
    vector<Node *> children;
    Node(vector<char> &s, int sc = 0, Node *c = NULL) {
	    score = sc;
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
