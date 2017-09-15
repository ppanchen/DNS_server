/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:27:59 by ppanchen          #+#    #+#             */
/*   Updated: 2017/01/13 17:31:22 by ppanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strsub(char const *s, unsigned int start, size_t len) {
    size_t	i;
    char	*retstr;

    i = 0;
    if (!s)
        return (0);
    retstr = (char *)malloc(len + 1);
    if (!retstr)
        return (0);
    while (s[start] && i < len)
    {
        retstr[i] = s[start];
        start++;
        i++;
    }
    retstr[i] = 0;
    return (retstr);
}

char	*strjoin(char const *s1, char const *s2) {
    char	*ret;
    int		i;
    int		j;

    if (!s1)
        return (strdup(s2));
    if (!s2)
        return (strdup(s1));
    i = strlen((char *)s1) + strlen((char *)s2);
    ret = (char *)malloc(i + 1);
    if (!ret)
        return (0);
    i = -1;
    while (s1[++i])
        ret[i] = s1[i];
    j = 0;
    while (s2[j])
    {
        ret[i] = s2[j];
        i++;
        j++;
    }
    ret[i] = 0;
    return (ret);
}

void	join_free(char **retstr, char *buf) {
    char	*tmp;

    tmp = *retstr;
    *retstr = strjoin(*retstr, buf);
    free(tmp);
}

int		check_str(char **buf, char **line) {
	char	*n;
	char	*tmp;

	n = strchr(*buf, '\n');
	!n && (n = strchr(*buf, '\0'));
	*line = strsub(*buf, 0, n - *buf);
	tmp = *buf;
	*buf = strdup(n + 1);
	free(tmp);
	return (1);
}

void	dup_free(char **retstr, char **n)
{
	char	*tmp;

	tmp = *retstr;
	*retstr = **n ? strdup(*n + 1) : strdup(*n);
	free(tmp);
}

int		get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	char		*n;
	static char *retstr = NULL;

	if (retstr && strchr(retstr, '\n') != 0)
		return (check_str(&retstr, line));
	n = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		join_free(&retstr, buf);
		if ((n = strchr(retstr, '\n')) != 0)
			break ;
	}
	if ((ret == 0 && strlen(retstr) == 0) || ret == -1)
	{
		if (line)
			*line = "";
		return (line ? ret : -1);
	}
	!n && (n = strchr(retstr, '\0'));
	line && (*line = strsub(retstr, 0, n - retstr));
	dup_free(&retstr, &n);
	return (line ? 1 : -1);
}
