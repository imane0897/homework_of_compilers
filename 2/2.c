#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

typedef int STATUS;
typedef char CONDITION;

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
        fscanf(src,"%d%c%d", &current->origin, &current->condition, &current->des);
    }

    fscanf(src, "%d", &k);
    acc = (STATUS *)realloc(acc, k*sizeof(STATUS));
    for (int j = 0; j < k; j++) {
        fscanf(src, "%d", acc+j);
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
        if (d[i].condition == '#') {
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

int isNFA(trans *d) {

    qsort(d, m, sizeof(d[0]), cmp);
    for (int i = 0; i < m; i++) {
        if (d[i].condition == '#') {
            return 1;
        }
        for (int j = i + 1; j < m; j++) {
            if (d[i].origin == d[j].origin) {
                if (d[i].condition == d[j].condition) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool isAcc(STATUS statu) {
    for (int i = 0; i < k; i++) {
        if (acc[i] == statu) {
            return true;
        }
    }
    return false;
}

void minimize(trans *d) {

}

int main(void) {
    FILE *automaton;
    automaton = fopen("./automaton", "r");

    trans *d = read(automaton);

    if (isNFA(d)) {
        determine(d);
    }

    minimize(d);
    for (int i = 0; i < m; i++) {
        printf("%d %c %d\n", d[i].origin, d[i].condition, d[i].des);
    }
    return 0;
}
