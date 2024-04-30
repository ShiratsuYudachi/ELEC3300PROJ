#include <cstdint>
#include "SERVO42C.hpp"

enum GCodeCommandType{
    RAPID_POSITIONING = 0,
    LINEAR_INTERPOLATION = 1,
    CW_CIRCULAR_INTERPOLATION = 2,
    CCW_CIRCULAR_INTERPOLATION = 3
};

enum BasicCommandType{
    SET_POSITION = 0,
    SET_SPEED = 1
};


class BasicCommand{
public:
    BasicCommandType type;
    float x, y, z;
    float speed;
    static float currentSpeed; // mm/s
    
    BasicCommand(BasicCommandType type, float x, float y, float z){
        this->type = type;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    BasicCommand(BasicCommandType type, float speed){
        this->type = type;
        this->speed = speed;
    }

    void execute(){
        switch (type)
        {
        case SET_POSITION:
            setPosition3d(x, y, z, currentSpeed);
            break;
        case SET_SPEED:
            currentSpeed = speed;
            break;
        case 
        default:
        }
        

    }
};
