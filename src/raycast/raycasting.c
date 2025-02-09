#include "../../includes/cub3d.h"

static t_intersect calc_vertical_intersection(t_player *p, t_data *data, float ra)
{
	t_intersect	inter;
	int			dof = 0;
	float		Tan = tan(degToRad(ra));
	float		rx;
	float		ry;
	float		xo;
	float		yo;

	if (cos(degToRad(ra)) > 0.001)
	{
		rx = (((int)p->player_pos_x >> 6) << 6) + MAP_S;
		ry = (p->player_pos_x - rx) * Tan + p->player_pos_y;
		xo = MAP_S;
		yo = -xo * Tan;
	}
	else if (cos(degToRad(ra)) < -0.001)
	{
		rx = (((int)p->player_pos_x >> 6) << 6) - 0.0001;
		ry = (p->player_pos_x - rx) * Tan + p->player_pos_y;
		xo = -MAP_S;
		yo = -xo * Tan;
	}
	else
	{
		rx = p->player_pos_x;
		ry = p->player_pos_y;
		dof = 8;
		inter.rx = rx; inter.ry = ry; inter.dist = 1000000;
		return inter;
	}
	while (dof < 8)
	{
		int mx = (int)rx / MAP_S;
		int my = (int)ry / MAP_S;
		if (mx >= 0 && mx < data->map_width && my >= 0 && my < data->map_height &&
			data->map[my][mx] == 1)
			break;
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
	inter.rx = rx;
	inter.ry = ry;
	inter.dist = cos(degToRad(ra)) * (rx - p->player_pos_x) \
		- sin(degToRad(ra)) * (ry - p->player_pos_y);
	return inter;
}

static t_intersect calc_horizontal_intersection(t_player *p, t_data *data, float ra)
{
	t_intersect inter;
	int dof = 0;
	float Tan = tan(degToRad(ra));
	float rx, ry, xo, yo;
	if (sin(degToRad(ra)) > 0.001)
	{
		ry = (((int)p->player_pos_y >> 6) << 6) - 0.0001;
		rx = (p->player_pos_y - ry) * (Tan == 0 ? 0.0001 : 1.0 / Tan) + p->player_pos_x;
		yo = -MAP_S;
		xo = -yo * (Tan == 0 ? 0.0001 : 1.0 / Tan);
	}
	else if (sin(degToRad(ra)) < -0.001)
	{
		ry = (((int)p->player_pos_y >> 6) << 6) + MAP_S;
		rx = (p->player_pos_y - ry) * (Tan == 0 ? 0.0001 : 1.0 / Tan) + p->player_pos_x;
		yo = MAP_S;
		xo = -yo * (Tan == 0 ? 0.0001 : 1.0 / Tan);
	}
	else
	{
		rx = p->player_pos_x;
		ry = p->player_pos_y;
		dof = 8;
		inter.rx = rx; inter.ry = ry; inter.dist = 1000000;
		return inter;
	}
	while (dof < 8)
	{
		int mx = (int)rx / MAP_S;
		int my = (int)ry / MAP_S;
		if (mx >= 0 && mx < data->map_width && my >= 0 && my < data->map_height &&
			data->map[my][mx] == 1)
			break;
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
	inter.rx = rx;
	inter.ry = ry;
	inter.dist = cos(degToRad(ra)) * (rx - p->player_pos_x)
		- sin(degToRad(ra)) * (ry - p->player_pos_y);
	return inter;
}

t_intersect get_vertical_intersection(t_player *p, t_data *data, float ra)
{
	return calc_vertical_intersection(p, data, ra);
}

t_intersect get_horizontal_intersection(t_player *p, t_data *data, float ra)
{
	return calc_horizontal_intersection(p, data, ra);
}

void drawRays2D(mlx_image_t *img, t_player *p, t_data *data)
{
	int		r;
	int		ca;
	float	corrected_dist;
	int		lineH;
	int		lineOff;
	int		xStart;
	float	ra;

	draw_rect(img, 530, 0, 480, 160, 0x87CEFAFF);  // bleu clair (ciel)
	draw_rect(img, 530, 160, 480, 160, 0x00008BFF); // bleu foncer (sol)
	for (r = 0; r < 60; r++)
	{
		ra = FixAng(p->player_angle + 30 - r);
		t_intersect vert = get_vertical_intersection(p, data, ra);
		t_intersect horiz = get_horizontal_intersection(p, data, ra);
		t_intersect final;
		uint32_t rayColor = 0x00CC0080;

		if (vert.dist < horiz.dist)
		{
			final = vert;
			rayColor = 0x00990080;
		}
		else
			final = horiz;
		draw_line(img, (int)p->player_pos_x, (int)p->player_pos_y,
				  (int)final.rx, (int)final.ry, rayColor);

		ca = FixAng(p->player_angle - ra);
		corrected_dist = final.dist * cos(degToRad(ca));
		lineH = (MAP_S * 320) / (corrected_dist ? corrected_dist : 1);
		if (lineH > 320)
			lineH = 320;
		lineOff = 160 - (lineH >> 1);
		xStart = r * 8 + 530;
		draw_rect(img, xStart, lineOff, 8, lineH, 0xFF0000FF);
	}
}