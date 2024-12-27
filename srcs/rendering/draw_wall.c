// #include "../include/cub3D.h"

// /**
//  * @brief Calculate wall distance and height
//  * Determines wall height based on perpendicular distance
//  * to avoid fisheye effect
//  * 
//  * @param ray_info Structure containing ray calculation data
//  * @param side Which wall side was hit (0 for X, 1 for Y)
//  */
// void    calculate_wall_dist(t_camera *ray_info, int side)
// {
//     if (side == 0)  // Vertical wall hit (X-side)
//     {
//         // Instead of using the difference between final and starting positions
//         // Calculate the actual perpendicular distance to the wall
//         if (ray_info->ray_dir_x != 0)
//             ray_info->perp_wall_dist = (ray_info->map_x - ray_info->start_x + 
//                 (1 - ray_info->step_x) / 2) / ray_info->ray_dir_x;
//     }
//     else  // Horizontal wall hit (Y-side)
//     {
//         if (ray_info->ray_dir_y != 0)
//             ray_info->perp_wall_dist = (ray_info->map_y - ray_info->start_y + 
//                 (1 - ray_info->step_y) / 2) / ray_info->ray_dir_y;
//     }
// 	printf("Detailed Distance Calculation:\n");
// 	printf("Wall X: %d, Start X: %.2f\n", ray_info->map_x, ray_info->start_x);
// 	printf("Step X: %d, Offset: %.2f\n", ray_info->step_x, (1 - ray_info->step_x) / 2.0);
// 	printf("Raw difference: %.2f\n", ray_info->map_x - ray_info->start_x);
// 	printf("With offset: %.2f\n", ray_info->map_x - ray_info->start_x + (1 - ray_info->step_x) / 2.0);

//     // Ensure distance is always positive
//     ray_info->perp_wall_dist = fabs(ray_info->perp_wall_dist);
// }

// /**
//  * @brief Draw vertical wall stripe
//  * Renders a vertical line representing wall slice
//  * 
//  * @param game Game state containing display information
//  * @param x Current x position on screen
//  * @param wall_height Height of wall to render
//  */
// void	draw_wall_stripe(t_game *game, int x, int wall_height)
// {
// 	int	draw_start;
// 	int	draw_end;

// 	draw_start = -wall_height / 2 + game->display.height / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = wall_height / 2 + game->display.height / 2;
// 	if (draw_end >= game->display.height)
// 		draw_end = game->display.height - 1;
// 	draw_line(game, x, draw_start, x, draw_end, WHITE);
// }
