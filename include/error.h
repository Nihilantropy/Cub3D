#ifndef ERROR_H
# define ERROR_H

/* checks err msg */
# define ERR_ARG "Error\nInvalid argument\n"
# define P_USAGE "[Usage]\n./cub3D map/map*.cub\n"
# define ERR_EMPY_FILE "Error\nMap file is empty\n"
# define ERR_WRONG_CHAR "Error\nWrong CHAR in map matrix\n"
# define ERR_MAP_ORDER "Error\nMap should start with the infos\n"
# define ERR_NO_MAP "Error\nNo Map matrix found in map file\n"
# define ERR_INV_MAP "Error\nMap provided is not valid\n"
# define ERR_NO_INFOS "Error\nMap infos are incomplete\n"
# define ERR_MATRIX_LEN "Error\nMap matrix length is too small\n"
# define ERR_MAP_MATRIX "Error\nMap matrix format is incorrect\n"
# define ERR_MAP_ISLAND "Error\nMap matrix contain an island\n"
# define ERR_MAP_BORDERS "Error\nMap matrix borders are open\n"
# define ERR_NBR_PLAYER "Error\nWrong number of player\n"

/* generic err msg*/
#define ERR_DISPLAY_OPEN "Error\nCould not open display. Exiting..."

/* allocation err msg */
# define ERR_ALLOC_MATRIX "Error\nMatrix alloc failed\n"
# define ERR_ALLOC_MATRIX_COPY "Error\nMatrix copy alloc failed\n"
# define ERR_ALLOC_INFO "Error\nInfo list alloc failed\n"
# define ERR_ALLOC_NEW_MATRIX_ROW "Error\nNew matrix row alloc failed\n"
# define ERR_ALLOC_NEW_MATRIX_COL "Error\nNew matrix column alloc failed\n"
# define ERR_ALLOC_BOOL_MATRIX "Error\nBool matrix column alloc failed\n"

#endif