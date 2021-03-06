/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/13 08:26:17 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 10:10:00 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substring;

	substring = (char *)ft_memalloc(sizeof(char) * (len + 1));
	ft_strncpy(substring, s + start, len);
	substring[len] = '\0';
	return (substring);
}
