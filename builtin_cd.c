#include "minishell.h"

int	check_arg(char *arg)
{
	int i = 0;
	int o = 0;
	while (arg[i])
	{
		if (arg[i] != ' ')
			o++;
		i++;
	}
	if (o > 0)
		return (1);
	else
		return (0);
	
}

int	print_cd(t_storage *s, char *cmd)
{
	if (s->paramc > 2)
		return (ft_error("cd : trop d'arguments \n"));
	int i = 0;
	/*while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}*/
	if (s->paramc == 1)
	{
		if (chdir("/home/lorin") != 0)
			ft_putstr_fd("error with cd \n", 1);
	}
	else
	{
		if (chdir(s->arg[1]) != 0)
		{
			ft_putstr_fd(s->arg[1], 1);
			ft_putstr_fd(" : Aucun fichier ou dossier de ce type \n", 1);
		}
	}
}

int is_redirection(t_storage *s)
{
	int i = 0;
	int a = 0;
	while (s->arg[a])
	{
		while (s->arg[a][i])
		{
			if (s->arg[a][i] == '>' || s->arg[a][i] == '<')
				return (1);
				i++;
		}
		i = 0;
		a++;
	}
	return (0);
}

char *get_name(t_storage *s, int a, int i)
{
	char *name;
	int k = 0;
//	a = a - 1;
	i++;
	//printf("%d\n", a);
	if (s->arg[a][i] == '>')
		i++;
	int tmp = i;
	while (s->arg[a][i] && s->arg[a][i] != '>' && s->arg[a][i] != '<')
	{
		i++;
		k++;
	}
	if (!(name = malloc(sizeof(char) * k + 1)))
		exit;
	k = 0;
	i = tmp;
	while (s->arg[a][i] && s->arg[a][i] != '>' && s->arg[a][i] != '<')
		name[k++] = s->arg[a][i++];
	name[k] = '\0';
	return (name);
}

int		create_files2(t_storage *s, int a)
{
	int i = 0;
	int count = 0;
	printf("%d\n", a);
	while (s->arg[a][i])
	{
		if (s->arg[a][i] == '>')
		{
			if (s->arg[a][i + 1] == '>')
			{
				open(get_name(s, a, i), O_WRONLY | O_CREAT | O_APPEND,S_IRWXU);
				i = i + 2;
			}
			else
			{
				open(get_name(s, a, i), O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU);
				i++;
			}
		}
		i++;
	}
	return (0);
}
int		create_files(t_storage *s)
{
	int a = 1;
	int i = 0;
	int k = 0;
	while (a < s->paramc)
	{
		while (s->arg[a][i])
		{
			if (s->arg[a][i] == '>')
			{	
				create_files2(s, a);
				break;
			}
			i++;
		}
		a++;
		i = 0;
	}
	return (0);
}

int	do_redirection(t_storage *s)
{
	int a = s->paramc - 1;
	int i = 0;
	int k = 0;
	int fd = 0;
	while (a > 0 && k == 0)
	{
		i = ft_strlen(s->arg[a]);
		while (i > 0 && k == 0)
		{
			if (s->arg[a][i] == '<' || s->arg[a][i] == '>')
				k = 1;
			i--;
		}
		if (k == 0)
			a--;
	}
	create_files(s);
	if (s->arg[a][i + 2] == '>')
		fd = open(get_name(s, a, i + 1), O_RDWR | O_CREAT | O_APPEND,S_IRWXU);
	else
		fd = open(get_name(s, a, i + 1), O_RDWR | O_CREAT | O_TRUNC,S_IRWXU);
	return (fd);
}

void	ft_putstr_fd_exep(char *str, int fd)
{
	int i = 0;
	int k = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			k = 1;
		if (k == 0)
		write(fd, &str[i], 1);
		i++;
	}
}

int print_echo(t_storage *s, char *cmd)
{
	int i = 1;
	int fd = 1;
	if (is_redirection(s))
		fd = do_redirection(s);
	if (s->paramc == 1)
	{
		write(fd, "\n", 1);
		return (1);
	}
	i = 1;
	if (ft_strncmp(s->arg[1], "-n", ft_strlen(s->arg[1])) == 0)
		i = 2;
	while (i < s->paramc)
	{
		ft_putstr_fd_exep(s->arg[i], fd);
		i++;
		if (i < s->paramc)
			write(fd, " ", 1);
	}
	if (ft_strncmp(s->arg[1], "-n", ft_strlen(s->arg[1])) == 0)
		return (1);
	write(fd, "\n", 1);
	return (1);
}
