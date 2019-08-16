// File name: ExtremeC_examples_chapter5_5.c
// Description: Example 5.5

#include <stdio.h> // For printf function
#include <stdlib.h> // For heap memory functions

#define QUEUE_MAX_SIZE 100

typedef struct {
  int front;
  int rear;
  double* arr;
} queue_t;

void init(queue_t* q) {
  q->front = q->rear = 0;
  // The heap memory block allocated here is owned
  // by the queue object.
  q->arr = (double*)malloc(QUEUE_MAX_SIZE * sizeof(double));
}

void destroy(queue_t* q) {
  free(q->arr);
}

int size(queue_t* q) {
  return q->rear - q->front;
}

void enqueue(queue_t* q, double item) {
  q->arr[q->rear] = item;
  q->rear++;
}

double dequeue(queue_t* q) {
  double item = q->arr[q->front];
  q->front++;
  return item;
}

int main(int argc, char** argv) {
  // The heap memory block allocated here is owned
  // by the function main
  queue_t* q = (queue_t*)malloc(sizeof(queue_t));

  // Allocate needed memory for the queue object
  init(q);

  enqueue(q, 6.5);
  enqueue(q, 1.3);
  enqueue(q, 2.4);

  printf("%f\n", dequeue(q));
  printf("%f\n", dequeue(q));
  printf("%f\n", dequeue(q));

  // Release resources acquired by the queue object
  destroy(q);

  // Free the memory allocated for the queue object
  // acquired by the function main
  free(q);
  return 0;
}
