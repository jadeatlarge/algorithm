#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
using namespace std;

void printarray(int arr[], int n) {
  for (int i = 0; i < n; ++i)
    cout << arr[i] << " ";
  cout << endl;
}

void selectionsort(int arr[], int n) {
  int min_idx;

  for (int i = 0; i < n - 1; ++i) {
    min_idx = i;
    for (int j = i + 1; j < n; ++j)
      if (arr[j] < arr[min_idx])
        min_idx = j;
    swap(arr[min_idx], arr[i]);
  }
}

void bubblesort(int arr[], int n) {
  bool swapped;
  for (int i = 0; i < n - 1; ++i) {
    swapped = false;
    for (int j = 0; j < n - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }

    if (!swapped)
      break;
  }
}

void insertionsort(int arr[], int n) {
  int key;
  for (int i = 1; i < n; ++i) {
    key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

void shellsort(int arr[], int n) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; ++i) {
      int tmp = arr[i];
      int j;

      for (j = i; j >= gap && arr[j - gap] > tmp; j -= gap)
        arr[j] = arr[j - gap];
      arr[j] = tmp;
    }
  }
}

void merge(int arr[], const int l, const int m, const int r) {
  int sub_l = m - l + 1, sub_r = r - m;
  int *leftarr = new int[sub_l], *rightarr = new int[sub_r];

  for (int i = 0; i < sub_l; ++i)
    leftarr[i] = arr[l + i];
  for (int i = 0; i < sub_r; ++i)
    rightarr[i] = arr[m + 1 + i];

  int lindex = 0, rindex = 0, mindex = l;

  while (lindex < sub_l && rindex < sub_r) {
    if (leftarr[lindex] <= rightarr[rindex]) {
      arr[mindex] = leftarr[lindex];
      ++lindex;
    } else {
      arr[mindex] = rightarr[rindex];
      ++rindex;
    }
    ++mindex;
  }
  while (lindex < sub_l) {
    arr[mindex++] = leftarr[lindex++];
  }
  while (rindex < sub_r) {
    arr[mindex++] = rightarr[rindex++];
  }
  delete[] leftarr;
  delete[] rightarr;
}

void mergesort(int arr[], int begin, int end) {
  if (begin < end) {
    int mid = begin + (end - begin) / 2;
    mergesort(arr, begin, mid);
    mergesort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
  }
}

void countsort(int arr[], int n) {
  int *output = new int[n];
  int count[128];
  memset(count, 0, sizeof(count));

  for (int i = 0; i < n; ++i)
    ++count[arr[i]];
  for (int i = 1; i < 128; ++i)
    count[i] += count[i - 1];
  for (int i = 0; i < n; ++i) {
    output[count[arr[i]] - 1] = arr[i];
    --count[arr[i]];
  }

  for (int i = 0; i < n; ++i)
    arr[i] = output[i];
  delete[] output;
}

int main() {
  int arr[] = {64, 25, 12, 22, 22, 11};
  int n = sizeof(arr) / sizeof(arr[0]);
  // selectionsort(arr, n);
  // bubblesort(arr, n);
  // insertionsort(arr, n);
  // shellsort(arr, n);
  // mergesort(arr, 0, n - 1);
  // countsort(arr, n);
  printarray(arr, n);
}