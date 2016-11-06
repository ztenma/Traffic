
typedef struct {
    int width;
    int height;
    ObjectId **grid;
} Map;
typedef Map * PMap;


Map* initMap (int width, int height);
void destroyMap (Map *map);

Map* loadMap (char *filename);
void displayMap (Map *map);
void loadDisplayMap (char * filename);

