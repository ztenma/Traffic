


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
