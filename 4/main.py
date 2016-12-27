#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from init_grammar import *
from select import *
from ll_parser import *


def get_parser(rules):
    '''
    init Grammar(V, T, S, P), set first_set and follow_set, set select_set
    :param rules: Grammar rules
    :return: select_set
    '''
    g = get_grammar(rules)
    par = parser(g)
    select_set = get_select(g)
    par.set_table(select_set)

    return par


if __name__ == '__main__':
    g = \
'''E : T E’
E’ : + T E’ | #
T : F T’
T’ : * F T’ | #
F : ( E ) | i'''
    p = get_parser(g)

    with open('/Users/AnYameng/Desktop/c/homework_of_compilers/4/4_1.txt', 'r') as f:
        l = f.readlines()
        for input in l:
            str = input
            input = input.strip().split(" ")
            result = p.parse(input)
            if result:
                # print(input)
                print(str.strip() + '\n\t\t\tis legal')
            else:
                # str = input + 'illegal'
                # print(str)
                # print(input)
                print(str.strip() + '\n\t\t\tis illegal')
