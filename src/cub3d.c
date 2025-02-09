/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:29:12 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/08 23:53:42 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_menu(t_data *data)
{
	mlx_texture_t	*image_menu;
	printf("Init menu\n");
	image_menu = mlx_load_png("src/img/menu.png");
	if (!image_menu)
	{
		free_data(data);
		return_error("Can't load menu image");
	}
	data->img_menu = mlx_texture_to_image(data->mlx, image_menu);
	if (!data->img_menu)
	{
		free_data(data);
		return_error("Can't load menu image");
	}
	//mlx_image_to_window(data->mlx, data->img_menu, 0, 0);
	mlx_delete_texture(image_menu);
}

void	init_data(t_data *data, char **av)
{
	data->parse = malloc(sizeof(t_parsing));
	data->player = malloc(sizeof(t_player));
	if (!data->parse || !data->player)
	{
		free_data(data);
		return_error("Malloc error");
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
	data->minimap_tile_size = TILE_SIZE / 4;
	data->map_width = 0;
	data->map_height = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = 0;
	data->map = NULL;
	data->parse->map = NULL;
	data->parse->description = NULL;
	data->player->move_speed = WALK_SPEED;
	if (!parsing(av[1], data))
	{
		free_data(data);
		return_error("Parsing error");
	}
}

bool	initialize_game(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!data->mlx)
	{
		return_error((char *)mlx_strerror(mlx_errno));
		return (false);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		return_error((char *)mlx_strerror(mlx_errno));
		return (false);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return_error((char *)mlx_strerror(mlx_errno));
		return (false);
	}
	if (data->icon)
		mlx_set_icon(data->mlx, data->icon);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	init_menu(data);
	return (true);
}


void	draw_menu(t_data *data)
{
	int	x;
	int	y;
	int	i;
	mlx_image_to_window(data->mlx, data->img_menu, 0, 0);
	
	if (data->selected_option == 0)
	{
		x = 0;
		y = 0;
	}
	else
	{
		x = 0;
		y = 100;
	}
	i = x + 10;
	while (++x <= i)
	{
		my_put_pixel(data, x, y, MINIMAP_BORDER_COLOR);
		my_put_pixel(data, x, y + 10, MINIMAP_BORDER_COLOR);
	}
	i = y + 10;
	while (++y <= i)
	{
		my_put_pixel(data, x, y, MINIMAP_BORDER_COLOR);
		my_put_pixel(data, x + 10, MAP_OFFSET_Y + y, MINIMAP_BORDER_COLOR);
	}
}

void	draw_pause(t_data *data)
{
	mlx_put_string(data->mlx, "PAUSE", 940, 400);
}

void	render_frame(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clear_image(data, 0x00000FF);
	if (data->state == STATE_GAME)
	{
		if (data->img_menu)
		{
			mlx_delete_image(data->mlx, data->img_menu);
			data->img_menu = NULL;
		}
		if (data->show_minimap)
			draw_minimap(data);
	}
	else if (data->state == STATE_MENU)
	{
		draw_menu(data);
	}
	else if (data->state == STATE_PAUSE)
		draw_pause(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_data			*data;
	mlx_texture_t	*icon;

	if (ac != 2)
		return_error("Invalid number of arguments");
	data = malloc(sizeof(t_data));
	if (!data)
		return_error("Malloc error");
	init_data(data, av);
	icon = mlx_load_png("src/img/icon.png");
	if (!icon)
		return_error("Can't load icon");
	if (!initialize_game(data))
		return_error("Can't initialize game");
	printf("Start game\n");
	mlx_key_hook(data->mlx, handle_keypress, data);
	mlx_loop_hook(data->mlx, (void (*)(void *))render_frame, data);
	mlx_cursor_hook(data->mlx, handle_mouse_move, data);
	mlx_loop(data->mlx);
}
