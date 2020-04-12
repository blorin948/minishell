#include "minishell.h"

int		count_unset(t_storage *s)
{
	int i = 0;
	int a = 0;
	int c = 0;
	int count = 0;
	while (s->env[a])
	{
		while (s->env[a][i] != '=')
			i++;
		while (s->arg[c])
		{
			if (ft_strncmp(s->env[a], s->arg[c], i) == 0)
				count++;
			c++;
		}
		a++;
		i = 0;
		c = 0;
	}
	return (count);
}

char **copy_unset(t_storage *s, char **new)
{
	int i = 0;
	int a = 0;
	int c = 0;
	int k = 0;
	int o = 0;
	a = 0;
	while (s->env[a])
	{
		while (s->env[a][i] != '=')
			i++;
		while (s->arg[c])
		{
			if (ft_strncmp(s->env[a], s->arg[c], i) == 0)
				k++;
			c++;
		}
		if (k == 0)
		{
			i = 0;
			if (!(new[o] = malloc(sizeof(char) * ft_strlen(s->env[a]) + 1)))
				exit;
			while (s->env[a][i])
			{
				new[o][i] = s->env[a][i];
				i++;
			}
			new[o][i] = '\0';
			o++;
		}
		a++;
		k = 0;
		i = 0;
		c = 0;
	}
	return (new);
}

int 	print_unset(t_storage *s)
{
	int i = 0;
	int a = 0;
	char **new;
	int count = 0;
	if (s->paramc == 1)
		return (0);
	while (s->env[a])
		a++;
	count = a - count_unset(s);
	if (!(new = malloc(sizeof(char *) * count + 1)))
		exit;
		a = 0;
	s->env = copy_unset(s, new);
	s->env[count] = 0;
}