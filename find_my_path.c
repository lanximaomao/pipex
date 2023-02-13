#include "pipex.h"

int find_my_path()
{
	//use which command
	int fd[2];
	int pid;
	char *arg[] = {"which", "ls", NULL};

	if(pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (pid == 0)
	{
		execve("/usr/bin/which", arg, NULL);
	}
	wait(NULL);
	get_next_line(fd[0]);
	close(fd[0]);
	close(fd[1]);
	return(0);
}

void ft_which()
{
	char cmd[] = "/usr/bin/which";
	char *argVec[] = {"which", "ls", NULL};
	char *envVec[] = {NULL};
	if (execve(cmd, argVec, envVec) == -1)
	{
		perror("execve");
		exit(errno);
	}
}


int main()
{
	//find_my_path();
	ft_which();
	return(0);
}
