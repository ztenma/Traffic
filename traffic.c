# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <time.h>

# include "bitops.h"
# include "map.h"
# include "traffic.h"

MAX_VEHICLE_COUNT = 10;

/*
printf("\033[%d,%dH%s\n", x, y, s);
printf("\033[1;91;48;5;8m%s\033[0m\n", x, y, s);
*/

PVehicle generateVehicle (enum DisplayCode code)
{
    PVehicle veh = malloc(sizeof(Vehicle));
    veh->displayCode = code;
    veh->infos = 0;
    set_bit(&veh->infos, 0, 1);
    set_bit(&veh->infos, 1, rand()%2);
    set_bit(&veh->infos, 2, rand()%2);
    set_bit(&veh->infos, 3, 0);
} 

void simulate ()
{
    bool simulation_end = false;
    PVeheicle[MAX_VEHICLE_COUNT] vehicles;
    
    while (!simulation_end) {
        update_model(vehicles);
        update_UI(vehicles);
        usleep(100000); // 100ms
    }
}

int main (int argc, char ** argv)
{
    srand(time(NULL));
    /*char * utf8str = u8"hellô";
    u_int32_t
    printf("%s %lu\n", utf8str, strlen(utf8str)); */
    printf("'\xe2\x94\x83'\n");
    
    Map *map = loadMap ("default.map");
    displayMap (map);
    destroyMap (map);
    
    return EXIT_SUCCESS;
}
