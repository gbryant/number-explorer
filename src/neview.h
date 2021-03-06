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


#ifndef NEVIEW_H
#define NEVIEW_H

#include <QtWidgets>
#include "nedisplayobject.h"
#include <boost/multiprecision/gmp.hpp>
using boost::multiprecision::mpz_int;
using boost::multiprecision::mpf_float;

class NEConsoleWindow;

class NEView : public QWidget
{
    Q_OBJECT
public:
    explicit NEView(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void render();

    void setPoint(mpz_int x, mpz_int y);
    void setPoint(mpz_int x, mpz_int y, int r, int g, int b);

    void setPoint(mpf_float x, mpf_float y);
    void setPoint(mpf_float x, mpf_float y, int r, int g, int b);

    void setXPos(mpz_int x);
    void setYPos(mpz_int y);
    void setScale(int scale);
    void getScreenBounds(mpz_int *top, mpz_int *bottom, mpz_int *left, mpz_int *right);
    void printScreenPoint(int x, int y);

    QImage *image;
    QPoint clickPoint;
    boost::multiprecision::mpz_int originalXOffset;
    boost::multiprecision::mpz_int originalYOffset;
    QList<NEDisplayObject*> displayObjects;
    NEConsoleWindow *consoleWindow;
    boost::multiprecision::mpz_int xOffset,yOffset;
    boost::multiprecision::mpz_int originalXScrollAmt, originalYScrollAmt;
    boost::multiprecision::mpz_int xScrollAmt, yScrollAmt;
    bool factorialXScrolling;
    bool factorialYScrolling;
    long int xFactorialOffset;
    long int yFactorialOffset;
    int scale;
    int resolution;

    bool showClickPoints;
    bool showCrossHairs;

//test to optimize setPoint
    mpz_int xVal;
    mpz_int yVal;

signals:

public slots:
};

#endif // NEVIEW_H
