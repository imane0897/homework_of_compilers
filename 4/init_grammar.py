from grammar import Grammar
from first_follow import *
from pre_disposal import *


def init_grammar(string):
    '''
    returns a Grammar instance initialized with as per given grammar rules.
    :param string: Grammar rules
    :return: Grammar instance with V, T, S, P only
    '''
    G = Grammar()
    string = string.split('\n')

    for line in string:
        line = line.split(" : ")
        n_term = line[0]

        G.add_V(n_term)

        line = line[1].split("|")

        line = map(str.strip, line)
        for p in line:
        #for each possible production of n_term
            #add the production to the grammar
            G.add_P(n_term, p)
            p = p.split(" ")

            for t in p:
            #for every term in the production
            #if term is not a non termianl, add it to the set of terminals for G
                if t not in G.variables and t != '#':
                    G.add_T(t)

            #above does not ensure that all added term is not a non terminal,
            #so this func below will ensure correctness
        for i in G.variables:
            if i in G.terminals:
                G.terminals.remove(i)
        G.start = G.variables[0]

    # G.productions = left_disposal(G.productions)
    return G


def get_grammar(string):
    '''
    set a grammar instance with given rules and set its first_set and follow_set
    :param string: Grammar rules
    :return: Grammar instance (V, T, S, P, first_set, follow_set)
    '''
    g = init_grammar(string)
    print(g)
    fr = first_set_elem(g)
    g.set_first(fr)

    fl = follow_set(g)
    g.set_follow(fl)

    set_ll_first(g)

    print(g)
    return g


if __name__ == '__main__':
    g = \
'''E : TE'
E': + T E' | #
T : F T'
T' : * F T' | #
F : ( E ) | i'''
    p = get_grammar(g)