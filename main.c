#include "minishell.h"


int   ft_exit()
{
  exit;
}

int ft_error(char *str)
{
  ft_putstr_fd(str, 1);
  return (0);
}
int suite(t_storage *s)
{
 // ft_free(s->line[0][0]);
}

int ft_count(char *str, char c)
{
  int i = 0;
  int o = 0;
  while (str[i])
  {
    if (str[i] == c)
      o++;
    i++;
  }
  return (o);
}

int    ft_strstr(char *str,char *to_find, int n)
{
        int i;
        int j;

        i = 0;
        j = 0;
        while (str[i] != '\0' && n > 0)
        {
                n = n + j;
                j = 0;
                while (str[i + j] == to_find[j] && n > 0)
                {
                        j++;
                        n--;
                        if (to_find[j] == '\0' && (str[i - 1] == ' ' || i == 0)  && (str[i + j] == ' ' || str[i + j] == '\0'))
                          return (j + 1);
                }
                i++;
                n--;
        }
        return (-1);
}

int   ft_builtin(t_storage *s, char *cmd, int i)
{
  if (i == 1)
    print_cd(s, cmd);
  if (i == 2)
    print_echo(s, cmd);
  if (i == 3)
    print_pwd(s);
  if (i == 4)
    print_export(s);
  
  return (1);
}
int   is_builtin(char *cmd, t_storage *s)
{
  if (ft_strncmp(s->arg[0], "cd", ft_strlen(s->arg[0])) == 0)
    return (1);
  if (ft_strncmp(s->arg[0], "echo", ft_strlen(s->arg[0])) == 0)
    return (2);
  if (ft_strncmp(s->arg[0], "pwd", ft_strlen(s->arg[0])) == 0)
    return (3);
  if (ft_strstr(s->arg[0], "export", ft_strlen(s->arg[0])) > -1)
    return (4);
  if (ft_strncmp(s->arg[0], "unset", ft_strlen(s->arg[0])) == 0)
    return (5);
  if (ft_strncmp(s->arg[0], "env", ft_strlen(s->arg[0])) == 0)
    return (6);
  if (ft_strncmp(s->arg[0], "exit", ft_strlen(s->arg[0])) == 0)
    return (7);
  return (0);
}

int exec(char *cmd, t_storage *s)
{
  int i;
  s->arg = ft_split(cmd, ' ', s);
  	i = 0;
  i = is_builtin(cmd, s);
if (i > 0)
    ft_builtin(s, cmd, i);
 else
 {
   ft_putstr_fd("dmg\n", 1);
 }
  //printf("%s\n", cmd);
}

char *get_arg_cd(char *cmd, char *built)
{
  int i;
  int a = 0;
char *new; 
  i = ft_strstr(cmd, built, ft_strlen(cmd));
  while (cmd[i] && cmd[i] == ' ')
    i++;
  while (cmd[i] && cmd[i] != ' ')
  {
    i++;
    a++;
  }
  if (!(new = malloc(sizeof(char) * a + 1)))
    exit;
  i = ft_strstr(cmd, built, ft_strlen(cmd));
  a = 0;
  while (cmd[i] && cmd[i] == ' ')
    i++;
  while (cmd[i] && cmd[i] != ' ')
  {
    new[a] = cmd[i];
    i++;
    a++;
  }
  new[a] = '\0';
  return (new);
}

char *split_line(char *str, int c)
{
  int i = 0;
  int j = 0;
  int a = 0;
  char *new;
  while (str[i] && a < c)
  {
    if (str[i] == ';')
      a++;
    i++;
  }
  a = i;
  while (str[i] && str[i] != ';')
  {
    i++;
    j++;
  }
    if (!(new = malloc(sizeof(char) * j + 1)))
      exit;
    i = a;
    j = 0;
    while (str[i] && str[i] != ';')
    {
      new[j] = str[i];
      i++;
      j++;
    }
    new[j] = '\0';
    return (new);
}

int prompt()
{
  char *str;
  str = malloc(sizeof(char) * 200);
  getcwd(str, 200);
  ft_putstr_fd(str, 1);
  ft_putstr_fd(" > ", 1);
}

int start(t_storage *s)
{
   int fd;
  int i = 0;
  int c = -1;
  while (1)
  {
    c = -1;
  prompt();
    get_next_line(1, &s->line);
    s->sep_count = ft_count(s->line, ';');
    while (c < s->sep_count)
    {
        c++;
        exec(split_line(s->line, c), s);
    }
  }
}

int main(int ac, char **av, char **envp)
{
    t_storage s;

    s.env = envp;
    start(&s);
    return (0);
}
