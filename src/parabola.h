/***********************************************************************
Copyright 2018 Gregory Bryant

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************/


#ifndef PARABOLA_H
#define PARABOLA_H

#include "nedisplayobject.h"
#include <boost/multiprecision/gmp.hpp>
using boost::multiprecision::mpz_int;

class Parabola : public NEDisplayObject
{
public:
    Parabola();
    Parabola(int aIn,int bIn, int cIn);
    Parabola(int aIn,int bIn, int cIn, int cR, int cG, int cB);
    void init(void);
    bool isVisible(NEView *view);
    void render(NEView *view);
    double getArcLength(double x1, double x2,double precision);

    int cR,cG,cB;
    int a,b,c;      //y = ax^2 + bx + c
    int directrix;
    std::pair<float,float> focus;
    std::pair<float,float> vertex;
    int direction;

    mpz_int left;
    mpz_int right;
    mpz_int top;
    mpz_int bottom;
};

#endif // PARABOLA_H
