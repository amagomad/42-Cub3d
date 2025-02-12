#include "../../includes/cub3d.h"

void draw_vertical_line(t_data *data, int x, int start_y, int end_y, uint32_t color)
{
    int y;

    y = start_y;
    while (y <= end_y)
    {
        my_put_pixel(data, x, y, color);
        y++;
    }
}

void raycasting(t_data *data)
{
	t_ray ray;
	//uint32_t *pixel_buffer = (uint32_t *)data->img->pixels;
    ray.x = 0;
	draw_rect(data, 0, 0, WIDTH, HEIGHT, data->ceiling_color);  // bleu clair (ciel)
	draw_rect(data, 0, 450, WIDTH, HEIGHT, data->floor_color); // bleu foncer (sol)
 	while (ray.x < WIDTH)
	{
		// Calculate ray position and direction
		ray.camera_x = 2 * ray.x / (double)WIDTH - 1; // x-coordinate in camera space
		ray.ray_dir_x = data->player->player_dir_x + data->player->plane_x * ray.camera_x;
		ray.ray_dir_y = data->player->player_dir_y + data->player->plane_y * ray.camera_x;

		// Which box of the map we're in
		ray.map_x = (int)(data->player->player_pos_x / TILE_SIZE);
		ray.map_y = (int)(data->player->player_pos_y / TILE_SIZE);

		// Length of ray from current position to next x or y-side

		// Length of ray from one x or y-side to next x or y-side
		if (ray.ray_dir_x == 0)
			ray.delta_dist_x = 1e30;
		else
			ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
		if (ray.ray_dir_y == 0)
			ray.delta_dist_y = 1e30;
		else
			ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
		// Direction to step in x or y direction (either +1 or -1)

		// Calculate step and initial side_dist
		if (ray.ray_dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (data->player->player_pos_x / TILE_SIZE - ray.map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (ray.map_x + 1.0 - data->player->player_pos_x / TILE_SIZE) * ray.delta_dist_x;
		}
		if (ray.ray_dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (data->player->player_pos_y / TILE_SIZE - ray.map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (ray.map_y + 1.0 - data->player->player_pos_y / TILE_SIZE) * ray.delta_dist_y;
		}

		// Perform DDA
		int hit = 0;  // was there a wall hit?
		int side;     // was a NS or a EW wall hit?
		while (hit == 0)
		{
			// Jump to next map square, either in x-direction, or in y-direction
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				side = 1;
			}
			// Check if ray has hit a wall
			if (data->map[ray.map_y][ray.map_x] > 0)
				hit = 1;
		}

		// Calculate distance projected on camera direction
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;

		// Calculate height of line to draw on screen
		int line_height = (int)(HEIGHT / perp_wall_dist);

		// Calculate lowest and highest pixel to fill in current stripe
		int draw_start = (-line_height / 2) + (HEIGHT / 2 - 100); // i added -100 because it look the ceiling
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = (line_height / 2) + (HEIGHT / 2 - 100);
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		mlx_texture_t *texture;
		if (data->map[ray.map_y][ray.map_x] == 2)
			texture = data->door_texture;  // Yellow
		else if (side == 0)
		{
			if (ray.ray_dir_x > 0)
				texture = data->ea_texture;
			else
				texture = data->we_texture;
		}
		else
		{
			if (ray.ray_dir_y > 0)
				texture = data->so_texture;
			else
				texture = data->no_texture;
		}
		float wall_x;

		if (side == 0)
			wall_x = data->player->player_pos_y / TILE_SIZE + perp_wall_dist * ray.ray_dir_y;
		else
			wall_x = data->player->player_pos_x / TILE_SIZE + perp_wall_dist * ray.ray_dir_x;
		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * (double)texture->width);
		if ((side == 0 && ray.ray_dir_x > 0) || (side == 1 && ray.ray_dir_y < 0))
			tex_x = texture->width - tex_x - 1;
		int y = draw_start;
		while (y < draw_end)
		{
			// Calculate texture Y coordinate
			double tex_pos = (y - (-line_height / 2 + HEIGHT / 2 - 100)) * texture->height / line_height;
			int tex_y = (int)tex_pos & (texture->height - 1);
			
			// Add bounds checking
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= (int)texture->height) 
				tex_y = texture->height - 1;
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= (int)texture->width)
				tex_x = texture->width - 1;
			int pixel_pos = (tex_y * texture->width + tex_x) * 4;
			uint8_t r = texture->pixels[pixel_pos + 0];
			uint8_t g = texture->pixels[pixel_pos + 1];
			uint8_t b = texture->pixels[pixel_pos + 2];
			uint8_t a = texture->pixels[pixel_pos + 3];
			// Now safely access the texture
			uint32_t color = (a << 24) | (b << 16) | (g << 8) | r;
			// Use your existing pixel writing code
			my_put_pixel(data, ray.x, y, color);
			//pixel_buffer[y * WIDTH + ray.x] = color;
			y++;
		}
		ray.x++;

	}
	//mlx_image_to_window(data->mlx, data->img, 0, 0);
}



// Draw the vertical line
		/*int y = draw_start;
		// Inside your raycasting loop, replace the color part with:
		 uint32_t color;
		if (data->map[ray.map_y][ray.map_x] == 2)
			color = YELLOWY;  // Yellow
		else if (side == 0)  // East-West walls (vertical walls)
		{
			if (ray.ray_dir_x > 0)  // East facing
				color = REDY;  // Red
			else                // West facing
				color = GREENY;  // Green
		}
		else  // North-South walls (horizontal walls)
		{
			if (ray.ray_dir_y > 0)  // North facing
				color = PINKY;  // Yellow
			else                // South facing
				color = BLUEY;  // Blue
		}

		// Then use this color in your drawing loop:
		while (y <= draw_end)
		{
			my_put_pixel(data, ray.x, y, color);
			y++;
		}
		ray.x++; */