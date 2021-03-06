/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** del_after_pylst:
**
** Delete each element from the given index
*/

void	del_after_pylst(t_pylst **pylst, int index)
{
	t_pylst		*del_node;
	t_pylst		*precedence;

	del_node = NULL;
	if (index == 0)
	{
		free_pylst(pylst, 0);
		return ;
	}
	precedence = precedence_pylst(*pylst, index);
	del_node = precedence->next;
	precedence->next = NULL;
	free_pylst(&del_node, 0);
}
