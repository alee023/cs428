#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <limits.h>
#include <algorithm>

using namespace std ;

vector<vector<int>> graph1{ { 0, 2, 5, 1, INT_MAX, INT_MAX }, 
							{ 2, 0, 3, 2, INT_MAX, INT_MAX }, 
							{ 5, 3, 0, 3, 1, 5 }, 
							{ 1, 2, 3, 0, 1, INT_MAX }, 
							{ INT_MAX, INT_MAX, 1, 1, 0, 2 }, 
							{ INT_MAX, INT_MAX, 5, INT_MAX, 2, 0 }} ;
							
vector<vector<int>> graph2{ { 0, 2, 4, INT_MAX, INT_MAX, 7, INT_MAX }, 
							{ 2, 0, 3, 3, INT_MAX, INT_MAX, INT_MAX }, 
							{ 4, 3, 0, 4, 3, 8, INT_MAX }, 
							{ INT_MAX, 3, 4, 0, 6, INT_MAX, INT_MAX }, 
							{ INT_MAX, INT_MAX, 3, 6, 0, 6, 8 }, 
							{ 7, INT_MAX, 8, INT_MAX, 6, 0, 12 }, 
							{ INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8, 12, 0 }} ;
							
vector<vector<int>> graph3{ { 0, 4, INT_MAX, 6, INT_MAX, INT_MAX }, 
							{ 4, 0, 6, 3, INT_MAX, INT_MAX }, 
							{ INT_MAX, 6, 0, 6, 9, 5 }, 
							{ 6, 3, 6, 0, 1, INT_MAX }, 
							{ INT_MAX, INT_MAX, 9, 1, 0, 1 }, 
							{ INT_MAX, INT_MAX, 5, INT_MAX, 1, 0 }} ;
							
void printVect( vector<int> vect ) {
	for( int x : vect ) {
		cout << to_string( x ) + " " ;
	}
	cout << "\n" ;
}
							
void djikstra( vector<vector<int>> graph, int size, int start ) {
	vector<int> visited = { start } ; // keeps track of visited nodes
	vector<int> adjVect = graph[ start ] ; // serves as adjacency "matrix"
	cout << to_string( start ) + ": " ;
	printVect( adjVect ) ;
	
	for( int i = 0; i < size - 1 ; i++ ) { // need at most size number of iterations
		int min = INT_MAX ;
		int minDex ; // index of minimum, unvisited node
		for( minDex = 0; minDex < size; minDex++ ) {
			if(( count( visited.begin(), visited.end(), minDex == 0 )) && ( adjVect[ minDex ] < min )) {
				min = adjVect[ minDex ] ;
			}
		}
		for( int ii = 0; ii  < size; ii ++ ) {
			int visitedTimes = count( visited.begin(), visited.end(), ii ) ;
			// cout << "count: " + to_string( visitedTimes ) << endl ;
			// cout << "dist: " + to_string( adjVect[ ii ]) << endl ;
			if(( visitedTimes == 0 ) && ( adjVect[ ii ] < min )) {
				min = adjVect[ ii ] ;
				minDex = ii ;
			}
		}
		
		visited.push_back( minDex ) ; // add this to the visited nodes list
		
		for( int j = 0; j < size; j++ ) {
			int currDist = adjVect[ minDex ] ; // cost of start node to current node
			int dist = graph[ minDex ][ j ] ; // cost of current node to a node 
			
			if(( dist != INT_MAX ) && ( currDist + dist < adjVect[ j ])) {
				adjVect[ j ] = currDist + dist ; // update distances if new shorter dist is found
			}
		}
		
		for( int x : visited ) {
			cout << to_string( x ) ;
		}
		cout << ": " ;
		printVect( adjVect ) ;
	}
	
}

int main( int argc, char *argv[]) {
	cout << "===================== FIGURE 4.27 ==========================" << endl ;
	djikstra( graph1, 6, 0 ) ; 		// u = 0, v=1, w=2, x=3, y=4, z=5
	cout << "======================== GIVEN GRAPH =======================" << endl ;
	djikstra( graph2, 7, 0 ) ; 		// u = 0, v=1, w=2, x=3, y=4, z=5
	cout << "===================== GENERATED GRAPH ==========================" << endl ;
	djikstra( graph3, 6, 0 ) ; 		// u = 0, v=1, w=2, x=3, y=4, z=5
}