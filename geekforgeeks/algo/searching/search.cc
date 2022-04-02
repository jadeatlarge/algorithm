#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int search(int arr[], int n, int x) {
  for (int i = 0; i < n; ++i)
    if (arr[i] == x)
      return i;
  return -1;
}

int searchimprove(int arr[], int n, int x) {
  int left = 0, right = n - 1;
  int position = -1;

  for (; left <= right;) {
    if (arr[left] == x) {
      return left;
    } else if (arr[right] == x) {
      return right;
    }
    ++left;
    --right;
  }
  return -1;
}

int binarysearch(int arr[], int l, int r, int x) {
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (arr[m] == x)
      return m;
    else if (arr[m] < x)
      l = m + 1;
    else
      r = m - 1;
  }
  return -1;
}

int jumpsearch(int arr[], int x, int n) {
  int step = sqrt(n);
  int prev = 0;

  while (arr[min(step, n) - 1] < x) {
    prev = step;
    step += sqrt(n);
    if (prev >= n)
      return -1;
  }

  while (arr[prev] < x) {
    ++prev;
    if (prev == min(step, n))
      return -1;
  }

  if (arr[prev] == x)
    return prev;
  else
    return -1;
}

int interpolationsearch(int arr[], int lo, int hi, int x) {
  int pos;

  if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
    pos = lo + (((double)(hi - lo) / (arr[hi] - arr[lo])) * (x - arr[lo]));

    if (arr[pos] == x)
      return pos;
    if (arr[pos] < x)
      return interpolationsearch(arr, pos + 1, hi, x);
    if (arr[pos] > x)
      return interpolationsearch(arr, lo, pos - 1, x);
  }
  return -1;
}

int exponentialsearch(int arr[], int n, int x) {
  if (arr[0] == x)
    return 0;

  int i = 1;
  while (i < n && arr[i] <= x)
    i *= 2;

  return binarysearch(arr, i / 2, min(i, n - 1), x);
}

int main() {
  int arr[] = {2, 3, 4, 10, 40};
  int x = 10, n = sizeof(arr) / sizeof(arr[0]);

  cout << search(arr, n, x) << '\n';
  cout << searchimprove(arr, n, x) << '\n';
  cout << binarysearch(arr, 0, n - 1, x) << '\n';

  int arr2[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
  n = sizeof(arr2) / sizeof(arr2[0]);
  x = 55;
  cout << jumpsearch(arr2, x, n) << '\n';
  cout << interpolationsearch(arr2, 0, n - 1, x) << '\n';
  cout << exponentialsearch(arr2, n, x) << '\n';
}