# from gramtools import *

def set_ll_first(g):
        '''Sets the ll_first set for the ll_grammer'''
        g.ll_first = {}
        for n_terms in g.variables:
            g.ll_first[n_terms] = {}
            for prod in g.productions[n_terms]:
                g.ll_first[n_terms][prod],_ = first_set_exp(g, prod, g.first)


def first_set_elem(G):
    '''
    Defines the first set for every non terminal and terminal
    returns {S: [...], A : [...], B : [...]}

    Algorithm:
    For every terminal in the grammar G, add it to firsts, key and value as terminal itself
    Then for every non terminal in G, add its first set to the dict firsts.
    do this by calling first_r(.,.,non terminal) which adds the n_term's first set to dict
    remove duplicates in the first set of every n_term
    '''
    firsts = {}

    def first_r(firsts, n_term):
        '''
        when called adds the first set of the n_term to the dict firsts
        '''
        if (n_term in firsts):
            if firsts[n_term] == "#":
                pass
            else:
                return None
            #exit since n_term already exists in the dictionary

        rules = G.productions[n_term]
        firsts[n_term] = []
        for prod in rules:
            elems = prod.split(" ")
            for i in elems:
                if i == '#':
                    if '#' not in firsts[n_term]:
                        firsts[n_term].extend('#')
                    break
                else:
                    first_r(firsts, i)
                    firsts[n_term].extend(firsts[i])
                    if i in G.terminals or '' not in G.productions[i]:
                        #if first non-term is nullable then we also have to include the next symbols first set
                        #but if it is not nullable then, break
                        break

    # x is a Terminal variable
    for t in G.terminals:
        firsts[t] = [t]

    # x produces '#' directly
    for p in G.productions:
        if '#' in G.productions[str(p)]:
            firsts[str(p)] = '#'

    # x is a Non-terminal variable
    for n_term in G.variables:
        # if (n_term not in firsts) or (firsts[n_term] == "#"):
        first_r(firsts, n_term)

    for i in firsts:
        firsts[i] = list(set(firsts[i]))
    return firsts


def first_set_exp(G, s, firsts):
    '''
    This function takes in Grammar and a string (RHS of a production) as its paramaters
    returns a list of first set for the particular RHS
    '''
    elems = s.split(" ")
    flag = False
    tup = []
    for i in elems:
        if i == '#':
            break
        tup.extend(firsts[i])
        if i in G.terminals or '' not in G.productions[i]:
            break
    if '#' in tup:
        tup.remove('#')
        flag = True
    return tup, flag


def follow_set(G):
    '''
    Takes in Grammar as paramater
    returns the follow  set for each non terminal in G.variables
    '''
    follows = {}
    # follows = collections.OrderedDict()
    #this is the dict which will contain the mappings for n_term to the corresponding follow set (viz a list)
    firsts = first_set_elem(G)
    #dict of first set
    g_prods = G.productions
    #production rules of the grammar
    def follow_r(G, n_term, follows):
        '''
        This is the recursive follow set function, pass the Grammar G, non terminal n_term (string) and  the follows set (dict) of the grammar
        if the follow set is already present in the follows dict, then this will just return
        else it will recursively find all the elements in the follow set for the given n_term, and updates follows
        '''
        #if n_term in follows.keys():#problem
            #return None
            #if n_term already exists in follows, nothing to update. end function.

        follows[n_term] = []
        #n_term does not exist in follows, create an entry for it and populate it.
        if n_term == G.start:
            follows[n_term] = ['$']

        for lhs in g_prods:
            #this for loop takes every non term in the lhs of G.productions, and runs the following operations on it.

            for rule in g_prods[lhs]:
                #for every production of the lhs (non terminal) in question
                symbols = rule.split(" ")
                if '#' in symbols:
                    break;
                #split the rhs of the production into list of individual symbols (non terminals and tokens)
                l = [i for i,x in enumerate(symbols) if x == n_term]
                #l is the list of indices where n_term appears in the production rule
                for pos in l:
                    if pos == len(symbols)-1:
                        #if n_term has appeared in the end of the production
                        if lhs not in follows.keys():
                            follow_r(G, lhs, follows)
                        follows[n_term].extend(follows[lhs])
                        #then the follow of lhs is subset of follow of n_term,
                        #before this we updated follows with follow set of lhs
                    else:
                        #lhs has occured somewhere in between the production
                        s = " ".join(symbols[pos+1:])
                        #get the part of the production which occurs after n_term
                        f, flag = first_set_exp(G, s, firsts)
                        #find the first set of that part of production
                        if '' in f:
                            #if lambda production exists
                            f.remove('')
                            follows[n_term].extend(f)
                            #then also add follow of lhs to follows of n_term
                            if lhs not in follows.keys():
                                follow_r(G, lhs, follows)
                            follows[n_term].extend(follows[lhs])
                        else:
                            #else just add the first set to the follows of n_term
                            follows[n_term].extend(f)
                        if flag:
                            follows[n_term].extend(follows[lhs])
        follows[n_term] = list(set(follows[n_term]))
        #remove any repeating symbols in the follow set of n_term


    for n_term in G.variables:
        follow_r(G, n_term, follows)

    return follows