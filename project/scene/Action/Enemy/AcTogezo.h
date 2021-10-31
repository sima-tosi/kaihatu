#pragma once
#include "AcEnemy.h"
class AcTogezo :
    public AcEnemy
{
public:
    AcTogezo(AcCamera* camera, AcMap* map, Vector2F pos,int _image);

    void Init(void) override;

};

