#include "minishell.h"

char    **ft_free(char **tab, int a)
{
        a--;
        while (a >= 0)
        {
                free(tab[a]);
                a--;
        }
        free(tab);
        return (0);
}


int	is_accent(int i, char const *s, int *size)
{
	int count = 0;
	int over = 0;
	if (s[i] != '"' && s[i] != 39)
		return (i);
	while (over == 0)
	{
	while (s[i] && s[i] == '"' || s[i] == 39)
	{
		count++;
		i++;
	}
	while (s[i] && (s[i] != '"' && s[i] != 39))
		i++;
	while (s[i] && s[i] == '"' || s[i] == 39)
	{
		i++;
		count++;
	}
	if (count % 2 == 1)//(s[i] == '"' || s[i] == 39 && (count % 2 == 1))
					over = 0;
				else
					over = 1;
	}		
	return (i);
}

char    **ft_tab(char const *s, char c, char **tab, int i, int a)
{
   	int over = 0;
	   int count = 0;
	int k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == 39)
		{
			while (over == 0)
			{
				while (s[i] && s[i] == '"' || s[i] == 39)
				{
					i++;
					count++;
				}
				while (s[i] && s[i] != '"' && s[i] != 39)
					tab[a][k++] = s[i++];
				while (s[i] && s[i] == '"' || s[i] == 39)
				{
					i++;
					count++;
				}
					if (count % 2 == 1)//(s[i] == '"' || s[i] == 39 && (count % 2 == 1))
					over = 0;
				else
					over = 1;
			}
		over = 0;
		}
		if (s[i] == c || s[i] == '\0')
		{
			tab[a][k] = '\0';
			return (tab);
		}
		else
			tab[a][k++] = s[i++];
	}
	return (tab);
}


int		is_last(char const *s, int i, char c)
{
	while (s[i] != '\0')
	{
		if (s[i] != '"' && s[i] != c && s[i] != 39)
			return (1);
		i++;
	}
	return (0);
}
int             size(char const *s, char c)
{
        int size;
        int i;

        i = 0;
        size = 0;
        if (s[0] != '\0' && s[0] != c)
                size = 1;
        while (s[i] == c)
                i++;
        while (s[i] != '\0')
        {
			i = is_accent(i, s, &size);
                if (s[i] == c)
                {
					if (is_last(s, i, c) > 0)
                        	size++;
                        while (s[i] == c && s[i + 1] != 39 && s[i + 1] != '"')
                                i++;
                }
                if (s)
                        i++;
        }
        return (size);
}

int		size_str(char const *s, int i, char c, int *k)
{
	int over = 0;
	int count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == 39)
		{
			while (over == 0)
			{
				while (s[i] && s[i] == '"' || s[i] == 39)
				{
					i++;
					count++;
				}
				while (s[i] && s[i] != '"' && s[i] != 39)
				{
					i++;
					*k = *k + 1;
				}
				while (s[i] == '"' || s[i] == 39)
				{
					count ++;
					i++;
				}
				if (count % 2 == 1)//(s[i] == '"' || s[i] == 39 && (count % 2 == 1))
					over = 0;
				else
					over = 1;
			}
		*k = *k + 1;
		over = 0;
		}
		if (s[i] == c || s[i] == '\0')
			return (i);
		else
		{
			i++;
			*k = *k + 1;
		}
	}
	return (i);

}
char    **ft_split(char const *s, char c, t_storage *stru)
{
        char    **tab;
        int             k;
        int             i;
        int             a;
		int tmp = 0;

        i = 0;
        k = 0;
        a = 0;
        if (!(tab = malloc(sizeof(char *) * (size(s, c) + 1))))
                return (0);
		stru->paramc = size(s, c);
        while (s[i] == c && s[i] != '\0')
                i++;
        while (s[i] != '\0')
        {
			tmp = i;
			i = size_str(s, i, c, &k);
			//printf("nbr = %d\n", k);
             if (!(tab[a] = malloc(sizeof(char) * (k +1 ))))
                 return (ft_free(tab, a));
			ft_tab(s, c, tab, tmp, a);
			a++;
            k = 0;
            while (s[i] == c)
                i++;
        }
		tab[a] = 0;
        return (tab);
}
