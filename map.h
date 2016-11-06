int OBJECT_ID_COUNT = 29;

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
    TRAMWAY_LEFT, TRAMWAY_BODY, TRAMWAY_RIGHT,
    PEDESTRIAN, PEDESTRIAN_GARBAGE
};

char * ID_DISPLAY_MAP[] = \
{
    " ", " ",
    "┃", "━",
    "┛", "┗", "┓", "┏", 
    "┱", "┲", "┹", "┺", 
    "X", 
    "╵", "╴", 
    "─", 
    "◉", "◉", "◉", 
    "◯", "◯", "◯", 
    "🚘", "🛱", "🚍"
    "🚎", "🚎", "🚎",
    "🚶", "🚮"
};
//🐧pinguin 🚦vertical_traffic_light



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


