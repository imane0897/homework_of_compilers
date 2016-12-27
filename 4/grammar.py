class Grammar():

    def __init__(self, V=None, T=None, S=None, P=None):
        '''
        self     : Grammar Object G
        V        : G.variables, strings in list
        T        : G.terminals, strings in list
        S        : G.startSymbol, string
        P        : G.productions, dict of lists
        first    : G.first_set, dict of lists (include V first and T first)
        follow   : G.follow_set, dict of lists
        ll_first : G.ll_first_set, dict of lists (include V first only)
        '''
        if V:
            self.variables = V
        else:
            self.variables = []

        if S:
            self.start = S
        else:
            self.start = ''

        if T:
            self.terminals = T
        else:
            self.terminals = []

        if P:
            self.productions = P
        else:
            self.productions = {}

        self.first = {}
        self.follow = {}
        self.ll_first = {}


    def add_V(self, symbol):
        '''Add a new symbol to the set of non terminals'''
        if symbol not in self.variables and symbol != '#':
            self.variables.append(str(symbol))


    def add_T(self, symbol):
        '''Add a new terminal to the current set of terminals'''
        if symbol not in self.terminals and symbol != '#':
            self.terminals.append(str(symbol))


    def add_P(self, lval, rval):
        '''Add a new production rule'''
        if lval in self.productions:
            self.productions[lval].append(rval)
        else:
            self.productions[lval] = [rval]


    def set_S(self, symbol):
        '''set the start symbol for the grammar'''
        self.start = symbol


    def set_first(self, f_set):
        '''Sets the first set for the ll_grammar'''
        self.first = f_set


    def set_follow(self, f_set):
        '''Sets the follow set for the ll_grammar'''
        self.follow = f_set


    def __str__(self):
        '''Prints out G(V, T, S, P, First_set, Follow_set)'''
        s = '''
_____________________Grammar_____________________


Start Symbol
\t\t\t{}

Terminals
\t\t\t{}

Variables
\t\t\t{}

________________________________________________

'''.format(self.start, self.terminals, self.variables)
        return s
