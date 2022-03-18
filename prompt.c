#include <unistd.h> //getcwd
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#define GRN  "\x1B[1;32m"
#define BLU  "\x1B[1;34m"
#define NRM  "\x1B[0m"


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
	printf("%s%s@%s:%s~%s$%s ", GRN, user, desktop, BLU, dir, NRM);
}

int	main(void)
{
	int	n;

	display_prompt();
	scanf("%d", &n);
	return (0);
}
