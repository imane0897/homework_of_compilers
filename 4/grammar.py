# import gramtools

class Grammar():

    def __init__(self, V=None, T=None, S=None, P=None):
        '''
        self : Grammar Object G
        V    : G.variables, list of non terminal symbols held as strings
        T    : G.terminals, list of terminal symbols held as strings
        S    : G.startSymbol, symbol which is a start symbol, stored as string
        P    : G.productions, dict of lists of production rules for the given Grammar
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
        '''Prints out G(V, T, S, P)'''
        s = 'Grammar \n'
        s += 'Start Symbol \n' + str(self.start) + '\n'
        s += 'Terminals \n' + str(self.terminals) + '\n'
        s += 'Variables \n' + str(self.variables) + '\n'
        s += 'Productions \n' + str(self.productions) + '\n'
        s += '\nFirst set :\n' + str(self.first) + '\n'
        s += '\nFollow set :\n' + str(self.follow) + '\n'
        s += '\nLL_First set :\n' + str(self.ll_first) + '\n'
        return s
