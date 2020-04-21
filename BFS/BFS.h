#pragma once
#include <climits>
#include <queue>
#include "CSR.h"
#include <algorithm>

#define NIL -1

using  namespace std;

enum class Color { WHITE, GRAY, GRAYs, GRAYv, BLACK };


bool bfs_all(CSR& graph, int s, vector<int>& pre, vector<int>& distance) {
	int n = graph.getSize();
	vector<Color> color(n);
	for (int i = 0; i < n; i++) {
		if (i != s) {
			color[i] = Color::WHITE;
			distance[i] = INT_MAX;
			pre[i] = NIL;
		}
		else {
			color[i] = Color::GRAY;
			distance[i] = 0;
			pre[i] = NIL;
		}
	}
	queue<int> Q;
	Q.push(s);
	int u;
	while (!Q.empty()) {
		u = Q.front();
		Q.pop();
		for (int j = 0; j < n; j++) {
			if (graph.at(u, j) == 1) {
				if (color[j] == Color::WHITE) {
					color[j] = Color::GRAY;
					distance[j] = distance[u] + 1;
					pre[j] = u;
					Q.push(j);
				}
			}
		}
		color[u] = Color::BLACK;
	}
	return true;
}

vector<int>* bfs(CSR& graph, int s, int v) {
	int n = graph.getSize();
	vector<int> pre(n);
	vector<int> distance(n);
	vector<Color> color(n);
	for (int i = 0; i < n; i++) {
		if (i != s) {
			color[i] = Color::WHITE;
			distance[i] = INT_MAX;
			pre[i] = NIL;
		}
		else {
			color[i] = Color::GRAY;
			distance[i] = 0;
			pre[i] = NIL;
		}
	}
	queue<int> Q;
	Q.push(s);
	int u;
	while (!Q.empty()) {
		u = Q.front();
		Q.pop();
		for (int j = 0; j < n; j++) {
			if (color[j] == Color::WHITE && graph.at(u, j) == 1) {
				color[j] = Color::GRAY;
				distance[j] = distance[u] + 1;
				pre[j] = u;
				Q.push(j);
				if (j == v) {
					vector<int>* route = new vector<int>;
					int k;
					for (k = j; k != NIL; k = pre[k]) {
						route->emplace_back(k);
					}
					reverse(route->begin(), route->end());
					return route;
				}

			}
		}
		color[u] = Color::BLACK;
	}
	return nullptr;
}

vector<int>* bi_bfs(CSR& graph, int s, int v) {
	int n = graph.getSize();
	vector<int> pre(n);
	vector<int> distance(n);
	vector<Color> color(n);
	for (int i = 0; i < n; i++) {
		if (i != s && i != v) {
			color[i] = Color::WHITE;
			distance[i] = INT_MAX;
			pre[i] = NIL;
		}
		else {
			if (i == s)
				color[i] = Color::GRAYs;
			else
				color[i] = Color::GRAYv;
			distance[i] = 0;
			pre[i] = NIL;
		}
	}
	queue<int> Qs;
	queue<int> Qv;
	Qs.push(s);
	Qv.push(v);
	int s_m, v_m;
	while (!Qs.empty() || !Qv.empty()) {
		if (!Qs.empty()) {
			s_m = Qs.front();
			Qs.pop();
			for (int j = 0; j < n; j++) {
				//if (graph.at(s_m, j) == 1) {
				if (color[j] == Color::WHITE && graph.at(s_m, j) == 1) {
					color[j] = Color::GRAYs;
					distance[j] = distance[s_m] + 1;
					pre[j] = s_m;
					Qs.push(j);
				}
				else if (color[j] == Color::GRAYv && graph.at(s_m, j) == 1) { //j belong to v
					vector<int>* route = new vector<int>;
					int k;
					for (k = s_m; k != NIL; k = pre[k]) {
						route->emplace_back(k);
					}
					reverse(route->begin(), route->end());
					for (k = j; k != NIL; k = pre[k]) {
						route->emplace_back(k);
					}
					return route;
				}
				//}
			}
			color[s_m] = Color::BLACK;
		}
		if (!Qv.empty()) {
			v_m = Qv.front();
			Qv.pop();
			for (int j = 0; j < n; j++) {
				//if (graph.at(v_m, j) == 1) {
				if (color[j] == Color::WHITE && graph.at(v_m, j) == 1) {
					color[j] = Color::GRAYv;
					distance[j] = distance[v_m] + 1;
					pre[j] = v_m;
					Qv.push(j);
				}
				else if (color[j] == Color::GRAYs && graph.at(v_m, j) == 1) {// j belongs to s
					vector<int>* route = new vector<int>;
					int k;
					for (k = j; k != NIL; k = pre[k]) {
						route->emplace_back(k);
					}
					reverse(route->begin(), route->end());
					for (k = v_m; k != NIL; k = pre[k]) {
						route->emplace_back(k);
					}
					return route;
				}
				//}
			}
			color[v_m] = Color::BLACK;
		}
	}
	return nullptr;
}