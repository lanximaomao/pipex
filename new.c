int	get_pipe(t_pipex *pipex)
{
	int	fd[2];
	int	pid1;
	int status;

	if (pipe(fd) == -1)//perror
		return(1);
	pid1 = fork();
	if (pid1 == -1)//perror
		return(1);
	else if (pid1 == 0)
		pipe_child1(pipex, fd[0], fd[1]);
	waitpid(pid1, &status, 0);
	pipe_child2(pipex, fd[0], fd[1]);
	close_all(pipex, fd[0], fd[1]);
	return (0);
}
