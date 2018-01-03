#include <stdio.h>
#include <limits>
#include <stack>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;
//An implementation of a second shortest path algorithm, designed specifically for
// a graph that can be represented as a grid with limitations on movement.
#define R 80

#define C 80

ofstream fout("output.txt");

int min(int x, int y);


struct xypair{	//for constructing previous array

	int x;
	int y;

};

int grid_SP(int cost[R][C], int m, int n){ //finds shortest path and prints it
	int i, j = 1;

	stack<int> first_path;
	xypair prev[R][C];
	int total_cost[R][C];
	total_cost[0][0] = cost[0][0];
	prev[0][0].x = 0;
	prev[0][0].y = 0;



	for (j = 1; j < n; j++){
		total_cost[0][j] = total_cost[0][j - 1] + cost[0][j];	//first row initialized
		prev[0][j].x = 0;
		prev[0][j].y = j - 1;	//first row prev nodes initialized

	}
	for (i = 1; i < m; i++){
		total_cost[i][0] = total_cost[i - 1][0] + cost[i][0];		//initializes current columns
		prev[i][0].x = i - 1;		//initialize column prev nodes
		prev[i][0].y = 0;

		for (j = 1; j < n; j++){
			total_cost[i][j] = min(total_cost[i - 1][j], total_cost[i][j - 1]) + cost[i][j];	//first column nodes init
			

			if (min(total_cost[i - 1][j], total_cost[i][j - 1]) == total_cost[i - 1][j]){

				xypair p;		//previous node matrix op
				p.x = i - 1;
				p.y = j;
				prev[i][j] = p;
			}
			else {				//previous node matrix op
				xypair p;
				p.x = i;
				p.y = j - 1;
				prev[i][j] = p;
			}

		}

	}


	//end shortest route code
	

	

	vector<int> back_track;    //keep backwards path for simplicity in backtracking
	j = C;
	for (i = R; i >= 0; i--){		//find and print path in 1's and 0's

		if (prev[i - 1][j - 1].x == (i - 2) && prev[i - 1][j - 1].y == (j - 1)){
			first_path.push(0);
			back_track.push_back(0);

		}
		else if (prev[i - 1][j - 1].y == (j - 2) && prev[i - 1][j - 1].x == (i - 1)){
			first_path.push(1);
			back_track.push_back(1);
			j--;
			i++;
		}

	}

	///begin second shortest path code
	vector<int> min_diff;
	for (int i = 0; i < back_track.size(); i++)
		min_diff.push_back(10000);

	int sml, grt, diff;
	int count = 0;
	i = R - 1;
	j = C - 1;
	for (int k = 0; k < back_track.size(); k++){  //finding the difference between choices

		if (back_track[k] == 0)
		{
			grt = total_cost[i][j - 1];
			sml = total_cost[i - 1][j];
			diff = abs(grt - sml);
			min_diff[k] = diff;
			if (i != 0)
				i--;
		}
		else if (back_track[k] == 1)
		{
			grt = total_cost[i - 1][j];
			sml = total_cost[i][j - 1];
			diff = abs(grt - sml);
			min_diff[k] = diff;
			if (j != 0)
				j--;
		}


	}
	

	int min = 10000, min_index;
	for (int k = 0; k < back_track.size(); k++)	//finding minimum diff and the index for pathfinding
		if (min_diff[k] < min)
			min = min_diff[k];
	for (int k = 0; k < back_track.size(); k++)
		if (min_diff[k] == min)
			min_index = k;

	stack<int> ssp;

	for (int k = 0; k < min_index; k++)     //populating second path stack
		ssp.push(back_track[k]);
	i = R;
	j = C;

	for (int k = 0; k < min_index; k++){	//write path up to turning point
		if (back_track[k] == 1)
			j--;
		if (back_track[k] == 0)
			i--;
	}

	if (back_track[min_index] == 0){		//check shortest path, choose opposite at min_index
		ssp.push(1);
		j--;
	}
	else{
		ssp.push(0);
		i--;
	}

	for (int k = i;k >= 0; k--){		//following previous nodes back to origin
		if (prev[k - 1][j - 1].x == (k - 2) && prev[k - 1][j - 1].y == (j - 1)){
			ssp.push(0);
			
		}
		else if (prev[k - 1][j - 1].y == (j - 2) && prev[k - 1][j - 1].x == (k - 1)){
			ssp.push(1);
			j--;
			k++;
		}
	}


		fout << "First shortest path: " << endl;
		while (first_path.size() != 0){
			fout << first_path.top() << " ";
			first_path.pop();
		}
		
		fout <<"\n"<< "Second shortest path: " << endl;
		while (ssp.size() != 0){
			fout << ssp.top() << " ";
			ssp.pop();
		}

		fout << endl;
		fout << "First Path Travel Cost: " << total_cost[m - 1][n - 1] << endl;
		fout << "Second Path Travel Cost: " << total_cost[m - 1][n - 1] + min << endl;
		fout.close();
		return total_cost[m - 1][n - 1];
	}




int min(int x, int y){
	if (x < y)
		return x;
	else
		return y;
}


	//traverse shortest path starting at the end--
	//find difference between left and up values in total_cost array
	//store that value in min_diff array
	//find the minimum difference in the array after traversing entire path
	//*the index of the minimum is the step in the path, we need to copy this path so far
	//into our new path array ***the index of minimum difference corresponds to first path array index

	//find shortest path to start from there
	//use prev data, mark 0's and 1's carefully
	

