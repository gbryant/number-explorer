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


#include "neview.h"
#include "neconsolewindow.h"
#include <iostream>
#include <sstream>
#include <string>
#include <boost/multiprecision/gmp.hpp>
using boost::multiprecision::mpz_int;
using boost::multiprecision::mpf_float;
using boost::multiprecision::abs;


#define QN(X) QString::number(X)

NEView::NEView(QWidget *parent) : QWidget(parent)
{
    image = new QImage(width(),height(),QImage::Format_RGB32);
    image->fill(Qt::black);
    setFocusPolicy(Qt::StrongFocus);
    xFactorialOffset = 0;
    yFactorialOffset = 0;
    factorialXScrolling=false;
    factorialYScrolling=false;
    yOffset = 0;
    xOffset = 0;
    xScrollAmt=0;
    yScrollAmt=0;
    originalXScrollAmt=0;
    originalYScrollAmt=0;
    scale=1;
    showCrossHairs=true;
    showClickPoints=true;
}

void NEView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,*image);
}

void NEView::getScreenBounds(mpz_int *top, mpz_int *bottom, mpz_int *left, mpz_int *right)//bounds in terms of points, not pixels
{
    //the plus and minus 1s are to over report the points to draw by one in each dimension
    //this ensures edge points aren't left off due to rounding down when zoomed in

    *top = (yOffset+height()-1)/scale;
    *top += 1;
    *bottom = yOffset/scale;
    *bottom -= 1;
    *left = xOffset/scale;
    *left -= 1;
    *right = (xOffset+width()-1)/scale;
    *right += 1;

}

void NEView::setXPos(mpz_int x)
{
    xScrollAmt=x*scale-width()/2;
    xOffset=xScrollAmt;
}

void NEView::setYPos(mpz_int y)
{
    yScrollAmt=y*scale-height()/2;
    yOffset=yScrollAmt;
}

void NEView::setPoint(mpz_int x, mpz_int y)
{
    yVal = height()-1-(y*scale)+yOffset;
    xVal = (x*scale)-xOffset;

    //we can speed this up by minimizing the use of the mpz types, precompute when possible
    //        and convert to int early if possible!


    if(scale==1)
    {
        if(static_cast<int>(yVal)>0 && static_cast<int>(yVal)<height() && static_cast<int>(xVal)>0 && static_cast<int>(xVal)<width())
        {
            QRgb *scanLine = reinterpret_cast<QRgb*>(image->scanLine(static_cast<int>(yVal)));
            scanLine[static_cast<int>(xVal)]=qRgb(255,255,255);
        }
    }
    else
    {
        for(int j=0;j<scale;j++)
        {
            for(int i=0;i<scale;i++)
            {
                if(static_cast<int>(yVal)+j>0 && static_cast<int>(yVal)+j<height() && static_cast<int>(xVal)+i>0 && static_cast<int>(xVal)+i<width())
                {
                    QRgb *scanLine = reinterpret_cast<QRgb*>(image->scanLine(static_cast<int>(yVal)+j));
                    scanLine[static_cast<int>(xVal)+i]=qRgb(255,255,255);
                }
            }
        }
    }

}

void NEView::render()
{
    image->fill(Qt::black);
    for( int i=0; i<displayObjects.count(); i++ )
    {
        displayObjects[i]->render(this);
    }
    if(showCrossHairs)
    {
        QPainter painter(image);
        painter.setPen(Qt::green);
        painter.setBrush(Qt::green);
        painter.drawLine(0,height()/2,width()-1,height()/2);
        painter.drawLine(width()/2,0,width()/2,height()-1);
    }
}

void NEView::resizeEvent(QResizeEvent *event)
{
    delete image;
    image = new QImage(width(),height(),QImage::Format_RGB32);
    render();
}

void NEView::printScreenPoint(int x, int y)
{
    mpz_int pX = x+xOffset;
    mpf_float fX = pX;
    mpf_float fScale = scale;
    pX.assign(boost::multiprecision::floor(fX/scale));
    std::stringstream pXStream;
    pXStream<<pX;

    mpz_int pY = height()-y+yOffset;
    mpf_float fY = pY;
    pY.assign(boost::multiprecision::ceil(fY/fScale));
    std::stringstream pYStream;
    pYStream<<pY;

    consoleWindow->appendText(QString::fromStdString(pXStream.str())+","+QString::fromStdString(pYStream.str())+"\n");
}


void NEView::mouseMoveEvent(QMouseEvent *event)
{
    xOffset = originalXOffset+(clickPoint.x()-event->pos().x());
    yOffset = originalYOffset+(event->pos().y()-clickPoint.y());

    xScrollAmt = originalXScrollAmt+(clickPoint.x()-event->pos().x());
    yScrollAmt = originalYScrollAmt+(event->pos().y()-clickPoint.y());

    render();
    update();
}

void NEView::mousePressEvent(QMouseEvent *event)
{
    clickPoint = event->pos();
    originalXOffset = xOffset;
    originalYOffset = yOffset;
    originalXScrollAmt = xScrollAmt;
    originalYScrollAmt = yScrollAmt;
    if(showClickPoints)
    {
        printScreenPoint(clickPoint.x(),clickPoint.y());
    }

}

