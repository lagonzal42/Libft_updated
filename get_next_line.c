/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <larraingonzalez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:50:20 by lagonzal          #+#    #+#             */
/*   Updated: 2023/05/31 13:50:20 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_depurate(char *save, int pos_lb);
static char	*ft_read_file(int fd, char *save);
static char	*ft_clean(char *s);

char	*get_next_line(int fd)
{
	static char *save;
	char		*lb;
	char		*ret;

	if (fd < 0)
		return (NULL);
	save = ft_read_file(fd, save);
	if (!save)
		return (NULL);
	lb = ft_strchr(save, '\n');
	if (!lb)
	{
		if (ft_strlen(save) == 0)
			ret = ft_strdup(save);
		ft_clean(save);
	}
	else
	{
		ret = ft_substr(save, 0, lb-save+1);
		save = ft_depurate(save, lb-save+1);
	}
	return (ret);
}

static char	*ft_read_file(int fd, char *save)
{
	int		readed;
	char	*reader;
	char	*holder;

	readed = 1;
	reader = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!reader)
		return (NULL);
	while (readed > 0 && ft_strchr(save, (int)'\n') == NULL)
	{
		holder = save;
		readed = read(fd, reader, BUFFER_SIZE);
		if (readed == -1)
			return (free(reader), ft_clean(save));
		reader[readed] = '\0';
		save = ft_strjoin(holder, reader);
		if (!save)
			return (free(reader), free(holder), ft_clean(save));
		free(holder);
	}
	return (free(reader), save);
}

static char	*ft_clean(char *s)
{
	free(s);
	s = NULL;
	return (s);
}

static char	*ft_depurate(char *save, int pos_lb)
{
	char	*dep;

	if ((int)(ft_strlen(save)) <= pos_lb)
		return (ft_clean(save));
	dep = ft_strdup(&save[pos_lb]);
	return (free(save), dep);
}