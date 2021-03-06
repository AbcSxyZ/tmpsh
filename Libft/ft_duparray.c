/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_duparray.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/25 09:31:36 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 09:58:53 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	array_size(char **array)
{
	int index;

	index = 0;
	while (array[index])
		index++;
	return (index);
}

char		**ft_duparray(char **array)
{
	char	**duplicate;
	int		index;

	duplicate = (char **)ft_memalloc(sizeof(char *) * (array_size(array) + 1));
	index = 0;
	while (*array)
	{
		duplicate[index] = ft_strdup(*array++);
		index++;
	}
	duplicate[index] = NULL;
	return (duplicate);
}
