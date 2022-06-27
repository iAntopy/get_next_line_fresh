/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:31:22 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/27 13:31:30 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	scan_for_nl(char *str, size_t *idx)
{
	*idx = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*(str++) == '\n')
		{
			(*idx)++;
			return (1);
		}
		(*idx)++;
	}
	return (0);
}

char	*clear_mem_err(char **buff, char **line, char **rems)
{
	int	i;

	i = -1;
	if (*buff)
		malloc_free_p(0, (void **)buff);
	if (*line)
		malloc_free_p(0, (void **)line);
	while (++i < _OPEN_MAX_)
		if (rems[i])
			malloc_free_p(0, (void **)&rems[i]);
	return (NULL);
}

int	gnl_prep(char **rem, char **buff, char **line)
{
	size_t	nl_found;
	size_t	idx;
	char	*temp;

	*buff = NULL;
	nl_found = scan_for_nl(*rem, &idx);
	if (*rem)
	{
		temp = *rem;
		*rem = NULL;
		if (!nl_found || temp[idx] == '\0')
			*line = temp;
		else if (!join_swap(line, temp, idx)
			|| !join_swap(rem, temp + idx, SIZE_MAX)
			|| !malloc_free_p(0, (void **)&temp))
			return (0);
	}
	if (!nl_found
		&& !malloc_free_p(sizeof(char) * (BUFFER_SIZE + 1), (void **)buff))
		return (0);
	return (1);
}

int	read_wrapper(int fd, char *buff, size_t *n_chrs)
{
	*n_chrs = read(fd, buff, BUFFER_SIZE);
	if (!(*n_chrs) || *n_chrs == SIZE_MAX)
	{
		*n_chrs = SIZE_MAX;
		return (0);
	}
	buff[*n_chrs] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rems[_OPEN_MAX_];
	char		*line;
	char		*buff;
	size_t		idx;
	size_t		n_chrs;

	line = NULL;
	if (fd < 0 || fd >= _OPEN_MAX_ || BUFFER_SIZE < 1)
		return (NULL);
	if (!gnl_prep(&rems[fd], &buff, &line))
		return (clear_mem_err(&buff, &line, rems));
	if (!buff && line)
		return (line);
	while (read_wrapper(fd, buff, &n_chrs) && !scan_for_nl(buff, &idx))
		if (!join_swap(&line, buff, n_chrs))
			return (clear_mem_err(&buff, &line, rems));
	if (n_chrs != SIZE_MAX && scan_for_nl(buff, &idx)
		&& !(join_swap(&line, buff, idx)
			&& join_swap(&rems[fd], buff + idx, SIZE_MAX)))
		return (clear_mem_err(&buff, &line, rems));
	malloc_free_p(0, (void **)&buff);
	return (line);
}
