/*********************************************************************
*File: Compare.h
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
