#!/usr/bin/env python3

import utils.global_var as gv

# TODO: alias gesture
# TODO: {} can't be only by terminator
# TODO: 2 >> lol
# TODO: escape $PATH\\


class TagsTokensMonitor():
    """docstring for TagsTokensMonitor."""

    def __init__(self, tt):
        self.tt = tt
        self.i = -1
        self.tag = ''
        self.token = ''
        self.begin_cmd = True
        self.after_red = False
        self.opened = ['']
        self.passed_alias = []
        self.check()

    def get_tagstokens(self):
        return self.tt

    def reset(self):
        self.begin_cmd = True
        self.passed_alias = []

    def next_tag_token(self):
        self.i += 1
        ret = self.i < self.tt.length
        if ret:
            self.tag = self.tt.tags[self.i]
            self.token = self.tt.tokens[self.i]
        return ret

    def check(self):
        while self.tt.valid and self.next_tag_token():
            self.op_selector()

    def op_selector(self, skip=False):
        # print(self.tag, self.begin_cmd)
        if self.tt.valid:
            if self.tag == 'STMT':
                self.check_aliases()
            elif self.tag == 'BRACEPARAM':
                self.is_braceparam()
            elif self.tag == 'DQUOTES':
                self.is_dquote()
            elif self.tag == 'QUOTE':
                self.is_quote()
            elif self.tag in gv.GRAMMAR.grammar['ABS_TERMINATOR']:
                self.is_abs_terminator()
            elif self.tag in ['CURSH', 'SUBSH']:
                self.in_command_sh()
            elif self.tag in gv.GRAMMAR.opening_tags:
                self.in_sub_process()
            elif self.tag in gv.GRAMMAR.grammar['REDIRECTION']:
                self.in_redirection()
            elif self.opened[-1] == self.tag:
                self.opened.pop(-1)

            if skip or (self.begin_cmd and self.tag == 'SPACES'):
                print('LOL')
                pass
            else:
                self.begin_cmd = False

    def check_aliases(self):
        pass

    def is_braceparam(self):
        self.next_tag_token()
        stmt_tag = self.tag
        self.next_tag_token()
        if stmt_tag != 'STMT' or self.tag != 'END_BRACE':
            self.tt.valid = False
            self.tt.token_error = 'bad substitution'

    def is_dquote(self):
        indquote = True
        self.opened.append('DQUOTES')
        while indquote and self.next_tag_token():
            if self.tag == 'DQUOTES' and self.opened[-1] == 'DQUOTES':
                self.opened.pop(-1)
                self.tt.tags[self.i] = 'END_DQUOTES'
                indquote = False
            elif self.tag in gv.GRAMMAR.dquotes_opening_tags:
                self.op_selector()
            else:
                self.tt.tags[self.i] = 'STMT'

    def is_quote(self):
        inquote = True
        while inquote and self.next_tag_token():
            if self.tag == 'QUOTE':
                self.tt.tags[self.i] = 'END_QUOTE'
                inquote = False
            else:
                self.tt.tags[self.i] = 'STMT'

    def is_abs_terminator(self):
        self.reset()
        self.next_tag_token()

    def in_sub_process(self):
        self.reset()
        in_command = True
        self.opened.append(self.tag)
        exit_tag = gv.GRAMMAR.opening_tags[self.tag]
        while in_command and self.next_tag_token():
            if self.tag == exit_tag:
                self.opened.pop(-1)
                in_command = False
            else:
                self.op_selector()

    def in_command_sh(self):
        end = 0
        ret = 0
        if self.begin_cmd:
            self.in_sub_process()
            ret = self.next_tag_token()
            if self.tag == 'SPACES':
                ret = self.next_tag_token()
            print(ret, )
            if ret and (self.tag not in gv.GRAMMAR.grammar['ABS_TERMINATOR']
                        or self.tag not in gv.GRAMMAR.grammar['REDIRECTION']):
                self.tt.valid = False
                self.tt.token_error = self.token
            else:
                self.op_selector()
        else:
            end = self.tt.skip_openning_tags(self.i) - 1
            self.tt.tags[self.i] = 'STMT'
            if end < self.tt.length:
                self.tt.tags[end] = 'STMT'

    def in_redirection(self):
        not_end = self.next_tag_token()
        if self.tag == 'SPACES':
            not_end = self.next_tag_token()
        if not_end:
            self.op_selector(True)
            self.begin_cmd = True
        else:
            self.tt.valid = False
            self.tt.token_error = self.token
        self.begin_cmd = True

        # def prev_tokens_ok(self, i):
        #     if i == -1 or (i == 0 and self.tags[0] == 'SPACES'):
        #         return True
        #     ret = self.find_prev_token(i, False)\
        #         in gv.GRAMMAR.grammar['ABS_TERMINATOR']
        #     ret |= self.find_prev_token(i, False)\
        #         in gv.GRAMMAR.opening_tags
        #     return ret

        # def alias_gesture(self):
        #     i = 0
        #     tok = ''
        #     local = []
        #     passed_alias = []
        #
        #     while i < self.length:
        #         tok = self.tokens[i]
        #         print(passed_alias)
        #         if self.tags[i] in gv.GRAMMAR.grammar['ABS_TERMINATOR']\
        #                 or self.tags[i] in gv.GRAMMAR.opening_tags:
        #             passed_alias = []
        #         elif self.prev_tokens_ok(i - 1) and tok in gv.ALIAS and\
        #                 tok not in passed_alias:
        #             passed_alias.append(tok)
        #             tk.tokenize(gv.ALIAS[tok], local)
        #             self.tokens[i:i + 1] = local
        #             self.get_tags()
        #             local = []
        #             i -= 1
        #         i += 1
