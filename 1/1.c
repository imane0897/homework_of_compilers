#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ID "id"
#define NUM "num"
#define CH "ch"
#define STR "str"
#define KW_INT "kw_int"
#define KW_CHAR "kw_char"
#define KW_VOID "kw_void"
#define KW_IF "kw_if"
#define KW_ELSE "kw_else"
#define KW_SWITCH "kw_switch"
#define KW_CASE "kw_case"
#define KW_DEFAULT "kw_default"
#define KW_WHILE "kw_while"
#define KW_DO "kw_do"
#define KW_FOR "kw_for"
#define KW_BREAK "kw_break"
#define KW_CONTINUE "kw_continue"
#define KW_RETURN "kw_return"
#define ADD "add"
#define SUB "sub"
#define MUL "mul"
#define DIV "div"
#define MOD "mod"
#define INC "inc"
#define DEC "dec"
#define NOT "not"
#define AND "and"
#define OR "or"
#define ASSIGN "assign"
#define GT "gt"
#define GE "ge"
#define LT "lt"
#define LE "le"
#define EQU "equ"
#define NEQU "nequ"
#define COMMA "comma"
#define COLON "colon"
#define SIMCON "simcom"
#define LPAREN "lparen"
#define RPAREN "rparen"
#define LBRAC "lbrac"
#define RBRAC "rbrac"

char current[1];
char token[10];
char *text;
char *symbol;
char *reserver_list[50];
int cur_point;
int buffer_len = 0;

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

bool isSQuotation() {
    if (text[cur_point] == '\'') {
        return true;
    } else {
        return false;
    }
}

bool isDQuotation() {
    if (text[cur_point] == '"') {
        return true;
    } else {
        return false;
    }
}

bool isODigit() {
    if (text[cur_point] >= '0' && text[cur_point] <= '7') {
        return true;
    } else {
        return false;
    }
}

bool isHDigit() {
    if ((text[cur_point] >= '0' && text[cur_point] <= '9') || (text[cur_point] >= 'a' && text[cur_point] <= 'f') || (text[cur_point] >= 'A' && text[cur_point] <= 'F')) {
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

void reserver() {
    if (strcmp(token, "int") == 0) {
        symbol = KW_INT;
    } else if (strcmp(token, "char") == 0) {
        symbol = KW_CHAR;
    } else if (strcmp(token, "void") == 0) {
        symbol = KW_VOID;
    } else if (strcmp(token, "if") == 0) {
        symbol = KW_IF;
    } else if (strcmp(token, "else") == 0) {
        symbol = KW_ELSE;
    } else if (strcmp(token, "switch") == 0) {
        symbol = KW_SWITCH;
    } else if (strcmp(token, "case") == 0) {
        symbol = KW_CASE;
    } else if (strcmp(token, "default") == 0) {
        symbol = KW_DEFAULT;
    } else if (strcmp(token, "while") == 0) {
        symbol = KW_WHILE;
    } else if (strcmp(token, "do") == 0) {
        symbol = KW_DO;
    } else if (strcmp(token, "for") == 0) {
        symbol = KW_FOR;
    } else if (strcmp(token, "break") == 0) {
        symbol = KW_BREAK;
    } else if (strcmp(token, "continue") == 0) {
        symbol = KW_CONTINUE;
    } else if (strcmp(token, "return") == 0) {
        symbol = KW_RETURN;
    } else {
        symbol = "id";
    }
}

int transONum() {
    int num = 0;
    for (int i = 0; token[i] != '\0'; i++) {
        num = num * 8 + (token[i] - '0');
    }
    return num;
}

int transDNum() {
    int num = 0;
    for (int i = 0; token[i] != '\0'; i++) {
        num = num * 10 + (token[i] - '0');
    }
    return num;
}

int transHNum() {
    int num = 0;
    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] >= '0' && token[i] <= '9') {
            num = num * 16 + (token[i] - '0');
        } else if (token[i] >= 'a' && token[i] <= 'f') {
            num = num * 16 + (token[i] - 'a' + 10);
        } else if (token[i] >= 'A' && token[i] <= 'F') {
            num = num * 16 + (token[i] - 'A' + 10);
        }
    }
    return num;
}

