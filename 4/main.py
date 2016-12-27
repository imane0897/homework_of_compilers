from select import *
from init_grammar import *

def get_parser(rules):
    '''
    init Grammar(V, T, S, P), set first_set and follow_set, set select_set
    :param rules: Grammar rules
    :return: select_set
    '''
    g = get_grammar(rules)
    par = ll_parser.parser(g)
    par.set_table(set_select(g))

    return par


if __name__ == '__main__':
    g = \
'''E : E + T | T
T : T * F | F
F : ( E ) | i'''
    p = get_parser(g)

    with open('/Users/AnYameng/Desktop/c/homework_of_compilers/4/4_1.txt', 'r') as f:
        l = f.readlines()
        for input in l:
            input = input.strip().split(" ")
            result = p.parse(input)

            if result:
                print('legal')
            else:
                print('illegal')
