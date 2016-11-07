# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>

# include "map.h"
# include "traffic.h"

# define SLEEP_TIME 100000
# define MAX_VEHICLE_COUNT 16
# define TRAFFIC_LIGHTS_COUNT 5 

//Pos ORIGINS[5] = {{0, 5}, {79, 5}, {0, 15}, {79, 15}, {22, 17}}; 
//Pos DESTINATIONS[5] = {{0, 5}, {79, 5}, {0, 15}, {79, 15}, {22, 17}}; 

/*
printf("\033[%d,%dH%s\n", x, y, s);
printf("\033[1;91;48;5;8m%s\033[0m\n", x, y, s);
*/

PVehicle initVehicle (enum ObjectId id)
{
    PVehicle veh  = malloc(sizeof(Vehicle));
    veh->objectId = id;
    veh->pos      = (Pos){0, 0};
    veh->dest     = rand() % 4;
    veh->origin   = rand() % 4;
    veh->align    = rand() % 2;
    veh->speed    = rand() % 2;
    veh->active   = 1;
    veh->parked   = 0;

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
    tc->trafficLights = calloc(MAX_VEHICLE_COUNT, sizeof(TrafficLight));
    tc->trafficLightCount = 5;

    return tc;
}

void destroyTrafficController (PTrafficController tc)
{
    int i;
    for (i = 0; i < MAX_VEHICLE_COUNT; i++)
        free(tc->vehicles[i]);
    free(tc->vehicles);
    free(tc->trafficLights);
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

Pos randomSource ()
{

}

void displaySmallVehicle(PVehicle veh)
{
    Pos pos = veh->pos;
    if (pos.x == 0) printf("\x1b[%d;%dH \n", pos.y+1, 80);
    else printf("\x1b[%d;%dH \n", pos.y+1, pos.x);
    printf("\x1b[%d;%dH%s\n", pos.y+1, pos.x+1, getDisplayChar(veh->objectId));
}

/////////////////////// Logic //////////////////////////////
void update_traffic_lights (PTrafficController tc) 
{
	int i, light;
	long timeLight;
	unsigned long long time = tc->time;
	//tc->trafficLights[i]->activeLight = (tc->trafficLights[i]->activeLight + 1)%3;
	
	for (i =0; i < 5; i++) {
		
		light = tc->trafficLights[i].activeLight;
		timeLight = tc->trafficLights[i].time;
		
		if (timeLight + 5000 <= time && light == GREEN_LIGHT) {
			tc->trafficLights[i].activeLight = (light + 1)%3;
			timeLight = time;
		}
		if (timeLight + 2000 <= time && light == YELLOW_LIGHT) {
			tc->trafficLights[i].activeLight = (light + 1)%3;
			timeLight = time;
		}
		if (timeLight + 7000 <= time && light == RED_LIGHT) {
			tc->trafficLights[i].activeLight = (light + 1)%3;
			timeLight = time;
		}
	}
}

void update_model (PTrafficController tc)
{
    if (tc->vehicleCount == 0) {//< MAX_VEHICLE_COUNT) {
        PVehicle newVeh = initVehicle(BLUE_CAR);
        newVeh->pos.y = 5;
        addVehicle(tc, newVeh);
    }
    PVehicle veh = tc->vehicles[0];
    veh->pos.x = (veh->pos.x + 1) % 80;
    //getchar(); // pause

    /* Update traffic lights */
}

void display_traffic_lights (PTrafficController tc) 
{
	int i;
	for (i =0; i < 5; i++) {
		
		int x, y, light;
		x = tc->trafficLights[i].pos.x;
		y = tc->trafficLights[i].pos.y;
		light = tc->trafficLights[i].activeLight;
		
		if (light == GREEN_LIGHT) {
			printf( GREEN "\x1b%d;%dH%s" RESET "\n", y, x, "◉" );
		}
		if (light == YELLOW_LIGHT) {
			printf( YELLOW "\x1b%d;%dH%s" RESET "\n", y, x + 1, "◉" );
		}
		if (light == RED_LIGHT) {
			printf( RED "\x1b%d;%dH%s" RESET "\n", y, x + 2, "◉" );
		}	
	}
}

void update_UI (PTrafficController tc)
{
    int vehIndex = 0;
    //for (
    PVehicle veh = tc->vehicles[0];
    displaySmallVehicle(veh);
    
    /* Print debug info */
    printf("\x1b[20;2H[%d] (%d,%d)\n", vehIndex, veh->pos.x, veh->pos.y);
}

void simulate (PTrafficController tc)
{
    bool simulation_end = false;
    PVehicle vehicles[MAX_VEHICLE_COUNT];
    
    printf("\x1b[1;1H"); fflush(stdout); // Place sursor at top left
    printf("\x1b[2J"); // clear screen
    displayMap (tc->map);

    while (!simulation_end) {
        update_model(tc);
        update_UI(tc);
        
        usleep(SLEEP_TIME);
    }
}

int main (int argc, char ** argv)
{
    srand(time(NULL));
    /*char * utf8str = u8"hellô";
    //printf("%s %lu\n", utf8str, strlen(utf8str)); */
    //printf("'\xe2\x94\x83'\n");
    //printf("size: %d, objectId: %d, dest: %d, origin: %d, parked: %d, align: %d, speed: %d, active: %d\n", sizeof(veh), veh.objectId, veh.dest, veh.origin, veh.parked, veh.align, veh.speed, veh.active);
    //Area a1 = (Area){{0, 0}, {2, 3}};
    //printf("%d %d %d %d %d\n", sizeof(a1), a1.no.x, a1.no.y, a1.se.x, a1.se.y);
    
    PMap map = loadMap ("default.map");
    PTrafficController tc = initTrafficController(map);

    simulate(tc);

    destroyTrafficController(tc);
    destroyMap (map);
    
    return EXIT_SUCCESS;
}
