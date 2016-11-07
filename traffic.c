# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

# include "map.h"
# include "traffic.h"

# define SLEEP_TIME 100000
# define MAX_VEHICLE_COUNT 16
# define TRAFFIC_LIGHTS_COUNT 5 

char* CARDINAL_POINTS[4] = {"N", "E", "S", "W"};

Pos ORIGINS[4]      = {{0, 0}, {79, 5}, {34, 22}, {0, 17}}; /* North invalid*/
Pos DESTINATIONS[4] = {{39, 0}, {79, 17}, {30, 22}, {0, 7}}; 

Area area_ALL  = (Area){{0, 0}, {79, 22}};
 
Area area_N_N  = (Area){{38, 0}, {45, 4}};
Area area_EW  = (Area){{0, 5}, {79, 7}};
Area area_WE  = (Area){{0, 15}, {79, 17}};
Area area_S_N  = (Area){{33, 18}, {36, 22}};
Area area_NS  = (Area){{30, 5}, {30, 22}};
Area area_SN = (Area){{43, 5}, {43, 17}};
Area area_TL0 = (Area){{46, 5}, {49, 7}};
Area area_TL1 = (Area){{46, 9}, {49, 9}};
Area area_TL2 = (Area){{25, 13}, {28, 13}};
Area area_TL3 = (Area){{25, 15}, {28, 17}};
Area area_TL4 = (Area){{29, 19}, {36, 19}};
Area area_P0 = (Area){{13, 5}, {14, 5}};
Area area_P1 = (Area){{54, 5}, {55, 5}};
Area area_P2 = (Area){{47, 17}, {48, 17}};
Area area_P3 = (Area){{63, 17}, {64, 17}};

/*
printf("\033[%d,%dH%s\n", x, y, s);
printf("\033[1;91;48;5;8m%s\033[0m\n", x, y, s);
*/

void print_debug (Pos pos, char* message)
{
    printf("\x1b[%d;%dH%s", pos.y+1, pos.x+1, message); fflush(stdout);
}

PVehicle initVehicle (enum ObjectId id)
{
    PVehicle veh  = malloc(sizeof(Vehicle));
    veh->objectId = id;
    veh->dest     = rand() % 4;
    veh->origin   = rand() % 3 + 1;
    veh->align    = rand() % 2;
    veh->speed    = rand() % 2;
    veh->active   = 1;
    veh->parked   = rand() % 2;
    veh->pos      = ORIGINS[veh->origin];

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
    tc->trafficLights = calloc(TRAFFIC_LIGHTS_COUNT, sizeof(TrafficLight));
    tc->trafficLights[0] = (TrafficLight){{46, 4}, GREEN_LIGHT};
    tc->trafficLights[1] = (TrafficLight){{46, 8}, GREEN_LIGHT};
    tc->trafficLights[2] = (TrafficLight){{25, 14}, GREEN_LIGHT};
    tc->trafficLights[3] = (TrafficLight){{25, 18}, GREEN_LIGHT};
    tc->trafficLights[4] = (TrafficLight){{36, 19}, RED_LIGHT};

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
        destroyVehicle(tc->vehicles[index]);
        /*int i;
        for (i = index; i < vehicleCount; i++)
            tc->vehicles[i] = tc->vehicles[i+1];*/
        tc->vehicles[index] = tc->vehicles[tc->vehicleCount-1];
        --tc->vehicleCount;
        tc->vehicles[tc->vehicleCount] = NULL;
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
    return pos.x >= area.nw.x && pos.y >= area.nw.y
        && pos.x <= area.se.x && pos.y <= area.se.y;
}


/////////////////////// Logic //////////////////////////////

void displaySmallVehicle (PVehicle veh)
{
    Pos pos = veh->pos;
    printf("\x1b[%d;%dH%s\n", pos.y+1, pos.x+1, getDisplayChar(veh->objectId));
}

void eraseSmallVehicle (PVehicle veh)
{
    Pos pos = veh->pos;
    printf("\x1b[%d;%dH \n", pos.y+1, pos.x+1);
}

