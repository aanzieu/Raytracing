/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/16 10:48:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include "../includes/display.h"
#include "../libft/libft.h"
#include "./cuda/cudaheader/gpu_rt.cuh"
#include "../frameworks/SDL2.framework/Headers/SDL.h"

void	render(t_world *world)
{
	int x;
	int y;
	int color = 0;

	y = 0;
	while (y < world->viewplane.y_res)
	{
		x = 0;
		while (x < world->viewplane.x_res)
		{
			// color = ray_tracer(world, x, y);
			pixel_to_image(world->window.screen, x, y, color);
			x++;
		}
		y++;
	}
}
