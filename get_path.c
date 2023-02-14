#include "pipex.h"

char	**get_env(char **env)
{
	int		i;
	char	*path;
	char	**path_env;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H')
			break ;
		else
			i++;
	}
	path = ft_substr(env[i], 4, ft_strlen(env[i]));
	path_env = ft_split(path, ':');
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
		free(pipex->cmd1_path);
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
		free(pipex->cmd2_path);
		i++;
	}
	return (0);
}

int	get_path(char **env, t_pipex *pipex)
{
	int		i;
	char	**path_env;

	i = 0;
	path_env = get_env(env);
	get_path_cmd1(path_env, pipex);
	get_path_cmd2(path_env, pipex);
	free_char(path_env);
	return (0);
}
