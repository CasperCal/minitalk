/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaluwe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:12:02 by ccaluwe           #+#    #+#             */
/*   Updated: 2022/04/04 11:14:33 by ccaluwe          ###   ########.fr       */
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

void	ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	value = 0;
	static int				bitv = 1;
	static int				id = 0;

	if (info->si_pid != 0)
		id = info->si_pid;
	(void)context ;
	if (sig == SIGUSR1)
		value += 0;
	if (sig == SIGUSR2)
		value += bitv;
	bitv *= 2;
	if (bitv == 256)
	{
		bitv = 1;
		if (value == 0)
			if (kill(id, SIGUSR2) == -1)
				ft_error(0);
		if (value != 0)
			write(1, &value, 1);
		value = 0;
	}
	if (kill(id, SIGUSR1) == -1)
		ft_error(0);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_signal_handler;
	pid = getpid();
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_error(1);
		return (1);
	}
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
