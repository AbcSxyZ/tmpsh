/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tokenizer.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 10:39:37 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/16 12:21:44 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "tmpsh.h"
#include "libft.h"
#include "tokenizer_utils.h"

/*
** add_token:
**
** @current: actual created token.
** @tokens: pylst of actual tokens.
**
** If current tokens is not empty it appends to tokens then reset.
*/

static	void	add_token(char *current, t_pylst **tokens)
{
	if (*current)
	{
		push_pylst(tokens, current, sizeof(char) *\
			(ft_strlen(current) + 1), _chare);
		ft_bzero(current, ft_strlen(current));
	}
}

/*
** span:
**
** @command: raw input shell command.
** @tokens: pylst of actual tokens.
** @current: actual created token.
**
** Append current token if exist.
** If command begin with an operator it appends to tokens.
** Then length of this operator is returned.
** If not the first char of command it appends to current.
** Then one is resturned.
*/

static	int		span(char *command, t_pylst **tokens, char *current)
{
	int		length_cmd;
	int		j;
	int		i;
	char	*to_add;

	j = 1;
	i = 1;
	length_cmd = ft_strlen(command);
	add_token(current, tokens);
	while (j <= g_grammar->maxlen_leaf_op
			&& j <= length_cmd
			&& ops_begin_with(ft_strndup(command, j),\
				g_grammar->leaf_op, true))
		j += 1;
	to_add = ft_strndup(command, --j);
	if (in_pylst_chare(to_add, g_grammar->leaf_op))
	{
		push_pylst(tokens, to_add, sizeof(char) *\
				(ft_strlen(to_add) + 1), _chare);
		i = j;
	}
	else
		current[ft_strlen(current)] = *command;
	return (ft_strdel_out(&to_add, i));
}

/*
** escape_token:
**
** @command: raw input shell command.
** @tokens: pylst of actual tokens.
** @current: actual created token.
**
** Append current token if exist.
** Append a token formed with a \ and the next char if its exists.
** Return the incremented command pointer.
*/

static	char	*escape_token(char *command, t_pylst **tokens, char *current)
{
	add_token(current, tokens);
	command++;
	current[ft_strlen(current)] = g_grammar->escape[0];
	if (*command)
	{
		current[ft_strlen(current)] = *command;
		command++;
	}
	add_token(current, tokens);
	return (command);
}

/*
** span_space:
**
** @command: raw input shell command.
** @tokens: pylst of actual tokens.
** @current: actual created token.
**
** Append current token if exist.
** Then span all kind of spaces and append them to tokens.
** Return the number of spanned spaces.
*/

static	int		span_space(char *command, t_pylst **tokens, char *current)
{
	int		i;
	char	*spaces;

	i = 1;
	add_token(current, tokens);
	while (ft_incharset(command[i], " \t"))
		i++;
	spaces = ft_strndup(command, i);
	push_pylst(tokens, spaces, sizeof(char) * (ft_strlen(spaces) + 1), _chare);
	ft_strdel(&spaces);
	return (i);
}

/*
** tokenize:
**
** @command: raw input shell command.
** @tokens: address of NULL pointer of t_pylst tokens.
**
** Tokenize input in function of g_grammar.
** Put each tokens in *tokens.
*/

void			tokenize(char *command, t_pylst **tokens)
{
	char *current;

	current = ft_strnew(ft_strlen(command));
	while (*command)
	{
		if (ops_begin_with(ft_strndup(command, 1), g_grammar->leaf_op, true))
			command += span(command, tokens, current);
		else if (*command == g_grammar->escape[0])
			command = escape_token(command, tokens, current);
		else if (ft_incharset(*command, " \t"))
			command += span_space(command, tokens, current);
		else
			current[ft_strlen(current)] = *command++;
	}
	add_token(current, tokens);
	ft_strdel(&current);
}
