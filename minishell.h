#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>


typedef struct s_storage
{
    char **env;
    char *line;
    int sep_count;
    int test;
    int paramc;
    char **arg;

}               t_storage;

int	print_cd(t_storage *s, char *cmd);
char *get_arg_cd(char *cmd, char *built);
int print_echo(t_storage *s, char *cmd);
int ft_error(char *str);
char			**ft_split(char const *s, char c, t_storage *stru);
int is_redirection(t_storage *s);
int		print_pwd(t_storage *s);
int	print_export(t_storage *s);
