/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:14:19 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/26 16:25:12 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "nuklear.h"
#include "gui.h"

int	key_press(struct nk_context *ctx, t_world *world)
{
	if (ctx->input.keyboard.keys[NK_KEY_L].down)
		world->keys.light_none = 1;
	else if (ctx->input.keyboard.keys[NK_KEY_K].down)
		world->keys.light_none = 0;
	else
		return (0);
	return (1);
}
