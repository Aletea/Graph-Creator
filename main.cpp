#include <iostream>
#include <cstring>
#include "graph.h"

int main() {
  graph* G = new graph();
  bool stillGoing = true;
  while (stillGoing == true) {
    cout << endl << "Please enter a number for one of the following options: " << endl;
  cout << "1. Add a Vertex" << endl;
  cout << "2. Add an Edge" << endl;
  cout << "3. Remove a Vertex" << endl;
  cout << "4. Remove an Edge" << endl;
  cout << "5. Find Shortest Path" << endl;
  cout << "6. Quit" << endl;
  cout << "7. Print" << endl;
  int input;
  cin >> input;
  cin.ignore();
  //add vertex
  if (input == 1) {
    //get vertex name and run insertion function for a vertex
    cout << "Enter vertex label: " << endl;
    char label[100];
    cin.get(label,100);
    cin.get();
    G->insertVertex(label);
  }
  else if (input == 2) {
    //add edge
    //get the two verticies and the weight of the edge between them, then runn the insertion function for an edge
    cout << "First Vertex: ";
    char first[100];
    cin.get(first,100);
    cin.get();
    cout << "Second Vertex: ";
    char second[100];
    cin.get(second,100);
    cin.get();
    cout << "Edge Weight: ";
    int weight;
    cin >> weight;
    cin.ignore();
    G->insertEdge(first, second, weight);
  }
  else if (input == 3) {
    //get vertex label and run removal function for vertex
    //remove vertex
    cout << "Vertex Label: " << endl;
    char label[100];
    cin.get(label,100);
    cin.get();
    G->removeVertex(label);
  }
  else if (input == 4) {
    //remove edge
    //get two vertices and run removal function to remove edge from vertex one to vertex two
    cout << "First Vertex: ";
    char first[100];
    cin.get(first,100);
    cin.get();
    cout << "Second Vertex: ";
    char second[100];
    cin.get(second,100);
    cin.get();
    G->removeEdge(first,second);
  }
  else if (input == 5) {
    //find shortest path
    //get start and end vertex and run shortest path for them
    cout << "First Vertex: ";
    char first[100];
    cin.get(first,100);
    cin.get();
    cout << "End Vertex: ";
    char end[100];
    cin.get(end,100);
    cin.get();
    G->shortestPath(first,end);
  }
  else if (input == 6) {
    //quit
    break;
  }
  else {
    //print
    G->print();
  }
  }
  return 0;
}
