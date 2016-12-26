# import ll_gramtools
import ll_parser
import gramtools
import collections

def set_select(ll_g):
    '''
    returns the ll_parsing table, given the ll_grammar as param
    '''
    # table = collections.OrderedDict()
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
                    # pass
                # else:
                    select[n_term][term] = rule

    return select


