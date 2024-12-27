#ifndef TEST_H
# define TEST_H

# include "player.h"

/**
 * @brief Test structure for raycasting tests
 * Contains input data and expected results for each test case
 */
typedef struct s_ray_test
{
	t_player	player;
	double		expected_dist;
	bool		should_hit;
	int			expected_side;
}	t_ray_test;

#endif