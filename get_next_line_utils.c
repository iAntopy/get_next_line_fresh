/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:38:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/09 18:15:56 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

int	malloc_free_p(size_t size, void **ptr)
{	
	if (size)
	{
//		printf("malloc : of size %zu\n", size);
		*ptr = malloc(size);
//		printf("malloc : new ptr %p\n", *ptr);
		return (*ptr != NULL);
	}
	else if (ptr && *ptr)
	{
//		printf("free : ptr %p\n", *ptr);
		free(*ptr);
		*ptr = NULL;
	}
	return (1);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (*(str++))
		len++;
	return (len);
}

int	join_swap(char **old, char *new, size_t n)
{
	char	*s;
	char	*c;
	char	*line;
	size_t	oldlen;

//	printf("join : start new (%s)\n", new);
	if (!new)
		return (0);
	if (n == SIZE_MAX)
		while (new[++n])
			continue ;
//	printf("join : old (%s), new (%s), n = %zu\n", *old, new, n);
//	printf("join : new first char is '\\0' ? %s\n", (*new == '\0')?"TRUE":"FALSE");
	if (!n || (new[0] == '\0'))
	{
//		printf("join : !n ? %d, *new == \\0 ? %s\n", !n, (*new == '\0')?"TRUE":"FALSE");
//		printf("join current *old : %s\n", *old);
		malloc_free_p(0, (void **)old);
//		printf("join : new old : %s\n", *old);
		return (1);
	}
	oldlen = ft_strlen(*old);
//	printf("join : trying to malloc %zu bytes of mem\n", oldlen + n + 1);
	if (!malloc_free_p(sizeof(char) * (oldlen + n + 1), (void **)&line))
		return (0);
	s = *old;
	c = line;
	if (s)
		while (*s)
			*(c++) = *(s++);
	malloc_free_p(0, (void **)old);
	*old = line;
	while (n-- && *new)
		*(c++) = *(new++);
	*c = '\0';
	return (1);
}
/*
typedef struct s_lst
{
	s_lst	*next;
	char	*str;
}	t_lst;

void	lst_push(t_lst **lst, char *str_p)
{
	t_lst	*elem;

	elem = malloc(sizeof(t_lst));
	if (!elem)
		return ;
	if (lst && *lst)
		elem->next = NULL;
	elem->str = str_p;
	*lst = elem;
}

int	main()
{
	char	buff[] = "Salut comment";
	char	buff2[] = " ca va.";
	t_lst	*fu;

	fu = NULL;
	lst_push(&fu);

}*/
