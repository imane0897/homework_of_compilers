"""
the functions of finite automaton.
"""
from copy import deepcopy
from DeterministicFiniteAutomaton import DeterministicFiniteAutomaton
from collections import defaultdict
import random


def distinguish(nfa):
    """
    return if the input automaton is dfa or nfa.
    """
    for state in nfa.transition.keys():
        for sigma in nfa.alphabet():
            try:
                if nfa.transition[state]['e']:
                    print("it is a nfa")
                    return nfa
            except KeyError:
                pass

            try:
                if len(nfa.transition[state][sigma]) > 1:
                    print("it is a nfa")
                    return nfa
            except KeyError:
                pass
    dfa = DeterministicFiniteAutomaton(nfa.start_state, nfa.accept_states, nfa.transition)
    print("it is dfa")
    return dfa


def convert(nfa):
    start_state = frozenset(nfa.epsilon_closure(nfa.start_state))
    states = {start_state}
    unprocessed_states = states.copy()
    transition = {}
    accept_states = set()
    sigma = nfa.alphabet()
    try:
        sigma.remove('e')
    except KeyError:
        pass

    while len(unprocessed_states) > 0:
        q = unprocessed_states.pop()
        transition[q] = {}
        for a in sigma:
            next_states = set()
            for state in q:
                next_states = next_states | nfa.epsilon_closure(nfa.trans(frozenset([state]), a))
            next_states = frozenset(next_states)
            transition[q][a] = next_states
            if not next_states in states:
                states.add(next_states)
                unprocessed_states.add(next_states)
    for state in states:
        if len(state & nfa.accept_states):
            accept_states.add(state)
    dfa = DeterministicFiniteAutomaton(start_state, accept_states, transition)
    return dfa


def rename(dfa):
    """
    rename the states in a DFA, change a set which has many status [format: frozenset({'0', '7', '2'})]
    to a set has one status. [format: frozenset({'0'})]
    [tips: it just changes state's name not merge the states.]
    :return: a new DFA which changes the states' name.
    """

    # create a dictionary which map the old states' name to the new names.
    rename_dict = {dfa.start_state: frozenset(['0'])}
    # rename_dict [format: {frozenset({'0', '7', '2', '4', '1'}): frozenset({'0'})}]
    count = 1
    for key in dfa.transition.keys():
        for sigma in dfa.alphabet():
            try:
                rename_dict[dfa.transition[key][sigma]]
            except KeyError:
                new_state_name = str(count)
                rename_dict[dfa.transition[key][sigma]] = frozenset([new_state_name])
                count += 1

    # change the transition table && create a new DFA.
    new_transition = defaultdict(dict)
    for key in rename_dict.keys():
        for sigma in dfa.alphabet():
            new_transition[rename_dict[key]][sigma] = rename_dict[dfa.transition[key][sigma]]
    new_start_state = frozenset(['0'])
    new_accept_state = frozenset()
    for state in dfa.accept_states:
        new_accept_state = new_accept_state | frozenset(rename_dict[state])

    new_dfa = DeterministicFiniteAutomaton(new_start_state, new_accept_state, new_transition)
    return new_dfa


def get_source_set(dfa, target_set, sigma):
    """
    get a set of states for which a transition on sigma leads to a state in target_set.
    :param target_set: a frozenset [format: frozenset({'0'})]
    :return: a frozenset [format: frozenset({'0'})]
    """
    source_set = set()
    for state in dfa.states():
        try:
            if dfa.trans(frozenset([state]), sigma).issubset(target_set):
                source_set.update([state])
        except KeyError:
            pass
    return source_set


def minimization(dfa):
    """
    merge the nondistinguishable states of a DFA using Hopcroft's algorithm.
    :return: a dfa which has minimum states
    """
    # Hopcroft's algorithm

    accept_set = set() | dfa.accept_states
    P = [frozenset(accept_set), frozenset(dfa.states()-accept_set)]
    W = [frozenset(accept_set), frozenset(dfa.states()-accept_set)]
    while W:
        A = random.choice(W)
        W.remove(A)
        for sigma in dfa.alphabet():
            X = get_source_set(dfa, A, sigma)
            P_copy = []
            for Y in P:
                if X & Y and Y-X:
                    P_copy.append(X & Y)
                    P_copy.append(Y-X)
                    if Y in W:
                        W.remove(Y)
                        W.append(X & Y)
                        W.append(Y - X)
                    else:
                        if len(X & Y) <= len(Y-X):
                            W.append(X & Y)
                        else:
                            W.append(Y-X)
                else:
                    P_copy.append(frozenset(Y))
            P = deepcopy(P_copy)

    # create a new dfa which has minimum states.
    new_transition = defaultdict(dict)
    start_state = set()
    accept_states = set()
    for state in P:
        if len(state & dfa.start_state):
            start_state = state
        if len(state & dfa.accept_states):
            accept_states.add(state)
        for sigma in dfa.alphabet():
            for s in state:
                if dfa.trans(frozenset([s]), sigma) in P:
                    new_transition[state][sigma] = dfa.trans(frozenset([s]), sigma)
                else:
                    for a in P:
                        for b in a:
                            if dfa.trans(frozenset([s]), sigma) == frozenset([b]):
                                new_transition[state][sigma] = a
    new = DeterministicFiniteAutomaton(start_state, accept_states, new_transition)
    new = rename(new)
    return new


def print_automaton(fa):
    # print('start_state: ', fa.start_state)
    # print('accept_states: ', fa.accept_states)
    # print('transition_table:')
    # for x in fa:
    #     print(x)
    str = '''
    _____________________Automation_____________________


        Start State
        \t\t\t{}

        Accept States
        \t\t\t{}

        Transition Table
'''.format(fa.start_state, fa.accept_states)
    for x in fa:
        str +=  '\t\t\t\t\t' + x + '\n'
    print(str)
