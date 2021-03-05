/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:56:58 by pleonel           #+#    #+#             */
/*   Updated: 2021/03/05 16:36:57 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 40000
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *s1);
char	*ft_strnjoin(char **s1, char const *s2, size_t n_s2);
size_t	ft_strlen(const char *s);
int		ft_str_find_char(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
