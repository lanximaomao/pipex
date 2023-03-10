/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:01:43 by lsun              #+#    #+#             */
/*   Updated: 2023/02/16 19:14:37 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_path(t_pipex *pipex)
{
	int		i;
	char	**path_env;

	i = 0;
	path_env = get_env(pipex->env);
	if (!path_env)
		return (1);
	if (get_path_cmd1(path_env, pipex) == 1)
		return (1);
	if (get_path_cmd2(path_env, pipex) == 1)
		return (1);
	free_char(path_env);
	return (0);
}

char	**get_env(char **env)
{
	int		i;
	char	*path;
	char	**path_env;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	path = ft_substr(env[i], 5, ft_strlen(env[i]));
	if (!path)
		return (NULL);
	path_env = ft_split(path, ':');
	if (!path_env)
		return (NULL);
	free(path);
	return (path_env);
}

int	get_path_cmd1(char **path_env, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (path_env[i])
	{
		pipex->cmd1_path = ft_strjoin(path_env[i], pipex->cmd1);
		if (!pipex->cmd1_path)
			return (1);
		if (access(pipex->cmd1_path, X_OK) == 0)
			break ;
		if (pipex->cmd1_path)
		{
			free(pipex->cmd1_path);
			pipex->cmd1_path = NULL;
		}
		i++;
	}
	return (0);
}

int	get_path_cmd2(char **path_env, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (path_env[i])
	{
		pipex->cmd2_path = ft_strjoin(path_env[i], pipex->cmd2);
		if (!pipex->cmd2_path)
			return (1);
		if (access(pipex->cmd2_path, X_OK) == 0)
			break ;
		if (pipex->cmd2_path)
		{
			free(pipex->cmd2_path);
			pipex->cmd2_path = NULL;
		}
		i++;
	}
	return (0);
}
