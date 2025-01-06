#include "../../includes/char.h"

char	*append_char(char *old_str, char c)
{
	int		len;
	char	*new_str;

	len = 0;
	if (old_str)
		len = ft_strlen(old_str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	int i = 0;
	while (old_str && old_str[i])
	{
		new_str[i] = old_str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	if (old_str)
		free(old_str);
	return (new_str);
}
