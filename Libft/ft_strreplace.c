/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strreplace.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/11 18:24:18 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/23 00:13:40 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

char	*ft_strreplace(char *dst, char chr, char repl_chr)
{
	char *s;

	s = dst;
	while (*s)
	{
		if (*s == chr)
			*s = repl_chr;
		s++;
	}
	return (dst);
}
