#!/usr/bin/env python3

from pprint import pprint
from collections import namedtuple
from collections import deque as dq
BeginEnd = namedtuple('Token', ['lol', 'end'])



# def atomize(command, singlechars):
# 	list_tokens_atomic = []
# 	curr_token = ""
# 	while command:
# 		actual = command.popleft()
# 		if not actual in ' \t' :
# 			if actual in singlechars:
# 				if curr_token != "":
# 					list_tokens_atomic.append(curr_token)
# 					curr_token = ""
# 				list_tokens_atomic.append(actual)
# 			else:
# 				curr_token += actual
# 		else:
# 			if curr_token != "":
# 				list_tokens_atomic.append(curr_token)
# 				curr_token = ""
# 	if curr_token != "":
# 		list_tokens_atomic.append(curr_token)
# 	#list_tokens_atomic = dq(list_tokens_atomic)
# 	return list_tokens_atomic # char **

# def list_begin_op(atomic_op, begin_op):
# 	len_op = len(begin_op)
# 	return [op for op in atomic_op if op[:len_op] == begin_op]

# def recompose_op(list_tokens_atomic, atomic_op):
# 	list_tokens = []
# 	while list_tokens_atomic:
# 		actual = list_tokens_atomic.popleft()
# 		if len(actual) > 1:
# 			list_tokens.append(actual)
# 			actual = ""
# 		else:
# 			op = ""
# 			while 1:
# 				list_op = list_begin_op(atomic_op, op + actual)
# 				if list_op == []:
# 					list_tokens.append(op)
# 					break
# 				op += actual
# 				if list_tokens_atomic:
# 					actual = list_tokens_atomic.popleft()
# 		if actual != "":
# 			list_tokens.append(actual)
# 			actual = ""
# 	return list_tokens

# def recompose_op(list_tokens_atomic, atomic_op, singlechars):
# 	list_tokens = []
# 	lta = list_tokens_atomic
# 	len_lta = len(lta)
# 	i = 0
# 	op = ''
# 	next = ''
# 	while (i < len_lta):
# 		if next == '':
# 			next = lta[i]
# 		if next not in singlechars:
# 			list_tokens.append(next)
# 			next = ''
# 		elif next in singlechars:
# 			while (i < len_lta and (op + next in atomic_op or op == "")):
# 				op += next
# 				print(op)
# 				i+=1
# 				next = lta[i]
# 			list_tokens.append(op)
# 			op = ''
# 		i += 1
# 	return list_tokens


		# self.grammar = get_grammar_from_path(path)
		# self.reverse = get_reverse_grammar(self.grammar)
		# self.atomic_op = get_atomic_op(self.reverse.keys())
		# self.singlechars = get_singlechars(self.reverse.keys())


def tokenize(command, grammar):
	# rev_gra = grammar.grammar
	# singlechars = get_singlechars(rev_gra.)
	# atomic_op = get_atomic_op(rev_gra.keys())
	print(grammar.grammar)
	print(grammar.reverse)
	# list_tokens_atomic = atomize(command, singlechars)
	# tokens = recompose_op(list_tokens_atomic, atomic_op, singlechars)


	tokens = []
	return tokens
