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
  if (i == 5)
    print_unset(s);
  if (i == 6)
    print_env(s);
  if (i == 7)
    exit(0);
  return (1);
}

int   is_builtin(char *cmd, t_storage *s)
{
 if (ft_strstr(s->arg[0], "cd", ft_strlen(s->arg[0])) > -1)
    return (1);
 if (ft_strstr(s->arg[0], "echo", ft_strlen(s->arg[0])) > -1)
    return (2);
 if (ft_strstr(s->arg[0], "pwd", ft_strlen(s->arg[0])) > -1)
    return (3);
  if (ft_strstr(s->arg[0], "export", ft_strlen(s->arg[0])) > -1)
    return (4);
   if (ft_strstr(s->arg[0], "unset", ft_strlen(s->arg[0])) > -1)
    return (5);
 if (ft_strstr(s->arg[0], "env", ft_strlen(s->arg[0])) > -1)
    return (6);
   if (ft_strstr(s->arg[0], "exit", ft_strlen(s->arg[0])) > -1)
    return (7);
  return (0);
}

char   *comp_var(char *var, t_storage *s)
{
  int i = 0;
  int n = 0;
  int a = 0;
  char *new;
//    printf("%s\n", var);
  while (s->env[a] && n == 0)
  {
      while (s->env[a][i] && s->env[a][i] != '=')
        i++;
       if (ft_strncmp(s->env[a], var, i) == 0)
       {
          new = ft_strdup(s->env[a] + (i + 1));
          n++;
             //  printf("%s\n", new);
       }
    a++;
    i = 0;
  }
//  printf("yoyo\n");
  if (n == 0)
    new = NULL;
  return (new);
}

char  *get_var(char *cmd, int i, t_storage *s)
{
  char *var;
  int a = 0;
  int tmp = i;
  char *var2;
  while (cmd[i] && ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9')))
      i++;
  if (!(var = malloc(sizeof(char) * (i - tmp + 1))))
      exit ;
  i = tmp;
  while (cmd[i] && ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9')))
      var[a++] = cmd[i++];
  var2 = comp_var(var, s);
  return(var2);
}

char *replace_var(char *cmd, char *var, int i, t_storage *s)
{
  int a = 0;
  int n  = 0;
  int tmp = i - 2;
  char *new;
   while (cmd[i] && ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9')))
  {
    i++;
    a++;
  }
  if (var != NULL)  
    n = ft_strlen(var);
  if (!(new = malloc(sizeof(char) * (ft_strlen(cmd) - a + n + 1))))
    exit ;
  i = 0;
  while (i < tmp + 1)
  {
    new[i] = cmd[i];
    i++;
  }
   int k = 0;
  a = i + a + 1;
  /*if (var == NULL)
    i = i + 2;*/
  if (var != NULL)
  {
    while (var[k]) 
      new[i++] = var[k++];
  }
    while (cmd[a])
      new[i++] = cmd[a++];
      new[i] = '\0';
      return (new);
}

char    *swap_env(char *cmd, t_storage *s)
{
  int i = 0;
  char  *var;
  int a = 0;
  while (cmd[i])
  {
    if (cmd[i] == '$')
    {
      i++;
      var = get_var(cmd, i, s);
      cmd = replace_var(cmd, var, i, s);
     // printf("%s\n", cmd);
      //i = 0;
    }
    i++;
  }
  return (cmd);
}

int   set_param(t_storage *s)
{
  int a = 0;
  int i = 0;
  int count = 0;
  while (s->arg_all[a])
  {
    while (s->arg_all[a][i])
    {
        if (s->arg_all[a][i] == '|')
        {
          if (count == 0)
            count = 2;
          else
          count++;
        }
      i++;
   }
  a++;
  i = 0;
}
if (count == 0)
  count = 1;
return (count);
}


char **split_cmd(t_storage *s, int count)
{
  int i = 0;
  int  a = 0;
  int count2 = 0;
  int tmp = 0;
  char **new;
  s->in = 0;
  s->out = 0;
  if (s->count == 1)
    return (s->arg_all);
  while (s->arg_all[a])
  {
    if (s->arg_all[a][0] == '|')
    {
      if (count2 == count)
        break ;
      count2++;
        tmp = a + 1;
    }
    a++;
  }
  if (!(new = malloc(sizeof(char *) * a - tmp + 1)))
    exit(0);
  if (tmp > 0 && s->arg_all[tmp - 1][0] == '|')
    s->in = 2;
  while (tmp < a)
  {
    new[i] = ft_strdup(s->arg_all[tmp]);
    i++;
    tmp++;
  }
  new[i] = 0;
  //printf("ICI tmp + 1= %d = %s\n",tmp +1 , s->arg_all[tmp]);
if (tmp + 1 < s->paramc && s->arg_all[tmp][0] == '|')
{
  s->out = 2;
}
  return (new);
}

int   find_in_out(t_storage *s)
{
  int a = 0;
  s->fd = 0;
  int i = 0;
    while (s->arg[a])
    {
      while (s->arg[a][i])
      {
        if (s->arg[a][i] == '<')
        {
            s->in = 3;
        }
        i++;
      }
      a++;
      i = 0;
    }
    if (s->in == 0)
      s->in = 1;
    a = 0;
    i = 0;
    while (s->arg[a])
    {
      while (s->arg[a][i])
      {
        if (s->arg[a][i] == '>')
            s->out = 3;
        i++;
      }
      a++;
      i = 0;
    }
    if (s->out == 0)
      s->out = 1;
    if (s->in == 3)  
      s->fd = do_redirection(s, '<');
    if (s->out == 3)
	{
      s->fd = do_redirection(s, '>');
	}
}

int   *make_pipe(t_storage *s)
{
  int i = 0;
  int *pipefd;
  if (!(pipefd = malloc(sizeof(int) * (s->count - 1) * 2 + 1)))
      exit(0);
	pipefd[(s->count - 1) * 2] = 0;
    return (pipefd);
}

int exec(char *cmd, t_storage *s)
{
  int i;

 cmd = swap_env(cmd, s);
 int a = 0;
 int status;
 int k = 0;
 char sop[3];
 sop[0] = ' ';
 sop[1] = '|';
 sop[2] = '\0';
 pid_t pid;
  s->arg_all = ft_split(cmd, sop, s);
    s->count = set_param(s);
s->current = 0;
int count = 0;
a = 0;
int c = 0;
s->pipefd = make_pipe(s);
while (count < s->count - 1)
{
	pipe(s->pipefd + c);
	c = c + 2;
	count++;
}
count = 0;
  while (s->current < s->count)
  {
      s->arg_count = 0;
	 s->arg = split_cmd(s, s->current);
	find_in_out(s);
    while (s->arg[s->arg_count])
        s->arg[s->arg_count++];
  	i = 0;
    i = is_builtin(cmd, s);
   	if (i > 0)
     	ft_builtin(s, cmd, i);
	else
	{
		pid = fork();
		if (pid == 0)
		{
     		do_shell(s);
		}
					s->k++;
	}
  a = 0;
  s->current++;
	}
	
int cl = (s->count - 1) * 2;
cl--;
	while (cl > 0)
		close(s->pipefd[cl--]);
	while (s->k > -1)
	{
		waitpid(-1, &status, 0);
		s->k--;
	}
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
  ft_putstr_fd("ICI CEST PARIS", 1);
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
