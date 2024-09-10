#ifndef ERROR_H
# define ERROR_H

# define ERR_ARG "Error\nInvalid argument\n"
# define P_USAGE "[Usage]\n./cub3D map/map*.cub"
# define ERR_EMPY_FILE "Error\nMap file is empty\n"
# define ERR_MAP_ORDER "Error\nMap should start with the infos\n"
# define ERR_NO_MAP "Error\nNo map matrix found in map file\n"
# define ERR_INV_MAP "Error\nMap provided is not valid\n"
# define ERR_NO_INFOS "Error\nMap infos are incomplete\n"
# define ERR_MATRIX_LEN "Error\nMatrix length is too small\n"
# define ERR_MATRIX_TOP "Error\nMatrix top border isn't closed\n"
# define ERR_MATRIX_BOT "Error\nMatrix bot border isn't closed\n"
# define ERR_MATRIX_SIDE "Error\nMatrix side border isn't closed\n"


/* allocation error msg */
# define ERR_ALLOC_MATRIX "Error\nMatrix alloc failed\n"
# define ERR_ALLOC_INFO "Error\nInfo list alloc failed\n"
# define ERR_ALLOC_NEW_MATRIX_ROW "Error\nNew Matrix row alloc failed\n"
# define ERR_ALLOC_NEW_MATRIX_COL "Error\nNew Matrix column alloc failed\n"


#endif