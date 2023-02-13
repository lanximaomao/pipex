/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:06:27 by linlinsun         #+#    #+#             */
/*   Updated: 2023/02/13 01:20:22 by linlinsun        ###   ########.fr       */
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
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_cmd
{
	char* name;
	char* arg;

} t_cmd;

t_cmd get_cmd(char* input)
{
	t_cmd cmd;
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		len++;
	}
	cmd.name = (char*)malloc(sizeof(char)*(len+1));
	//remember to free
	cmd.name[len] = '\0';
	i = 0;
	while (i < len)
	{
		cmd.name[i] = input[i];
		len--;
		i++;
	}
	j = 0;
	while (input[i] != '\0')
	{
		cmd.arg[j] = input[i];
		i++;
		j++;
	}
	printf("my cmd is %s\n", cmd.name);
	return(cmd);
}


int main(int argc, char** argv)
{
	//char cmd[] = "/bin/ls";
	//char *argVec[] = {"ls", NULL};
	//char *envVec[] = {NULL};
	//execve(cmd, argVec, envVec);
	//printf("%s\n", argv[0]);
	//printf("%s\n", argv[1]);
	//printf("%s\n", argv[2]);
	//printf("%s\n", argv[3]);
	//printf("%s\n", argv[4]);

	char* outfile;
	char* infile;
	int i;
	int count;
	char **input;
	t_cmd cmd_tt;

	count = argc - 3;
	outfile = strdup(argv[argc - 1]);
	infile = strdup(argv[1]);
	input = (char**)malloc(sizeof(char*)*(count+1));

	printf("count number is %d\n", count);
	printf("outfile %s\n", outfile);
	printf("infile %s\n", infile);

	i = 0;
	while (i + 2 < argc - 1)
	{
		input[i] = argv[i + 2];
		printf("cmd i is %s\n", input[i]);
		cmd_tt = get_cmd(input[i]);
		printf("my command is %s", cmd_tt.name);
		printf("my command arguments are %s", cmd_tt.arg);
		i++;
	}



	// free(outfile);
	// free(infile);
	return (0);
}
