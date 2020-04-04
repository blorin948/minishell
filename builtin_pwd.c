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

char **create_env(t_storage *s)
{
	char **new;
	int i = 0;
	int a = 0;
	int count = 0;
	count = count_export(s);
	while (new[i])
	{
		i++;
		count++;
	}
	new = malloc(sizeof(char *) * count + 1);
	new = copy_env(s);
//	new[57] = malloc(sizeof(char) * 30);
	new[60] =  "une bonne buche";
	new[61] = 0;
	while (new[i])
		printf("i = %d | %s\n", i, new[i++]);

}
int	print_export(t_storage *s)
{
	int a = 0;
	int i = 0;
	//while (s->env[a])
	//	printf("%s\n", s->env[a++]);
	s->env = create_env(s);
}