#ifndef __UTILS_H__
#define __UTILS_H__

#include <math.h>
#include <string>
#include <fstream>

inline float DegToRad(int degree)
{
    return degree*static_cast<float>(M_PI)/180.0;
}

inline int FixAngle(int degree)
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

inline std::string ReadFile(const char* filename)
{
     std::ifstream in(filename, std::ios::binary);
     if(in)
     {
          std::string content;
          in.seekg(0, std::ios::end);
          content.resize(in.tellg());
          in.seekg(0, std::ios::beg);
          in.read(&content[0], content.size());
          in.close();
          return content;
     }
     throw(errno);
}

#endif