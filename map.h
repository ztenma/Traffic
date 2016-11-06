
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


