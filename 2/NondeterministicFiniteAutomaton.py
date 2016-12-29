import functools


class NondeterministicFiniteAutomaton:
    def __init__(self,start_state, accept_states, transition):
        self.start_state = start_state
        self.accept_states = accept_states
        self.transition = transition

    def __iter__(self):
        keys = self.transition.keys()
        for key in sorted(keys):
            yield '{0} {1}'.format(key, self.transition[key])

    def trans(self, input_state, input_string):
        """
        :param state: a frozenset [format: frozenset({'0'})]
        :return: a frozenset [format: frozenset({'1', '2'})]
        """
        states = {input_state}
        for a in input_string:
            new_states = set([])
            for state in states:
                try:
                    new_states = new_states | self.transition[state][a]
                except KeyError:
                    pass
            states = new_states
        return states

    def alphabet(self):
        sigma = functools.reduce(lambda a, b: set(a) | set(b), [x.keys() for x in self.transition.values()])
        return sigma

    def states(self):
        reach_states = set()
        for key in self.transition.keys():
            for sigma in self.alphabet():
                reach_states = reach_states | self.trans(key, sigma)
        states = set() | self.start_state | reach_states
        return states

    def epsilon_closure(self, states):
        """
        return a set of states which is reachable through epsilon.
        [tips: use 'e' instead of epsilon]
        """
        total_set = set() | states
        for state in states:
            state_set = set(self.trans(frozenset([state]), 'e'))
            while True:
                state_set_copy = state_set.copy()
                for s in state_set:
                    state_set = state_set | self.trans(frozenset([s]), 'e')
                if not state_set ^ state_set_copy:
                    break
            total_set = total_set | state_set
        return total_set
