#ifndef UTILS_KEY_H
# define UTILS_KEY_H

void	modify_gold_key(char *gold_key);
int		quoted_gold_key(char *gold_key);
char	*get_key(char *key, char *tag, char *token, t_bool minus);

#endif