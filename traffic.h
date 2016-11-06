# if !defined(TRAFFIC_H)
# define TRAFFIC_H

# define MAX_VEHICLE_COUNT 16

typedef struct
{
    char x; 
    char y;
} Pos;

typedef struct
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


typedef struct
{
    Pos no; 
    Pos se; 
} Area;

typedef struct
{
    PMap map;
    PVehicle * vehicles;
    unsigned char vehicleCount;
    Area areas[];
    
} TrafficController;
typedef TrafficController * PTrafficController;

# endif