void update_traffic_lights (PTrafficController tc) 
{
	int i, light;
	unsigned long long time = tc->time, timeLight;
	//tc->trafficLights[i]->activeLight = (tc->trafficLights[i]->activeLight + 1)%3;
	
	for (i = 0; i < TRAFFIC_LIGHTS_COUNT; i++) {
		
		light = tc->trafficLights[i].activeLight;
		timeLight = tc->trafficLights[i].time;
		
		if (timeLight + 5000 <= time && light == GREEN_LIGHT) {
			tc->trafficLights[i].activeLight = (light + 1) % 3;
			tc->trafficLights[i].time = time;
		}
		if (timeLight + 2000 <= time && light == YELLOW_LIGHT) {
			tc->trafficLights[i].activeLight = (light + 1) % 3;
			tc->trafficLights[i].time = time;
		}
		if (timeLight + 7000 <= time && light == RED_LIGHT) {
			tc->trafficLights[i].activeLight = (light + 1) % 3;
			tc->trafficLights[i].time = time;
		}
	}
}


void check_and_take_action (PVehicle veh, PTrafficController tc)
{
    bool in_N_N = inArea(veh->pos, area_N_N);
    bool in_EW = inArea(veh->pos, area_EW);
    bool in_WE = inArea(veh->pos, area_WE);
    bool in_S_N = inArea(veh->pos, area_S_N);
    bool in_NS = inArea(veh->pos, area_NS);
    bool in_SN = inArea(veh->pos, area_SN);
    bool in_TL0 = inArea(veh->pos, area_TL0);
    bool in_TL1 = inArea(veh->pos, area_TL1);
    bool in_TL2 = inArea(veh->pos, area_TL2);
    bool in_TL3 = inArea(veh->pos, area_TL3);
    bool in_TL4 = inArea(veh->pos, area_TL4);
    bool in_P0 = inArea(veh->pos, area_P0);
    bool in_P1 = inArea(veh->pos, area_P1);
    bool in_P2 = inArea(veh->pos, area_P2);
    bool in_P3 = inArea(veh->pos, area_P3);
    
    char dest = veh->dest;
    char parked = veh->parked;
    
    int tl0 = tc->trafficLights[0].activeLight;
    int tl1 = tc->trafficLights[1].activeLight;
    int tl2 = tc->trafficLights[2].activeLight;
    int tl3 = tc->trafficLights[3].activeLight;
    int tl4 = tc->trafficLights[4].activeLight;
    
    
    if (in_EW) {
        if (in_NS) {
            if (dest == 1 || dest == 2) veh->pos.y++;
            else veh->pos.x--;
        } else if (in_SN) {
            if (dest == 0) veh->pos.y--;
            else veh->pos.x--;
        } else if (in_TL0) { 
            if (tl0 == RED_LIGHT) {return;}
            else veh->pos.x--;
        } /* else if (in_P1) { 
            if (parked == 1) { veh->pos.y--; return;}
            else veh->pos.x--;
        } else if (in_P0) { 
            if (parked == 1) { veh->pos.y--; return;}
            else veh->pos.x--;
        } */ else veh->pos.x--;
    } else    
    if (in_WE) {
        if (in_NS) {
            if (dest == 2) veh->pos.y++;
            else veh->pos.x++;
        } else if (in_SN) {
            if (dest == 1) veh->pos.x++;
            else veh->pos.y--;
        } else if (in_TL3) {
            if (tl3 == RED_LIGHT) {return;}
            else veh->pos.x++;
        } /*else if (in_P2) { 
            if (parked == 1) { veh->pos.y++; return;}
            else veh->pos.x++;
        } else if (in_P3) { 
            if (parked == 1) { veh->pos.y++; return;}
            else veh->pos.x++;
        } */else veh->pos.x++;
    } else if (in_N_N) veh->pos.y--;
    
    else if (in_EW) {
        if (in_TL0) {
            if (tl0 == RED_LIGHT) {return;}
            else veh->pos.x--;
        } else veh->pos.x--;   
    }
    else if (in_WE) {
        if (in_TL3) {
            if (tl3 == RED_LIGHT) {return;}
            else veh->pos.x++;
        } else veh->pos.x++;
        
    }
    else if (in_S_N) { 
        if (in_TL4) {
            if (tl4 == RED_LIGHT) {return;}
            else veh->pos.y--;
        } else veh->pos.y--;
    }
    else if (in_NS) veh->pos.y++;
    else if (in_SN) veh->pos.y--;
    
    else {
        char debug_message[50];
        sprintf(debug_message, "(%d,%d) no action!", veh->pos.x, veh->pos.y);
        print_debug((Pos){1,2}, debug_message);
    }
}

