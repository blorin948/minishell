/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 00:00:42 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 00:13:27 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
void 	ft_free2(char *s);
char 	*ft_strdup_n(char *src);
int		get_n(char *save);
int		get_next_line(int fd, char **line);
int		check_error(int fd, char **line);
char	*get_out(char *save);

#endif
