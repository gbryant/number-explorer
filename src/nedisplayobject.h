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


#ifndef NEDISPLAYOBJECT_H
#define NEDISPLAYOBJECT_H

#include <QtWidgets>

class NEView;
class NEConsoleWindow;


class NEDisplayObject
{
public:
    NEDisplayObject();

    virtual void render(NEView *view)=0;

    NEConsoleWindow *consoleWindow;
    unsigned long id;
    QString name;
};

#endif // NEDISPLAYOBJECT_H
