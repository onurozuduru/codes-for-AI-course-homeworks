/*
Developed by:
name:			Onur Ozuduru
github page:	https://github.com/onurozuduru
twitter:		https://twitter.com/OnurOzuduru

This work is licensed under the Creative Commons Attribution 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.
*/

#include "Puzzle.h"

void show(vector<int> v) {
	for(int i = 0; i < v.size() ; i++)
		cout<<v[i]<<" ";
	cout<<endl;
}

vector<int> setStartState(){
	int ar[] = {1,2,3,4,5,6,7,8,0, 8};
	int in = 0;
	cout<<"Please enter the puzzle as one line."<<endl
	<<"example: Enter\n1 2 3\n4 5 6\n7 8 0\nas one line like\n123456780\n\n";
	cin>>in;
	
	for(int i = 8; i != 0; i--){
		ar[i] = in%10;
		if(ar[i] == 0) ar[9] = i;
		in = in / 10;
		if(i-1 == 0){ 
			ar[0] = in;
			if(in == 0) ar[9] = 0;
		}
	}

	vector<int> s(ar, ar + 10);
	return s;
}

vector<Puzzle *> setAutoPuzzle(){
	int exampleSet[][10] = { {1,2,3,4,5,6,7,8,0, 8},
							 {1,2,3,4,5,6,0,7,8, 6},
							 {1,2,3,4,5,0,6,7,8, 5},
							 {0,2,3,1,4,6,7,5,8, 0},
							 {1,2,3,5,0,6,4,7,8, 4},
							 {0,1,3,4,2,5,7,8,6, 0},
							 {7,1,2,6,0,4,5,8,3, 4},//takes too much time for BFS UCS
							 };
	vector<Puzzle *> p;
	for(int i = 0; i < 7; i++){
		vector<int> s(exampleSet[i],exampleSet[i]+10);
		Puzzle *ptr = new Puzzle(s);
		p.push_back(ptr);
	}
	
	return p;
}

void help() {
	cout<<"Usage:\n./8puzzle [options]"<<endl;
	cout<<"Options:\n"
		<<"-u --user\tUser creates new puzzle."<<endl
		<<"-a --auto\tAuto test will run."<<endl
		<<"-h --help\tCalls this help."<<endl;
}

int main(int argc,const char *argv[]) {
// DFS takes too much time thats why cases do not solved by DFS,
// 	however if you replace p.solvePuzzle(-3) line with p.solvePuzzle()
// 	all algorithms will be used.
	if((argc < 2) || string(argv[1]) == "-h" || string(argv[1]) == "--help")
		help();
	else if(string(argv[1]) == "-u" || string(argv[1]) == "--user") {
	//////User
		vector<int> start = setStartState(); //start(ar, ar+10);	
		Puzzle p(start);
		p.printStart();
		p.solvePuzzle(-3);//except DFS
	}
	else if(string(argv[1]) == "-a" || string(argv[1]) == "--auto") {
	//////Auto fill
		vector<Puzzle *> puz = setAutoPuzzle();
		for(int i = 0; i < 7; i++){
			puz[i]->printStart();
			puz[i]->solvePuzzle(-3);//except DFS
			delete puz[i];
		}
	}
	//////One by one
	
	//int ar[] = {7,1,2,6,0,4,5,8,3, 4};
	//vector<int> start(ar, ar+10);
	//Node x(start);
	//Puzzle p(start);
	
	//p.BFS(x);
	//p.UCS(x);
	//p.DFS(x);
	//p.IDS(x);
	//p.GBFS(x);
	//p.AStar(x);
	return 0;
}

/*
void showC(Node &n) {
	for(int i = 0; i < n.children.size(); i++){
		for(int j = 0; j < n.children[i]->state.size() ; j++)
			cout<<n.children[i]->state[j]<<" ";
		cout<<n.children[i]->moves<<endl;
	}
}

void showA(Node &n) {
	for(int i = 0; i < n.state.size() ; i++)
		cout<<n.state[i]<<" ";
	cout<<n.moves;
	cout<<endl;
}
*/
