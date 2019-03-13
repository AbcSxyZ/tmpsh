#include "display.h"
#include "t_line_utils.h"
#include "t_caps_utils.h"
#include "t_cursor_utils.h"
#include "screen_size.h"
#include "t_char_utils.h"

/*
** clean_lines:
**
** Delete the given number of line, moving up the cursor each time.
*/

void			clean_lines(int nb_line, int is_last_line)
{
	ft_printf(g_caps->start_line);
	ft_dprintf(fd_debug, "last : %d\n", is_last_line);
	while (nb_line--)
	{
		ft_printf(g_caps->del_line);
		if (nb_line > 0 || is_last_line == FALSE)
		{
			ft_printf(g_caps->move_up);
			ft_dprintf(fd_debug, "up\n");
		}
	}
}

/*
** reset_cursor:
**
** Reset the cursor to the position where the prompt will be printed.
*/

void			reset_cursor(t_line *shell_lines, t_cursor *cursor)
{
	int		win_lines;
	int		win_cols;
	int		line_len;
	static int	current_shell_size;
	int		tmp_to_clean;	

	screen_size(&win_cols, &win_lines);
	while (shell_lines)
	{
		line_len = char_lst_len(shell_lines->chars);
		ft_dprintf(fd_debug, "total len : %d\n", line_len);
		if (!shell_lines->next && is_cursor_last_pos(shell_lines, cursor))
			line_len++;
		tmp_to_clean = line_len / win_cols;
		tmp_to_clean += line_len % win_cols > 1;
		ft_dprintf(fd_debug, "to_clean : %d | len : %d | win_col : %d| modulo : %d\n", 
				tmp_to_clean, line_len, win_cols, line_len % win_cols);
		shell_lines = shell_lines->next;
	}
	if (tmp_to_clean > current_shell_size)
		current_shell_size = tmp_to_clean;
	clean_lines(tmp_to_clean, TRUE);
}

/*
** display_shell:
**
** Display the representation of the shell using the t_line and t_char
** structure.
*/

void			display_shell(t_line *prompt_lines, t_cursor *cursor, int first_display)
{
	int			printed_cursor;

	printed_cursor = FALSE;
	if (first_display == FALSE)
		reset_cursor(prompt_lines, cursor); // to improve
	while (prompt_lines)
	{
		display_chars(prompt_lines->chars, cursor, prompt_lines->position, 
				&printed_cursor);
		if (printed_cursor == FALSE && cursor->row == prompt_lines->position)
			show_cursor(' ');
		else if (prompt_lines)
			write(1, "\n", 1);
		prompt_lines = prompt_lines->next;
	}
}
