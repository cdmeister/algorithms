#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

#define QUEUE_SIZE 50

struct node {

	int vertex;
  int cost;
	struct node * parent;
  struct node * next;
};

struct Graph {
	struct node ** adjList;
	int numVertices;
  int * visited;
};

/* Node Operations */
struct node * createNode(int vertex);
void printNode(struct node *);
void printNodeArray(struct node * array, int size);

/* Graph Operations */
struct Graph * createGraph(int numVertices);
struct node * cheapestNode(struct node * costParentArray, int * visited);
void addDirectedEdgeCost(struct Graph * graph,int src, int dest,int cost);


/* Djikstra's Algo */
void dk(struct Graph * graph, int src, int dest);


int main (void){

  struct Graph * graph = createGraph(6);
  /*
  * 0 = Book
  * 1 = LP
  * 2 = Poster
  * 3 = Bass Guitar
  * 4 = Drum Set
  * 5 = Piano
  */

  addDirectedEdgeCost(graph,0,1,5);
  addDirectedEdgeCost(graph,0,2,0);


  addDirectedEdgeCost(graph,1,3,15);
  addDirectedEdgeCost(graph,1,4,20);

  addDirectedEdgeCost(graph,2,3,30);
  addDirectedEdgeCost(graph,2,4,35);

  addDirectedEdgeCost(graph,3,5,20);

  addDirectedEdgeCost(graph,4,5,10);
  dk(graph,0,5);

  return 0;
}

/* Djikstra's Algo */
void dk(struct Graph * graph, int src, int dest){

  struct node * costParentArray =
          (struct node *) malloc(graph->numVertices * sizeof(struct node));
  int * visited = (int *) malloc(graph->numVertices * sizeof(int));
  int i;
  struct node * dummy = (struct node *) malloc(sizeof(struct node));
  dummy->vertex=INT_MAX;
  for(i=0;i<graph->numVertices;i++){
    costParentArray[i].vertex=i;
    costParentArray[i].cost=INT_MAX;
    costParentArray[i].parent=dummy;
    visited[i]=0;
  }
/* Initialize the costParentArray first befor running dk */
  struct node * neighborInit = graph->adjList[src];
  struct node * parent = createNode(src);
  while(neighborInit){
    costParentArray[neighborInit->vertex].cost=neighborInit->cost;
    costParentArray[neighborInit->vertex].parent=parent;
    neighborInit=neighborInit->next;
  }
  visited[src]=1;
  /*Sanity Check*/
  printNodeArray(costParentArray,graph->numVertices);
  struct node * cheapNode = cheapestNode(costParentArray, visited);
  int finished = 0;
  while(finished != 1){
    struct node * neighbors = graph->adjList[cheapNode->vertex];
    printNode(cheapNode);
    while(neighbors){
      if(cheapNode->cost + neighbors->cost < costParentArray[neighbors->vertex].cost) {
        costParentArray[neighbors->vertex].cost = cheapNode->cost+ neighbors->cost;
        costParentArray[neighbors->vertex].parent = cheapNode;
      }
      neighbors=neighbors->next;
    }
    cheapNode = cheapestNode(costParentArray, visited);
    if(cheapNode->vertex == dest) finished =1;

  }

  printNodeArray(costParentArray,graph->numVertices);
  /*Print final path*/
  while(cheapNode){
    printf("%d\t",cheapNode->vertex);
    cheapNode=cheapNode->parent;
  }
  printf("\n");
}



/* Graph Operations */
struct Graph * createGraph(int numVertices){

  struct Graph * graph = (struct Graph *) malloc(sizeof(struct Graph));
  graph->numVertices = numVertices;
  graph->visited = (int *) malloc(numVertices * sizeof(int));
  graph->adjList = (struct node **) malloc(numVertices * sizeof(struct node *));

  int i;
  for(i=0;i<numVertices;++i){
    graph->adjList[i] = NULL;
    graph->visited[i] = 0;

  }
  return graph;
}

/* TODO: Clean up indicies of loops */
struct node * cheapestNode(struct node * costParentArray,int * visited){

  struct node *  minNode;

  /* Workaround for setting minNode->cost to inf
  * just find the first node I haven't visit and set that as the minNode
  */
  int i;
  for(i=0;i<6;i++){
    if(visited[i] == 0 ){
      minNode = &costParentArray[i];
      break;
    }

  }

  /* Now try to find the minNode from our costParentArray table */
  for(i=0;i<6;i++){
    if(visited[i] == 0 ){
      if(costParentArray[i].cost < minNode->cost){
        minNode = &costParentArray[i];

      }
    }
  }
  visited[minNode->vertex]=1;
  return minNode;
}


void addDirectedEdgeCost(struct Graph * graph, int src, int dest,int cost){

  /* Add an edge from src to dest */
  struct node * newNode = createNode(dest);
  newNode->next = graph->adjList[src];
  newNode->cost = cost;
  graph->adjList[src] = newNode;

}



/* Node Operations Implementation */
struct node * createNode(int vertex){
	struct node * newNode  = (struct node *) malloc(sizeof(struct node));
	newNode->vertex = vertex;
  newNode->next=NULL;
  newNode->parent=NULL;
  newNode->cost = 0;
	return newNode;

}

void printNode(struct node * n){
  printf("Vertex: %d\tCost: %d\n", n->vertex, n->cost);
}

void printNodeArray(struct node * array, int size){
  int i = 0;
  printf("COST TABLE\n");
  for(;i<size;i++){
    printf("Node: %d\tParent: %d\tCost: %d\n",array[i].vertex,array[i].parent->vertex,array[i].cost);
  }

}


