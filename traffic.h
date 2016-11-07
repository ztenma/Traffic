# if !defined(TRAFFIC_H)
# define TRAFFIC_H

typedef struct Pos
{
    char x; 
    char y;
} Pos;

typedef struct Vehicle
{
    enum ObjectId objectId : 8; // Code mapped to a text output
    Pos pos;
    // destination (2), origin (2), parked, align, speed, active
    unsigned char dest   : 2; // N, E, S, W
    unsigned char origin : 2; // N, E, S, W
    unsigned char align  : 1; // 0: left, 1: right
    unsigned char speed  : 1; // 0: slow, 1: quick
    unsigned char active : 1; 
    unsigned char parked : 1; 
} __attribute__((packed)) Vehicle;
typedef Vehicle *PVehicle;

enum TrafficLightColor {GREEN_LIGHT, YELLOW_LIGHT, RED_LIGHT};

typedef struct TrafficLight
{
    Pos pos;
    enum TrafficLightColor activeLight;
    unsigned long long time;
} TrafficLight;

typedef struct Area
{
    Pos nw;
    Pos se;
} Area;

typedef struct TrafficController
{
    unsigned long long time;
    PMap map;
    PVehicle * vehicles;
    unsigned char vehicleCount;
    TrafficLight * trafficLights;
    
} TrafficController;
typedef TrafficController * PTrafficController;

# endif
