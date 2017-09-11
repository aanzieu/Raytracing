/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_render_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:17:41 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/11 17:18:44 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

/* ===============================================================
 *
 *                          RENDER DEMO
 *
 * ===============================================================*/

void ui_widget_render(struct nk_context *ctx, struct media *media, float height)
{
	(void)media;
	nk_layout_row_static(ctx, height, WIN_WIDTH, 1);
}

void load_video_buffer(int *a_h, unsigned char *video_buffer)
{
	int i;
	t_color tmp;

	for (i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
	{
		tmp = int_to_rgb(a_h[i]);
		video_buffer[4 * i + 0] = tmp.r;
		video_buffer[4 * i + 1] = tmp.g;
		video_buffer[4 * i + 2] = tmp.b;
		video_buffer[4 * i + 3] = 255;
	}
}

struct nk_image screen_load(int *a_h, unsigned char *video_buffer)
{
	int x,y;//,n;
	GLuint tex;

	x = WIN_WIDTH;
	y = WIN_HEIGHT;

	load_video_buffer(a_h, video_buffer);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, video_buffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	return nk_image_id((int)tex);
}

void	render_scene(struct nk_context *ctx, struct media *media, int *a_h, t_world *world)
{
	static struct nk_image screen;
	struct nk_vec2	pos;
	// (void)a_h;

	nk_style_set_font(ctx, &media->font_20->handle);
	if(nk_begin(ctx, world->title, nk_rect((world->screen.width - WIN_WIDTH) / 2, (world->screen.height - WIN_HEIGHT) / 2, WIN_WIDTH - 50, WIN_HEIGHT + 50),
			NK_WINDOW_MOVABLE|NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_TITLE|NK_WINDOW_BACKGROUND))
	{
		if((world->reload_buffer == 1 && world->redraw == 0) || world->redraw == 3)
		{
			// if((screen.handle.ptr) != NULL){
			// 	screen.handle.ptr = NULL;}
			screen = screen_load(a_h, world->video_buffer);
			world->reload_buffer = 0;
		}
		pos = nk_window_get_position(ctx);
		world->pos_render.x = pos.x;
		world->pos_render.y = pos.y;
		ui_widget_render(ctx, media, WIN_HEIGHT);
		nk_image(ctx, screen);
	/*------------------------------------------------
	 *                  SELECTED OBJET
	 *------------------------------------------------*/
		mousepress_middle(ctx, world, pos);
		mousepress_left(ctx, world, pos);
		if((key_press(ctx, world)))
			world->redraw = 1;
	}
	

	if(world->redraw == 3)
	{
		nk_clear(ctx);
		world->redraw = 0;
	}

	nk_end(ctx);
}