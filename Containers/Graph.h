//
//  Graph.h
//  Algorithms
//
//  Created by Max Reshetey on 30/11/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include "vector"
#include "list"
#include "queue" // For BFS

class Graph
{
public:
	void addVertex(int v)
	{
		// TODO: For now only incremental vertices are allowed
		assert(v == _adj.size()+1);

		const auto l = list<int>();
		_adj.push_back(l);
	}

	void addEdge(int u, int v)
	{
		assert(u <= _adj.size());
		assert(v <= _adj.size());

		_adj[u-1].push_back(v);
	}

	// Time O(V + E)
	void breadthFirstSearch(int s)
	{
		std::vector<int> color(_adj.size(), 1); // 0 - black, 1 - white
		std::vector<int> distance(_adj.size(), -1);

		auto q = std::queue<int>(); // TODO: Replace with own queue

		color[s-1] = 0;
		distance[s-1] = 0;

		q.push(s);

		while (!q.empty())
		{
			auto u = q.front();
			q.pop();

			std::cout << std::to_string(u) + "(" + std::to_string(distance[u-1]) + ")" + ", ";

			for (auto v : _adj[u-1])
			{
				if (color[v-1] == 1)
				{
					color[v-1] = 0;
					distance[v-1] = distance[u-1] + 1;

					q.push(v);
				}
			}
		}
	}
	
	std::string description()
	{
		std::string str = "";

		for (int u = 0; u < _adj.size(); u++)
		{
			str += std::to_string(u+1) + ": (";

			for (const auto &v : _adj[u])
			{
				str += std::to_string(v) + (v != _adj[u].back() ? ", " : "");
			}

			str += ")\n";
		}
		
		return str;
	}

private:
	std::vector<list<int>> _adj;
};

void test_Graph()
{
	auto g = Graph();

//	Graph from figure 22.2(a)
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addVertex(5);
	g.addVertex(6);

	g.addEdge(1, 2);
	g.addEdge(1, 4);
	g.addEdge(2, 5);
	g.addEdge(3, 5);
	g.addEdge(3, 6);
	g.addEdge(4, 2);
	g.addEdge(5, 4);
	g.addEdge(6, 6);

	std::cout << "Graph:\n" << g.description();
	
	g.breadthFirstSearch(1);
	
	
	std::cout << "\n";
	
	
}

#endif /* Graph_h */
