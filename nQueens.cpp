#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;
int SIZE;

//This is to remember what we just changed so we don't hit a false plateau
int last = -1;

//keeping arrays to hold the number of queens in each row / diagonal to find heuristic
//Math is a little tricky
int getHeuristic(int* candidate){
    int i, ret = 0;
    int row[SIZE];
    int ldiag[(SIZE * 2) - 2];
    int rdiag[(SIZE * 2) - 2];
    for (int j = 0; j < SIZE; j++){
        i = candidate[j];
        row[i]++;
        rdiag[abs(i - SIZE) + j]++;
        ldiag[i + j]++;
    }
    for(int j = 0; j < SIZE; j++){
        if (row[j] > 1) ret += (row[j] - 1);
        if (ldiag[j] > 1) ret += (ldiag[j] - 1);
        if (rdiag[j] > 1) ret += (rdiag[j] - 1);
    }

    return ret;
}

int getRand(){
    return rand() % SIZE;
}

//We will be finding "neighbors on one column at a time(randomly) just to not generate too many at once
//"last" variable will make sure we don't edit the same column twice in a row
//When using greedy, we will just change the original to the best neighbor to avoid copying costs
bool getBestNeighbor(int* candidate, int& curH){
    int rando = getRand();
    while (rando == last) rando = getRand();
    int curLoc = candidate[rando];
    //just put 1000 so it will be overwritten on the first cycle
    int newVal, bestLoc;
    int bestVal = 1000;
    for (int i = 0; i < SIZE; i++){
        candidate[rando] = i;
        newVal = getHeuristic(candidate);
        if (newVal < bestVal){
            bestVal = newVal;
            bestLoc = i;
        }
    }
    if (bestLoc != curLoc){
        candidate[rando] = bestLoc;
        curH = bestVal;
        return true;
    }
return false;
}

void shuffle(int* board){
    int rando = getRand();
    int rando2 = getRand();

    board[rando] = rando2;

}

bool hillClimbSearch(int* board){
    int val = -1;
    bool good;
    while(true){
        good = getBestNeighbor(board, val);
        if(val == 0) return true;
        if(!good) shuffle(board);
    }
    return true;
}





int main(int argc, char ** argv){
/*
if(argc != 2){
    cout << "Unexpexted number of arguments. Run with [n] to solve for queens.\n";
    exit(1);
}
*/
SIZE = 4;
srand(time(0));
//Board stored as an array of squares from the bottom
//Make board

int board[SIZE];

for(int i = 0; i < SIZE; i++){
        board[i] = getRand();
        cout << board[i];
    }

if(hillClimbSearch(board)){
    string s;
    cout << "Found a solution" << endl << "Enter 'p' to print concise or 'P' to print full board (anything else to quit)" << endl;
    cin >> s;

    if(s == "p"){
        for(int i = 0; i < SIZE; i++){
            cout << board[i];
        }
    }
}

    return 0;    
}
