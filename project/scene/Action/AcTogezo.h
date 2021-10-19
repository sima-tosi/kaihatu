#pragma once
#include "AcEnemy.h"
class AcTogezo :
    public AcEnemy
{
public:
    AcTogezo(AcCamera* camera);

    void Init(void) override;

};

