/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:29:59 by lsun              #+#    #+#             */
/*   Updated: 2023/02/14 17:30:07 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char** argv, char** env)
{
	t_pipex *pipex;

	if (argc != 5)
		exit(1);
	pipex = malloc(sizeof(t_pipex));
	if (pipex_init(pipex, argv) == 1)
		exit(1);
	get_path(env, pipex);
	if (get_pipe(pipex) == 1)
		exit(1);
	free_all(pipex);
	return (0);
}
