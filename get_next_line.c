/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:37:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/09 19:51:57 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

int	scan_for_nl(char *str, size_t *idx)
{
//	printf("scan : start\n");
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

char	*clear_mem_err(char **buff, char **line, char *rems[OPEN_MAX])
{
	int	i;

	printf("clear : ALL!\n");
	printf("clear : buff ptr %p, line ptr %p, rems ptr %p\n", *buff, *line, rems);
	i = -1;
	printf("clr : freeing buff\n");
	if (*buff)
		malloc_free_p(0, (void **)buff);
	printf("clr freeing line\n");
	if (*line)
		malloc_free_p(0, (void **)line);
	printf("clr : freeing rems\n");
	while (++i < OPEN_MAX)
	{
		if (rems[i])
			malloc_free_p(0, (void **)&rems[i]);
	}
	return (NULL);
}

int	gnl_prep(char **rem, char **buff, char **line)
{
	size_t	nl_found;
	size_t	idx;
	char	*temp;

//	printf("prep : start\n");
	*buff = NULL;
	nl_found = scan_for_nl(*rem, &idx);
//	printf("prep : nl_found %zu, idx %zu\n", nl_found, idx);
	if (*rem)
	{
//		printf("prep : rem found : %s\n", *rem);
		temp = *rem;
		*rem = NULL;
		if (!nl_found || temp[idx] == '\0')
			*line = temp;
		else if (!join_swap(line, temp, idx)
			|| !join_swap(rem, temp + idx, SIZE_MAX)
			|| !malloc_free_p(0, (void **)&temp))
			return (0);
	}
//	printf("prep : trying malloc of size %d when nl was %s found\n", BUFFER_SIZE + 1, (!nl_found)?"NOT":"");
	if (!nl_found && !malloc_free_p(sizeof(char) * (BUFFER_SIZE + 1), (void **)buff))
		return (0);
//	printf("prep : buff ptr %p\n", *buff);
	return (1);
}

int	read_wrapper(int fd, char *buff, size_t *n_chrs)
{
	if (!buff)
		printf("read : trying to read in no buffer\n");
	*n_chrs = read(fd, buff, BUFFER_SIZE);
	buff[*n_chrs] = '\0';
//	printf("readwrap : buffer read : %s\n", buff);
	if (*n_chrs == SIZE_MAX)
		printf("read : quit due to INVALID FD\n");
	if (!(*n_chrs))
		*n_chrs = SIZE_MAX;
	if (!(*n_chrs) || *n_chrs == SIZE_MAX)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rems[OPEN_MAX];
	char		*line;
	char		*buff;
	size_t		idx;
	size_t		n_chrs;

	line = NULL;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (!gnl_prep(&rems[fd], &buff, &line))
		return (clear_mem_err(&buff, &line, rems));
	if (!buff && line)
		return (line);
	if (!buff && !line)
		printf("gnl : OOPS ! !buff && !line incident !\n");
	while (read_wrapper(fd, buff, &n_chrs) && !scan_for_nl(buff, &idx))
	{
//		printf("gnl : current line : %s\n", line);
		if (!join_swap(&line, buff, n_chrs))
			return (clear_mem_err(&buff, &line, rems));
	}
//	printf("gnl : while over. buff ptr %p, n_chrs %zu, idx : %zu\n", buff, n_chrs, idx);
//	printf("gnl : current rem : %s\n", rems[fd]);
	if (n_chrs != SIZE_MAX && scan_for_nl(buff, &idx)
			&& !(join_swap(&line, buff, idx)
			&& join_swap(&rems[fd], buff + idx, SIZE_MAX)))
		return (clear_mem_err(&buff, &line, rems));
//	printf("gnl : over with line : %s\n", line);
//	printf("gnl : over with rem : %s\n", rems[fd]);
//	if (rems[fd])
//		printf("gnl : rem is empty line : %s, %d\n", (rems[fd][0] == '\0')?"TRUE":"FALSE", (int)rems[fd][0]);

	malloc_free_p(0, (void **)&buff);
	return (line);
}
