#include "../includes/cub3d.h"

void ft_free(t_data *data)
{
	if (data)
	{
		if (data->parse)
		{
			if (data->parse->map)
			{
				for (int i = 0; i < data->parse->map_height; i++)
				{
					if (data->parse->map[i])
						free(data->parse->map[i]);
				}
				free(data->parse->map);
			}
			free(data->parse);
		}
		if (data->player)
			free(data->player);
		if (data->map)
		{
			for (int i = 0; i < data->map_height; i++)
				free(data->map[i]);
			free(data->map);
		}
		if (data->mlx)
			mlx_terminate(data->mlx);
	}
}
