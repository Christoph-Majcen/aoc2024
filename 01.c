#include <stdio.h>
#include <stdlib.h>

int comp (const void * elem1, const void * elem2) {
  return *(int*) elem1 - *(int*) elem2;
}

int main(void) {
  int list1[1000];
  int list2[1000];
  
  FILE* fd = fopen("input1.txt", "r");
  
  for(int i = 0; i < 1000; i++) {
    fscanf(fd, "%d   %d", &list1[i], &list2[i]);
  }
  fclose(fd);

  qsort(list1, 1000, sizeof(int), comp);  
  qsort(list2, 1000, sizeof(int), comp);

  int res1 = 0;

  for(int i = 0; i < 1000; i++) {
    int dif = list1[i] - list2[i];
    res1 += abs(dif);
  }

  printf("Result 1: %d\n", res1);
  
  int res2 = 0;

  for(int i = 0; i < 1000; i++) {
    for(int j = 0; j < 1000; j++) {
      if(list1[i] == list2[j]) {
        res2 += list1[i];
      }
    } 
  }


  printf("Result 2: %d\n", res2);
  
  return 0; 
}
