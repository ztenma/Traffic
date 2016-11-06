# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>

# include "map.h"
# include "traffic.h"

char MAX_VEHICLE_COUNT = 10;

/*
printf("\033[%d,%dH%s\n", x, y, s);
printf("\033[1;91;48;5;8m%s\033[0m\n", x, y, s);
*/

PVehicle generateVehicle (enum ObjectId id)
{
    PVehicle veh = malloc(sizeof(Vehicle));
    veh->objectId = id;
    veh->dest   = rand() % 4;
    veh->origin = rand() % 4;
    veh->align = rand() % 2;
    veh->speed = rand() % 2;
    veh->active = 1;
    veh->parked = 0;

    return veh;
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
