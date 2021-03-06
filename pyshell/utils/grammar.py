#!/usr/bin/env python3

import pprint
# from pprint import pprint


class Grammar(object):
    def __init__(self, path):
        self.path = path
        self.grammar = {}
        self.reverse = {}
        self.get_grammar_from_path()  # self.grammar
        self.get_reverse_grammar()  # self.reverse

    def get_grammar_from_path(self):
        with open(self.path, 'r') as file:
            text = file.read()
        lines = text.split('\n')
        length = len(lines)
        i = 0
        grammar = {}
        while i < length:
            if len(lines[i]) > 0 and lines[i][0] not in '\n#\t':
                keyword = lines[i].split(':')[0].strip()
                i += 1
                if keyword not in grammar:
                    grammar[keyword] = []
                while 1:
                    if len(lines[i]) > 0 and lines[i][0] == '\t':
                        grammar[keyword].append(lines[i].strip())
                    else:
                        break
                    i += 1
            i += 1
        self.grammar = grammar

    def get_reverse_grammar(self):
        reverse_grammar = {}
        for key in self.grammar:
            for value in self.grammar[key]:
                reverse_grammar[value] = key
        self.reverse = reverse_grammar

    def add_symbol(self, symbol, symbol_name):
        if symbol_name not in self.grammar:
            self.grammar[symbol_name] = []
        self.grammar[symbol_name].append(symbol)
        #Is the condition usefull ??
        if symbol not in self.reverse:
            self.reverse[symbol] = {}
        self.reverse[symbol] = symbol_name

    def __str__(self):
        return '\n\n'.join(
            ['\033[91m{}\033[0m\n{}'.format(name, pprint.pformat(value))
             for name, value
             in sorted(vars(self).items())])
