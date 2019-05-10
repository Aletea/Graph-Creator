#include <iostream>
#include <vector>

using namespace std;
//nodes for Dijkstra's algorithm
//keeps track of vertex name and position, distance to start node, and the previous node in the current path
struct node{
  char* name = new char[100];
  int position = 0;
  int distance = -1;
  node* previous = NULL;
  int next = -1;
};

class graph {
 public:
  graph();
  ~graph();
  void insertVertex(char name[100]);
  void insertEdge(char first[100], char second[100], int weight);
  void print();
  void removeVertex(char name[100]);
  void removeEdge(char first[100], char second[100]);
  void shortestPath(char first[100], char end[100]);
  void findPath(node* current, node* end, int distance, node** unvisited, node** visited);
 private:
  //keeps track of edge weights
  int array[20][20];
  //keeps track of labels
  char labels[20][100];
};
