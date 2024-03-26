#include <iostream>
#include <cassert>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

template<typename T>
class AdjMatGraph // Adjacent Matrix Graph
{
public:
	struct Vertex // Node
	{
		T item = T();
	};

	AdjMatGraph(int max_vertices)
	{
		max_vertices_ = max_vertices; // capacity

		matrix_ = new int*[max_vertices_];
		for (int r = 0; r < max_vertices_; r++) {
			matrix_[r] = new int[max_vertices_];
			for (int c = 0; c < max_vertices_; c++)
				matrix_[r][c] = 0;
		}

		vertices_ = new Vertex[max_vertices_];

		n_ = 0;
	}

	~AdjMatGraph()
	{
		delete[] vertices_;

		for (int i = 0; i < max_vertices_; i++)
			delete[] matrix_[i];
		delete[] matrix_;

		if (visited_)
			delete[] visited_;
	}

	void PrintMatrix()
	{
		using namespace std;
		if (n_)
			for (int r = 0; r < n_; r++) {
				for (int c = 0; c < n_; c++)
					cout << matrix_[r][c] << ", ";
				cout << endl;
			}
		else
			cout << "Empty" << endl;

		cout << endl;
	}

	void InsertVertex(T item)
	{
		vertices_[n_].item = item;
		n_++;
	}

	void InsertEdge(int u, int v) // 여기서 u, v는 인덱스
	{
		assert(u < n_ && v < n_);

		// TODO:
		matrix_[u][v] = 1;
	}

	int Capacity()
	{
		return max_vertices_;
	}

	void DepthFirstTraversal()
	{
		cout << "Recursive DFS" << endl;

		ResetVisited();

		DepthFirstTraversal(0);

		cout << endl;
		cout << endl;
	}

	void DepthFirstTraversal(int v) // v는 인덱스 // 재귀방식 구현
	{
		// TODO:
		visited_[v] = true;
		cout << vertices_[v].item << " ";

		for (int i = 0; i < max_vertices_; i++)
		{
			if (visited_[i] == false && matrix_[v][i] == 1)
			{
				DepthFirstTraversal(i);
			}
		}

		//강의 해설
		//for (int w = 0; w < n_; w++)
		//	if (matrix_[v][w] && !visited_[w]) // <- 대신에 여기서 꼭 !visited_[w] 있어야 함
		//		DepthFirstTraversal(w);
		
	}

	void IterDFT()   // Depth First Search
	{
		cout << "Iterative DFS" << endl;

		// TODO:
		ResetVisited();
		int v = 0;

		Stack<int> s;

		s.Push(v);
		visited_[v] = true;


		while (!s.IsEmpty())
		{
			cout << v << " Stack : ";
			s.Pop();
			for (int i = max_vertices_ - 1; i >= 0; i--)
			{
				if (visited_[i] == false && matrix_[v][i] == 1)
				{
					s.Push(i);
					visited_[i] = true;
				}
			}
			s.Print();
			if (!s.IsEmpty()) { v = s.Top(); }
		}

		cout << endl;

	}

	void BreadthFirstTraversal()  // Breadth First Search
	{
		cout << "Breadth First Search" << endl;
		int v = 0; // 0번에서 시작

		Queue<int> q;

		ResetVisited();

		// TODO:
		q.Enqueue(v);
		visited_[v] = true;

		while (!q.IsEmpty())
		{
			cout << q.Front() << " Queue : ";
			q.Dequeue();
			for (int i = 0; i < max_vertices_; i++)
			{
				if (visited_[i] == false && matrix_[v][i] == 1)
				{
					q.Enqueue(i);
					visited_[i] = true;
				}
			}
			q.Print();
			if (!q.IsEmpty()) { v = q.Front(); }
		}

		// 강의 해설
		//while (!q.IsEmpty())
		//{
		//	v = q.Front();
		//	q.Dequeue();

		//	cout << vertices_[v].item << " ";

		//	for (int w = 0; w < n_; w++)
		//		if (matrix_[v][w] && !visited_[w])
		//		{
		//			visited_[w] = true;
		//			q.Enqueue(w);
		//		}
		//	cout << "Queue : ";
		//	q.Print();
		//	cout << endl;
		//}

	}

	void ResetVisited()
	{
		if (!visited_)
			visited_ = new bool[max_vertices_];
		for (int i = 0; i < max_vertices_; i++) visited_[i] = false; // 초기화
	}

private:
	int** matrix_ = nullptr;
	Vertex* vertices_ = nullptr;
	int n_ = 0;					// size
	int max_vertices_ = 0;		// capacity

	bool* visited_ = nullptr;
};

int main()
{
	// 정점(vertex), 간선(edge)

	AdjMatGraph<int> g(7);

	for (int i = 0; i < g.Capacity(); i++)
		g.InsertVertex(i);

	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);

	g.PrintMatrix();

	g.DepthFirstTraversal();

	g.IterDFT();

	g.BreadthFirstTraversal();

	return 0;
}