void update_model (PTrafficController tc)
{
    int i;
    
    print_debug((Pos){1,2}, "                ");
    if (tc->vehicleCount < MAX_VEHICLE_COUNT) {
        PVehicle newVeh = initVehicle(BLUE_CAR);
        addVehicle(tc, newVeh);
        print_debug((Pos){1,1}, "Vehicle created!");
    }
    //PVehicle veh = tc->vehicles[0];
    //veh->pos.x = (veh->pos.x + 1) % 80;
    //getchar(); // pause
    for (i = 0; i < tc->vehicleCount; i++)
    {
        PVehicle veh = tc->vehicles[i];
        check_and_take_action(veh, tc);
        if (!inArea(veh->pos, area_ALL))
            delVehicleAt(tc, i);
    }
    
    update_traffic_lights(tc);
}

void display_traffic_lights (PTrafficController tc) 
{
	int i;
	for (i = 0; i < TRAFFIC_LIGHTS_COUNT; i++) {
		
		int x, y, light;
		x = tc->trafficLights[i].pos.x;
		y = tc->trafficLights[i].pos.y;
		light = tc->trafficLights[i].activeLight;
		
		if (light == GREEN_LIGHT) {
			printf( GREEN  "\x1b[%d;%dH%s" RESET, y + 1, x + 1, "◉" );
			printf( RESET  "\x1b[%d;%dH%s", y + 1, x + 1 + 1, "◉" );
			printf( RESET  "\x1b[%d;%dH%s", y + 1, x + 1 + 2, "◉" );
			fflush(stdout);
		}
		if (light == YELLOW_LIGHT) {
		    printf( RESET  "\x1b[%d;%dH%s", y + 1, x + 1, "◉" );
			printf( YELLOW "\x1b[%d;%dH%s" RESET, y + 1, x + 1 + 1, "◉" );
			printf( RESET  "\x1b[%d;%dH%s", y + 1, x + 1 + 2, "◉" );
			fflush(stdout);
		}
		if (light == RED_LIGHT) {
		    printf( RESET  "\x1b[%d;%dH%s", y + 1, x + 1, "◉" );
		    printf( RESET  "\x1b[%d;%dH%s", y + 1, x + 1 + 1, "◉" );
			printf( RED    "\x1b[%d;%dH%s" RESET, y + 1, x + 1 + 2, "◉" );
			fflush(stdout);
		}	
	}
}

void update_UI (PTrafficController tc)
{
    int vehIndex;
    
    /*printf("\x1b[1;1H"); fflush(stdout); // Place sursor at top left
    printf("\x1b[2J"); // clear screen
    displayMap (tc->map);*/
    for (vehIndex = 0; vehIndex < tc->vehicleCount; vehIndex++)
    {
        PVehicle veh = tc->vehicles[vehIndex];
        displaySmallVehicle(veh);
        
        /* Print debug info */
        char debug_message[50];
        sprintf(debug_message, "[%d] (%d,%d) dest %s", vehIndex, veh->pos.x, veh->pos.y, CARDINAL_POINTS[veh->dest]);
        print_debug((Pos){1,19 + vehIndex}, "                    ");
        print_debug((Pos){1,19 + vehIndex}, debug_message);
    }
    display_traffic_lights(tc);
}

void erase_UI (PTrafficController tc)
{
    int vehIndex;
    for (vehIndex = 0; vehIndex < tc->vehicleCount; vehIndex++)
        eraseSmallVehicle(tc->vehicles[vehIndex]);
}

unsigned long long time_miliseconds ()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000 * tv.tv_sec + tv.tv_usec / 1000;
}

void simulate (PTrafficController tc)
{
    bool simulation_end = false;
    unsigned long long time, last_time = time_miliseconds(), dt;
    int i;
    
    for (i = 0; i < TRAFFIC_LIGHTS_COUNT; i++)
        tc->trafficLights[i].time = time_miliseconds();
    
    printf("\x1b[1;1H"); fflush(stdout); // Place sursor at top left
    printf("\x1b[2J"); // clear screen
    displayMap (tc->map);

    while (!simulation_end) {
        time = time_miliseconds();
        dt = time - last_time;
        tc->time = time;
    
        erase_UI(tc);
        update_model(tc);
        update_UI(tc);
        
        usleep(SLEEP_TIME);
        last_time = time;
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
