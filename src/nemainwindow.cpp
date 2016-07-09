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


#include "nemainwindow.h"
#include "factormap.h"

NEMainWindow::NEMainWindow(QWidget *parent):QMainWindow(parent)
{
    //qApp->setStyleSheet("QDockWidget { background-color: yellow }");

    //graphicsScene.addText("Hello, world!");
    //graphicsScene.setSceneRect(0,0,INT_MAX,INT_MAX);
    //graphicsView.setScene(&graphicsScene);
    //QPixmap *pixmap = new QPixmap(100,100);

    setCentralWidget(&view);

    view.consoleWindow = &consoleWindow;

    FactorMap *fm = new FactorMap();
    fm->consoleWindow = &consoleWindow;
    view.displayObjects.append(fm);

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
