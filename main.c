/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:29:59 by lsun              #+#    #+#             */
/*   Updated: 2023/02/16 19:18:13 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;

	if (argc != 5)
	{
		ft_printf("Incorrect number of arguments!\n");
		exit(1);
	}
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		exit(1);
	pipex->env = env;
	pipex_init(pipex, argv);
	if (get_path(pipex) == 1)
		exit(1);
	if (get_pipe(pipex) == 1)
		exit(1);
	free_all(pipex);
	return (0);
}
