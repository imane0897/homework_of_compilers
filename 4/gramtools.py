from grammar import Grammar
from first_follow import *



def init_grammar(string):
    '''
    function takes in lines of the grammar rules as input
    returns a Grammar instance initialized with as per given grammar rules.
    '''
    G = Grammar()
    string = string.split('\n')
    #This loop reads every line for rules
    for line in string:
        line = line.split(" : ")
        #n_term is non terminal symbol for the rule in particular line
        n_term = line[0]
        #add the non terminal to the set of non-terminals in G
        G.add_V(n_term)
        #line contains list of possble right hand productions for the n_term
        line = line[1].split("|")
        #remove leading-trailing whitespaces
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

    # fr = first_set_elem(g)
    # g.set_first(fr)
    #
    # fl = follow_set(g)
    # g.set_follow(fl)

    return G





def get_grammar(string):

    g = init_grammar(string)

    fr = first_set_elem(g)
    g.set_first(fr)

    fl = follow_set(g)
    g.set_follow(fl)

    set_ll_first(g)

    return g