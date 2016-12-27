class Grammar():

    def __init__(self, V=None, T=None, S=None, P=None):
        '''
        self : Grammar Object G
        V    : G.variables, strings in list
        T    : G.terminals, strings in list
        S    : G.startSymbol, string
        P    : G.productions, dict of lists
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


    def __str__(self):
        '''Prints out G(V, T, S, P)'''
        s = '______________Grammar______________\n'
        s += 'Start Symbol \n' + '\t\t\t'+str(self.start) + '\n'
        s += 'Terminals \n' + '\t\t\t'+str(self.terminals) + '\n'
        s += 'Variables \n' + '\t\t\t'+str(self.variables) + '\n'
        s += 'Productions \n' + '\n'
        for p in self.productions:
            s += '\t\t\t'+str(p) + ' ::= '
            for i in self.productions[str(p)][:-1]:
                s += str(i) + ' | '
            s += str(self.productions[str(p)][-1])
            s += '\n'
        return s