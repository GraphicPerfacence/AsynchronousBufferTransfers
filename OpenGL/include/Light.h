//
//  Light.h
//
//
//  Created by xt on 16/3/25.
//
//

#ifndef ____Light__
#define ____Light__

#include <glm/glm.hpp>

class Light
{
public:
    Light();
    ~Light();
    
    
    
    void setPosition(glm::vec3 pos) {_position = pos;};
    glm::vec3 getPosition() {return _position;}
private:
    glm::vec3 _position;
};
#endif