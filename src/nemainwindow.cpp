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


#include "nemainwindow.h"
#include "factormap.h"
#include "parabola.h"
#include "pointset.h"
#include "trigonometric.h"

NEMainWindow::NEMainWindow(QWidget *parent):QMainWindow(parent)
{
    //qApp->setStyleSheet("QDockWidget { background-color: yellow }");

    //graphicsScene.addText("Hello, world!");
    //graphicsScene.setSceneRect(0,0,INT_MAX,INT_MAX);
    //graphicsView.setScene(&graphicsScene);
    //QPixmap *pixmap = new QPixmap(100,100);

    setCentralWidget(&view);

    view.consoleWindow = &consoleWindow;

    Trigonometric *tm = new Trigonometric();
    //tm->consoleWindow = &consoleWindow;
    FactorMap *fm = new FactorMap();
    fm->consoleWindow = &consoleWindow;
    //PointSet *ps = new PointSet();

    /*
    ps->points.append(qMakePair(1.0,1.0));
    ps->points.append(qMakePair(2.0,1.0));
    ps->points.append(qMakePair(3.0,1.0));
    ps->points.append(qMakePair(4.0,1.0));
    ps->points.append(qMakePair(5.0,1.0));
    */

    view.displayObjects.append(fm);

    //view.displayObjects.append(tm);
/*
    for(int i=1;i<=1000;i++)
    {
        if(i%2)
        {
            view.displayObjects.append(new Parabola(-1,i,0,255,0,0));
        }
        else
        {
            view.displayObjects.append(new Parabola(-1,i,0,0,0,255));
        }
    }
*/
    //setCentralWidget(&graphicsView);
    QDockWidget *dock = new QDockWidget(tr("Console"), this);
    dock->setWidget(&consoleWindow);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    consoleWindow.mainWindow = this;
    consoleWindow.lineEdit.setFocus();
    consoleWindow.init();

    QAction *action = new QAction("E&xit",this);
    action->setShortcut(QKeySequence::Quit);
    QMenu *menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(action);
    connect(action,&QAction::triggered,this,&NEMainWindow::quitApp);

    menu = menuBar()->addMenu(tr("&Edit"));
}

NEMainWindow::~NEMainWindow()
{

}


void NEMainWindow::quitApp()
{
    qApp->exit(0);
}
