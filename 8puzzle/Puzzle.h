/*********************************************************************************
*File: Puzzle.h
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

#ifndef PUZZLE_H
#define PUZZLE_H

#include <algorithm>
#include <list>
#include <stack>
#include <queue>
#include "Compare.h"//includes Tree.h

class Puzzle
{
private:
    // Empty place shown as 0
    // and last element of the vector shows position of the empty place.
    vector<int> goal;//{1,2,3,4,5,6,7,8,0, 8}
    vector<int> start;
    list<vector<int> > explored;
    Tree *opened;    
public:
    Puzzle(vector<int> &s) {
          for (int i=1; i<9; i++)
              goal.push_back(i);
          goal.push_back(0);
          goal.push_back(8);
          
          start = s;
          if(!this->isGoal(start)) {
              Node *pNode = new Node(start);
              opened = new Tree(pNode);
              explored.push_front(start);
          }
          else{
              cout<<"\nStarting case is The goal case!\n";
              opened = NULL;
              }
    }
    ~Puzzle() {
        if(opened != NULL){
        //Using BFS for destructor
            queue<Node *> del;
            del.push(opened->getRoot());
        
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
        delete opened;////    
    }
    
    ////////////////////ALGORITHMS BEGIN
    //Breadth First Seach
    void BFS(Node &n) {
        queue<Node *> bfs;
        bfs.push(&n);
        int count = 0;
        while(!bfs.empty()){
            Node *ptr = bfs.front();
            
            if(this->isGoal(ptr->state)){
                cout<<"Solution: "<<ptr->moves<<endl
                    <<count<<" new nodes are opened!"<<endl;
                break;
            }
            else{
                generateNewStates(*ptr);
                for(int i = 0; i < ptr->children.size(); i++){
                    bfs.push(ptr->children[i]);
                    ++count;
                }
            }            
            bfs.pop();
            explored.push_front(ptr->state);
        }
    }
    
    //Uniform Cost Search
    void UCS(Node &n) {
        priority_queue<Node *, vector<Node *>,CompareCost> ucs;//Oredered by Cost
        ucs.push(&n);
        int count = 0;
        while(!ucs.empty()){
            Node *ptr = ucs.top();
            ucs.pop();
            if(this->isGoal(ptr->state)){
                cout<<"Solution: "<<ptr->moves<<endl
                    <<count<<" new nodes are opened!"<<endl;
                break;
            }
            else{
                generateNewStates(*ptr);
                for(int i = 0; i < ptr->children.size(); i++){
                    ucs.push(ptr->children[i]);
                    ++count;
                }
            }            
            explored.push_front(ptr->state);
        }
    }
    
    //Depth First Search
    void DFS(Node &n) {
        stack<Node *> dfs;
        dfs.push(&n);
        int count = 0;
        while(!dfs.empty()){
            Node *ptr = dfs.top();
            dfs.pop();
            explored.push_front(ptr->state);
            if(this->isGoal(ptr->state)){
                cout<<"Solution: "<<ptr->moves<<endl
                    <<count<<" new nodes are opened!"<<endl;
                break;
            }
            else{
                generateNewStates(*ptr);
                for(int i = 0; i < ptr->children.size(); i++){
                    dfs.push(ptr->children[i]);
                    ++count;
                }
            }            
        }
    }
    
    //Iterative Deepening Search
    
    //DFS function which returns node pointer
    //That function helps IDS
    Node* df(Node &n){
        stack<Node *> dfs;
        dfs.push(&n);

        while(!dfs.empty()){
            Node *ptr = dfs.top();
            dfs.pop();
            if(this->isGoal(ptr->state)){
                return ptr;
            }
            else{
                for(int i = 0; i < ptr->children.size(); i++)
                    dfs.push(ptr->children[i]);
                }            
            }            
        return NULL;
    }
    
    void IDS(Node &n) {
        queue<Node *> newChildren;
        newChildren.push(&n);
        
        Node *found = df(n);//Search on the limited tree
        int count = 0;
        while(found == NULL){
            found = df(n);
            Node *p = newChildren.front();
            
            generateNewStates(*p);
            for(int i = 0; i < p->children.size(); i++){
                newChildren.push(p->children[i]);
                count++;    
            }
            newChildren.pop();
            explored.push_front(p->state);
        }
        
        cout<<"Solution: "<<found->moves<<endl
            <<count<<" new nodes are opened!"<<endl;
    }
    
    //Greedy Best-First Search    
    void GBFS(Node &n) {
        priority_queue<Node *, vector<Node *>,CompareHeuristic> gbfs;//Oredered by Heuristic Value
        gbfs.push(&n);
        int count = 0;
        while(!gbfs.empty()){
            Node *ptr = gbfs.top();
            gbfs.pop();
            if(this->isGoal(ptr->state)){
                cout<<"Solution: "<<ptr->moves<<endl
                    <<count<<" new nodes are opened!"<<endl;
                break;
            }
            else{
                generateNewStates(*ptr);
                for(int i = 0; i < ptr->children.size(); i++){
                    gbfs.push(ptr->children[i]);
                    ++count;
                }
            }            
            explored.push_front(ptr->state);
        }
    }
    
    //A* Search
    void AStar(Node &n) {
        priority_queue<Node *, vector<Node *>,CompareEvaluation> gbfs;//Oredered by (Heuristic Value + Cost)
        gbfs.push(&n);
        int count = 0;
        while(!gbfs.empty()){
            Node *ptr = gbfs.top();
            gbfs.pop();
            if(this->isGoal(ptr->state)){
                cout<<"Solution: "<<ptr->moves<<endl
                    <<count<<" new nodes are opened!"<<endl;
                break;
            }
            else{
                generateNewStates(*ptr);
                for(int i = 0; i < ptr->children.size(); i++){
                    gbfs.push(ptr->children[i]);
                    ++count;
                }
            }            
            explored.push_front(ptr->state);
        }
    }
    //******************ALGORITHMS END
    
    
    //Resets the puzzle
    void reset() {
        if(opened != NULL){
            queue<Node *> del;
            del.push(opened->getRoot());
        
            while(!del.empty()){
                Node *tmp = del.front();
            
                if(!tmp->children.empty()){
                    for(int i = 0; i < tmp->children.size(); i++)
                        del.push(tmp->children[i]);
                }
                del.pop();
                delete tmp;                    
            }
        
        explored.clear();
        }        
        Node *pNode = new Node(start);
          opened = new Tree(pNode);
          explored.push_front(start);
    }
    
    void printStart(){
        for(int i = 0; i < start.size()-1 ; i++){
            cout<<start[i]<<" ";
            if(i%3 == 2)
                cout<<endl;
        }
        cout<<"-----\n";
    }
    
    void solvePuzzle(int c = 0){
        if(isGoal(start)) return;
    
    //-1 Breadth-first search
    //-2 Uniform-cost search
    //-3 Depth-first search
    //-4 Iterative deepening search
    //-5 Greedy Best Search
    //-6 A* Search    
        if(c != -1){
            cout<<"Breadth-first search:\n";
            BFS(*(opened->getRoot()));
            reset();
            cout<<"**************************\n";
        }
        if(c != -2){
            cout<<"Uniform-cost search:\n";
            UCS(*(opened->getRoot()));
            reset();
            cout<<"**************************\n";
        }
        
        if(c != -3){
            cout<<"Depth-first search:\n";
            DFS(*(opened->getRoot()));
            reset();
            cout<<"**************************\n";
        }
        
        if(c != -4){
            cout<<"Iterative deepening search:\n";
            IDS(*(opened->getRoot()));
            reset();
            cout<<"**************************\n";
        }
        if(c != -5){
            cout<<"Greedy Best-First Search:\n";
            GBFS(*(opened->getRoot()));
            reset();
            cout<<"**************************\n";
        }
        if(c != -6){
            cout<<"A* Search:\n";
            AStar(*(opened->getRoot()));
            cout<<"**************************\n";
        }
    }
    
    bool isGoal(vector<int> &s) {
        return (s == this->goal);
    }
    
    ////////////////////MOVE FUNCTIONS BEGIN
    vector<int> moveRight(Node &n) {
        
        vector<int> newState(n.state);
        int tmp = newState[9];
        
        if(tmp%3 != 2) {
            swap(newState[tmp], newState[tmp+1]);
            newState[9] = tmp + 1;
            return newState;
        }
        return newState;
    }
    
    vector<int> moveLeft(Node &n) {
        
        vector<int> newState(n.state);
        int tmp = newState[9];
        
        if(tmp%3 != 0) {
            swap(newState[tmp], newState[tmp-1]);
            newState[9] = tmp - 1;
            return newState;
        }
        return newState;
    }
    
    vector<int> moveUp(Node &n) {
        
        vector<int> newState(n.state);
        int tmp = newState[9];
        
        if(tmp/3 != 0) {
            swap(newState[tmp], newState[tmp-3]);
            newState[9] = tmp - 3;
            return newState;
        }
        return newState;
    }
    
    vector<int> moveDown(Node &n) {
        
        vector<int> newState(n.state);
        int tmp = newState[9];
        
        if(tmp/3 != 2) {
            swap(newState[tmp], newState[tmp+3]);
            newState[9] = tmp + 3;
            return newState;
        }
        return newState;
    }
    //******************MOVE FUNCTIONS END
    
    
    void generateNewStates(Node &n) {
    //R: Right
    //D: Down
    //L: Left
    //U: Up
    
        //Move Right
        vector<int> tempState = moveRight(n);
        list<vector<int> >::iterator it = search_n(
            explored.begin(), explored.end(), 1, tempState
        );

        if( (tempState != n.state) && (it == explored.end()) ){
            Node *pNode = new Node(tempState, n.moves+'R');
            n.addChild(pNode);
        }
        
        //Move Down
        tempState = moveDown(n);
        it = search_n(
            explored.begin(), explored.end(), 1, tempState
        );

        if( (tempState != n.state) && (it == explored.end()) ){
            Node *pNode = new Node(tempState, n.moves+'D');
            n.addChild(pNode);
        }
        
        //Move Left
        tempState = moveLeft(n);
        it = search_n(
            explored.begin(), explored.end(), 1, tempState
        );

        if( (tempState != n.state) && (it == explored.end()) ){
            Node *pNode = new Node(tempState, n.moves+'L');
            n.addChild(pNode);
        }
        
        //Move Up
        tempState = moveUp(n);
        it = search_n(
            explored.begin(), explored.end(), 1, tempState
        );

        if( (tempState != n.state) && (it == explored.end()) ){
            Node *pNode = new Node(tempState, n.moves+'U');
            n.addChild(pNode);
        }            
    }

};

#endif
