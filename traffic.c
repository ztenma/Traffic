# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>

# include "map.h"
# include "traffic.h"



/*
printf("\033[%d,%dH%s\n", x, y, s);
printf("\033[1;91;48;5;8m%s\033[0m\n", x, y, s);
*/

PVehicle initVehicle (enum ObjectId id)
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

void destroyVehicle(PVehicle veh)
{
    free(veh);
}

PTrafficController initTrafficController (PMap map)
{
    PTrafficController tc = malloc(sizeof(TrafficController));
    tc->map = map;
    tc->vehicles = calloc(MAX_VEHICLE_COUNT, sizeof(PVehicle));
    tc->vehicleCount = 0;

    return tc;
}

void destroyTrafficController (PTrafficController tc)
{
    int i;
    for (i = 0; i < MAX_VEHICLE_COUNT; i++)
        free(tc->vehicles[i]);
    free(tc->vehicles);
    free(tc);
}

void addVehicle (PTrafficController tc, PVehicle veh)
{
    if (tc->vehicleCount == MAX_VEHICLE_COUNT)
    {
        printf("Error: cannot add vehicles\n");
        //destroyApplication();
    } else {
        tc->vehicles[tc->vehicleCount++] = veh;
    }
} 

void delVehicleAt (PTrafficController tc, char index)
{
    if (tc->vehicleCount == 0 || index < 0 || index >= tc->vehicleCount)
    {
        printf("Error: cannot delete vehicle at index %d\n", index);
        //destroyApplication();
    } else {
        --tc->vehicleCount;
        tc->vehicles[index] = NULL;
    }
} 

void delVehicle (PTrafficController tc, PVehicle veh)
{
    int i;
    for (i = 0; i < tc->vehicleCount; i++)
        if (tc->vehicles[i] == veh)
            delVehicleAt(tc, i);
}


bool inArea (Pos pos, Area area)
{
    return pos.x >= area.no.x && pos.y >= area.no.y
        && pos.x <= area.se.x && pos.y <= area.se.y;
}

/////////////////////// Logic //////////////////////////////

void update_model (PMap map, PVehicle * vehicles)
{
    //if (PV
}

void update_UI (PMap map, PVehicle * vehicles)
{
    displayMap (map);

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
    //printf("%s %lu\n", utf8str, strlen(utf8str)); */
    //printf("'\xe2\x94\x83'\n");
    //printf("size: %d, objectId: %d, dest: %d, origin: %d, parked: %d, align: %d, speed: %d, active: %d\n", sizeof(veh), veh.objectId, veh.dest, veh.origin, veh.parked, veh.align, veh.speed, veh.active);
    Area a1 = (Area){{0, 0}, {2, 3}};
    printf("%d %d %d %d %d\n", sizeof(a1), a1.no.x, a1.no.y, a1.se.x, a1.se.y);
    
    PMap map = loadMap ("default.map");

    //simulate(map);

    destroyMap (map);
    
    return EXIT_SUCCESS;
}
