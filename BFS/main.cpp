#include "BFS.h"
#include <string>

using namespace std;



int main() {
	int s, v, n, len, bi_len;
	vector<int>* route;
	vector<int>* bi_route;
	CSR graph("facebook_combined.txt");
	n = graph.getSize();
	/*vector<int> pre(n);
	vector<int> distance(n);
	bfs_all(graph, s, pre, distance);*/

	while (1) {
		cout << "Please input the source: ";
		cin >> s;
		cout << "Please input the destination: ";
		cin >> v;

		bi_route = bi_bfs(graph, s, v);
		bi_len = bi_route->size();
		cout << "\nBidirectional BFS:\nThe distance is: " << bi_len - 1 << endl;
		cout << "The shortest path is:\n" << bi_route->at(0);
		for (int i = 1; i < bi_len; i++) {
			cout << " -> " << bi_route->at(i);
		}
		delete bi_route;

		route = bfs(graph, s, v);
		len = route->size();
		cout << "\n\nTraditional BFS:\nThe distance is: " << len - 1 << endl;
		cout << "The shortest path is:\n" << route->at(0);
		for (int i = 1; i < len; i++) {
			cout << " -> " << route->at(i);
		}
		delete route;



		cout << "\n\n";

	}
}
