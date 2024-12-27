#include "../include/cub3D.h"

/**
 * @brief Test ray initialization calculations
 * Validates basic ray direction and delta distance calculations
 * 
 * @param game Game state (unused in this test)
 * @return bool Success or failure of test
 */
bool	test_ray_init(t_game *game)
{
	t_player	player;
	double		angle;
	double		expected_dir_x;
	double		expected_dir_y;
	t_camera	ray_info;

	(void)game;
	player.pos.x = 2.0;
	player.pos.y = 2.0;
	angle = 0.0;

	init_ray(&ray_info, &player, angle);

	expected_dir_x = cos(angle);
	expected_dir_y = sin(angle);

	if (fabs(ray_info.ray_dir_x - expected_dir_x) > 0.0001 ||
		fabs(ray_info.ray_dir_y - expected_dir_y) > 0.0001)
		return (false);
	return (true);
}

/**
 * @brief Create a test map for wall detection
 * Allocates and returns a new map for testing
 * 
 * @return char** Allocated test map
 */
static char	**create_test_map(void)
{
	char	**map;
	int		i;
	char	*test_layout[] = {
		"111111",
		"100001",
		"100001",
		"100001",
		"111111",
		NULL
	};

	map = (char **)malloc(sizeof(char *) * 6);
	if (!map)
		return (NULL);
	i = 0;
	while (test_layout[i])
	{
		map[i] = ft_strdup(test_layout[i]);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

/**
 * @brief Test wall detection algorithm
 * Validates DDA implementation and distance calculations
 * 
 * @param game Game state for testing
 * @return bool Success or failure of test
 */
bool    test_wall_detection(t_game *game)
{
	t_ray_test test_cases[] = {
		// Position is now at center of grid cell (2.5, 2.5)
		{{.pos = {2.5, 2.5}, .rot.current_angle = 0}, 1.5, true, 0},
		{{.pos = {2.5, 2.5}, .rot.current_angle = M_PI_2}, 1.5, true, 1},
		{{.pos = {2.5, 2.5}, .rot.current_angle = M_PI}, 1.5, true, 0}
	};
    int         i;
    bool        success;
    char        **original_map;
    
    // Save original map and create test map
    original_map = game->map.matrix;
    game->map.matrix = create_test_map();
    if (!game->map.matrix)
        return (false);

    success = true;
    i = 0;
    while (i < 3 && success)
    {
        t_camera ray;
        init_ray(&ray, &test_cases[i].player, test_cases[i].player.rot.current_angle);
        calculate_step_dist(&ray, &test_cases[i].player);
        
        // Debug information before DDA
        printf("\nTest case %d:\n", i);
        printf("Player position: (%.2f, %.2f)\n", 
               test_cases[i].player.pos.x, test_cases[i].player.pos.y);
        printf("Ray direction: (%.2f, %.2f)\n", ray.ray_dir_x, ray.ray_dir_y);
        printf("Initial map position: (%d, %d)\n", ray.map_x, ray.map_y);
        printf("Step direction: (%d, %d)\n", ray.step_x, ray.step_y);
        printf("Delta distance: (%.2f, %.2f)\n", ray.delta_dist_x, ray.delta_dist_y);
        printf("Side distance: (%.2f, %.2f)\n", ray.side_dist_x, ray.side_dist_y);

        int side = perform_dda(game, &ray);
        calculate_wall_dist(&ray, side);

        // Debug information after DDA
        printf("Hit position: (%d, %d)\n", ray.map_x, ray.map_y);
        printf("Wall distance: %.2f (Expected: %.2f)\n", 
               ray.perp_wall_dist, test_cases[i].expected_dist);
        printf("Hit side: %d (Expected: %d)\n", side, test_cases[i].expected_side);

        if (fabs(ray.perp_wall_dist - test_cases[i].expected_dist) > 0.1 ||
            side != test_cases[i].expected_side)
        {
            printf("❌ Test case %d failed!\n", i);
            success = false;
        }
        i++;
    }

    // Clean up
    i = 0;
    while (game->map.matrix[i])
        free(game->map.matrix[i++]);
    free(game->map.matrix);
    game->map.matrix = original_map;
    return (success);
}

/**
 * @brief Run all raycasting tests
 * Main testing function that coordinates all test cases
 * 
 * @param game Game state for testing
 * @return bool Overall success of all tests
 */
bool	test_raycasting(t_game *game)
{
	bool	all_passed;

	all_passed = true;
	printf("\nRunning raycasting tests...\n");

	if (!test_ray_init(game))
	{
		printf("❌ Ray initialization test failed\n");
		all_passed = false;
	}
	else
		printf("✅ Ray initialization test passed\n");

	if (!test_wall_detection(game))
	{
		printf("❌ Wall detection test failed\n");
		all_passed = false;
	}
	else
		printf("✅ Wall detection test passed\n");

	return (all_passed);
}