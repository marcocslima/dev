
#include "libft.h"

int	ft_findrchr(const char *s, int c)
{
	int	len_str;

	len_str = ft_strlen(s) - 1;
	if (s == NULL)
		return (0);
	if (c > 255)
		return (0);
	if (c == 0)
		return (0);
	while (len_str >= 0)
	{
		if (s[len_str] == 0 && s[len_str] != c)
			return (0);
		if (s[len_str] == c)
			return (len_str);
		len_str--;
	}
	return (0);
}
