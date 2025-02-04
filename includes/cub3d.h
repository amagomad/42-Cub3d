/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:27:19 by amagomad          #+#    #+#             */
/*   Updated: 2025/02/04 18:34:06 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <sys/stat.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"

# define WIDTH 2048  // Taille de la fenêtre
# define HEIGHT 1020

# define FOV 60  // Champ de vision

# define TILE_SIZE 30  // Taille d'une case

# define MOVE_SPEED 4.0  // Vitesse de déplacement
# define WALK_SPEED 2.0
# define SPRINT_SPEED 4.0
# define ROTATION_SPEED 5 // Vitesse de rotation


# define PLAYER_RADIUS 5 // Marge pour éviter de coller aux murs
# define MAP_OFFSET_X 20 // Décalage horizontal (gauche) (minimap)
# define MAP_OFFSET_Y 20 // Décalage vertical (haut) (minimap)
# define MINIMAP_TILE_SIZE (TILE_SIZE / 4)
# define MINIMAP_BORDER_COLOR 0xA0A0A0FF
# define MINIMAP_INNER_BORDER_COLOR 0x606060FF
# define MINIMAP_BG_COLOR 0x00000080


# define PI 3.14159265358979323846


typedef struct s_parsing
{
	int		file_fd;
	char	**description;
	char	**map;
	char 	*no_texture;
	char 	*so_texture;
	char 	*we_texture;
	char 	*ea_texture;
	char 	*floor_color;
	char 	*ceiling_color;
	int		map_width;
	int		map_height;
}	t_parsing;

typedef struct s_player
{
	float player_pos_x;
	float player_pos_y;
	float player_dir_x;
	float player_dir_y;
	float player_angle;
	float move_speed;
	float	velocity; // a voir si on garde
}	t_player;

typedef struct s_data
{
	t_player		 *player;
	t_parsing		*parse;
	mlx_t			*mlx;
	mlx_texture_t	*icon;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	mlx_image_t		*img;
	int				**map;
	int				map_width;
	int				map_height;
	bool			show_minimap;
	bool			debug_mode;
	char	player_dir;// a enlever
	int		player_x;  // a enlever
	int		player_y; // a enlever
	int in_menu;
}	t_data;

typedef struct  s_minimap
{
	int     map_width_px;
	int     map_height_px;
	uint32_t    border_color;
	uint32_t    inner_border_color;
	uint32_t    bg_color;
}   t_minimap;

// ================== PARSING ==================
bool	parsing(char *file, t_data *data);
bool	stock_map(t_data *data);
bool	stock_description(t_parsing *parse);
void	return_error(char *str);
bool	validity_description(t_parsing *parse);
bool	validity_map(char **map);
bool	open_file(char *file, t_parsing *parse);
bool	file_validity(char *file);
bool	valid_color(t_parsing *parsing);
bool	transform_map(t_data *data);
bool	validity_map_wall(t_data *data);
void	display_map(t_data *data);

// ================== MOUVEMENT ==================
void	handle_keypress(mlx_key_data_t keydata, void *param);
void	handle_keyrelease(mlx_key_data_t keydata, void *param);
void	handle_mouse_move(double xpos, double ypos, void *param);
void	rotate_player(t_data *data, float angle);
void	move_player(t_data *data, float move_x, float move_y);

// ================== MINIMAP & AFFICHAGE ==================
void	draw_player(t_data *data);
void	draw_minimap(t_data *data);
void	draw_line(t_data *data, int x1, int y1, int x2, int y2, uint32_t color);

// ================== UTILS ==================
float	degrees_to_radians(float degrees);
void	manage_door(t_data *data);
void	free_data(t_data *data);
void	clear_image(mlx_image_t *image, uint32_t color);

#endif