#include "stdio.h"
#include "stdlib.h"

#define QUEUE_SIZE 50

struct node {

	int vertex;
	struct node * next;
	struct node * parent;
};

struct queue {
	int size;
	struct node * list[QUEUE_SIZE];
	int front;
	int last;
};

struct Graph {
	struct node ** adjList;
	int numVertices;
  int * visited;
};

/* Node Operations */
struct node * createNode(int vertex);
void printNode(struct node *);

/* Queue Operations */
struct queue * createQueue();
void enqueue(struct queue * q, struct node * victim);
struct node * dequeue(struct queue * q);
int isEmpty(struct queue *q);
void printQueue(struct queue * q);

/* Graph Operations */
struct Graph * createGraph(int numVertices);
void addEdge(struct Graph * graph,int src, int dest);


/* Breath First Search */
void bfs(struct Graph * graph, int src, int dest);


int main (void){

  struct Graph * graph = createGraph(7);
  /*struct queue * q = createQueue();
  int i =0;
  for(;i<10;i++){
    struct node * newNode = createNode(i);
    enqueue(q, newNode);
  }
  printQueue(q);
  struct node * n = dequeue(q);
  printQueue(q);
  printNode(n);

  n = dequeue(q);
  printQueue(q);
  printNode(n);

  enqueue(q,createNode(99));
  printQueue(q);
*/
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 1, 6);
    addEdge(graph, 3, 5);
    addEdge(graph, 5, 6);
    //addEdge(graph, 0, 5);



  bfs(graph, 0,5);

  return 0;
}

/* BFS */
void bfs(struct Graph * graph, int src, int dest){

  struct queue * q = createQueue();

  /* Add src to the queue and mark as visited */
  enqueue(q,createNode(src));
  graph->visited[src]=1;

  while(!isEmpty(q)){
    printQueue(q);
    /* pop a place off the queue */
    struct node * currentVertex = dequeue(q);
    printNode(currentVertex);
    if (currentVertex->vertex == dest){
      printf("Found it\n");
      printf("%d\t",currentVertex->vertex);
      while (currentVertex->parent){
        printf("%d\t",currentVertex->parent->vertex);
        currentVertex = currentVertex->parent;
      }
      printf("\n");
      return;
    }
    else{
      struct node * temp = graph->adjList[currentVertex->vertex];
      while(temp){
        if (graph->visited[temp->vertex] == 0){
          graph->visited[temp->vertex]=1;
          temp->parent = currentVertex;
          enqueue(q,temp);
        }
        temp = temp->next;
      }

    }


  }
  printf("No path to dest\n");
  return;

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

void addEdge(struct Graph * graph, int src, int dest){

  /* Add an edge from src to dest */
  struct node * newNode = createNode(dest);
  newNode->next = graph->adjList[src];
  graph->adjList[src] = newNode;

  /* Add an edge from dest to src */
  newNode = createNode(src);
  newNode->next = graph->adjList[dest];
  graph->adjList[dest] = newNode;

}


/* Node Operations Implementation */
struct node * createNode(int vertex){
	struct node * newNode  = (struct node *) malloc(sizeof(struct node));
	newNode->vertex = vertex;
	newNode->next = NULL;
  newNode->parent = NULL;
	return newNode;

}

void printNode(struct node * n){
  printf("Vertex: %d\n", n->vertex);
}


/* Queue Operations */
struct queue * createQueue(){

  struct queue * q = (struct queue *) malloc(sizeof(struct queue));

  q->front = -1;
  q->last = -1;
  q->size =0;

  return q;
}

void enqueue(struct queue * q, struct node * victim){

  if(q->size == 50){
    printf("Queue if full\n");
  }
  else{
    if(q->front == -1){
      q->front =0;
    }
    q->last++;
    q->list[q->last]=victim;

    q->size++;
  }
}

struct node * dequeue(struct queue * q){

  struct node * victim = q->list[q->front];
  q->front++;
  q->size--;
  if ( q->front > q->last){
    q->front = -1;
    q->last = -1;
    q->size =0;
  }
  return victim;
}

int isEmpty(struct queue * q){

  if(q->size == 0) return 1;
  else return 0;
}


void printQueue(struct queue * q){

  int i =q->front;
  printf("Node:\t");
  for(;i<=q->last;i++){
    struct node * victim = q->list[i];
    printf("%d\t", victim->vertex);
  }

  printf("Front: %d Last: %d Size: %d\n",q->front,q->last,q->size);

}
