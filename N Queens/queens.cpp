//
//  queens.cpp
//  N Queens
//
//  Created by Ernie DeFoy on 4/22/17.
//  Copyright © 2017 Ernie DeFoy. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <math.h>

using namespace std;

int numSol = 0;

bool isSafe(const int n, int board[]) {
    
    vector<int> locs;
    
    for(int i = 0; i < (n*n); i++) {
        if(board[i] == 1) {
            int r = i / n;
            int c = i % n;
            locs.push_back(r);
            locs.push_back(c);
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

bool isSafe(const int n, const int board[], int i) {
    
    int r = i / n;
    int c = i % n;
    
    for(int i = 0; i < n; i++) {
        if(board[(r * n) + i] == 1)
            return false;
    }
    
    for(int i = 1; i < n; i++) {
        if(r - i >= 0 && c - i >= 0 && board[(r - 1) * n + (c - 1)] == 1)
            return false;
        if(r - i >= 0 && c + i < n && board[(r - 1) * n + (c + 1)] == 1)
            return false;
        if(r + i < n && c - i >= 0 && board[(r + 1) * n + (c - 1)] == 1)
            return false;
        if(r + i < n && c + i < n && board[(r + 1) * n + (c + 1)] == 1)
            return false;
    }
    
    return true;
}


void printBoard(const int n, int board[]) {
    
    for(int i = 0; i < n * n; i++) {
        cout << board[i];
        if(i % n == n - 1)
            cout << "\n";
    }
    
    cout << "\n";
}

void findSolutions(const int n, int board[], int col) {
    
    if(col == n) {
        numSol++;
        //printBoard(n, board);
        return;
    }
    
    // Look in each row of the current column for
    // safe spots to put queen
    for(int r = 0; r < n; r++) {
        int i = (r * n) + col;
        
        board[i] = 1;
        
        if(isSafe(n, board)) {
            findSolutions(n, board, col + 1);
        }
        
        board[i] = 0;
    }
}

/*
 *  Recursive function that using bitwise operations to
 *  determine number of solutions.  Rather than placing 
 *  queens, the function passes in only safe locations 
 *  after taking away a safe location in each row. 
 *  When all columns are threatened, there are no more 
 *  cases to test, and this indicates that a solution 
 *  has been found.
 *
 *  @param {const int} n - Number of queens.
 *  @param {int} leftDiag - Top-left-to-bottom-right diagonals threatend by queens.
 *  @param {int} somebody - Columns threatened by queens.
 *  @param {int} somebody - Top-right-to-bottom-left diagonals threatend by queens.
 */
void findSolutions(const int n, int leftDiag, int col, int rightDiag) {
    
    int full = pow(2, n) - 1;
    
    // All columns are threatened
    if(col == full) {
        numSol++;
        return;
    }
    
    // Bitwise NOT to find open spaces
    int open = ~(leftDiag | col | rightDiag);
    
    // Bitwise AND that keeps loop running as
    // long as there are safe spots
    while(open & full) {
        
        // Finds first open spot using 2'c complement
        // and an AND operator
        int firstOpen = open & -open;
        
        open -= firstOpen;
        
        findSolutions(n, (firstOpen | leftDiag) >> 1, col | firstOpen, (firstOpen | rightDiag) << 1);
    }
}

void solveNQueens(const int n) {
    
    if(n < 1) {
        cout << "Solution does not exist" << endl;
    }
    else {
        int board[n * n];
        
        for(int i = 0; i < n * n; i++)
            board[i] = 0;
        
        /* Solve with array */
        //findSolutions(n, board, 0);
        
        /* Solve using bitwise operators */
        findSolutions(n, 0, 0, 0);
        
        cout << n << "-queens has " << numSol << " solutions. " << endl;
    }
}

int main()
{
    std::clock_t start;
    double duration;
    
    int n;
    
    cout << "How many queens?" << endl;
    cin >> n;
    
    start = std::clock();
    
    solveNQueens(n);
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
    std::cout<<"Time to calculate: "<< duration <<'\n';
    
    return 0;
}
