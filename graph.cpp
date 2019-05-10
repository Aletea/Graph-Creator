#include <iostream>
#include <cstring>
#include "graph.h"

using namespace std;
//constructor
graph::graph() {
  //create empty array to keep track of edges
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      array[i][j] = 0;
    }
  }
  //empty array to keep track of vertices
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 100; j++) {
      labels[i][j] = '\0';
    }
  }
}

//destructor
graph::~graph() {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 100; j++) {
      labels[i][j] = '\0';
    }
  }
}

void graph::insertVertex(char name[100]) {
  //add vertex
  //add character array of label to end of array of labels
  for (int i = 0; i < 20; i++) {
    if (labels[i][0] == '\0') {
      for (int j = 0; j < 100; j++) {
	labels[i][j] = name[j];
      }
      break;
    }
  }
}

void graph::insertEdge(char first[100], char second[100], int weight) {
  //get the numerical position of the first and second vertex by finding them in the list
  //firspos is for index of first label
  int firstPos = 0;
  for (int i = 0; i < 20; i++) {
    if (strcmp(labels[i],first) == 0) {
      firstPos = i;
      break;
    }
    else if (i == 19) {
      cout << "first node not found" << endl;
      return;
    }
  }
  //index of second vertex
  int secondPos = 0;
  for (int i = 0; i < 20; i++) {
    if (strcmp(labels[i],second) == 0) {
      secondPos = i;
      break;
    }
    else if (i == 19) {
      cout << "second node not found" << endl;
      return;
    }
  }
  //add the weight to the array of edge weights for both directions
  array[secondPos][firstPos] = weight;
}

//prints out the labels and the table of edge values
void graph::print() {
  if (labels[0][0] == '\0') {
    cout << "No verticies" << endl;
    return;
  }
  int length = 0;
  cout << "Labels: " << endl;
  for (int i = 0; i < 20; i++) {
    if (labels[i][0] == '\0') {
      length = i;
      break;
    }
    cout << i+1 << ": " << labels[i] << endl;
  }
  cout << endl << "Table:" << endl;
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      cout << array[i][j] << " ";
    }
    cout << endl;
  }
}

//remove a vertex
void graph::removeVertex(char name[100]) {
  //find vertex
  int position = 0;
  for (int i = 0; i < 20; i++) {
    if (strcmp(labels[i],name) == 0) {
      position = i;
      break;
    }
    else if (i == 19) {
      cout << "vertex not found" << endl;
      return;
    }
  }
  //shift all edge table columns left
  for (int i = position; i < 20; i++) {
    if (i == 19) {
      for (int j = 0; j < 20; j++) {
	array[i][j] = 0;
      }
    }
    else {
      for (int j = 0; j < 20; j++) {
	array[i][j] = array[i+1][j];
      }
    }
  }
  //shift all edge table rows up
  for (int j = position; j < 20; j++) {
    if (j == 19) {
      for (int i = 0; i < 20; i++) {
	array[i][j] = 0;
      }
    }
    else {
      for (int i = 0; i < 20; i++) {
	array[i][j] = array[i][j+1];
      }
    }
  }
  //shift label list down
  for (int i = position; i < 20; i++) {
    if (i == 19) {
      for (int j = 0; j < 20; j++) {
	labels[i][j] = '\0';
      }
    }
    else {
    for (int j = 0; j < 20; j++) {
      labels[i][j] = labels[i+1][j];
    }
    }
  }
}

void graph::removeEdge(char first[100], char second[100]) {
  //first first position
  int firstpos = 0;
  for (int i = 0; i < 20; i++) {
    if (strcmp(labels[i],first) == 0) {
      firstpos = i;
      break;
    }
    else if (i == 19) {
      cout << "vertex 1 not found" << endl;
      return;
    }
  }
  //find second position
  int secondpos = 0;
  for (int i = 0; i < 20; i++) {
    if (strcmp(labels[i],second) == 0) {
      secondpos = i;
      break;
    }
    else if (i == 19) {
      cout << "vertex 2 not found" << endl;
      return;
    }
  }
  //remove edge if it exists
  if (array[secondpos][firstpos] == 0) {
    cout << "Edge does not exist." << endl;
  }
  array[secondpos][firstpos] = 0;
}
//Dijkstra's algorithm
void graph::shortestPath(char first[100], char end[100]) {
  //create a node for each vertex and set to unvisited
  node** unvisited = new node*[20];
  for (int i = 0; i < 20; i++) {
    if (labels[i][0] != '\0') {
      node* newNode = new node();
      newNode->name = labels[i];
      newNode->position = i;
      unvisited[i] = newNode;
    }
    else {
      unvisited[i] = NULL;
    }
  }
  //find the start node
  int firstNode = 0;
  for (int i = 0; i < 20; i++) {
    if (strcmp(labels[i],first) == 0) {
      firstNode = i;
      break;
    }
  }
  //find the end node
  int secondNode = 0;
  for (int i = 0; i < 20; i++) {
    if (strcmp(labels[i],end) == 0) {
      secondNode = i;
      break;
    }
  }
  /*for (int i = 0; i < 20;i++) {
    if (unvisited[i] != NULL) {
      cout << "Unvisited " << i << ": " << unvisited[i]->name << endl;
    }

    }*/
  //create array of visited nodes and set the start node to visited
  node** visited = new node*[20];
  visited[firstNode] = unvisited[firstNode];
  unvisited[firstNode] = NULL;
  //get start and end nodes
  node* start = visited[firstNode];
  node* finish = unvisited[secondNode];
  //run the algorithm
  findPath(start, finish, 0, unvisited, visited);
}

void graph::findPath(node* current, node* end, int distance, node** unvisited, node** visited) {
  //if current is the target, print shortest path and return
  if (current == end) {
    cout << "Shortest Path: " << end->name;
    node* place = end;
    while (place->previous != NULL) {
      cout << "<-" << place->previous->name;
      place = place->previous;
    }
    cout << endl;
    cout << "Distance: " << distance << endl;
    return;
  }
  //move current unvisited node to visited
  unvisited[current->position] = NULL;
  visited[current->position] = current;
  //for all unvisited neighbors
  for (int i = 0; i < 20; i++) {
    if (unvisited[i] != NULL) {
    if (array[i][current->position] != 0 && current->position != i) {
      //if the distance is less that the unvisited neighbor's distance
      int newdistance = distance + array[i][current->position];
      if (newdistance < unvisited[i]->distance || unvisited[i]->distance == -1) {
	//change distance
	unvisited[i]->distance = newdistance;
	//set new previous
	unvisited[i]->previous = current;
      }
    }
    }
  }
  //run for unvisited node with shortest distance
  int unvisitedDistances[20];
  for (int i = 0; i < 20; i++) {
    if (unvisited[i] != NULL) {
      unvisitedDistances[i] = unvisited[i]->distance;
    }
    else {
      unvisitedDistances[i] = -1;
    }
  }
  //find unvisited node with shortest distance
  int nextPos = -1;
  int nextdistance = -1;
  for (int i = 0; i < 20; i++) {
    if (unvisitedDistances[i] != -1 && (unvisitedDistances[i] < nextdistance || nextdistance == -1)) {
      nextPos = i;
      nextdistance = unvisited[i]->distance;
    }
  }
  //if no more nodes, there is no path
  if (nextdistance == -1) {
    cout << "No Path Found" << endl;
    return;
  }
  //recursive: run again for next unvisited node
  else {
    findPath(unvisited[nextPos], end, nextdistance, unvisited, visited);  
  }
  
}
