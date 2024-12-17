#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct line {
  int count;
  int* elements;
} line_t;

void parse_line(char* line, int* data, int* count) {
  char * token = strtok(line, " ");
  *data = atoi(token);
  data++;
  (*count)++;
  while((token = strtok(NULL, " ")) != NULL){
   *data = atoi(token);
   data++;
   (*count)++;
  }
}

int correct(int prev, int cur, int asc) {
  int dif = abs(prev - cur);
  return dif >= 1 && dif <= 3 && ((prev > cur && !asc) || (prev < cur && asc));
}

int validate_line(int* line, int count){
  if(count < 2) {
    return -1;
  }

  int asc = line[0] < line[1];
  
  for (int i = 0; i < count-1; i++){
    if(!correct(line[i], line[i+1], asc)) {
      return i;    
    }
  }
  return -1;
}

void remove_at(int * line, int count, int pos) {
  for(int i = pos; i < count-1; i++) {
    line[i] = line[i+1];
  }
}

int main(void) {
  FILE* fd = fopen("input2.txt", "r");
  char* lineptr = NULL; 
  size_t len = 0;
  ssize_t read;
  int result1 = 0;
  int result2 = 0;


  while((read = getline(&lineptr, &len, fd)) != -1) {    
    int parsed_line[MAX_LINE_LENGTH];
    int token_count = 0;
    parse_line(lineptr, parsed_line, &token_count);

    int orig_error_pos = validate_line(parsed_line, token_count);
    if(orig_error_pos < 0) {
      result1++;
      result2++;
      continue;
    }
    if(orig_error_pos >= token_count - 2) {
      result2++;
      continue;
    }

    int removed[MAX_LINE_LENGTH];
    int new_error_pos = 0;
    
    memcpy(removed, parsed_line, token_count*sizeof(int));
    remove_at(removed, token_count, orig_error_pos);
    new_error_pos = validate_line(removed, token_count-1);
    if(new_error_pos < 0) {
      result2++;
      continue;
    }

    memcpy(removed, parsed_line, token_count*sizeof(int));
    remove_at(removed, token_count, orig_error_pos + 1);
    new_error_pos = validate_line(removed, token_count-1);
    if(new_error_pos < 0) {
      result2++;
    }

    if(orig_error_pos == 1) {
      memcpy(removed, parsed_line, token_count*sizeof(int));
      remove_at(removed, token_count, 0);
      new_error_pos = validate_line(removed, token_count-1);
      if(new_error_pos < 0) {
        result2++;
      }
    }
  }

  printf("Result1: %d\n", result1);
  printf("Result2: %d\n", result2);


  free(lineptr);
  fclose(fd);
  
  return 0; 
}
