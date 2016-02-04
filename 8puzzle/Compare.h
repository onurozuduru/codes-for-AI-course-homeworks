/*********************************************************************************
*File: Compare.h
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

#ifndef COMPARE_H
#define COMPARE_H

#include <cmath>
#include <iomanip>
#include "Tree.h"

//Every move costs 1
class CompareCost {
public:
    bool operator()(Node *n1, Node *n2)
    {
       if (n1->moves.size() > n2->moves.size()) return true;
       if (n1->moves.size() == n2->moves.size()) return true;
       return false;
    }
};

//Uses Manhattan Distance
class CompareHeuristic {
public:
    int heuristic(Node &n){        
        int h = 0;
        for(int i = 0; i < 9; ++i){
            int x = i%3;
            int y = i/3;            
            switch(n.state[i]){
                case 0:
                    h = h + abs(2-x) + abs(2-y);
                    break;
                case 1:
                    h = h + x + y;
                    break;
                case 2:
                    h = h + abs(1-x) + y;
                    break;
                case 3:
                    h = h + abs(2-x) + y;
                    break;
                case 4:
                    h = h + x + abs(1-y);
                    break;
                case 5:
                    h = h + abs(1-x) + abs(1-y);
                    break;
                case 6:
                    h = h + abs(2-x) + abs(1-y);
                    break;
                case 7:
                    h = h + x + abs(2-y);
                    break;
                case 8:
                    h = h + abs(1-x) + abs(2-y);
                    break;
            }
        }        
        return h;
    }
    bool operator()(Node *n1, Node *n2)
    {
       if (heuristic(*n1) > heuristic(*n2)) return true;
       if (heuristic(*n1) == heuristic(*n2)) return true;
       return false;
    }
};

//Heuristic + Cost
class CompareEvaluation {
public:
    int heuristic(Node &n){        
        int h = 0;
        for(int i = 0; i < 9; ++i){
            int x = i%3;
            int y = i/3;            
            switch(n.state[i]){
                case 0:
                    h = h + abs(2-x) + abs(2-y);
                    break;
                case 1:
                    h = h + x + y;
                    break;
                case 2:
                    h = h + abs(1-x) + y;
                    break;
                case 3:
                    h = h + abs(2-x) + y;
                    break;
                case 4:
                    h = h + x + abs(1-y);
                    break;
                case 5:
                    h = h + abs(1-x) + abs(1-y);
                    break;
                case 6:
                    h = h + abs(2-x) + abs(1-y);
                    break;
                case 7:
                    h = h + x + abs(2-y);
                    break;
                case 8:
                    h = h + abs(1-x) + abs(2-y);
                    break;
            }
        }        
        return h;
    }
    bool operator()(Node *n1, Node *n2)
    {
       if (heuristic(*n1)+n1->moves.size() > heuristic(*n2)+n2->moves.size() )
            return true;
           
       if (heuristic(*n1)+n1->moves.size() == heuristic(*n2)+n2->moves.size())
               return true;       
       return false;
    }
};

#endif
