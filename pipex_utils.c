/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:27:46 by lsun              #+#    #+#             */
/*   Updated: 2023/02/14 20:36:02 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_all(t_pipex *pipex)
{
	free(pipex->cmd1);
	free(pipex->cmd2);
	free(pipex->cmd1_path);
	free(pipex->cmd2_path);
	free_char(pipex->cmd1_args);
	free_char(pipex->cmd2_args);
	free(pipex);
}

int	close_all(t_pipex *pipex, int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
	if (pipex->fd[0] > 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] > 0)
		close(pipex->fd[1]);
	return (0);
}
