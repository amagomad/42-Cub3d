/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/20 17:06:16 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_menu(t_data *data)
{
	mlx_texture_t	*image_menu[3];
	
	data->img_menu = malloc(sizeof(mlx_image_t *) * 2);
	printf("Init menu\n");
	image_menu[0] = mlx_load_png("src/img/menu_start.png");
	image_menu[1] = mlx_load_png("src/img/menu_quit.png");
	
	if (!image_menu[0] || !image_menu[1])
	{
		free_data(data);
		return_error("Can't load menu image", data);
	}
	data->img_menu[0] = mlx_texture_to_image(data->mlx, image_menu[0]);
	data->img_menu[1] = mlx_texture_to_image(data->mlx, image_menu[1]);
	if (!data->img_menu[0] || !data->img_menu[1])
	{
		free_data(data);
		return_error("Can't load menu image", data);
	}
	mlx_delete_texture(image_menu[0]);
	mlx_delete_texture(image_menu[1]);
}

void	init_data(t_data *data, char **av)
{
	data->parse = ft_calloc(sizeof(t_parsing), 1);
	data->player = ft_calloc(sizeof(t_player), 1);
	if (!data->parse || !data->player)
	{
		free_data(data);
		return_error("Malloc error", data);
	}
	data->mlx = NULL;
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->icon = NULL;
	data->state = STATE_MENU;
	data->selected_option = 0;
	data->show_minimap = false;
	data->minimap_T_SIZE = T_SIZE / 4;
	data->map_width = 0;
	data->map_height = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = 0;
	data->map = NULL;
	data->parse->map = NULL;
	data->parse->description = NULL;
	data->player->move_speed = WALK_SPEED;
	data->mouse_shown = false;
	if (!parsing(av[1], data))
	{
		free_all(data);
		return_error("Parsing error", data);
	}
}

bool	initialize_game(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!data->mlx)
	{
		return_error((char *)mlx_strerror(mlx_errno), data);
		return (false);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		return_error((char *)mlx_strerror(mlx_errno), data);
		return (false);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return_error((char *)mlx_strerror(mlx_errno), data);
		return (false);
	}
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_set_setting(MLX_DECORATED, false);
	
	if (data->icon)
		mlx_set_icon(data->mlx, data->icon);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	
	init_menu(data);
	return (true);
}

void	draw_menu(t_data *data)
{
	mlx_image_to_window(data->mlx, data->img_menu[0], 0 , 0);
	mlx_image_to_window(data->mlx, data->img_menu[1], 0, 0);
	
	if (data->selected_option == 0)
	{
		data->img_menu[0]->enabled = true;
		data->img_menu[1]->enabled = false;
	}
	else
	{
		data->img_menu[0]->enabled = false;
		data->img_menu[1]->enabled = true;
	}
}

void	draw_pause(t_data *data)
{
	mlx_put_string(data->mlx, "PAUSE", 940, 400);
}

void update_doors(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y][x] > 2 && data->map[y][x] < 17)
				data->map[y][x]++; // Animation progressive
			else if (data->map[y][x] == 17)
				data->map[y][x] = 0;
		}
	}
}

void	render_frame(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clear_image(data, 0x00000FF);
	if (data->state == STATE_GAME)
	{
		update_doors(data);
		//mlx_image_to_window(data->mlx, data->hud, 0, 0);
		raycasting(data);
		if (data->img_menu)
		{
			mlx_delete_image(data->mlx, data->img_menu[0]);
			mlx_delete_image(data->mlx, data->img_menu[1]);
		}
		if (data->show_minimap)
			draw_minimap(data);
	}
	else if (data->state == STATE_MENU)
		draw_menu(data);
	else if (data->state == STATE_PAUSE)
		draw_pause(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	free_map(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->map_height)
	{
		free(data->map[i]);
	}
	free(data->map);
}

void free_all(t_data *data)
{
//	free(data->parse->map);
	free(data->player);
	free_map(data);
	ft_free_str_tab(data->parse->map);
	ft_free_str_tab(data->parse->description);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->img_menu)
	{
		mlx_delete_image(data->mlx, data->img_menu[0]);
		mlx_delete_image(data->mlx, data->img_menu[1]);
	}
	if (data->no_texture)
		mlx_delete_texture(data->no_texture);
	if (data->so_texture)
		mlx_delete_texture(data->so_texture);
	if (data->we_texture)
		mlx_delete_texture(data->we_texture);
	if (data->ea_texture)
		mlx_delete_texture(data->ea_texture);
	if (data->icon)
		mlx_delete_texture(data->icon);
	if (data->door_texture)
		mlx_delete_texture(data->door_texture);
	if (data->mlx)
		mlx_close_window(data->mlx);
	free(data->img_menu);
	free(data->parse->no_texture);
	free(data->parse->so_texture);
	free(data->parse->we_texture);
	free(data->parse->ea_texture);
	free(data->parse->ceiling_color);
	free(data->parse->floor_color);
	free(data->parse);
	
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	
//	free(data->mlx);
	free(data);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data			*data;
	mlx_texture_t	*icon;

	if (ac != 2)
	{
		printf("Invalid number of arguments\n");
		return (0);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return_error("Malloc error", data);
	init_data(data, av);
	icon = mlx_load_png("src/img/icon.png");
	if (!icon)
		return_error("Can't load icon", data);
	if (!initialize_game(data))
		return_error("Can't initialize game", data);
	printf("Start game\n");
	mlx_key_hook(data->mlx, handle_keypress, data);
	mlx_cursor_hook(data->mlx, handle_mouse_move, data);
	mlx_loop_hook(data->mlx, (void (*)(void *))render_frame, data);
	mlx_loop(data->mlx);
	free_all(data);
}
