# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int     countPart(char *s, char del)
{
	int i;
	int part;

	i = 0;
	part = 0;
	if (!s)
		return part;
	while (s[i])
	{
		if (s[i] != del)
		{
			while (s[i] != del)
				i++;
			part++;
		}
		i++;
	}
	return part;
}

void    ft_strcpy(char *dest, char *src, int size)
{
	int i;

	i = 0;
	if (!dest || !src || !size)
		return ;
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
}

char    **ft_split(char *str, char del)
{
	int     i;
	int     r;
	int     part;
	int     size;
	char    **res;

	i = 0;
	r = 0;
	size = 0;
	if (!str)
		return NULL;
	part = countPart(str, del);
	if (!(res = malloc(sizeof(char *) * part + 1)))
		return NULL;
	res[part] = NULL;
	while (r < part)
	{
		while (str[i] && str[i] == del)
			i++;
		while (str[i] && str[i] != del)
		{
			i++;
			size++;
		}
		if (!(res[r] = malloc(sizeof(char) * size + 1)))
			return NULL;
		ft_strcpy(res[r], &(str[i - size ]), size);
		res[r][size] = '\0';
		size = 0;
		r++;
	}
	return res;
}

void    freeArray(char **s)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != NULL)
	{
		if (s[i])
			free(s[i]);
		i++;
	}
	free(s);
}

void    ft_putstr(char *s)
{
	if (!s)
		return ;
	while (*s)
		write(1, s++, 1);
}

int     ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return 0;
	while (*s++)
		i++;
	return i;
}

void    printArray(char **array)
{
	int i;

	i = 0;
	if (!array || !*array)
		return ;
	ft_putstr("Results:\n");
	while (array[i] != NULL)
	{
		ft_putstr(array[i]);
		write(1, "\n", 1);
		i++;
	}
}

int		main(int ac, char **av)
{
	char    **res;

	if (ac != 3)
	{
		dprintf(1, "argument error:\n\t%s string delimiter\n", av[0]);
		return 1;
	}
	else if (ft_strlen(av[2]) != 1)
	{
		ft_putstr("argument error: Delimiter must be only one character\n");
		return 1;
	}
	res = NULL;
	if (!(res = ft_split(av[1], av[2][0])))
	{
		ft_putstr("runtime error: malloc failed.");
		return 1;
	}
	dprintf(1, "Original string: %s\n", av[1]);
	dprintf(1, "Delimiter char: %c\n", av[1][0]);
	printArray(res);
	freeArray(res);
	return 0;
}