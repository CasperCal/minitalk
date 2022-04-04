/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaluwe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:27:40 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/04/04 11:13:14 by ccaluwe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(int i)
{
	if (i == 0)
	{
		write(1, "Error KILL\n", 12);
		exit(1);
	}
	if (i == 1)
	{
		write(1, "Error SIGACTION\n", 17);
		exit(1);
	}
}

void	ft_send_terminator(int pid)
{
	static int	i = 0;

	if (i <= 8)
		if (kill(pid, SIGUSR1) == -1)
			ft_error(0);
	i++;
}

void	ft_send(int pid, char *str)
{
	static int	bit = 0;
	static char	*str_tmp = 0;

	if (str)
		str_tmp = str;
	if (*str_tmp)
	{
		if ((((unsigned char)*str_tmp >> bit) % 2) == 0)
			if (kill(pid, SIGUSR1) == -1)
				ft_error(0);
		if ((((unsigned char)*str_tmp >> bit) % 2) == 1)
			if (kill(pid, SIGUSR2) == -1)
				ft_error(0);
		bit++;
		if (bit == 8)
		{
			str_tmp++;
			bit = 0;
		}
	}
	if (!(*str_tmp))
		ft_send_terminator(pid);
}

void	ft_sighandler(int sig, siginfo_t *info, void *context)
{
	static int	id;

	if (info->si_pid != 0)
		id = info->si_pid;
	(void)context ;
	if (sig == SIGUSR1)
		ft_send(id, NULL);
	if (sig == SIGUSR2)
		exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_sighandler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error(1);
	if (ac != 3)
	{
		write(1, "ERROR - use proper format: ./client <PID> <String>\n", 53);
		exit(EXIT_FAILURE);
	}
	ft_send(ft_atoi(av[1]), av[2]);
	while (1)
		pause();
	return (0);
}
