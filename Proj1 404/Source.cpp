#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stack>
#include "dp_method.h"
using namespace std;


int main(){
	//testing

	ifstream fin;
	ofstream fout("output.txt");
	fin.open("grid15.txt");
	char temp;
	int m, n, cost, x, y;
	fin >> m >> temp >> n; //read in dimensions
	int v = m;
	int grid[80][80];
	

	fout << m << " x " << n << endl;
	for (int i = 0; i < m; i++){ //build grid from text file
		for (int j = 0; j < n; j++){
			fin >> x >> temp >> y >> temp >> cost;
			grid[i][j] = cost;
		}
	}


	
	fout << endl;
	
	
	

	fout << endl;
	fout.close();
	fin.close();
	
	int a = grid_SP(grid, m, n);

	
	system("pause");
	
	
		


	return 0;

}

