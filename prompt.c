#include <unistd.h> //getcwd
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

void	display_prompt(void)
{
	char	*user;
	char	*dir;
	char	*pwd;
	char	*desktop;

	user =  getenv("USER");
	desktop = getenv("NAME");
	pwd = getenv("PWD");
	dir = ft_strrchr(pwd, '/');
	printf("%s@%s:~%s$ ", user, desktop, dir);
}

int	main(void)
{
	display_prompt();
	return (0);
}