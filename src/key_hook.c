#include "../includes/cub3d.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data = (t_data *)param;
	float	move_speed = 5;

	if ((keydata.key == MLX_KEY_ESCAPE) &&
	    (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		ft_free(data);
		exit(0);
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_A)
		{
			data->player->player_angle += 5;
			data->player->player_angle = FixAng(data->player->player_angle);
			data->player->player_dir_x = cos(degToRad(data->player->player_angle));
			data->player->player_dir_y = -sin(degToRad(data->player->player_angle));
		}
		else if (keydata.key == MLX_KEY_D)
		{
			data->player->player_angle -= 5;
			data->player->player_angle = FixAng(data->player->player_angle);
			data->player->player_dir_x = cos(degToRad(data->player->player_angle));
			data->player->player_dir_y = -sin(degToRad(data->player->player_angle));
		}
		else if (keydata.key == MLX_KEY_W)
		{
			float new_px = data->player->player_pos_x + data->player->player_dir_x * move_speed;
			float new_py = data->player->player_pos_y + data->player->player_dir_y * move_speed;
			if (!is_wall(data, new_px, data->player->player_pos_y))
				data->player->player_pos_x = new_px;
			if (!is_wall(data, data->player->player_pos_x, new_py))
				data->player->player_pos_y = new_py;
		}
		else if (keydata.key == MLX_KEY_S)
		{
			float new_px = data->player->player_pos_x - data->player->player_dir_x * move_speed;
			float new_py = data->player->player_pos_y - data->player->player_dir_y * move_speed;
			if (!is_wall(data, new_px, data->player->player_pos_y))
				data->player->player_pos_x = new_px;
			if (!is_wall(data, data->player->player_pos_x, new_py))
				data->player->player_pos_y = new_py;
		}
	}
}
