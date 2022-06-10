/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:05:43 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/09 22:01:01 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512 
# endif

# ifndef SIZE_MAX
#  define SIZE_MAX 0xffffffffffffffffULL
# endif

char	*get_next_line(int fd);
int		malloc_free_p(size_t size, void **ptr);
int		join_swap(char **old, char *new, size_t n);

#endif
