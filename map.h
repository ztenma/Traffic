# if !defined(MAP_H)
# define MAP_H

# define OBJECT_ID_COUNT 28

#define RED     "\x1b[1;31m"
#define GREEN   "\x1b[1;32m"
#define YELLOW  "\x1b[1;33m"
#define BLUE    "\x1b[1;34m"
#define MAGENTA "\x1b[1;35m"
#define CYAN    "\x1b[1;36m"
#define BG_GRAY	"\x1b[48;5;246m"
#define RESET   "\x1b[0m"


static char * ID_DISPLAY_MAP[] = \
{
    " ", BG_GRAY " " RESET,
    "┃", "━",
    "┛", "┗", "┓", "┏", 
    "┱", "┲", "┹", "┺", 
    "X", 
    "╵", "╴", 
    "─", 
    GREEN "◉" RESET, YELLOW "◉" RESET, RED "◉" RESET, 
    GREEN "◯" RESET, YELLOW "◯" RESET, RED "◯" RESET, 
    BLUE "🚘" RESET, RED "🛱" RESET, MAGENTA "🚍" RESET,
    CYAN "🚎" RESET, CYAN "🚎" RESET,
    "🚶", "🚮"
};
//🐧pinguin 🚦vertical_traffic_light


enum ObjectId
{
    ROAD, PAVEMENT, 
    VERT_BORDER, HORI_BORDER, 
    NW_BORDER, NE_BORDER, SW_BORDER, SE_BORDER,
    RLLDH_BORDER, LLRDH_BORDER, RLLUH_BORDER, LLRUH_BORDER, 
    PARKING_GROUND, 
    VERT_DASHED_LINE, HORI_DASHED_LINE,
    HORI_RAIL,
    TRAFFIC_LIGHT1_GREEN, TRAFFIC_LIGHT1_YELLOW, TRAFFIC_LIGHT1_RED, 
    TRAFFIC_LIGHT2_GREEN, TRAFFIC_LIGHT2_YELLOW, TRAFFIC_LIGHT2_RED, 
    BLUE_CAR, FIRE_ENGINE, BUS,
    TRAMWAY1, TRAMWAY2,
    PEDESTRIAN, PEDESTRIAN_GARBAGE
};


typedef struct {
    int width;
    int height;
    enum ObjectId **grid;
} Map;
typedef Map * PMap;


PMap initMap (int width, int height);
void destroyMap (PMap map);

PMap loadMap (char *filename);
void displayMap (PMap map);

# endif
