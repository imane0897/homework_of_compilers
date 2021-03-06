#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATES	256
#define SYMBOLS	20

int N_symbols;
int N_NFA_states;
char *NFAtab[STATES][SYMBOLS];

int N_DFA_states;	/* number of DFA states */
int DFAtab[STATES][SYMBOLS];
char *DFA_finals;	/* final-state string */

char StateName[STATES][STATES+1];

int N_optDFA_states;
int OptDFA[STATES][SYMBOLS];
char NEW_finals[STATES+1];

typedef struct trans {
    char origin;
    char condition;
    char des;
} trans;

trans *read(FILE *src) {
    if (!src) return NULL;  // file read error
    trans *d = NULL;
    int dataset_size = 0;
    int N_forms, i, j, k;

    fscanf(src, "%d %d %d", &N_DFA_states, &N_symbols, &N_forms);
    for (i = 0; i < N_forms; i++) {
        if (dataset_size == i) {
            d = (trans *)realloc(d, N_forms * sizeof(trans));
            if (!d) {
                fprintf(stderr, "memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
        // get data
        trans *current = d + i;
        fscanf(src,"%c%c%c", &current->origin, &current->condition, &current->des);
    }
    fscanf(src, "%d", &k);
    DFA_finals = (char *)realloc(DFA_finals, k*sizeof(char));
    for (j = 0; j < k; j++) {
        fscanf(src, "%c", DFA_finals+j);
    }
    return d;
}

void init_NFA_table() {
    NFAtab[0][0] = "12";
    NFAtab[0][1] = "13";
    NFAtab[1][0] = "12";
    NFAtab[1][1] = "13";
    NFAtab[2][0] = "4";
    NFAtab[2][1] = "";
    NFAtab[3][0] = "";
    NFAtab[3][1] = "4";
    NFAtab[4][0] = "4";
    NFAtab[4][1] = "4";

    N_NFA_states = 5;
    N_DFA_states = 0;
    N_symbols = 2;
    DFA_finals = "E";
}

void print_table(
                 int tab[][SYMBOLS],
                 int nstates,
                 int nsymbols) {
    int i, j;

    printf("     | ");
    for (i = 0; i < nsymbols; i++) printf("  %c  ", '0'+i);

    printf("\n-----+--");
    for (i = 0; i < nsymbols; i++) printf("-----");
    printf("\n");

    for (i = 0; i < nstates; i++) {
        printf("  %c  | ", 'A'+i);	/* state */
        for (j = 0; j < nsymbols; j++)
            printf("  %c  ", tab[i][j]);
        printf("\n");
    }
}

// 字符串 t 按照字典序合并到字符串 s
void string_merge(char *s, char *t) {
    char temp[STATES], *r=temp, *p=s;

    while (*p && *t) {
        if (*p == *t) {
            *r++ = *p++; t++;
        } else if (*p < *t) {
            *r++ = *p++;
        } else
            *r++ = *t++;
    }
    *r = '\0';

    if (*p) strcat(r, p);
    else if (*t) strcat(r, t);

    strcpy(s, temp);
}

// 找到当前 NFA 状态可到达的全部状态
void get_next_nfa_state(char *nextstates, char *cur_states,
                        char *nfa[STATES][SYMBOLS], int symbol)
{
    int i;
    char temp[STATES];

    temp[0] = '\0';
    for (i = 0; i < strlen(cur_states); i++)
        string_merge(temp, nfa[cur_states[i]-'0'][symbol]);
    strcpy(nextstates, temp);
}

// NFA 转 DFA。返回值为 DFA 的状态个数
int nfa_state_index(char *state, char statename[][STATES], int *pn)
{
    int i;

    if (!*state) return -1;	/* no next state */

    for (i = 0; i < *pn; i++)
        if (!strcmp(state, statename[i])) return i;

    strcpy(statename[i], state);	/* new state-name */
    return (*pn)++;
}

// NFA 转 DFA。返回值为 DFA 的状态个数
int nfa_to_dfa(char *nfa[STATES][SYMBOLS], int n_nfa,
               int n_sym, int dfa[][SYMBOLS])
{
    char statename[STATES][STATES];
    int i = 0;	/* current index of DFA */
    int n = 1;	/* number of DFA states */

    char nextstate[STATES];
    int j;

    strcpy(statename[0], "0");	/* start state */

    for (i = 0; i < n; i++) {	/* for each DFA state */
        for (j = 0; j < n_sym; j++) {	/* for each input symbol */
            get_next_nfa_state(nextstate, statename[i], nfa, j);
            dfa[i][j] = nfa_state_index(nextstate, statename, &n) + 'A';
        }
    }

    return n;	/* number of DFA states */
}

// 找到当前 DFA 状态可到达的全部状态
void get_next_dfa_state(char *nextstates, char *cur_states,
                        int dfa[STATES][SYMBOLS], int symbol)
{
    int i;

    for (i = 0; i < strlen(cur_states); i++)
        *nextstates++ = dfa[cur_states[i]-'A'][symbol];
    *nextstates = '\0';
}

// 找到当前状态的等价状态集，返回值为状态集的索引号或-1
char equiv_class_ndx(char ch, char stnt[][STATES+1], int n)
{
    int i;

    for (i = 0; i < n; i++)
        if (strchr(stnt[i], ch)) return i+'0';
    return -1;	/* next state is NOT defined */
}

// 判断nextstates是不是同一状态，是则返回该状态，否则返回0
char is_one_nextstate(char *s)
{
    char equiv_class;	/* first equiv. class */

    while (*s == '@') s++;
    equiv_class = *s++;	/* index of equiv. class */

    while (*s) {
        if (*s != '@' && *s != equiv_class) return 0;
        s++;
    }

    return equiv_class;	/* next state: char type */
}

// 如果下一状态集是同一状态，返回其索引号，否则建立一个新的状态集
int dfa_state_index(char *state, char stnt[][STATES+1], int n, int *pn,
                    int cur)	/* 'cur' is added only for 'printf()' */
{
    int i;
    char state_flags[STATES+1];	/* next state info. */

    if (!*state) return -1;	/* no next state */

    for (i = 0; i < strlen(state); i++)
        state_flags[i] = equiv_class_ndx(state[i], stnt, n);
    state_flags[i] = '\0';

    printf("   %d:[%s]\t--> [%s] (%s)\n",
           cur, stnt[cur], state, state_flags);

    if ((i=is_one_nextstate(state_flags)))
        return i-'0';	/* deterministic next states */
    else {
        strcpy(stnt[*pn], state_flags);	/* state-division info */
        return (*pn)++;
    }
}

// 将状态划分为 1终结状态 + 0非终结状态
int init_equiv_class(char statename[][STATES+1], int n, char *finals)
{
    int i, j;

    if (strlen(finals) == n) {	/* all states are final states */
        strcpy(statename[0], finals);
        return 1;
    }

    strcpy(statename[1], finals);	/* final state group */

    for (i=j=0; i < n; i++) {
        if (i == *finals-'A') {
            finals++;
        } else statename[0][j++] = i+'A';
    }
    statename[0][j] = '\0';

    return 2;
}

// 根据nextstates对状态集进行划分
int get_optimized_DFA(char stnt[][STATES+1], int n,
                      int dfa[][SYMBOLS], int n_sym, int newdfa[][SYMBOLS])
{
    int n2=n;		/* 'n' + <num. of state-division info> */
    int i, j;
    char nextstate[STATES+1];

    for (i = 0; i < n; i++) {	/* for each pseudo-DFA state */
        for (j = 0; j < n_sym; j++) {	/* for each input symbol */
            get_next_dfa_state(nextstate, stnt[i], dfa, j);
            newdfa[i][j] = dfa_state_index(nextstate, stnt, n, &n2, i)+'A';
        }
    }

    return n2;
}

// 将字符ch插入到字符串结尾
void chr_append(char *s, char ch)
{
    int n=strlen(s);

    *(s+n) = ch;
    *(s+n+1) = '\0';
}

// 对StateName[][]进行排序
void sort(char stnt[][STATES+1], int n)
{
    int i, j;
    char temp[STATES+1];

    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (stnt[i][0] > stnt[j][0]) {
                strcpy(temp, stnt[i]);
                strcpy(stnt[i], stnt[j]);
                strcpy(stnt[j], temp);
            }
}

// 划分状态集。更新状态集数量
int split_equiv_class(char stnt[][STATES+1],
                      int i1,	/* index of 'i1'-th equiv. class */
                      int i2,	/* index of equiv. vector for 'i1'-th class */
                      int n,	/* number of entries in 'stnt' */
                      int n_dfa)	/* number of source DFA entries */
{
    char *old=stnt[i1], *vec=stnt[i2];
    int i, n2, flag=0;
    char newstates[STATES][STATES+1];	/* max. 'n' subclasses */

    for (i=0; i < STATES; i++) newstates[i][0] = '\0';

    for (i=0; vec[i]; i++)
        chr_append(newstates[vec[i]-'0'], old[i]);

    for (i=0, n2=n; i < n_dfa; i++) {
        if (newstates[i][0]) {
            if (!flag) {	/* stnt[i1] = s1 */
                strcpy(stnt[i1], newstates[i]);
                flag = 1;	/* overwrite parent class */
            } else	/* newstate is appended in 'stnt' */
                strcpy(stnt[n2++], newstates[i]);
        }
    }

    sort(stnt, n2);	/* sort equiv. classes */

    return n2;	/* number of NEW states(equiv. classes) */
}

// 找到需要划分的状态集并对其进行划分
int set_new_equiv_class(char stnt[][STATES+1], int n,
                        int newdfa[][SYMBOLS], int n_sym, int n_dfa)
{
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n_sym; j++) {
            k = newdfa[i][j]-'A';	/* index of equiv. vector */
            if (k >= n)	/* equiv. class 'i' should be segmented */
                return split_equiv_class(stnt, i, k, n, n_dfa);
        }
    }

    return n;
}

// 打印当前等价状态
void print_equiv_classes(char stnt[][STATES+1], int n)
{
    int i;

    printf("\nEQUIV. CLASS CANDIDATE ==>");
    for (i = 0; i < n; i++)
        printf(" %d:[%s]", i, stnt[i]);
    printf("\n");
}

// DFA 的确定化
int optimize_DFA(
                 int dfa[][SYMBOLS],
                 int n_dfa,
                 int n_sym,
                 char *finals,
                 char stnt[][STATES+1],
                 int newdfa[][SYMBOLS]) {

    int n;	/* number of new DFA states */
    int n2;	/* 'n' + <num. of state-dividing info> */

    n = init_equiv_class(stnt, n_dfa, finals);

    while (1) {
        print_equiv_classes(stnt, n);
        n2 = get_optimized_DFA(stnt, n, dfa, n_sym, newdfa);
        if (n != n2)
            n = set_new_equiv_class(stnt, n, newdfa, n_sym, n_dfa);
        else break;	/* equiv. class segmentation ended!!! */
    }

    return n;	/* number of DFA states */
}

// 判断t是不是s的子集
int is_subset(char *s, char *t) {
    int i;

    for (i = 0; *t; i++)
        if (!strchr(s, *t++)) return 0;
    return 1;
}

// DFA确定化之后的新的终结状态
void get_NEW_finals(
                    char *newfinals,	/* new DFA finals */
                    char *oldfinals,	/* source DFA finals */
                    char stnt[][STATES+1],	/* state name table */
                    int n) {
    int i;

    for (i = 0; i < n; i++)
        if (is_subset(oldfinals, stnt[i])) *newfinals++ = i+'A';
    *newfinals++ = '\0';
}

int main() {

    init_NFA_table();
    N_DFA_states = nfa_to_dfa(NFAtab, N_NFA_states, N_symbols, DFAtab);
    print_table(DFAtab, N_DFA_states, N_symbols);

    N_optDFA_states = optimize_DFA(DFAtab, N_DFA_states,
                                   N_symbols, DFA_finals, StateName, OptDFA);
    get_NEW_finals(NEW_finals, DFA_finals, StateName, N_optDFA_states);

    print_table(OptDFA, N_optDFA_states, N_symbols);
    printf("Final states = %s\n", NEW_finals);

    return 0;
}
