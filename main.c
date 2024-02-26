#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define array_lenght(array) (sizeof(array) / sizeof(array[0]))

typedef struct {
  int V1;
  int V2;
  int weight;
} Node;

int node_compare_weight(const void *a, const void *b) {
  const Node(*x) = a;
  const Node(*y) = b;

  return x->weight - y->weight;
}

void dump_graph(Node graph[], size_t total_nodes) {
  printf("graph G {\n");
  for (size_t i = 0; i < total_nodes; i++) {
    printf("\t%d -- %d [label=%d]\n", graph[i].V1, graph[i].V2,
           graph[i].weight);
  }
  printf("}\n");
}

void print_array(int arr[], size_t arr_len) {
  for (size_t i = 0; i < arr_len; i++) {
    printf("[%zu] -> %d\n", i, arr[i]);
  }
}

void new_union_find(int parent[], int size[], size_t n_nodes) {
  for (size_t i = 0; i < n_nodes; i++) {
    parent[i] = i;
    size[i] = 0;
  }
}

int find_parent(int parent[], int p) {
  while (parent[p] != p) {
    p = parent[parent[p]];
  }
  return p;
}

bool node_union(int v1, int v2, int parent[], int size[]) {
  int root1 = find_parent(parent, v1);
  int root2 = find_parent(parent, v2);

  if (root1 == root2) {
    return false;
  }

  if (size[root1] > size[root2]) {
    parent[root2] = root1;
    size[root1] += 1;
  } else {
    parent[root1] = root2;
    size[root2] += 1;
  }
  return true;
}

void kruscal(Node graph[], size_t n_nodes) {
  qsort(graph, n_nodes, sizeof(graph[0]), node_compare_weight);

  int parent[n_nodes];
  int size[n_nodes];

  new_union_find(parent, size, n_nodes);

  int min_cost = 0;
  printf("graph G {\n");
  for (size_t i = 0; i < n_nodes; i++) {
    if (node_union(graph[i].V1, graph[i].V2, parent, size)) {
      printf("\t%d -- %d [label=%d]\n", graph[i].V1, graph[i].V2,
             graph[i].weight);
      min_cost += graph[i].weight;
    }
  }

  printf("}\n");
  printf("\n\n MINIMUM TOTAL WEIGHT: %d \n\n", min_cost);
}

int main(void) {
  Node graph[] = {
      {.weight = 2, .V1 = 0, .V2 = 2}, {.weight = 6, .V1 = 0, .V2 = 3},
      {.weight = 5, .V1 = 1, .V2 = 2}, {.weight = 1, .V1 = 1, .V2 = 4},
      {.weight = 2, .V1 = 2, .V2 = 3}, {.weight = 3, .V1 = 3, .V2 = 4},
  };

  printf("\nGRAPH:\n");
  dump_graph(graph, array_lenght(graph));

  printf("\nMST:\n");
  kruscal(graph, array_lenght(graph));

  return 0;
}
