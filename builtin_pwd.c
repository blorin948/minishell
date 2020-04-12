#include "minishell.h"

int		print_pwd(t_storage *s)
{
	//write(1, "\n", 1);
	  char *str;
  str = malloc(sizeof(char) * 200);
  getcwd(str, 200);
  ft_putstr_fd(str, 1);
  write(1, "\n", 1);
}

int		count_export(t_storage *s)
{
	int count = 0;
	int a = 0;
	int i  = 0;
	while (s->arg[a])
	{
		while (s->arg[a][i])
		{
			if (s->arg[a][i] == '=')
			{
				count++;
				break ;
			}
			i++;
		}
		a++;
		i = 0;
	}
	return (count);
}

char **copy_env(t_storage *s, char **new)
{
	int a = 0;
	int i = 0;
		i = 0;
		int c = 0;
		int k= 0;
		int o = 0;
	while (s->env[a])
	{
		while (s->env[a][i] != '=')
				i++;
		while (s->arg[c])
		{
			if (strncmp(s->env[a], s->arg[c], i) == 0)
				k++;
			c++;
		}
		if (k == 0)
		{
			i = 0;
			if (!(new[o] = malloc(sizeof(char) * ft_strlen(s->env[a]) + 1)))
				exit ;
				while (s->env[a][i])
				{
					new[o][i] = s->env[a][i];
					i++;
				}
				new[o][i] = '\0';
				o++;
		}
		a++;
		i = 0;
		c = 0;
		k = 0;
	}
	return (new);
}

char *ft_copy(char *str)
{
	char *new;
	int i = 0;
	int a = 0;
	while (str[i] != '=')
		i++;
	if (!(new = malloc(sizeof(char) * i + 1)))
		exit ;
	while (a < i)
	{
		new[a] = str[a];
		a++;
	}
	new[a] = '\0';
	return (new);
}

char **copy_arg(t_storage *s, char **new, int count)
{
	int i = 0;
	int a = 0;
	int k = 0;
	while (s->env[a])
		a++;
	while (s->arg[k])
	{
		while (s->arg[k][i])
		{
			if (s->arg[k][i] == '=' && s->arg[k][i + 1] != '>' && s->arg[k][i + 1] != '<')
				new[count++] = ft_strdup(s->arg[k]);
			else if (s->arg[k][i] == '=' && (s->arg[k][i + 1] == '>' || s->arg[k][i + 1] == '<'))
				new[count++] = ft_copy(s->arg[k]);
			i++;
		}
		i = 0;
		k++;
	}
	return (new);
}

int		is_variable(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}	
	return (0);
}

int		check_dup(t_storage *s)
{
	int i = 0;
	int a = 0;
	int c = 0;
	int count = 0;
	while (s->arg[a])
	{
		if (is_variable(s->arg[a]))
		{
			while (s->arg[a][i] != '=')
				i++;
			while (s->env[c])
			{
				if (strncmp(s->env[c], s->arg[a], i) == 0)
					count++;
				c++;
			}
		}
		a++;
		c = 0;
		i = 0;
	}
	return (count);
}

int		count_env(t_storage *s, int count, int *count_n_export)
{
	int a = 0;
	int i = 0;
	while (s->env[a])
		a++;
	count = count + a;
	count = count - check_dup(s);
	*count_n_export = count;
	count = count + count_export(s);
	return (count);
}

char **create_env(t_storage *s)
{
	char **new;
	int i = 0;
	int a = 0;
	int count = 0;
	int count_n_export = 0;

	count = count_env(s, count, &count_n_export);
	new = malloc(sizeof(char *) * count + 1);
	new = copy_env(s, new);
	new = copy_arg(s, new, count_n_export);
	new[count] = 0;
	i = 0;
	//while (new[i])
	//	printf("i = %d | %s\n", i, new[i++]);
	return (new);
}

int	print_export(t_storage *s)
{
	int a = 0;
	int i = 0;
	if (s->paramc == 1)
		return (0);
	s->env = create_env(s);
}

int		print_env(t_storage *s)
{
	int a = 0;
	while (s->env[a])
	{
		ft_putstr_fd(s->env[a++], 1);
		write(1, "\n", 1);
}
}
