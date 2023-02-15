/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:29:59 by lsun              #+#    #+#             */
/*   Updated: 2023/02/16 00:46:22 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

	if (argc != 5)
		exit(1);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		exit(1);
	if (pipex_init(pipex, argv) == 1)
		exit(1);
	if (get_path(env, pipex) == 1)
		exit(1);
	if (get_pipe(pipex) == 1)
		exit(1);
	free_all(pipex);
	return (0);
}
