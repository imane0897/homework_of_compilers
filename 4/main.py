from ll_parse_tools import *

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
            input = input.strip().split(" ")
            result = p.parse(input)

            if result:
                print('legal')
            else:
                print('illegal')