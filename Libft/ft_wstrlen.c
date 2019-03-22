/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 16:07:34 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 16:07:47 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <wchar.h>

size_t	ft_wstrlen(wchar_t *str)
{
	int	index;

	index = 0;
	while (*(str + index))
		index++;
	return (index);
}