/*********************************************************************************
*File: Tree.h
*Author: Onur Ozuduru
*   e-mail: onur.ozuduru { at } gmail.com
*   github: github.com/onurozuduru
*   twitter: twitter.com/OnurOzuduru
*
*License: The MIT License (MIT)
*
*   Copyright (c) 2015 Onur Ozuduru

*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*  
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*  
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*********************************************************************************/

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
