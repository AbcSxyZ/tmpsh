#!/usr/bin/env python3

import utils.global_var as gv
import utils.key as k


def strncmp(s1, s2, n):
    return s1 == s2[:n]


class TagsTokensMonitor():
    """docstring for TagsTokensMonitor."""

    def __init__(self, tt):
        self.tt = tt
        self.i = -1
        self.tag = ''
        self.token = ''
        self.begin_cmd = True
        self.heredocs_keys = []
        self.opened = ['']
        self.check()

    def get_tagstokens(self):
        return self.tt

    def reset(self):
        self.begin_cmd = True
        gv.PASSED_ALIAS = []

    def next_tag_token(self, clear=False):
        self.i += 1
        ret = self.i < self.tt.length
        if ret:
            self.tag = self.tt.tags[self.i]
            self.token = self.tt.tokens[self.i]
            if clear:
                del self.tt.tags[self.i]
                del self.tt.tokens[self.i]
                self.tt.update_length()
                self.i -= 1
        return ret

    def check(self):
        while self.next_tag_token():
            self.op_selector()

    def op_selector(self, skip=False):
        print(self.tag, self.begin_cmd)
        if self.tt.valid:
            if self.tag == 'STMT':
                self.check_aliases()
            elif self.tag == 'BRACEPARAM':
                self.is_braceparam()
            elif self.tag == 'DQUOTES':
                self.is_dquote()
            elif self.tag == 'QUOTE':
                self.is_quote()
            elif self.tag == 'NEW_LINE':
                self.is_newline()
            elif self.tag in gv.GRAMMAR.grammar['ABS_TERMINATOR']:
                self.is_abs_terminator()
            elif self.tag in ['CURSH', 'SUBSH']:
                self.in_command_sh()
            elif self.tag in gv.GRAMMAR.opening_tags:
                self.in_sub_process()
            elif self.tag == 'HEREDOC' or self.tag == 'HEREDOCMINUS':
                self.is_heredocs()
            elif self.tag in gv.GRAMMAR.grammar['REDIRECTION']:
                self.in_redirection()
            elif self.opened[-1] == self.tag:
                self.opened.pop(-1)

            if skip or (self.begin_cmd and self.tag == 'SPACES'):
                pass
            else:
                self.begin_cmd = False

    def is_newline(self):
        # should be improved or factorize
        import utils.heredocs as hd

        tuple_key_len = []
        key = ''
        heredoc = None
        not_end = True
        minus = False
        self.is_abs_terminator()
        while self.heredocs_keys != [] and not_end:
            tuple_key_len = self.heredocs_keys[0]
            heredoc = hd.Heredocs(
                tuple_key_len[0], tuple_key_len[1], tuple_key_len[2])
            tuple_key_len[0] = k.modifify_gold_key(tuple_key_len[0])
            minus = tuple_key_len[2]
            gv.HEREDOCS.append(heredoc)
            not_end = self.next_tag_token(True)
            while not_end:
                if key == tuple_key_len[0]:
                    heredoc.close()
                    break
                heredoc.add_tags_tokens(self.tag, self.token)
                key = k.get_key(key, self.tag, self.token, minus)
                if self.tag == 'NEW_LINE':
                    key = ''
                not_end = self.next_tag_token(True)
            self.heredocs_keys.pop(0)
            key = ''

    def check_aliases(self):
        result_alias = ''
        assignation = self.i + 1 < self.tt.length and self.tt.find_next_token(
            self.i + 1, False) in ["ASSIGNATION_EQUAL", "CONCATENATION"]
        if not assignation and self.begin_cmd and (self.token in gv.ALIAS and
                                                   self.token not in
                                                   gv.PASSED_ALIAS):
            result_alias = gv.ALIAS[self.token]
            self.begin_cmd = result_alias[-1:].isspace()
            gv.PASSED_ALIAS.append(self.token)
            self.tt.replace_alias(result_alias, self.i)
            if self.begin_cmd:
                self.reset()
        elif assignation:
            if not self.begin_cmd:
                self.tt.tags[self.i + 1] = 'STMT'
            else:
                self.reset()

    def is_braceparam(self):
        not_end = self.next_tag_token()
        stmt_tag = self.tag
        not_end = not_end and self.next_tag_token()
        if stmt_tag != 'STMT' or self.tag != 'END_BRACE':
            if not_end:
                self.tt.valid = False
                self.tt.token_error = 'bad substitution'

    def is_heredocs(self):
        def get_end_tag(tag):
            if tag in gv.GRAMMAR.grammar['QUOTES']:
                return tag
            return 'NEW_LINE'

        def transform_end_tag(tag):
            if tag == 'QUOTE':
                return 'END_QUOTE'
            if tag == 'DQUOTES':
                return 'END_DQUOTES'
            return tag

        minus = self.tag == 'HEREDOCMINUS'
        not_end = self.next_tag_token()
        key = ()
        j = 0
        list_tok = []
        if self.tag == 'SPACES':
            not_end = self.next_tag_token()
        if not_end:
            if self.tag in gv.GRAMMAR.opening_tags:
                j = self.tt.skip_openning_tags(self.i, get_end_tag(self.tag))
                list_tok = self.tt.tokens[self.i:j]
                key = [''.join(list_tok), len(list_tok), minus]
                self.i = j - 1
                self.tt.tags[self.i] = transform_end_tag(self.tag)
            else:
                key = [self.token, 1, minus]
            self.heredocs_keys.append(key)
        else:
            self.tt.valid = False
            self.tt.token_error = self.token
        self.begin_cmd = True

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
                self.tt.tags[self.i] = 'STMT' if self.tt.tags[self.i] != 'VAR' else 'VAR'

    def is_quote(self):
        inquote = True
        while inquote and self.next_tag_token():
            if self.tag == 'QUOTE':
                self.tt.tags[self.i] = 'END_QUOTE'
                inquote = False
                break
            else:
                self.tt.tags[self.i] = 'STMT'

    def is_abs_terminator(self):
        self.reset()

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
            end = (self.tag in gv.GRAMMAR.grammar['ABS_TERMINATOR']
                   or self.tag in gv.GRAMMAR.grammar['REDIRECTION']
                   or self.tag in ['END_BRACE', 'END_BRACKET'])
            if ret and not end:
                self.tt.valid = False
                self.tt.token_error = self.token
            elif ret and end:
                print("QWERTYUIOP")
                self.reset()
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
            self.op_selector()
            self.begin_cmd = True
        else:
            self.tt.valid = False
            self.tt.token_error = self.token
        self.begin_cmd = True
