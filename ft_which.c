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

//from chatGPT

void ft_which()
{
    char cmd[] = "/usr/bin/which";
    char *argVec[] = {"which", "ls", NULL};
    char *envVec[] = {NULL};
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(fd[0]); // Close read end
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(fd[1]); // Close write end
        if (execve(cmd, argVec, envVec) == -1)
        {
            perror("execve");
            exit(errno);
        }
    }
    else { // Parent process
        close(fd[1]); // Close write end
        char buf[1024];
        int numRead = 0;

        while ((numRead = read(fd[0], buf, sizeof(buf))) > 0) {
            write(STDOUT_FILENO, buf, numRead);
        }

        if (numRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        close(fd[0]); // Close read end
        wait(NULL);
    }
}
