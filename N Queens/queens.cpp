//
//  queens.cpp
//  N Queens
//
//  Created by Ernie DeFoy on 4/22/17.
//  Copyright © 2017 Ernie DeFoy. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int n;
int numSol = 0;

bool isSafe(vector<vector<int> > board)
{
    vector<int> locs;
    
    for(int r = 0; r < board.size(); r++) {
        for(int c = 0; c < board[0].size(); c++) {
            if(board[r][c] == 1) {
                locs.push_back(r);
                locs.push_back(c);
            }
        }
    }
    
    for(int i = 0; i < locs.size(); i = i + 2)
        for(int j = i + 2; j < locs.size(); j = j + 2) {
            if(locs[i] == locs[j])
                return false;
            if(locs[i + 1] == locs[j + 1])
                return false;
            if(locs[i] - locs[i + 1] == locs[j] - locs[j + 1])
                return false;
            if(locs[i] + locs[i + 1] == locs[j] + locs[j + 1])
                return false;
        }
    
    
    return true;
}

void printBoard(vector<vector<int> > board)
{
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            
            cout << board[r][c];
        }
        cout << "\n";
    }
    
    cout << "\n";
}



bool findSolutions(vector<vector<int> > board, int col)
{
    if(!isSafe(board))
        return false;
    
    if(col == board.size()) {
        numSol++;
        printBoard(board);
        return true;
    }
    
    for(int r = 0; r < board.size(); r++) {
        board[r][col] = 1;
        
        findSolutions(board, col + 1);
        
        board[r][col] = 0;
        
    }
    
    
    return true;
}

void solveNQueens(const int n)
{
    if(n < 1) {
        cout << "Solution does not exist" << endl;
    }
    else {
        vector<vector<int> > board;
    
        board.resize(n);
    
        for(int i = 0; i < n; i++)
            board[i].resize(n);
    
        for(int r = 0; r < n; r++)
            for(int c = 0; c < n; c++)
                board[r][c] = 0;
    
        findSolutions(board, 0);
        
        cout << n << "-queens has " << numSol << " solutions. " << endl;
    }
}

int main()
{
    cout << "How many queens?" << endl;
    cin >> n;
    
    solveNQueens(n);
    
    return 0;
}
