/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:05:43 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/27 13:24:54 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512 
# endif

# ifndef SIZE_MAX
#  define SIZE_MAX 0xffffffffffffffffULL
# endif

# ifdef FOPEN_MAX
#  define _OPEN_MAX_ FOPEN_MAX
# elif OPEN_MAX
#  define _OPEN_MAX_ OPEN_MAX
# elif _SC_OPEN_MAX
#  define _OPEN_MAX_ _SC_OPEN_MAX
# else
#  define _OPEN_MAX_ 65535
# endif

char	*get_next_line(int fd);
int		malloc_free_p(size_t size, void **ptr);
int		join_swap(char **old, char *new, size_t n);

#endif
