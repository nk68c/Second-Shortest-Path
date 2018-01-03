//Implementation of Dijkstra's second shortest path algorithm, a combination of selected resources
//attempting to address a specified problem
//
//Nicholas King
//Project 1

int dist[55];
struct ltDist{
	bool operator()(int u, int v) const {
		return make_pair(dist[u], u) < make_pair(dist[v], v);
	}
};

void djikstra(int s, int grid[7][8], int dist[56], int prev[56]){
	for (int i = 0; i < 56; i++){
		dist[i] = INT_MAX / 2;
		prev[i] = -1;
	}
	dist[s] = 0;
	set<int, ltDist> heap;
	heap.insert(s);

	while (!heap.empty()){
		int u = *heap.begin();			//select smallest element
		int alt = dist[u] + grid[u + 1][u];		//moving right
		if (alt < dist[u]){
			dist[u + 1] = alt;
			prev[u + 1] = u;
			if (heap.count((u + 1))){	//if the vertex is already in queue
				heap.erase(u + 1);		//remove that vertex
				heap.insert(u + 1);		//insert it with its updated value
			}
			else{
				heap.insert(u + 1);		//insert vertex into heap
			}
		}
		alt = dist[u] + grid[u][u + 1]; //moving down
		if (alt < dist[u]){
			dist[u + 7] = alt;
			prev[u + 7] = u;
			if (heap.count((u + 7))){	//if the vertex is already in queue
				heap.erase(u + 7);		//remove that vertex
				heap.insert(u + 7);		//insert it with its updated value
			}
			else{
				heap.insert(u + 7);		//insert vertex into heap

			}
		}
	}
}//dist and prev will contain data for path distance and the prev node for tracing path

//Notes on Dijkstra's formula -- moving right and down only is a specification of the project, and this may be the

// --in order to access the 'n' value when accessing the grid, the function uses the current vertex plus 
//a calculated value to correctly choose right or down according to vertex number, the same number that is the index
//of the shortest distance to that node