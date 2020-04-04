/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 23:06:23 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/09 18:18:24 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_out(char *save)
{
	int		i;
	int		a;
	char	*str;

	if (save == NULL)
		return (0);
	a = 0;
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	while (save[a] != '\0')
		a++;
	if (!(str = malloc(sizeof(char) * (a - i + 1))))
		return (0);
	i++;
	a = 0;
	while (save[i] != '\0')
		str[a++] = save[i++];
	str[a] = '\0';
	ft_free2(save);
	return (str);
}

int		check_error(int fd, char **line)
{
	if (line == NULL || fd == -1)
		return (-1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*save = NULL;
	char		buf[100 + 1];
	int			ret;
	char		*tmp;

	ret = 0;
	if (check_error(fd, line) < 0)
		return (-1);
	while ((get_n(save) == 0) && (ret = read(0, buf, 100)) > 0)
	{
		buf[ret] = '\0';
		tmp = save;
		save = ft_strjoin(save, buf);
		ft_free2(tmp);
		if (get_n(save) == 1)
			break ;
	}
	buf[ret] = '\0';
	*line = ft_strdup_n(save);
	if (get_n(save) == 1)
	{
		save = get_out(save);
		return (1);
	}
	ft_free2(save);
	return (0);
}
