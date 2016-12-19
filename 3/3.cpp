#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cctype>
#include <map>
#include <set>
#define MAX 100

using namespace std;

class parser {
public:
    string left;
    set<string> right;
    parser (const string& temp) {
        left = temp;
        right.clear();
    }
    void print () {
        printf ("%s::=", left.c_str() );
        set<string>::iterator it = right.begin();
        printf ( "%s", it->c_str());
        it++;
        for ( ; it!= right.end() ; it++ )
            printf ( "|%s" , it->c_str() );
        puts("");
    }
    void insert ( const string& temp )
    {
        right.insert(temp);
    }
};

map<string, size_t> dic;
vector<parser> form;
bool used[MAX];

void remove() {
    for (size_t i = 0; i < form.size(); i++) {
        bool flag = true;
        char ch = form[i].left[0];
        // set<string> temp = form[i].right;
        set<string>::iterator it;
        string ff = form[i].left.substr(0,1)+"\'";

        for (it = form[i].right.begin(); it != form[i].right.end(); it++) {
            if (it->at(0) == ch) {
                form.push_back(parser(ff));
                dic[ff] = form.size();
                flag = false;
                break;
            }
        }
        if (flag) continue;

        vector<string> cont;
        set<string>& ss = form[dic[ff]-1].right;
        ss.insert ("#");
        std::cout << dic[form[i].left] << '\n';
        /*
        while (!form[i].right.empty()) {
            if (form[i].right.begin()->at(0) == ch) {
                ss.insert(form[i].right.begin()->substr(1)+ff);

            }
            else {
                cont.push_back(form[i].right.begin()->substr(0)+ff);
            }
            form[i].right.erase(form[i].right.begin());
        }
        for (size_t i = 0; i < cont.size(); i++) {
            form[i].right.insert(cont[i]);
        }
        */
    }
}

void print() {
    for (size_t i = 0; i < form.size(); i++)
        form[i].print();
    puts("");
}

int main() {
    dic.clear();
    form.clear();

    // 产生式的数量
    int n;
    cin >> n;

    // 输入产生式
    size_t i;
    char buf[MAX];
    while (n--) {
        cin >> buf;
        for (i = 0; i < strlen(buf); i++)
            if (buf[i] == ':'){
                buf[i] = '\0';
                break;
            }
        string left = buf;
        if (!dic[left]) {
            form.push_back(parser(left));
            dic[left] = form.size();
        }
        string right = buf+i+3;
        form[dic[left]-1].insert(right);
    }
    //remove();
    print();
    for (size_t i = 0; i < n; i++) {
        std::cout << dic[form[i].left] << '\n';
    }
    return 0;
}
