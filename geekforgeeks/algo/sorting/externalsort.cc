#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

struct MinHeapNode {
  int element;
  int i;
};

class MinHeap {
  MinHeapNode *harr;
  int heap_size;

public:
  MinHeap(MinHeapNode a[], int size) {
    heap_size = size;
    harr = a;
    int i = (heap_size - 1) / 2;
    while (i >= 0) {
      MinHeapify(i--);
    }
  }

  void MinHeapify(int i) {
    int l = left(i), r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l].element < harr[i].element)
      smallest = l;
    if (r < heap_size && harr[r].element < harr[smallest].element)
      smallest = r;
    if (smallest != i) {
      swap(harr[i], harr[smallest]);
      MinHeapify(smallest);
    }
  }

  int left(int i) { return 2 * i + 1; }

  int right(int i) { return 2 * i + 2; }

  MinHeapNode getMin() { return harr[0]; }

  void replaceMin(MinHeapNode x) {
    harr[0] = x;
    MinHeapify(0);
  }
};

void merge(int arr[], int l, int m, int r) {
  int n1 = m - l + 1, n2 = r - m;
  int *L = new int[n1], *R = new int[n2];

  for (int i = 0; i < n1; ++i)
    L[i] = arr[l + i];
  for (int i = 0; i < n2; ++i)
    R[i] = arr[m + 1 + i];

  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j])
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];

  delete[] L;
  delete[] R;
}

void mergesort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergesort(arr, l, m);
    mergesort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

FILE *openfile(char *filename, const char *mode) {
  FILE *fp = fopen(filename, mode);
  if (!fp) {
    fprintf(stderr, "open file error");
    exit(1);
  }
  return fp;
}

void createInitialRuns(char *input_file, int run_size, int num_ways) {
  FILE *in = openfile(input_file, "r");
  FILE *out[num_ways];
  char filename[5];

  for (int i = 0; i < num_ways; ++i) {
    snprintf(filename, sizeof(filename), "%d", i);
    out[i] = openfile(filename, "w");
  }

  int *arr = (int *)malloc(run_size * sizeof(int));
  bool more_input = true;
  int next_out_file = 0;
  int i;

  while (more_input) {
    for (i = 0; i < run_size; ++i) {
      if (fscanf(in, "%d ", &arr[i]) != 1) {
        more_input = false;
        break;
      }
    }

    mergesort(arr, 0, i - 1);
    for (int j = 0; j < i; ++j)
      fprintf(out[next_out_file], "%d ", arr[j]);
    ++next_out_file;
  }
  for (int i = 0; i < num_ways; ++i)
    fclose(out[i]);
  fclose(in);
  free(arr);
}

void mergeFiles(char *outputFile, int n, int k) {
  FILE *in[15];
  for (int i = 0; i < k; ++i) {
    char fileName[2];
    snprintf(fileName, sizeof(fileName), "%d", i);
    in[i] = openfile(fileName, "r");
  }
  FILE *out = openfile(outputFile, "w");

  MinHeapNode *harr = new MinHeapNode[k];
  int i;
  for (i = 0; i < k; ++i) {
    if (fscanf(in[i], "%d ", &harr[i].element) != 1)
      break;
    harr[i].i = i;
  }
  MinHeap hp(harr, i);
  int count = 0;

  while (count != i) {
    MinHeapNode root = hp.getMin();
    fprintf(out, "%d ", root.element);

    if (fscanf(in[root.i], "%d ", &root.element) != 1) {
      root.element = INT32_MAX;
      ++count;
    }
    hp.replaceMin(root);
  }
  for (int i = 0; i < k; ++i)
    fclose(in[i]);
  fclose(out);
  free(harr);
}

int main() {
  int num_ways = 10, run_size = 1000;
  char input_file[] = "input.txt";
  char output_file[] = "output.txt";

  FILE *in = openfile(input_file, "w");
  srand(time(NULL));
  for (int i = 0; i < num_ways * run_size; ++i)
    fprintf(in, "%d ", rand());
  fclose(in);

  createInitialRuns(input_file, run_size, num_ways);
  mergeFiles(output_file, run_size, num_ways);
}