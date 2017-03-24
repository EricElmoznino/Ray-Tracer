#ifndef PlaneLightSource_h
#define PlaneLightSource_h

#include "Plane.h"
#include <stdio.h>

class PlaneLightSource : public Plane {
public:
    PlaneLightSource(const ColourRGB colour);
};

#endif /* PlaneLightSource_h */
