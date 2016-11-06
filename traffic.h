
typedef struct
{
    enum ObjectId objectId; // Code mapped to a text output
    // destination (2), origin (2), parked, align, speed, active
    char info;
} Vehicle;
typedef Vehicle *PVehicle;

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

char * ID_DISPLAY_MAP = \
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
}
//🐧pinguin 🚦vertical_traffic_light

int getObjectId (char * ID_DISPLAY_MAP, char * displayChar) {
    int i, index = -1;
    
    for (i = 0; i < OBJECT_ID_COUNT, i++)
        if (diaplayChar == ID_DISPLAY_MAP[i]) // TODO: unicode comparison!
            index = i;
    
    return index;
}