void NEView::keyPressEvent(QKeyEvent *event)
{
    //float sW,sH,sX,sY;
    //factorial+=1;
    //mpz_fac_ui(yOffset.backend().data(),factorial);
    boost::multiprecision::mpz_int amount;
    switch(event->key())
    {
        case Qt::Key_Space:
        {
            printScreenPoint(width()/2,height()/2);
        }
        break;
        case Qt::Key_Equal:
        {
            if(event->modifiers()&Qt::ControlModifier)
            {
                scale++;
                mpf_float w = width();
                mpf_float s = scale;
                mpf_float sW = w/(s-1)/2;
                mpf_float h = height();
                mpf_float sH = h/(s-1)/2;
                mpf_float xo = xOffset;
                mpf_float sX = xo/(s-1)*s;
                mpf_float yo = yOffset;
                mpf_float sY = yo/(s-1)*s;

                mpf_float a = sX+sW;
                mpf_float b = sY+sH;

                xOffset = (mpz_int)a;
                yOffset = (mpz_int)b;

                xScrollAmt = xOffset;
                yScrollAmt = yOffset;

                /*
                sW = static_cast<mpf_float>(width())/static_cast<mpf_float>(scale-1)/2;
                sH = (float)height()/(float)(scale-1)/2;

                sX = (float)xOffset/(float)(scale-1)*(float)scale;
                sY = (float)yOffset/(float)(scale-1)*(float)scale;

                xOffset = boost::multiprecision::round(sX+sW);
                yOffset = boost::multiprecision::round(sY+sH);
                */
                render();
                update();
            }
        }
        break;
        case Qt::Key_Minus:
        {
            if(event->modifiers()&Qt::ControlModifier)
            {
                scale--;
                if(scale<1){scale=1;}

                mpf_float w = width();
                mpf_float s = scale;
                mpf_float sW = w/(s+1)/2;
                mpf_float h = height();
                mpf_float sH = h/(s+1)/2;
                mpf_float xo = xOffset;
                mpf_float sX = xo/(s+1)*s;
                mpf_float yo = yOffset;
                mpf_float sY = yo/(s+1)*s;

                mpf_float a = sX-sW;
                mpf_float b = sY-sH;

                xOffset = (mpz_int)a;
                yOffset = (mpz_int)b;

                xScrollAmt = xOffset;
                yScrollAmt = yOffset;

                render();
                update();
            }
        }
        break;
        case Qt::Key_Up:
        {
            amount=10;
            if(event->modifiers()&Qt::ShiftModifier){amount=1;}
            if(event->modifiers()&Qt::ControlModifier){amount=100;}
            if(event->modifiers()&Qt::ControlModifier&&event->modifiers()&Qt::ShiftModifier){amount=500;}
            if(event->modifiers()==Qt::AltModifier)
            {
                yFactorialOffset+=1;
                amount=0;
            }

            if(yFactorialOffset!=0)
            {
                mpz_fac_ui(yOffset.backend().data(),abs(yFactorialOffset));
                if(yFactorialOffset<0){yOffset*=-1;}
            }
            else
            {
                yOffset=0;
            }
            yScrollAmt+=amount;
            yOffset+=yScrollAmt;

            render();
            update();
        }
        break;

    case Qt::Key_Down:
    {
        amount=10;
        if(event->modifiers()&Qt::ShiftModifier){amount=1;}
        if(event->modifiers()&Qt::ControlModifier){amount=100;}
        if(event->modifiers()&Qt::ControlModifier&&event->modifiers()&Qt::ShiftModifier){amount=500;}
        if(event->modifiers()==Qt::AltModifier)
        {
            yFactorialOffset-=1;
            amount=0;
        }

        if(yFactorialOffset!=0)
        {
            mpz_fac_ui(yOffset.backend().data(),abs(yFactorialOffset));
            if(yFactorialOffset<0){yOffset*=-1;}

        }
        else
        {
            yOffset=0;
        }
        yScrollAmt-=amount;
        yOffset+=yScrollAmt;

        render();
        update();
    }
    break;

    case Qt::Key_Left:
    {
        amount=10;
        if(event->modifiers()&Qt::ShiftModifier){amount=1;}
        if(event->modifiers()&Qt::ControlModifier){amount=100;}
        if(event->modifiers()&Qt::ControlModifier&&event->modifiers()&Qt::ShiftModifier){amount=500;}
        if(event->modifiers()==Qt::AltModifier)
        {
            xFactorialOffset-=1;
            amount=0;
        }

        if(xFactorialOffset!=0)
        {
            mpz_fac_ui(xOffset.backend().data(),abs(xFactorialOffset));
            if(xFactorialOffset<0){xOffset*=-1;}
        }
        else
        {
            xOffset=0;
        }
        xScrollAmt-=amount;
        xOffset+=xScrollAmt;

        render();
        update();
    }
    break;

    case Qt::Key_Right:
    {
        amount=10;
        if(event->modifiers()&Qt::ShiftModifier){amount=1;}
        if(event->modifiers()&Qt::ControlModifier){amount=100;}
        if(event->modifiers()&Qt::ControlModifier&&event->modifiers()&Qt::ShiftModifier){amount=500;}
        if(event->modifiers()==Qt::AltModifier)
        {
            xFactorialOffset+=1;
            amount=0;
        }

        if(xFactorialOffset!=0)
        {
            mpz_fac_ui(xOffset.backend().data(),abs(xFactorialOffset));
            if(xFactorialOffset<0){xOffset*=-1;}
        }
        else
        {
            xOffset=0;
        }
        xScrollAmt+=amount;
        xOffset+=xScrollAmt;

        render();
        update();
    }
    break;

    case Qt::Key_Escape:
    {
       scale=1;
       resolution=1;
       xOffset=0;
       yOffset=0;
       xScrollAmt=0;
       yScrollAmt=0;
       xFactorialOffset=0;
       yFactorialOffset=0;
       render();
       update();
    }
    break;
    }
}
