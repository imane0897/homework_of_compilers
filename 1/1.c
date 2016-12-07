#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char current[1];
char token[10];
char *text;
char *reserver_list[50];
int cur_point;
int buffer_len = 0;

void initReserverList() {
    reserver_list[0] = "const";
    reserver_list[1] = "int";
    reserver_list[2] = "char";
    reserver_list[3] = "void";
    reserver_list[4] = "if";
    reserver_list[5] = "else";
    reserver_list[6] = "switch";
    reserver_list[7] = "case";
    reserver_list[8] = "default";
    reserver_list[9] = "while";
    reserver_list[10] = "do";
    reserver_list[11] = "for";
    reserver_list[12] = "break";
    reserver_list[13] = "continue";
    reserver_list[14] = "return";
}

void clearToken() {
    strcpy(token, "\0");
}

bool isSpace() {
    if (text[cur_point] == ' ') {
        return true;
    } else {
        return false;
    }
}

bool isNewline() {
    if (text[cur_point] == '\n') {
        return true;
    } else {
        return false;
    }
}

bool isTab() {
    if (text[cur_point] == '\t') {
        return true;
    } else {
        return false;
    }
}

bool isLetter() {
    if (text[cur_point] >= 'a' && text[cur_point] <= 'z') {
        return true;
    } else {
        return false;
    }
}

bool isDigit() {
    if (text[cur_point] >= '0' && text[cur_point] <= '9') {
        return true;
    } else {
        return false;
    }
}

bool isColon() {
    if (text[cur_point] == ':') {
        return true;
    } else {
        return false;
    }
}

bool isComma() {
    if (text[cur_point] == ',') {
        return true;
    } else {
        return false;
    }
}

bool isSemicolon() {
    if (text[cur_point] == ';') {
        return true;
    } else {
        return false;
    }
}

bool isLparen() {
    if (text[cur_point] == '(') {
        return true;
    } else {
        return false;
    }
}

bool isRparen() {
    if (text[cur_point] == ')') {
        return true;
    } else {
        return false;
    }
}

bool isAssign() {
    if (text[cur_point] == '=') {
        return true;
    } else {
        return false;
    }
}

bool isAdd() {
    if (text[cur_point] == '+') {
        return true;
    } else {
        return false;
    }
}

bool isSub() {
    if (text[cur_point] == '-') {
        return true;
    } else {
        return false;
    }
}

bool isMul() {
    if (text[cur_point] == '*') {
        return true;
    } else {
        return false;
    }
}

bool isDiv() {
    if (text[cur_point] == '/') {
        return true;
    } else {
        return false;
    }
}

bool isMod() {
    if (text[cur_point] == '<') {
        return true;
    } else {
        return false;
    }
}

bool isNot() {
    if (text[cur_point] == '!') {
        return true;
    } else {
        return false;
    }
}

bool isGt() {
    if (text[cur_point] == '>') {
        return true;
    } else {
        return false;
    }
}

bool isLt() {
    if (text[cur_point] == '<') {
        return true;
    } else {
        return false;
    }
}

bool isAnd() {
    if (text[cur_point] == '&') {
        return true;
    } else {
        return false;
    }
}

bool isOr() {
    if (text[cur_point] == '|') {
        return true;
    } else {
        return false;
    }
}

bool isLbrace() {
    if (text[cur_point] == '{') {
        return true;
    } else {
        return false;
    }
}

bool isRbrace() {
    if (text[cur_point] == '}') {
        return true;
    } else {
        return false;
    }
}

void _getchar() {
    if (cur_point < buffer_len) {
        cur_point++;
    } else {
        printf("Getchar Error.\n");
    }
}

void readIn() {
    int buffer_size = 0;
    char cur;

    while ((cur = getchar()) != EOF) {
        if (buffer_len == buffer_size) {
            text = (char*)realloc(text, buffer_size += 16);
        }
        text[buffer_len++] = cur;
    }

    if (buffer_len == buffer_size) {
        text = (char*)realloc(text, buffer_size += 16);
    }
    text[--buffer_len] = '\0';
}

void catToken() {
    current[0] = text[cur_point];
    strcat(token, current);
}

