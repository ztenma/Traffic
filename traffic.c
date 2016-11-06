# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>

# include "bitops.h"
//# include "map.h"
//# include "traffic.h"

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

typedef struct {
    int width;
    int height;
    enum ObjectId **grid;
} Map;
typedef Map * PMap;

typedef struct
{
    enum ObjectId objectId : 8; // Code mapped to a text output
    // destination (2), origin (2), parked, align, speed, active
    unsigned char dest   : 2; // N, E, S, W
    unsigned char origin : 2; // N, E, S, W
    unsigned char align  : 1; // 0: left, 1: right
    unsigned char speed  : 1; // 0: slow, 1: quick
    unsigned char active : 1; 
    unsigned char parked : 1; 
} __attribute__((packed)) Vehicle;
typedef Vehicle *PVehicle;

char MAX_VEHICLE_COUNT = 10;

/*
printf("\033[%d,%dH%s\n", x, y, s);
printf("\033[1;91;48;5;8m%s\033[0m\n", x, y, s);
*/

PVehicle generateVehicle (enum ObjectId id)
{
    PVehicle veh = malloc(sizeof(Vehicle));
    veh->objectId = id;
    veh->dest   = rand % 4;
    veh->origin = rand % 4;
    veh->align = rand % 2;
    veh->speed = rand % 2;
    veh->active = 1;
    veh->parked = 0;
}

void update_model (PMap map, PVehicle * vehicles)
{

}

void update_UI (PMap map, PVehicle * vehicles)
{

}

void simulate (PMap map)
{
    bool simulation_end = false;
    PVehicle vehicles[MAX_VEHICLE_COUNT];
    
    while (!simulation_end) {
        update_model(map, vehicles);
        update_UI(map, vehicles);
        usleep(100000); // 100ms
    }
}

int main (int argc, char ** argv)
{
    srand(time(NULL));
    /*char * utf8str = u8"hellô";
    u_int32_t
    //printf("%s %lu\n", utf8str, strlen(utf8str)); */
    //printf("'\xe2\x94\x83'\n");
    //printf("size: %d, objectId: %d, dest: %d, origin: %d, parked: %d, align: %d, speed: %d, active: %d\n", sizeof(veh), veh.objectId, veh.dest, veh.origin, veh.parked, veh.align, veh.speed, veh.active);
    
    /*Map *map = loadMap ("default.map");
    displayMap (map);
    destroyMap (map);
    */
    
    
    return EXIT_SUCCESS;
}
