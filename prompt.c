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

int	display_prompt(void)
{
	char *s;
	char *dir;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		s =  getenv("USER");
		dir = ft_strrchr(cwd, '/');
		printf("%s@42Wolfsburg %s %% ", s, &dir[1]);
		return (0);
	}
	else
	{
		printf("getcwd error");
		return (1);
	}
}

int	main(void)
{
	if (display_prompt() == 1)
		return (1);
	return (0);
}