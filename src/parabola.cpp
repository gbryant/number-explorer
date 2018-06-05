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


#include "parabola.h"
#include "neconsolewindow.h"
#include "neview.h"
#include <cmath>

Parabola::Parabola()
{
    name.append("Parabola");
    a=1;
    b=1;
    c=0;
    init();
}

Parabola::Parabola(int aIn, int bIn, int cIn)
{
    name.append("Parabola");
    a=aIn;
    b=bIn;
    c=cIn;
    init();
}

Parabola::Parabola(int aIn,int bIn, int cIn, int cR, int cG, int cB)
{
    name.append("Parabola");
    a=aIn;
    b=bIn;
    c=cIn;
    init();
    this->cR = cR;
    this->cG = cG;
    this->cB = cB;
}

void Parabola::init()
{
    cR=255;
    cG=255;
    cB=255;
    directrix = c-(1+b*b)/(4*a);
    focus.first = -b/(2*a);
    focus.second = c+(1-b*b)/(4*a);
    vertex.first = -b/(2*a);
    vertex.second = c - b*b/(4*a);
    if(focus.second>directrix){direction=1;}
    else{direction=-1;}
}

bool Parabola::isVisible(NEView *view)
{return true;
/*
    view->getScreenBounds(&top,&bottom,&left,&right);

    if(direction<0)
    {
        if(mpz_cmp_si(bottom.backend().data(),vertex.second)>0){return false;}
    }
    else
    {
        if(mpz_cmp_si(top.backend().data(),vertex.second)<0){return false;}
    }
    return true;
*/
}

void Parabola::render(NEView *view)
{
    mpz_int rStart;
    mpz_int rEnd;
    view->getScreenBounds(&top,&bottom,&left,&right);

    if(isVisible(view))
    {
        rStart=left;
        rEnd=right;

        mpz_int prevX,prevY;
        mpz_int x=rStart;
        prevX=x;
        mpz_int y=a*x*x+b*x+c;
        prevY=y;
        if(x%2)
        {
            view->setPoint(x,y,cR,255,cB);
        }
        else
        {
            view->setPoint(x,y,cR,cG,cB);
        }
        for(x=rStart+1;x<=rEnd;x++)
        {
            y=a*x*x+b*x+c;
            //image->drawLine(prevX,prevY,x,y,cR,cG,cB);
            if(x%2)
            {
                view->setPoint(x,y,cR,255,cB);
            }
            else
            {
                view->setPoint(x,y,cR,cG,cB);
            }
            prevX=x;
            prevY=y;
        }
        return;
    }
}

double Parabola::getArcLength(double x1, double x2,double precision)
{
    double x,endX;
    double y1,y2,xSqrd,ySqrd;
    double totalDistance=0;
    double segmentDistance;

    if(x1<x2)
    {x=x1;endX=x2;}
    else
    {x=x2;endX=x1;}

    do
    {
        y1=a*x*x+b*x+c;
        y2=a*(x+precision)*(x+precision)+b*(x+precision)+c;

        double xSqrd = ((x+precision)-x)*((x+precision)-x);
        double ySqrd = (y2-y1)*(y2-y1);

        segmentDistance = sqrt(xSqrd+ySqrd);
        totalDistance += segmentDistance;

        x+=precision;
    }
    while(x<=endX);

    return totalDistance;
}
