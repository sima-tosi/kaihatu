#pragma once
#include "AcEnemy.h"
class AcTogezo :
    public AcEnemy
{
public:
    AcTogezo(AcCamera* camera, AcMap* map);

    void Init(void) override;

};

