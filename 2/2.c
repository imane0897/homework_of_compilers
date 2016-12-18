#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

typedef char STATUS;
typedef int CONDITION;

typedef struct trans {
    STATUS origin;
    CONDITION condition;
    STATUS des;
} trans;

int n;          // number of status
int m;          // number of conditions
int k;          // number of acc
STATUS start;
STATUS *acc;

trans *read(FILE *src) {
    if (!src) return NULL;  // file read error
    trans *d = NULL;
    int dataset_size = 0;
    char ch;
    fscanf(src, "%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        if (dataset_size == i) {
            d = (trans *)realloc(d, m * sizeof(trans));
            if (!d) {
                fprintf(stderr, "memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
        // get data
        trans *current = d + i;
        fscanf(src, "%c", &ch);
        fscanf(src,"%c %d %c", &current->origin, &current->condition, &current->des);
    }
    fscanf(src, "%c", &ch);
    fscanf(src, "%c", &start);
    fscanf(src, "%c", &ch);
    fscanf(src, "%d", &k);
    acc = (STATUS *)realloc(acc, k*sizeof(STATUS));
    for (int j = 0; j < k; j++) {
        fscanf(src, "%c", &ch);
        fscanf(src, "%c", acc+j);
    }
    return d;
}

void trans_status(trans *d, STATUS origin, STATUS des) {
    for (int i = 0; i < m; i++) {
        if (d[i].origin == des) {
            d[i].origin = origin;
        } else if (d[i].des == des) {
            d[i].des = origin;
        }
    }
    for (int i = 0; i < k; i++) {
        if (acc[i] == des) {
            acc[i] = origin;
        }
    }
}

void rearrange(trans *d, int count){
    trans temp;
    for (int i = 0; i < m; i++) {
        if (d[i].condition == -1) {
            printf("current i is %d %d\n", i, d[i].condition);
            temp.origin = d[i].origin;
            temp.condition = d[i].condition;
            temp.des = d[i].des;
            for (int j = i+1; j < n; j++) {
                d[j-1].origin = d[j].origin;
                d[j-1].condition = d[j].condition;
                d[j-1].des = d[j].des;
            }
            d[n-1].origin = temp.origin;
            d[n-1].condition = temp.condition;
            d[n-1].des = temp.des;
        }
    }
    m -= count;
}

int cmp(const void *a, const void *b) {
    trans *aa = (trans *)a;
    trans *bb = (trans *)b;
    if(aa->origin == bb->origin) {
        if (aa->condition == bb->condition) {
            return aa->des > bb->des ? 1: -1;
        }
        return aa->condition > bb->condition ? 1: -1;
    }
    return aa->origin > bb->origin ? 1: -1;
}

void determine(trans *d) {
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (d[i].condition == -1) {
            trans_status(d, d[i].origin, d[i].des);
            count++;
        }
    }

    qsort(d, m, sizeof(d[0]), cmp);
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (d[i].origin == d[j].origin) {
                if (d[i].condition == d[j].condition) {
                    trans_status(d, d[i].des, d[j].des);
                }
            } else {
                break;
            }
        }
    }
}

int main(void) {
    FILE *automaton;
    automaton = fopen("./automaton", "r");

    trans *d = read(automaton);

    determine(d);
    for (int i = 0; i < m; i++) {
        printf("%c %d %c\n", d[i].origin, d[i].condition, d[i].des);
    }
    return 0;
}
