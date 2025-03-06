/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagomad <amagomad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 07:29:26 by amagomad          #+#    #+#             */
/*   Updated: 2025/03/06 07:37:38 by amagomad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	compute_tex_y(int y, t_proj *proj, int tex_height)
{
	int		d;
	int		tex_y;

	d = (y - proj->draw_start_y) * 256;
	d = d - (proj->draw_end_y - proj->draw_start_y) * 128;
	tex_y = (d * tex_height) / ((proj->draw_end_y - proj->draw_start_y) * 256);
	return (tex_y);
}

int	compute_tex_x(int stripe, t_proj *proj, mlx_texture_t *tex)
{
	int		tex_x;
	double	temp;

	temp = stripe - (-proj->sprite_width / 2 + proj->sprite_screen_x);
	tex_x = (int)(temp * tex->width / (double)proj->sprite_width);
	return (tex_x);
}

static void	draw_sprite_line(t_draw_ctx *ctx, int y)
{
	int			tex_y;
	int			tex_x;
	uint8_t		*pixel;
	uint32_t	color;

	tex_y = compute_tex_y(y, ctx->proj, ctx->tex->height);
	if (tex_y < 0)
		return ;
	if (tex_y >= (int)ctx->tex->height)
		return ;
	tex_x = compute_tex_x(ctx->stripe, ctx->proj, ctx->tex);
	pixel = &ctx->tex->pixels[(tex_y * ctx->tex->width + tex_x) * 4];
	if (pixel[3] > 0)
	{
		color = (pixel[3] << 24) | (pixel[2] << 16) | \
				(pixel[1] << 8) | pixel[0];
		my_put_pixel(ctx->data, ctx->stripe, y, color);
	}
}

void	draw_sprite_stripe(t_data *data, int stripe, \
						t_proj *proj, mlx_texture_t *tex)
{
	t_draw_ctx	ctx;
	int			y;

	ctx.data = data;
	ctx.stripe = stripe;
	ctx.proj = proj;
	ctx.tex = tex;
	y = proj->draw_start_y;
	while (y < proj->draw_end_y)
	{
		draw_sprite_line(&ctx, y);
		y = y + 1;
	}
}
