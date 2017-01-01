#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import collections
from pre_disposal import *

global symbol
global sym
global i
global flag


def nextsym():
    global i
    global sym
    if i < len(symbol)-1:
        i += 1
        sym = symbol[i]
    else:
        sym = '#'

def error():
    global flag
    flag = 0

def F():
    if sym == '(':
        nextsym()
        if E():
            if sym == ')':
                pass
            else:
                error()
                return False
        else:
            error()
            return False
    elif sym == 'i':
        pass
    else:
        error()
        return False
    nextsym()
    return True

def E():
    if T():
        if _E():
            return True
        else:
            error()
            return False
    else:
        error()
        return False
    return True

def _E():
    if sym == '+':
        nextsym()
        if T():
            if _E():
                return True
            else:
                error()
                return False
        else:
            error()
            return False
    else:
        return True

def T():
    if F():
        if _T():
            return True
        else:
            error()
            return False
    else:
        error()
        return False

def _T():
    if sym == '*':
        nextsym()
        if F():
            if _T():
                return True
            else:
                error()
                return False
        else:
            error()
            return False
    else:
        return True

if __name__=='__main__':
    g = \
'''E : E + T | T
T : T * F | F
F : ( E ) | i'''

    dic = collections.OrderedDict()
    left_disposal(dic)
    # print_forms(dic)
    print('')

    # get_grammar(g)

    with open('3_2.txt', 'r') as f2:
        l = f2.readlines()

        for test_string in l:
            symbol = list(test_string.strip())
            i = -1
            flag = 1
            nextsym()

            while (sym != '#') and (flag == 1):
                if (sym == 'i') or (sym == '(') or (sym ==')'):
                    F()
                    continue
                elif sym == '*':
                    _T()
                    continue
                elif sym == '+':
                    _E()
                    continue
                else:
                    flag = 0
                    break

            if flag == 1:
                print(str(test_string.strip()) + '\t:\t legal')
            else:
                print(str(test_string.strip()) + '\t:\t illegal')
