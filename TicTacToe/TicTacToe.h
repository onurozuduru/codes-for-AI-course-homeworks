/*********************************************************************************
*File: TicTacToe.h
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

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <queue>
#include "Tree.h"

class TicTacToe
{
private:
    vector<char> state;
    char comp, user;
    Tree *moves;
    int nCount;
    int minimaxCount;
    int maxCount;
    int mC;
public:
    // If p is true( or 1) computer takes X, user takes O;
    // If p is false( or 0) computer takes O, user takes X.
    // Default value for p is false (computer takes 0).
    TicTacToe(bool p = false) {
	    char s[] = {'1','2','3','4','5','6','7','8','9'};
	    nCount = 0;
	    minimaxCount = maxCount = mC = 0;
	    for(int i = 0; i<9; ++i)
		    state.push_back(s[i]);
	
	    comp = (p) ? 'X' : 'O';
	    user = (p) ? 'O' : 'X';
	
	    if(comp == 'X') {
		    generate(state);
		    cout<<"Generated\n\n";
		    showState();
		    int test = minimax(state);
		    cout<<"index move: "<<test<<endl<<"Traveled Node: "<<minimaxCount<<endl;
		    if(minimaxCount > maxCount) {
			    maxCount = minimaxCount;
			    mC = nCount;
		    }
		    minimaxCount = 0;
		    move(comp,test);
	    }
	    else {
		    showState();
		    waitMove();
		    generate(state);
		    cout<<"Generated\n";
		    int test = minimax(state);
		    cout<<"index move: "<<test<<endl;
		    move(comp,test);
		    showState();
	    }
	
    }

    ~TicTacToe() {
	    if(moves != NULL){
	    //Using BFS for destructor
		    queue<Node *> del;
		    del.push(moves->getRoot());

		    while(!del.empty()){
			    Node *tmp = del.front();
		
			    if(!tmp->children.empty()){
				    for(int i = 0; i < tmp->children.size(); i++)
					    del.push(tmp->children[i]);
			    }
			    del.pop();
			    delete tmp;				
		    }
	    }
	    delete moves;
    }

    //Tree generator
    void generate(vector<char> s) {		
	    Node *pNode = new Node(s);
	    moves = new Tree(pNode);
	
	    int count = 0;
	    queue<Node *> q;
	    q.push(moves->getRoot());

	    while(!q.empty()){
		    Node *tmp = q.front();
		    s = tmp->state;
		    count = setCount(s);
		    if(isFinished(s) == 0) {
			    for(int i=0; i<9; ++i) {
				    if(isAvailable(i,s)) {
					    vector<char> nS = s;
					    nS[i] = (count%2 == 0) ? comp : user;
					    int fin = isFinished(nS);
					    if(fin == 0 || fin == -1){
						    Node *nNode = new Node(nS);
						    tmp->addChild(nNode);
					    }
					    else if(fin == 1) {
						    Node *nNode = new Node(nS, 1);
						    tmp->addChild(nNode);
					    }
					    else if(fin == 2) {
						    Node *nNode = new Node(nS, -1);
						    tmp->addChild(nNode);
					    }
				    }
			    }
			    if(!tmp->children.empty()){
				    for(int i = 0; i < tmp->children.size(); ++i)
					    q.push(tmp->children[i]);
			    }
		    }
		    q.pop();
	    }
    }

    int setCount(vector<char> &s) {
	    int count;
	    count = (comp == 'X') ? 0 : 1;
	    for(int i=0; i < s.size(); ++i) {
		    if(s[i] == 'X' || s[i] == 'O')
			    ++count;
	    }
	    return count;
    }

    void play() {
	    showState();
	    bool turn = (comp == 'X') ? 0 : 1;
	    while(!isFinished(state)) {
		    if(nCount % 2 == turn) {
		    int test = minimax(state);
		    cout<<"index move: "<<test + 1<<endl<<"Traveled Node: "<<minimaxCount<<endl;
		    if(minimaxCount > maxCount) {
			    maxCount = minimaxCount;
			    mC = nCount;
		    }
		    minimaxCount = 0;
		    move(comp,test);
		    showState();
		    }
		    else {
			    waitMove();
			    showState();
		    }
	    }
    }

    ////////Minimax Begin
    int minimax(vector<char> s) {
	    Node *current = BFS(s);
	    Node *bestMove = NULL;
	    Node *path = moves->getRoot();
	    if(comp == 'X') {
		    maxValue(current);
		    bestMove = max(current);
		    for(int i = 0; i < 9; ++i) {
			    if(current->state[i] != bestMove->state[i])
				    return i;
		    }
	    }
	    else {
		    Node *t = minValue(current);
		    for(int i = 0; i< path->children.size(); ++i){
			    showNodeState(path->children[i]);
		    }
		    bestMove = min(current);
		    for(int i = 0; i < 9; ++i) {
			    if(current->state[i] != bestMove->state[i])
				    return i;
		    }
	    }
    }

    Node* maxValue(Node *n) {
	    ++minimaxCount;
	    if(isFinished(n->state))
		    return n;
					
	    int bestValue = -1;
	    Node *bestMove = NULL;
	    for(int i = 0; i < n->children.size(); ++i) {
		    Node *value = minValue(n->children[i]);
		    if(value->score > bestValue){
			    bestValue = value->score;
			    bestMove = value;
		    }
		    else bestMove=value;
	    }
	    n->score = bestValue;
	    return bestMove;
    }	
    Node* minValue(Node *n) {
	    ++minimaxCount;
	    if(isFinished(n->state))
		    return n;

	    int bestValue = 1;
	    Node *bestMove = NULL;
	    for(int i = 0; i < n->children.size(); ++i) {
		    Node *value = maxValue(n->children[i]);
		    if(value->score < bestValue){
			    bestValue = value->score;
			    bestMove = value;
		    }
		    else bestMove=value;
	    }
	    n->score = bestValue;
	    return bestMove;
    }

    Node* max(Node *n) {
	    Node *pNode = NULL;
	    int max = -2;
	    for(int i = 0; i< n->children.size(); ++i){
		    if(n->children[i]->score > max){
			    pNode = n->children[i];
			    max = pNode->score;
		    }			
	    }
	    return pNode;
    }
    Node* min(Node *n) {
	    Node *pNode = NULL;
	    int min = 2;
	    for(int i = 0; i< n->children.size(); ++i){
		    if(n->children[i]->score < min){
			    pNode = n->children[i];
			    min = pNode->score;
		    }			
	    }
	    return pNode;
    }
    ////////Minimax End

    Node* BFS(vector<char> s) {
	    if(moves == NULL) return NULL;
	    queue<Node *> bfs;
	    bfs.push(moves->getRoot());
	    while(!bfs.empty()){
		    Node *tmp = bfs.front();
		    if(tmp->state == s)
			    return tmp;
		    if(!tmp->children.empty()){
			    for(int i = 0; i < tmp->children.size(); i++)
				    bfs.push(tmp->children[i]);
		    }
		    bfs.pop();				
	    }
	    return NULL;
    }

    void move(char &player, int index) {
	    if(0 <= index && index <= 8 && isAvailable(index,state)){
		    state[index] = player;
		    ++nCount;
	    }
    }

    bool isAvailable(int &index, vector<char> s) {
	    return (s[index] != 'X' && s[index] != 'O') ? true : false;
    }
	
    void waitMove() {
	    cout<<"Please enter a number: ";
	    int m;
	    cin>>m;
	
	    if(1 <= m && m <= 9)
		    move(user, --m);
	    else
		    cout<<"Invalid number!\n"; 
    }
	
	// Return Value : Meaning
	//			-1	: Draw
	//			0	: Not Finished
	//			1	: X Wins
	//			2	: O Wins
    int isFinished(vector<char> s) {
	    for(int i = 0; i < 9; ++i) {
		    if(i%3 == 0 && s[i] == s[i+1] && s[i+1] == s[i+2])
			    return (s[i] == 'X') ? 1 : 2;
		    else if(i/3 == 0 && s[i] == s[i+3] && s[i+3] == s[i+6])
			    return (s[i] == 'X') ? 1 : 2;
		    else if(i == 4 && s[i] == s[i-4] && s[i-4] == s[i+4])
			    return (s[i] == 'X') ? 1 : 2;
		    else if(i == 4 && s[i] == s[i-2] && s[i-2] == s[i+2])
			    return (s[i] == 'X') ? 1 : 2;
	    }
	
	    int count = 0;
	    for(int i = 0; i < 9; ++i)
		    if(isAvailable(i,s)) ++count;
	
	    return (count) ? 0 : -1;
    }
	
    void showNodeState(Node *n) {
	    for(int i=0; i<n->state.size(); ++i)
		    cout<<n->state[i];
	    cout<<" "<<n->score<<endl;
    }
	
    void showState() {
        for(int i = 0; i < 9; ++i) 
	        if(i%3 == 2)
		        cout<<state[i]<<endl;
	        else
		        cout<<state[i];
        cout<<endl;
    }
	
    void resultPage() {
        cout<<"********************************************\n";
        int fin = isFinished(state);
        if(fin == -1)
	        cout<<"Result of game: DRAW"<<endl;
        else if(fin == 1)
	        cout<<"Result of game: X WINS"<<endl;
        if(fin == 2)
	        cout<<"Result of game: O WINS"<<endl;
        cout<<"Number of moves: "<<nCount<<endl
	        <<"The most memory usage at: "<<mC+1<<" with "<<maxCount<<" nodes!"<<endl;
        cout<<"********************************************\n";
    }
	
    int getnCount() {
        return nCount;
    }

    char getComp() {
        return comp;
    }
    char getUser() {
        return user;
    }

    vector<char> getState() {
        return state;
    }

};

#endif
