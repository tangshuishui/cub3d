/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:52:43 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 17:59:28 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long long)(tv.tv_sec) *1000
	+ (unsigned long long)(tv.tv_usec) / 1000);
}

void	set_frame(t_game *game)
{
	unsigned long long	curr_time;

	curr_time = get_time_ms();
	game->frame_time = (curr_time - game->last_time) / 1000.0;
	game->last_time = curr_time;
	if (game->frame_time <= 0.00001)
		game->frame_time = 0.00001;
}
