/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   python_list.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 10:32:13 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 10:12:01 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** alloc_pylst_node:
**
** Allocate a single t_pylst * (aka struct s_pylst *) element.
** Duplicate his value content if the size is given.
*/

static int		alloc_pylst_node(t_pylst **py_node, void *value, int size, \
		int ctype)
{
	if (!(*py_node = (t_pylst *)MALLOC(sizeof(t_pylst))))
		return (ALLOC_ERROR);
	if (size > 0)
	{
		if (!((*py_node)->value = MALLOC(size)))
			return (free_pylst_node(py_node, ALLOC_ERROR));
		ft_memcpy((*py_node)->value, value, size);
	}
	else
		(*py_node)->value = value;
	(*py_node)->ctype = ctype;
	(*py_node)->size = size;
	(*py_node)->next = NULL;
	return (ALLOC_SUCCESS);
}

/*
** push_pylst:
**
** Push at the end of the current list a new element.
** Copy the given value if a size is given.
*/

int		push_pylst(t_pylst **pylst, void *value, int size, int ctype)
{
	if (!*pylst)
		return (alloc_pylst_node(pylst, value, size, ctype));
	while ((*pylst)->next)
		pylst = &(*pylst)->next;
	return (alloc_pylst_node(&(*pylst)->next, value, size, ctype));
}
