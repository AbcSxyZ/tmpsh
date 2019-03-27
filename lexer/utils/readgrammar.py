#!/usr/bin/env python3

from pprint import pprint
import utils.file as fl
from collections import deque as dq

def get_reverse_grammar(grammar):
	reverse_grammar = {}
	for key in grammar:
		for value in grammar[key]:
			reverse_grammar[value] = key
	return reverse_grammar

def containalphanum(key):
	return any([l.isalnum() for l in key])

def get_singlechars(rev_gra_keys):
	singlechars = set(''.join([k for k in rev_gra_keys
			if not containalphanum(k)]))
	singlechars.discard('.')
	singlechars.discard('$')
	singlechars.add('\n')
	return singlechars

def get_atomic_op(rev_gra_keys):
	atomic_op = [k for k in rev_gra_keys if not containalphanum(k)]
	atomic_op.append('\n')
	compose_op = [k for k in atomic_op if "." in k]
	for k in compose_op:
		atomic_op.remove(k)
		atomic_op.extend(k.split('.'))
	return atomic_op

def get_grammar_from_path(path):
	text = fl.get_text(path)
	lines = text.split('\n')
	length = len(lines)
	i = 0
	grammar = {}
	while (i < length):
		if len(lines[i]) > 0 and lines[i][0] not in '\n#\t':
			keyword = lines[i].split(':')[0].strip()
			i += 1
			if keyword not in grammar:
				grammar[keyword] = []
			while (1):
				if len(lines[i]) > 0 and lines[i][0] == '\t':
					grammar[keyword].append(lines[i].strip())
				else:
					break
				i += 1
		i += 1
	return grammar

class Grammar(object):
	def __init__(self, path):
		self.grammar = get_grammar_from_path(path)
		self.reverse = get_reverse_grammar(self.grammar)
		self.atomic_op = get_atomic_op(self.reverse.keys())
		self.singlechars = get_singlechars(self.reverse.keys())

def get_grammar(path):
	return Grammar(path)
