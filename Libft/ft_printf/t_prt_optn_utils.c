/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   t_prt_optn_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:12:36 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 10:04:24 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"

/*
** free_prt_opt:
**
** Free, if existing, a *format_option element and his content.
** Return the specified status.
*/

int			free_prt_opt(t_prt_opt **format_option, int status)
{
	if (*format_option)
	{
		FREE((*format_option)->flag);
		FREE((*format_option)->full_specifier);
		FREE(*format_option);
		*format_option = NULL;
	}
	return (status);
}

/*
** alloc_option:
**
** Malloc a t_prt_opt * element and his flag attribute.
*/

t_prt_opt	*alloc_option(void)
{
	t_prt_opt *option;

	option = (t_prt_opt *)ft_memalloc(sizeof(t_prt_opt));
	option->flag = (t_flags *)ft_memalloc(sizeof(t_flags));
	option->full_specifier = NULL;
	return (option);
}
