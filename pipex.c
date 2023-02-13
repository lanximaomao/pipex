/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:06:27 by linlinsun         #+#    #+#             */
/*   Updated: 2023/02/13 15:57:12 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
** allowed function: open, close, read, write, malloc, free, perror, strerror, access,
** dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
*/

/*
** ./pipex infile "ls -l" "wc -l" outfile
*/

/*
** ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
** ./pipex infile "ls -l" "cat pipex.c" "grep 3 " outfile
*/

// /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki

//inplement the perror, stdrr;

#include "pipex.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

void find_my_path ()
{
	return;
}



void get_cmd(char ** cmd_wth_arg)
{
	char *cmd_path;
	int fd;

	cmd_path = ft_strjoin("/bin/", cmd_wth_arg[0]);


	fd = open("infile", O_RDWR);
	dup2(fd, 1);
	execve(cmd_path, cmd_wth_arg, NULL);
	close(fd);
}

void ft_ls()
{
	char cmd[] = "/bin/ls";
	char *argVec[] = {"ls", "-l", NULL};
	char *envVec[] = {NULL};
	if (execve(cmd, argVec, envVec) == -1)
	{
		perror("execve");
		exit(errno);
	}
}

//void ft_which()
//{
//	char cmd[] = "/usr/bin/which";
//	char *argVec[] = {"which", "ls", NULL};
//	char *envVec[] = {NULL};
//	if (execve(cmd, argVec, envVec) == -1)
//	{
//		perror("execve");
//		exit(errno);
//	}
//}

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


int main(int argc, char** argv)
{
	char* outfile;
	char* infile;
	int i;
	int count;
	char **input;
	char **cmd_with_arg;

	count = argc - 3;
	outfile = ft_strdup(argv[argc - 1]);
	infile = ft_strdup(argv[1]);
	input = (char**)malloc(sizeof(char*)*(count+1));

	//ft_printf("count number is %d\n", count);
	//ft_printf("outfile %s\n", outfile);
	//ft_printf("infile %s\n", infile);

	i = 0;
	while (i + 2 < argc - 1)
	{
		input[i] = argv[i + 2];
		//ft_printf("cmd %d is %s:\n", i, input[i]);
		cmd_with_arg = ft_split(input[i], ' ');
		//remember to free inside a loop
		//ft_printf("my command:  %s\n", cmd_with_arg[0]);
		//ft_printf("my command arguments: %s\n", cmd_with_arg[1]);
		//function call
		//ft_ls();
		ft_which();
		//get_cmd(cmd_with_arg);
		//find_my_path();
		i++;
	}
	// free(outfile);
	// free(infile);
	return (0);
}
