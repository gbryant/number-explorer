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


#include "pointset.h"
#include "neconsolewindow.h"
#include "neview.h"
#include <boost/multiprecision/gmp.hpp>
#include <iostream>

PointSet::PointSet()
{
name = "PointSet";
}

void PointSet::render(NEView *view)
{
    //add checks to only draw on screen points
    view->getScreenBounds(&top,&bottom,&left,&right);
    for(int i=0;i<points.length();i++)
    {
        view->setPoint(points[i].first,points[i].second);
    }
}
