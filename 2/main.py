import automaton
from NFA import NFA
from collections import defaultdict


def initial(text_path):
    text = [line.strip() for line in open('{}'.format(text_path)).readlines()]
    transition = defaultdict(dict)
    # transition [format: {frozenset({'q0'}):{'e':frozenset({'q0', 'q1'}), 'a':frozenset({'q1', 'q2'})}}]
    for line in text[:len(text)-1]:
        alphabet = {}
        (state, alpha) = line.split(' :: ')
        alpha_list = alpha.split(' | ')
        for x in alpha_list:
            (sigma, alpha_value) = x.split(':')
            states = set(alpha_value.split(','))
            alphabet[sigma] = frozenset(states)
        transition[frozenset([state])] = alphabet
    nfa_test = NFA(start_state=frozenset(['q0']), accept_states={text[len(text) - 1]}, transition=transition)
    return nfa_test


if __name__ == '__main__':
    nfa = initial('2_1.txt')
    isNFA = automaton.isNFA(nfa)

    if isNFA:
        dfa = automaton.convert(nfa)
    else:
        dfa = nfa

    mini_dfa = automaton.minimization(dfa)
    automaton.print_automaton(mini_dfa)


    test_list = ['bbaaabb', 'bab', 'abbbba', 'aaabba', 'abc']
    for x in test_list:
        print(' ')
        print((x, mini_dfa.is_accept(x)))