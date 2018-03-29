#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;
int SIZE;
int arrSize;



//This is to remember what we just changed so we don't hit a false plateau
int last = -1;

//keeping arrays to hold the number of queens in each row / diagonal to find heuristic
//Math is a little tricky 
int getHeuristic(int* candidate){
    int i = 0, ret = 0;
    bool row[arrSize] = {false};
    bool ldiag[arrSize] = {false};
    bool rdiag[arrSize] = {false};
    for (int j = 0; j < SIZE; j++){
        i = candidate[j];
        if(row[i]) ret++;
            else row[i] = true;
        if(rdiag[(SIZE-1) - i + j]) ret++;
            else rdiag[(SIZE-1) - i + j] = true;
        if(ldiag[i + j]) ret++;
            else ldiag[i+j] = true;
    }
    return ret;
}

int getRand(){
    return rand() % SIZE;
}

//local search for finding best neighbor
int getBestNeighbor(int* candidate){
    int copy[SIZE];
    for(int i = 0; i <SIZE; i++){
        copy[i] = candidate[i];
    }
    //just put 1000 so it will be overwritten on the first cycle
    int newVal, bestLocI, bestLocJ, current;
    int bestVal = 1000;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            copy[i] = j;
            newVal = getHeuristic(copy);
            if (newVal < bestVal){
                bestVal = newVal;
                bestLocI = i;
                bestLocJ = j;
            }
            //reset to actual location
            copy[i] = candidate[i];
        }
        
    }
    candidate[bestLocI] = bestLocJ;
    return bestVal;
}

void shuffle(int* board){

    for(int i = 0; i< SIZE; i++){
        board[i] = getRand();
    }

}

bool hillClimbSearch(int* board){
    int myval = getHeuristic(board);
    int val = -1;
    bool good;
    while(true){
        val = getBestNeighbor(board);
        if(val == 0) return true;
        //if val > myval we have hit a non-solution local maximum and need to restart
        if(val >= myval) {
            shuffle(board);
            myval = getHeuristic(board);
        }
        else myval = val;
    }

}


void printBoard(int* board){
    for(int i = 0; i < SIZE; i++){
        for (int j = 0; j< SIZE; j++){
            if (board[j] == i) cout << "1 ";
            else cout << "0 ";
        }
        cout << endl;
    }

}

int main(int argc, char ** argv){

if(argc != 2){
    cout << "Unexpexted number of arguments. Run with [n] to solve for queens.\n";
    exit(1);
}

SIZE = atoi(argv[1]);
arrSize = SIZE * 2 - 1;
srand(time(0));
//Board stored as an array of squares from the bottom
//Make board

int board[SIZE];

for(int i = 0; i < SIZE; i++){
        board[i] = getRand();
    }

if(hillClimbSearch(board)){
    string s;
    cout << "Found a solution" << endl << "Enter 'p' to print concise or 'P' to print full board \nanything else to quit" << endl;
    cin >> s;
    if(s == "p"){
        for(int i = 0; i < SIZE - 1; i++){
            cout << board[i] << ",";
        }
        cout << board[SIZE - 1];
        cout << endl;
    }
    if(s == "P") printBoard(board);
}

    return 0;    
}
