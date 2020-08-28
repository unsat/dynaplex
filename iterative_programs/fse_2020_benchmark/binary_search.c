#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int binary_search(int search, int array[], int n, int *counter) {
  int first = 0;
  int last = n - 1;
  int middle = (first + last) / 2;

  while (first <= last) {
    *counter = *counter + 1;
    if (array[middle] < search)
      first = middle + 1;
    else if (array[middle] > search)
      last = middle - 1;
    else if (array[middle] == search)
      return middle;
    middle = (first + last) / 2;
  }
  return -1;
}

int comparator(const void *p, const void *q)
  {
     return (*(int*)p-*(int*)q);
     }

int main() {
  int counter = 0;
  int num, term;
  time_t t;

  opendir("binary_search");
  if (ENOENT == errno) {
      mkdir("binary_search", 0777);
  }

  FILE *file;
  file = fopen("binary_search/traces", "a");
  srand((unsigned) time(&t));
  int j;
  for (size_t i = 0; i < 150; i++) {
    num = rand() % 1500;
    int arr[num];
    for (j = 0; j < num; j++) {
        arr[j] = rand()%100;
    }
    term = rand()%600;
    qsort((void*)arr, num, sizeof(arr[0]), comparator);
    term = binary_search(term, arr, num, &counter);
    fprintf(file, "%d;%d\n", num, counter);
    counter = 0;
  }
  fclose(file);
  return term;
}
