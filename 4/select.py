from ll_parser import *

def set_select(ll_g):
    '''
    returns the ll_parsing table, given the ll_grammar as param
    :param ll_g: LL(1) Grammar instance
    :return: select_set
    '''
    select = {}
    prods = ll_g.ll_first
    #filling in the table with first sets
    for n_term in prods:
        select[n_term] = {}
        #row entery of the non terminal
        for rule in prods[n_term]:
            if '#' in rule:
                for t in ll_g.follow[n_term]:
                    select[n_term][t] = rule
            for term in prods[n_term][rule]:
                #if the corresponding column is filled, raise error
                if term in select[n_term]:
                    print ("Not LL(1) Grammar")
                    #raise Exception
                if rule != '':
                    select[n_term][term] = rule

    return select


def print_select(select):
    s = 'Select \n'
    for i in select:
        s += '\t\t\t' + str(i) + ' : '
        for j in select(str(i))[:-1]:
            s += str(j) + ' | '
        s += str(select[str(i)][-1])
        s += '\n'
    s += '\n'


def get_select(g):
    select = set_select(g)
    print_select(select)
    return select
