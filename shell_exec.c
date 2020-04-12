#include "minishell.h"

char	*find_path(t_storage *s)
{
	int i = 0;
	int a = 0;
	while (s->env[a])
	{
		while (s->env[a][i] != '=')
			i++;
		if (ft_strncmp(s->env[a], "PATH", i) == 0)
			return (s->env[a]);
		a++;
		i = 0;
	}
	return (NULL);
}

char *ft_strcat(char *dest, char *src)
{
	int i = 0;
	int a=  0;
	int c = 0;
	i = ft_strlen(dest);
	a = ft_strlen(src);
	while (a > 0)
	{
		dest[i++] = src[c++];
		a--;
	}
	dest[i] = '\0';
	return (dest);
}
char	**create_exec_path(t_storage *s, char **oldpath)
{
	char **newpath;
	int i = 0;
	int a = 0;
	int c = 0;
	while (oldpath[a])
		a++;
	if (!(newpath = malloc(sizeof(char * ) * a + 1)))
		exit(0);
	a = 0;
	while (oldpath[a])
	{
		if (a == 0)
			i = 5;
		if (!(newpath[a] = malloc(sizeof(char) * ((ft_strlen(oldpath[a]) - i) + ft_strlen(s->arg[0]) + 1) )))
			exit (0);
		while (oldpath[a][i])
			newpath[a][c++] = oldpath[a][i++];
		newpath[a][c++] = '/';
		newpath[a][c] = '\0';
		ft_strcat(newpath[a], s->arg[0]);
		a++;
		i = 0;
		c = 0;
	}
	return (newpath);
}

int		exec_ve(t_storage *s)
{
	int c = (s->current * 2) - 1;
	int cl = (s->count - 1) * 2;
	int i = 0;
	pid_t id;
	int a = 0;
	cl--;
		if (s->in == 2)
		{
			dup2(s->pipefd[c - 1], 0);
		}
		if (s->out == 2)
		{
			dup2(s->pipefd[c + 2] ,1);
		}
		if (s->in == 2 && s->out == 2)
		{
			while (cl > 0)
			{
				if (cl != c +2 && cl != c - 1)
					close(s->pipefd[cl]);
				cl--;
			}
		}
		if (s->in == 2 && s->out != 2)
		{
			while (cl > 0)
			{
				if (cl != c - 1)
					close(s->pipefd[cl]);
				cl--;
			}
		}
		if (s->in != 2 && s->out == 2)
		{
			while (cl > 0)
			{
				if (cl != c +2)
					close(s->pipefd[cl]);
				cl--;
			}
		}
		a = 0;
		while (s->newpath[a++])
			execve(s->newpath[a], s->arg, s->env);
		ft_putstr_fd("wrong command\n", 1);
	return (1);
}

int	do_shell(t_storage *s)
{
	int a = 0;
	char *c = ":";
		if (find_path(s) == NULL)
		{
			printf("rate\n");
			return (1);
		}
		s->newpath = ft_split(find_path(s), c, s);
		s->newpath = create_exec_path(s, s->newpath);
	exec_ve(s);
}
