#ifndef __UTILS__
#define __UTILS__

#include <math.h>

float degToRad(int degree)
{
    return degree*static_cast<float>(M_PI)/180.0;
}

int fixAngle(int degree)
{
   if(degree > 359) 
   {
        degree -= 360;
   }
   if (degree < 0)
   {
        degree += 360;
   }
   return degree;
}

#endif