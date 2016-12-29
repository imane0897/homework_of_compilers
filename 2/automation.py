import functools


class DAutomaton:
    def __init__(self, str_state, acc_states, trans):
        self.str_state = str_state
        self.acc_states = acc_states
        self.trans = trans

    # def __iter__(self):
    #     keys = self.transition.keys()
    #     for key in sorted(keys):
    #         yield '{0} {1}'.format(key, self.transition[key])

    def trans(self, state, input_string):
        """
        :param state: a frozenset [format: frozenset({'q0'})]
        :return: a frozenset [format: frozenset({'q1', 'q2'})]
        """
        for a in input_string:
            try:
                state = self.transition[state][a]
            except KeyError:
                pass
        return state

    def states(self):
        reach_states = set()
        for key in self.transition.keys():
            for sigma in self.alphabet():
                reach_states = reach_states | self.trans(key, sigma)
        states = set() | self.start_state | reach_states
        return states

    def alphabet(self):
        sigma = functools.reduce(lambda a, b: set(a) | set(b), [x.keys() for x in self.transition.values()])
        return sigma

    def is_acc(self, input_string):
        return self.trans(self.start_state, input_string).issubset(self.accept_states)
