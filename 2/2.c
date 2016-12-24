#include <stdio.h>
#include <string.h>

#define STATES	256
#define SYMBOLS	20

int N_symbols;
int NFA_states;
char *NFAtab[STATES][SYMBOLS];

int DFA_states;	/* number of DFA states */
int DFAtab[STATES][SYMBOLS];

/*Print state-transition table.*/
void put_dfa_table(
                   int tab[][SYMBOLS],	/* DFA table */
                   int nstates,	/* number of states */
                   int nsymbols)	/* number of input symbols */
{
    int i, j;

    puts("STATE TRANSITION TABLE");

    /* input symbols: '0', '1', ... */
    printf("     | ");
    for (i = 0; i < nsymbols; i++) printf("  %c  ", '0'+i);

    printf("\n-----+--");
    for (i = 0; i < nsymbols; i++) printf("-----");
    printf("\n");

    for (i = 0; i < nstates; i++) {
        printf("  %c  | ", 'A'+i);	/* state */
        for (j = 0; j < nsymbols; j++)
            printf("  %c  ", 'A'+tab[i][j]);
        printf("\n");
    }
}

<<<<<<< HEAD
// 将字符ch插入到字符串结尾
void chr_append(char *s, char ch) {
    int n=strlen(s);

    *(s+n) = ch;
    *(s+n+1) = '\0';
}

void init_table() {
    // chr_append(NFAtab[0][0], '1');
    // chr_append(NFAtab[0][0], '2');
=======
/*Initialize NFA table.*/
void init_NFA_table()
{
    /*
>>>>>>> parent of c835f89... DFA+NFA
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

    NFA_states = 5;
    DFA_states = 0;
    N_symbols = 2;*/
    NFAtab[0][0] = "12";
    NFAtab[0][1] = "";
    NFAtab[0][2] = "";
    NFAtab[1][0] = "1";
    NFAtab[1][1] = "3";
    NFAtab[1][2] = "";
    NFAtab[2][0] = "";
    NFAtab[2][1] = "";
    NFAtab[2][2] = "23";
    NFAtab[3][0] = "";
    NFAtab[3][1] = "";
    NFAtab[3][2] = "";

    NFA_states = 4;
    DFA_states = 0;
    N_symbols = 3;
}

<<<<<<< HEAD
// 将字符串 t 按照字典序合并到字符串 s
void string_merge(char *s, char *t) {
=======
/*String 't' is merged into 's' in an alphabetical order.*/
void string_merge(char *s, char *t)
{
>>>>>>> parent of c835f89... DFA+NFA
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

/*Get next-state string for current-state string.*/
void get_next_state(char *nextstates, char *cur_states,
                    char *nfa[STATES][SYMBOLS], int n_nfa, int symbol)
{
    int i;
    char temp[STATES];

    temp[0] = '\0';
    for (i = 0; i < strlen(cur_states); i++)
        string_merge(temp, nfa[cur_states[i]-'0'][symbol]);
    strcpy(nextstates, temp);
}


int state_index(char *state, char statename[][STATES], int *pn)
{
    int i;

    if (!*state) return -1;	/* no next state */

    for (i = 0; i < *pn; i++)
        if (!strcmp(state, statename[i])) return i;

    strcpy(statename[i], state);	/* new state-name */
    return (*pn)++;
}

/*
	Convert NFA table to DFA table.
	Return value: number of DFA states.
 */
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

            nextstate[0] = '\0';
            for (int k = 0; k < strlen(statename[i]); k++)
                string_merge(nextstate, nfa[statename[i][k]-'0'][j]);

            dfa[i][j] = state_index(nextstate, statename, &n);
        }
    }

    return n;	/* number of DFA states */
}

<<<<<<< HEAD
// 对StateName[][]进行排序
void stnt_sort(char stnt[][STATES+1], int n) {
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
                      int i1,	// stnt[i][]中的i
                      int i2,	// newdfa[i][j]-'A'
                      int n,
                      int n_dfa) {
    char *old=stnt[i1], *vec=stnt[i2];
    int i, n2, flag=0;
    char newstates[STATES][STATES+1];

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

    stnt_sort(stnt, n2);

    return n2;	/* number of NEW states(equiv. classes) */
}

// 找到需要划分的状态集并对其进行划分
int set_new_equiv_class(char stnt[][STATES+1], int n,
                        int newdfa[][SYMBOLS], int n_sym, int n_dfa) {
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
void print_equiv_classes(char stnt[][STATES+1], int n) {
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

    int n;	// DFA 状态个数
    int n2;	// n + 需要划分的状态个数

    n = init_equiv_class(stnt, n_dfa, finals);

    while (1) {
        print_equiv_classes(stnt, n);
        n2 = get_optimized_DFA(stnt, n, dfa, n_sym, newdfa);
        if (n != n2)
            n = set_new_equiv_class(stnt, n, newdfa, n_sym, n_dfa);
        else break;
    }

    return n;
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
                    char *newfinals,
                    char *oldfinals,
                    char stnt[][STATES+1],
                    int n) {
    int i;

    for (i = 0; i < n; i++)
        if (is_subset(oldfinals, stnt[i])) *newfinals++ = i+'A';
    *newfinals++ = '\0';
}
/*
int isNFA() {

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
*/
int main() {
    init_table();

    // if (isNFA()) {
        N_DFA_states = nfa_to_dfa(NFAtab, N_symbols, DFAtab);
        print_table(DFAtab, N_DFA_states, N_symbols);
    // }

    N_optDFA_states = optimize_DFA(DFAtab, N_DFA_states,
                                   N_symbols, DFA_finals, StateName, OptDFA);
    get_NEW_finals(NEW_finals, DFA_finals, StateName, N_optDFA_states);

    print_table(OptDFA, N_optDFA_states, N_symbols);
    printf("Final states = %s\n", NEW_finals);

    return 0;
=======
int main()
{
    init_NFA_table();
    DFA_states = nfa_to_dfa(NFAtab, NFA_states, N_symbols, DFAtab);
    put_dfa_table(DFAtab, DFA_states, N_symbols);
>>>>>>> parent of c835f89... DFA+NFA
}
