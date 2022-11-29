#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N (9)
#define M (153)
   
char** wordidx;
char word[N];
int count[M];
int line;
int idx;

int isPrime(int n) {

  int i, flag = 0;

  if (n == 0 || n == 1)
    flag = 1;

  for (i = 2; i <= n / 2; ++i) {

    if (n % i == 0) {
      flag = 1;
      break;
    }
  }

  if (flag == 0)
    return 1;
  else
    return 0;
}

int main() {     
    wordidx = calloc(M, sizeof(char*));
    for(int i = 0; i < M; i++) {
        wordidx[i] = calloc(N, sizeof(char));
        count[i] = 0;
    }
    line = 0;
    idx = 0;

    while(scanf("%s\n", word) != EOF) {
        for(int i = 0; i < idx + 1; i++) {
            if(strcmp(wordidx[i], word) == 0) {
                break;
            } else {
                strcpy(wordidx[idx], word);
                idx++;
                break;
            }
        }
        line++;

        for(int m = 0; m < line; m++) {
            if(isPrime(line)){
                if(strcmp(wordidx[m], word) == 0){
                    printf("trying to delete %s: " , word);
                    if(count[m] == 0) {
                        printf("not found\n");
                    } else {
                        printf("deleted\n");
                        count[m] = 0;
                    }
                    break;
                }
            }
            else {
                if(strcmp(wordidx[m], word) == 0){
                    if(count[m] == 0) {
                        count[m] += 1;
                        printf("added %s\n", word);
                    } else {
                        count[m] += 1;
                        printf("counted %s\n", word);
                    }
                    break;
                }
            }
        }
    }

    idx = 0;
    for(int i = 0; i < 3; i++){
        if(count[i] > count[idx]){
            idx = i;
        }
    }
    printf("result: %s %d\n", wordidx[idx], count[idx]);

    for(int i = 0; i < M; i++) {
        free(wordidx[i]);
    }
    free(wordidx);
    return 0;
}
