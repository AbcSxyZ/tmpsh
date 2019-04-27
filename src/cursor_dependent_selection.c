#include "cursor_dependent_selection.h"
#include "char_utils.h"
#include "libft.h"
/*
** is_cursor_pos:
**
** Condition to check according to a t_line and a t_char if we are on
** the cursor position.
*/

static int		is_cursor_pos(t_line *shell_repr, t_char *char_lst, \
		t_cursor *cursor)
{
	return (shell_repr->position == cursor->row && \
			char_lst->position == cursor->column);
}

static void	research_prev_info(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **search_char)
{
	int in_word;

	in_word = FALSE;
	word_cursor->row = 0;
	word_cursor->column = char_lock_len(shell_repr->chars);
	while (shell_repr && shell_repr->position <= curr_cursor->row)
	{
		*search_char = get_unlocked_char(shell_repr->chars);
		while (*search_char && !is_cursor_pos(shell_repr, *search_char, cursor))
		{
			if (ft_isalnum((*search_char)->letter) && in_word == FALSE)
			{
				in_word = TRUE;
				word_cursor->row = shell_repr->position;
				word_cursor->column = (*search_char)->position;
			}
			else if (ft_isspace((*search_char)->letter) && in_word = TRUE)
				in_word = FALSE;
			*search_char = (*search_char)->next;
		}
		in_word = FALSE;
		shell_repr->next;
	}
}

void	get_last_word(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **word_char)
{
	t_char	*search_char;
	t_cursor	word_save;

	search_char = NULL;
	research_prev_info(shell_repr, cursor, &word_save, &search_char);
	if (word_cursor)
		ft_memcpy(word_cursor, &word_save, sizeof(t_cursor));
	if (word_char)
		*word_char = search_char;
}

/*
** set_last_pos:
**
** Set up to the cursor the last avaible position of the shell.
*/

static void			set_last_pos(t_line *shell_repr, t_cursor *cursor)
{
	shell_repr = get_last_line(shell_repr);
	cursor->row = shell_repr->position;
	cursor->column = char_lst_len(shell_repr->chars);
}

static void			skip_empty_char(t_line **cursor_line, t_char **search_char)
{
	while (*cursor_line)
	{
		while (*search_char && !ft_isalnum((*search_char)->letter))
			*search_char = (*search_char)->next;
		if (*search_char)
			break ;
		*cursor_line = (*cursor_line)->next;
		if (*cursor_line)
			*search_char = get_unlocked_char((*cursor_line)->chars);
}

void		get_next_word(t_line *shell_repr, t_cursor *cursor, \
		t_cursor *word_cursor, t_char **word_char)
{
	t_char	*search_char;
	t_line	*cursor_line;

	cursor_line = get_cursor_line(shell_repr, cursor);
	search_char = get_cursor_char(cursor, cursor_line->chars, NULL);
	while (search_char && ft_isalnum(search_char->letter))
		search_char = search_char->next;
	skip_empty_char(&cursor_line, &search_char);
	if (word_char)
		*word_char = search_char;
	if (cursor_line && word_cursor)
	{
		word_cursor->column = search_char->position;
		word_cursor->row = cursor_line->position;
	}
	else if (!cursor_line && word_cursor)
		set_last_pos(shell_repr, word_cursor);
}

/*
** get_cursor_line:
**
** Get the line where the cursor is present.
*/

t_line		*get_cursor_line(t_line *shell_lines, t_cursor *cursor)
{
	while (shell_lines->position != cursor->row)
		shell_lines = shell_lines->next;
	return (shell_lines);
}

/*
** get_prev_cursor_line:
**
** Get the t_line before the cursor row position
*/

t_line	*get_prev_cursor_line(t_cursor *cursor, t_line *shell_repr)
{
	if (cursor->row == 0)
		return (NULL);
	while (shell_repr->next->position != cursor->row)
		shell_repr = shell_repr->next;
	return (shell_repr);
}

/*
** get_cursor_char:
**
** Get the t_char * element corresponding to the selected cursor.
** Get also the previous element in the same time.
** If the cursor it at the last position, return NULL.
*/

t_char	*get_cursor_char(t_cursor *cursor, t_char *char_lst,\
		t_char **prev_char)
{
	t_char	*cursor_char;

	if (prev_char)
		*prev_char = NULL;
	cursor_char = char_lst;
	while (cursor_char && cursor_char->position != cursor->column)
	{
		if (prev_char)
			*prev_char = cursor_char;
		cursor_char = cursor_char->next;
	}
	return (cursor_char);
}
