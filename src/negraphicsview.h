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
/***********************************************************************/


#ifndef NEGRAPHICSVIEW_H
#define NEGRAPHICSVIEW_H
#include <QtWidgets>
#include <boost/multiprecision/gmp.hpp>

class NEConsoleWindow;

class NEGraphicsView : public QGraphicsView
{
public:
    NEGraphicsView();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void scrollContentsBy(int dx, int dy);

    NEConsoleWindow *consoleWindow;
    boost::multiprecision::mpz_int xOffset,yOffset;
    QPoint clickPoint;
};

#endif // NEGRAPHICSVIEW_H