void retract() {
    if (cur_point >= 0) {
        cur_point--;
    } else {
        printf("Retract Error.\n");
    }
}

int reserver() {
    for (size_t i = 0; i < 15; i++) {
        if (strcmp(token, reserver_list[i])) {
            return 0;
        }
    }
    return 1;
}

int transNum() {
    int num = 0;
    for (int i = 0; token[i] != '\0'; i++) {
        num = num * 10 + (token[i] - '0');
    }
    return num;
}

void error() {
    printf("The current character %c cannot be recognized.\n", text[cur_point]);
}

/*---------------------------------------
    0 - 关键字和保留字
    1 - 常量（数字，字符，字符串）
    2 - 单目运算符
    3 - 双目运算符
    4 - 分解符
---------------------------------------*/

int getsym() {

    clearToken();

    while (isSpace() || isNewline() || isTab()) {
        _getchar();            // 读取字符，跳过空格、换行和Tab
    }

    if (isLetter()) {

        while (isLetter()) {   // 将字符拼接成字符串
            catToken();
            _getchar();
        }
        retract();
        printf("%d\t:\t%s\n", reserver(), token);
    } else if (isDigit()) {

        while (isDigit()) {
            catToken();
            _getchar();
        }
        retract();
        int num = transNum();            // 把token中的字符串换成整数
        printf("1\t:\t%d\n", num);

    } else if (isAdd()) {

        _getchar();
        if (isAdd()) {
            printf("3\t:\t%s\n", "++");
        } else {
            printf("2\t:\t%c\n", '+');
            retract();
        }
    } else if (isSub()) {

        _getchar();
        if (isSub()) {
            printf("3\t:\t%s\n", "--");
        } else {
            printf("2\t:\t%c\n", '-');
            retract();
        }
    } else if (isAnd()) {

        _getchar();
        if (isAnd()) {
            printf("3\t:\t%s\n", "&&");
        } else {
            printf("2\t:\t%c\n", '&');
            retract();
        }
    } else if (isOr()) {

        _getchar();
        if (isOr()) {
            printf("3\t:\t%s\n", "||");
        } else {
            printf("2\t:\t%c\n", '|');
            retract();
        }
    } else if (isNot()) {

        _getchar();
        if (isAssign()) {
            printf("3\t:\t%s\n", "!=");
        } else {
            printf("2\t:\t%c\n", '!');
            retract();
        }
    } else if (isGt()) {

        _getchar();
        if (isAssign()) {
            printf("3\t:\t%s\n", ">=");
        } else {
            printf("2\t:\t%c\n", '>');
            retract();
        }
    } else if (isLt()) {

        _getchar();
        if (isAssign()) {
            printf("3\t:\t%s\n", "<=");
        } else {
            printf("2\t:\t%c\n", '<');
            retract();
        }
    } else if (isAssign()) {

        _getchar();
        if (isAssign()) {
            printf("3\t:\t%s\n", "==");
        } else {
            printf("2\t:\t%c\n", '=');
            retract();
        }
    } else if (isDiv()) {

        _getchar();
        if (isDiv()) {
            printf("3\t:\t%s\n", "//");
        } else {
            printf("2\t:\t%c\n", '/');
            retract();
        }
    } else if (isMul()) {
        printf("2\t:\t%c\n", '*');
    } else if (isMod()) {
        printf("2\t:\t%c\n", '%');
    } else if (isComma()) {
        printf("4\t:\t%c\n", ',');
    } else if (isColon()) {
        printf("4\t:\t%c\n", ':');
    } else if (isSemicolon()) {
        printf("4\t:\t%c\n", ';');
    } else if (isLparen()) {
        printf("4\t:\t%c\n", '(');
    } else if (isRparen()) {
        printf("4\t:\t%c\n", ')');
    } else if (isLbrace()) {
        printf("4\t:\t%c\n", '{');
    } else if (isRbrace()) {
        printf("4\t:\t%c\n", '}');
    } else {
        error();
    }

    return 0;
}

int main(void) {
    initReserverList();
    readIn();
    
    for (cur_point =0; text[cur_point] != '\0'; cur_point++) {
        getsym();
    }
    return 0;
}
