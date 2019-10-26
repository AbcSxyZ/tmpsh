/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_newline_ttm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 22:27:14 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 22:32:22 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

// static t_heredocs	*get_heredoc(t_pylst *list_param, char **gold_key)
// {
// 	t_heredocs	*heredoc;
// 	char		*tmp;
//
// 	tmp = (char *)vindex_pylst(list_param, 0);
// 	init_heredocs(&heredoc,
// 					tmp,
// 					*((int *)vindex_pylst(list_param, 1)),
// 					*((int *)vindex_pylst(list_param, 2)));
// 	modify_gold_key(tmp);
// 	*gold_key = tmp;
// 	return (heredoc);
// }

static	t_bool		full_heredoc(t_tags_tokens_monitor *self,
							t_heredocs *heredoc, char *gold_key)
{
	char	*key;
	t_bool	not_end;

	key = ft_strnew(0);
	not_end = next_ttm(self);
	while (not_end)
	{
		if (ft_strequ(key, gold_key))
		{
			close_heredocs(heredoc);
			break ;
		}
		add_tags_tokens_heredocs(heredoc, self->tag, self->token);
		key = get_key(key, self->tag, self->token, false);
		if (ft_strequ(self->tag, "NEW_LINE"))
		{
			ft_strdel(&key);
			key = ft_strnew(0);
		}
		not_end = next_ttm(self);
	}
	return (ft_strdel_out(&key, not_end));
}

/*
** is_newline_ttm:
**
** description:
** After newline create all presente heredoc and insert then in g_heredocs.
**
** parameter:
** - (t_tags_tokens_monitor*) self : actual tagstokensmonitor.
*/

void				is_newline_ttm(t_tags_tokens_monitor *self)
{
	char		*gold_key;
	t_heredocs	*heredoc;
	t_bool		not_end;

	not_end = true;
	gold_key = NULL;
	while (iter_pylst(g_heredocs, (void **)&heredoc) && not_end)
	{
		gold_key = ft_strdup(heredoc->key);
		modify_gold_key(gold_key);
		not_end = full_heredoc(self, heredoc, gold_key);
		ft_strdel(&gold_key);
	}
	reset_ttm(self);
}
