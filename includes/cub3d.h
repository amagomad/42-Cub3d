/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgorin <cgorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:27:19 by amagomad          #+#    #+#             */
/*   Updated: 2025/01/29 13:17:39 by cgorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <math.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"

# define WIDTH 2048
# define HEIGHT 1020
# define FOV 60
# define TILE_SIZE 30;
# define MOVE_SPEED 0.0045
# define PLAYER_SPEED 4

# define M_PI 3.14159265358979323846
# define mapS 10      //map cube size

	// structs

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
	float px;// = 100;
	float py;// = 100;
	float pdx;// = 0;
	float pdy;// = 0;
	float pa;// = 0;
}	t_player;

typedef struct s_data
{
	t_player		 *player;
	t_parsing		*parse;
	mlx_t			*mlx;
	void			*win;
	mlx_texture_t	*icon;
	mlx_image_t		*no_texture;
	mlx_image_t		*so_texture;
	mlx_image_t		*we_texture;
	mlx_image_t		*ea_texture;
	mlx_image_t		*img;
	//void	*floor_color;
	//void	*ceiling_color;
	int		t_size_x;
	int		t_size_y;
	int		width;
	int		height;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		player_dir;
	int		**map;
}	t_data;

	// functions

			/*PARSING*/
			
bool	parsing(char *file, t_data *data);
bool	stock_map(t_data *data);
bool	stock_description(t_parsing *parse);

/*UTILS_PARSING*/
void return_error(char *str);

/*CHECK_VALIDITY*/
bool	validity_description(t_parsing *parse);
bool	validity_map(char **map);
bool	open_file(char *file, t_parsing *parse);
bool	file_validity(char *file);
bool	valid_color(t_parsing *parsing);

bool	transform_map(t_data *data);
bool	validity_map_wall(t_data *data);

void	display_map(t_data *data);
void drawPlayer2D(t_data *data);
void draw_line(t_data *data, int x1, int y1, int x2, int y2, uint32_t color);
float degToRad(int a);
int FixAng(int a);
void clear_image(mlx_image_t *image, uint32_t color);

void	handle_keypress(mlx_key_data_t keydata, void *param);

#endif