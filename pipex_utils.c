/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:27:46 by lsun              #+#    #+#             */
/*   Updated: 2023/02/14 17:31:17 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char** get_env (char** env)
{
	int i;
	char *path;
	char** path_env;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
			break;
		else
			i++;
	}
	path = ft_substr(env[i], 4, ft_strlen(env[i]));//free?
	path_env = ft_split(path, ':'); // free_char?
	return(path_env);
}

void get_path(char **env, t_pipex *pipex)
{
	int i;
	char **path_env;

	i = 0;
	path_env = get_env(env);
	while (path_env[i])
	{
		pipex->cmd1_path = ft_strjoin(path_env[i], pipex->cmd1); // free
		if (access(pipex->cmd1_path, X_OK) == 0)
			break;
		i++;
	}
	i = 0;
	while (path_env[i])
	{
		pipex->cmd2_path = ft_strjoin(path_env[i], pipex->cmd2); // free
		if (access(pipex->cmd2_path, X_OK) == 0)
			break;
		i++;
	}
}

void free_char(char** str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}


void free_all(t_pipex *pipex)
{
	free_char(pipex->cmd1_args);
	free_char(pipex->cmd2_args);
	free(pipex);
}

int close_all(t_pipex *pipex, int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
	if (pipex->fd[0] > 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] > 0)
		close(pipex->fd[1]);
	return(0);
}
