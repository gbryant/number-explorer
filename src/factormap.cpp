/***********************************************************************
Copyright 2016 Gregory Bryant

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


#include "factormap.h"
#include "neconsolewindow.h"
#include "neview.h"
#include <boost/multiprecision/gmp.hpp>
#include <iostream>

using boost::multiprecision::abs;
using boost::multiprecision::mpz_int;



mpz_int FactorMap::fixYOffsetAndSign(mpz_int x, mpz_int y)
{
    if(y>=0)
    {
        if(y>abs(x))
        {
            if(y%abs(x)!=0)
            {return abs(x)-(y%abs(x))+y;}
            else{return y;}
        }
        else{return abs(x);}
    }
    else
    {
        if(abs(y)>=abs(x))
        {
            temp=abs(x)-(abs(y)%abs(x))+abs(y);
            temp=temp-abs(x);
            temp*=-1;
            return temp;
        }
        else{return 0;}
    }
}

FactorMap::FactorMap()
{
    name.append("FactorMap");
}

void FactorMap::render(NEView *view)
{

    view->getScreenBounds(&top,&bottom,&left,&right);


    //for(int i=left;i<right;i++)
    i = left;
    while(i<right)
    {
        if(i==0){i++;continue;}

        j = fixYOffsetAndSign(i,bottom);

        while(j<=top)
        {
            //mpz_int yVal = view->height()-1-j+view->yOffset;
            //mpz_int xVal = i-view->xOffset;
            //view->setPoint(static_cast<int>(xVal),static_cast<int>(yVal));
            view->setPoint(i,j);
            j+=abs(i);
        }
    i++;
    }
}
