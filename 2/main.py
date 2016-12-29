import FiniteAutomaton
from NondeterministicFiniteAutomaton import NondeterministicFiniteAutomaton
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
    nfa_test = NondeterministicFiniteAutomaton(start_state=frozenset(['q0']), accept_states={text[len(text)-1]}, transition=transition)
    return nfa_test


if __name__ == '__main__':
    nfa = initial('2_3.txt')
    nfa_or_dfa = FiniteAutomaton.distinguish(nfa)
    if nfa_or_dfa == nfa:
        dfa = FiniteAutomaton.convert(nfa)
        dfa = FiniteAutomaton.rename(dfa)
        FiniteAutomaton.print_automaton(dfa)
        mini_dfa = FiniteAutomaton.minimization(nfa_or_dfa)
        FiniteAutomaton.print_automaton(mini_dfa)

    else:
        mini_dfa = FiniteAutomaton.minimization(nfa_or_dfa)
        FiniteAutomaton.print_automaton(mini_dfa)

    # print([(x, mini_dfa.is_accept(x)) for x in ['abb', 'ab', 'baababb']]) # 2_1.txt expected result:[('abb', True), ('ab', False), ('baababb', True)]
    # print([(x, mini_dfa.is_accept(x)) for x in ['0101', '1100', '1011']]) # 2_2.txt expected result:[('0101', False), ('1100', True), ('1011', False)]
    # print((x, mini_dfa.is_accept(x)) for x in ['aa', 'ab', 'aba'])  # 2_3.txt expected result:[('aa', False), ('ab', True), ('aba', False)]

    test_list = ['aa', 'ab', 'aba']
    for x in test_list:
        print(' ')
        print((x, mini_dfa.is_accept(x)))