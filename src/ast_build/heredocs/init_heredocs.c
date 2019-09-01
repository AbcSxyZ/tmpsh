#include "heredocs.h"


/*
** init_heredocs:
**
** description:
** describe what you function do.
**
** parameter:
** - (type) name : what is this param?
**
** return value:
** - (type) value : descibe output.
*/

void	init_heredocs(t_heredocs **self, char *key, int len_key, t_bool minus)
{
	*self = ft_memalloc(sizeof(t_heredocs));
	(*self)->key = ft_strdup(key);
	(*self)->quoted = quoted_gold_key(key);
	(*self)->len_key = len_key;
	(*self)->minus = minus;
	(*self)->closed = false;
	init_tagstokens(&(*self)->tagstokens, NULL, NULL);
	(*self)->in_cmdsubst = false;
}