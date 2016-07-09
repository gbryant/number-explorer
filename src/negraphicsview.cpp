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


#include "negraphicsview.h"

NEGraphicsView::NEGraphicsView()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    yOffset+=200;
}

void NEGraphicsView::mousePressEvent(QMouseEvent *event)
{
    clickPoint = event->pos();

}

void NEGraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        {
            yOffset+=10;
            viewport()->update();
        }
        break;
    case Qt::Key_Down:
        {
            yOffset-=10;
            viewport()->update();
        }
        break;
    case Qt::Key_Equal:
        if(event->modifiers()==Qt::ControlModifier)
        {
            scale(1.08,1.08);
        }
        break;

    case Qt::Key_Minus:
        if(event->modifiers()==Qt::ControlModifier)
        {
            scale(.92,.92);
        }
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }


}

void NEGraphicsView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx,dy);
    if(verticalScrollBar()->value()==0)
    {
        verticalScrollBar()->setValue(verticalScrollBar()->maximum()/2);
    }
    //verticalScrollBar()->setValue(verticalScrollBar()->maximum()/2);
}