void error() {
    printf("The current character %c cannot be recognized.\n", text[cur_point]);
}

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
        reserver();
        printf("%-10s\t:\t%s\n", symbol, token);
    } else if (isDigit()) {

        int num = 0;
        if (text[cur_point] == '0') {
            _getchar();
            if (text[cur_point] == 'x' || text[cur_point] == 'X') {
                _getchar();
                while (isHDigit()) {
                    catToken();
                    _getchar();
                }
                num = transHNum();
            } else {
                while (isODigit()) {
                    catToken();
                    _getchar();
                }
                num = transONum();
            }
        } else {
            while (isDigit()) {
                catToken();
                _getchar();
            }
            num = transDNum();
        }

        retract();
        symbol = NUM;
        printf("%-10s\t:\t%d\n", symbol, num);

    } else if (isDQuotation()) {

        _getchar();
        while (!isDQuotation()) {
            catToken();
            _getchar();
        }
        symbol = STR;
        printf("%-10s\t:\t%s\n", symbol, token);
    } else if (isSQuotation()) {

        _getchar();
        symbol = CH;
        printf("%-10s\t:\t%c\n", symbol, text[cur_point]);
        _getchar();
    } else if (isAdd()) {

        _getchar();
        if (isAdd()) {
            symbol = INC;
            printf("%-10s\t:\t%s\n", symbol, "++");
        } else {
            symbol = ADD;
            printf("%-10s\t:\t%c\n", symbol, '+');
            retract();
        }
    } else if (isSub()) {

        _getchar();
        if (isSub()) {
            symbol = DEC;
            printf("%-10s\t:\t%s\n", symbol, "--");
        } else {
            symbol = SUB;
            printf("%-10s\t:\t%c\n", symbol, '-');
            retract();
        }
    } else if (isAnd()) {

        _getchar();
        if (isAnd()) {
            symbol = AND;
            printf("%-10s\t:\t%s\n", symbol, "&&");
        } else {
            symbol = "d_and";
            printf("%-10s\t:\t%c\n", symbol, '&');
            retract();
        }
    } else if (isOr()) {

        _getchar();
        if (isOr()) {
            symbol = OR;
            printf("%-10s\t:\t%s\n", symbol, "||");
        } else {
            symbol = "d_or";
            printf("%-10s\t:\t%c\n", symbol, '|');
            retract();
        }
    } else if (isNot()) {

        _getchar();
        if (isAssign()) {
            symbol = NEQU;
            printf("%-10s\t:\t%s\n", symbol, "!=");
        } else {
            symbol = NOT;
            printf("%-10s\t:\t%c\n", symbol, '!');
            retract();
        }
    } else if (isGt()) {

        _getchar();
        if (isAssign()) {
            symbol = GE;
            printf("%-10s\t:\t%s\n", symbol, ">=");
        } else {
            symbol = GT;
            printf("%-10s\t:\t%c\n", symbol, '>');
            retract();
        }
    } else if (isLt()) {

        _getchar();
        if (isAssign()) {
            symbol = LE;
            printf("%-10s\t:\t%s\n", symbol, "<=");
        } else {
            symbol = LT;
            printf("%-10s\t:\t%c\n", symbol, '<');
            retract();
        }
    } else if (isAssign()) {

        _getchar();
        if (isAssign()) {
            symbol = EQU;
            printf("%-10s\t:\t%s\n", symbol, "==");
        } else {
            symbol = ASSIGN;
            printf("%-10s\t:\t%c\n", symbol, '=');
            retract();
        }
    } else if (isDiv()) {

        _getchar();
        if (isMul()) {                           // 处理/**/注释
            while (!isDiv()) {
                while (!isMul()) {
                    _getchar();
                }
                _getchar();
            }
        } else {
            symbol = DIV;
            printf("%-10s\t:\t%c\n", symbol, '/');
            retract();
        }
    } else if (isMul()) {
        symbol = MUL;
        printf("%-10s\t:\t%c\n", symbol, '*');
    } else if (isMod()) {
        symbol = MOD;
        printf("%-10s\t:\t%c\n", symbol, '%');
    } else if (isComma()) {
        symbol = COMMA;
        printf("%-10s\t:\t%c\n", symbol, ',');
    } else if (isColon()) {
        symbol = COLON;
        printf("%-10s\t:\t%c\n", symbol, ':');
    } else if (isSemicolon()) {
        symbol = SIMCON;
        printf("%-10s\t:\t%c\n", symbol, ';');
    } else if (isLparen()) {
        symbol = LPAREN;
        printf("%-10s\t:\t%c\n", symbol, '(');
    } else if (isRparen()) {
        symbol = RPAREN;
        printf("%-10s\t:\t%c\n", symbol, ')');
    } else if (isLbrace()) {
        symbol = LBRAC;
        printf("%-10s\t:\t%c\n", symbol, '{');
    } else if (isRbrace()) {
        symbol = RBRAC;
        printf("%-10s\t:\t%c\n", symbol, '}');
    } else {
        error();
    }

    return 0;
}

int main(void) {
    readIn();

    for (cur_point =0; text[cur_point] != '\0'; cur_point++) {
        getsym();
    }
    return 0;
}
