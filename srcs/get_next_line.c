/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:48:44 by pleonel           #+#    #+#             */
/*   Updated: 2021/03/05 14:31:05 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

int	ft_trim_temp(char **line, char **temp, int start_new_line)
{
	int	i;

	if (start_new_line == -1 || !(*temp)[0])
		return (0);
	if (ft_strnjoin(line, *temp, start_new_line) == NULL)
		return (-1);
	i = start_new_line + 1;
	while (i < BUFFER_SIZE && (*temp)[i] != '\0')
	{
		(*temp)[i - (start_new_line + 1)] = (*temp)[i];
		(*temp)[i] = 0;
		i++;
	}
	i = i - (start_new_line + 1);
	while ((*temp)[i] != 0)
		(*temp)[i++] = 0;
	return (1);
}

int	ft_reading_next(int fd, char **temp, int *start_new_line, char **line)
{
	int	size_of_reading;

	while (1)
	{
		size_of_reading = read(fd, *temp, BUFFER_SIZE);
		if (size_of_reading == 0 && *line[0] == '\0')
			exit_ctrd();
		ft_putstr_fd("  \b\b", 2);
		(*temp)[size_of_reading] = '\0';
		if ((*start_new_line = ft_str_find_char(*temp, '\n')) == -1)
			ft_strnjoin(line, *temp, ft_strlen(*temp));
		else
		{
			if (g_exit.is_signal == 3)
			{
				free(*line);
				*line = ft_strdup("\0");
			}
			break ;
		}
		*start_new_line = -1;
	}
	return (size_of_reading);
}

int	ft_reading_line(int fd, char **temp, int *start_new_line, char **line)
{
	int			size_of_reading;

	size_of_reading = ft_reading_next(fd, temp, start_new_line, line);
	if (*start_new_line != -1)
		(*temp)[size_of_reading] = '\0';
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*temp;
	int			start_new_line;

	if (line == NULL || !(*line = ft_strdup("")) || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!temp)
	{
		if (!(temp = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		temp[0] = '\0';
	}
	else
	{
		if ((start_new_line = ft_str_find_char(temp, '\n')) != -1)
			return (ft_trim_temp(line, &temp, start_new_line));
		ft_trim_temp(line, &temp, ft_strlen(temp));
	}
	if (ft_reading_line(fd, &temp, &start_new_line, line) == -1)
		return (-1);
	if (ft_trim_temp(line, &temp, start_new_line) == 1)
		return (1);
	free(temp);
	temp = NULL;
	return (line ? 0 : -1);
}
