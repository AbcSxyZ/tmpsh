/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrdup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 16:05:22 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 10:10:13 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wstrdup(wchar_t *wstr)
{
	wchar_t	*duplicate;
	int		len;

	len = ft_wstrlen(wstr);
	duplicate = (wchar_t *)ft_memalloc(sizeof(wchar_t) * (len + 1));
	ft_wstrcpy(duplicate, wstr);
	return (duplicate);
}
