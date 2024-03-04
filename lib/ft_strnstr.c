
#include "../mini_shell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	y;

	if (!needle[0])
		return ((char *)haystack);
	if (!haystack[0])
		return (NULL);
	i = 0;
	while (i < len && haystack[i])
	{
		y = 0;
		while (i + y < len && haystack[i + y] == needle[y])
		{
			if (needle[y + 1] == '\0')
				return ((char *)&(haystack[i]));
			y++;
		}
		i++;
	}
	return (NULL);
}
