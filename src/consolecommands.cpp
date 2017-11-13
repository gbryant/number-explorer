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


#include "neconsolecommand.h"
#include "neconsolewindow.h"
#include "nemainwindow.h"
#include <boost/multiprecision/gmp.hpp>

using boost::multiprecision::abs;
using boost::multiprecision::mpz_int;

class ToggleBoolean : public NEConsoleCommand
{
public:

    QString label;
    QString aliasLabel;
    bool    *value;

    ToggleBoolean(NEConsoleWindow *consoleWindow,bool *boolVal, QString label, QString aliasLabel):NEConsoleCommand(consoleWindow)
    {
        name = "toggle";
        alias = "t";
        description = "toggle/t "+label+"/"+aliasLabel;
        this->label = label;
        this->value = boolVal;
        this->aliasLabel = aliasLabel;
    }
    void command(void *data);
};

void ToggleBoolean::command(void *data)
{
    QString *txt = (QString*)data;
    if(txt==label||txt==aliasLabel)
    {
        (*value) = !(*value);
        consoleWindow->appendText(label+": "+QString::number(*value)+"\n");
        consoleWindow->mainWindow->view.render();
        consoleWindow->mainWindow->view.update();
        consoleWindow->lineEdit.setText("");
    }
}

mpz_int _fixYOffsetAndSign(mpz_int x, mpz_int y);
mpz_int _fixYOffsetAndSign(mpz_int x, mpz_int y)
{
    mpz_int temp;

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

class QuitApp : public NEConsoleCommand
{
public:
    QuitApp(NEConsoleWindow *consoleWindow):NEConsoleCommand(consoleWindow)
    {
        name = "quit";
        alias = "q";
        description = "quit application";
    }
    void command(void *data);
};

void QuitApp::command(void *data)
{
    qApp->exit();
    consoleWindow->lineEdit.setText("");
}



class TestCommand : public NEConsoleCommand
{
public:
    TestCommand(NEConsoleWindow *consoleWindow):NEConsoleCommand(consoleWindow)
    {
        name = "test";
        alias = "t";
        description = "test command";
    }
    void command(void *data);
};

void TestCommand::command(void *data)
{
    /*
    QString outStr = QString("test ");
    outStr+="\n";
    consoleWindow->appendText(outStr);
    consoleWindow->lineEdit.setText("");








    int width = consoleWindow->mainWindow->graphicsView.viewport()->width();
    int height = consoleWindow->mainWindow->graphicsView.viewport()->height();

    QImage image(width,height,QImage::Format_RGB888);
    image.fill(Qt::black);



    int left = 0;
    int right = width-1;
    mpz_int top = height-1+consoleWindow->mainWindow->graphicsView.yOffset;
    mpz_int bottom = 0+consoleWindow->mainWindow->graphicsView.yOffset;


    for(int i=left;i<right;i++)
        {
            if(i==0){continue;}

            mpz_int j = _fixYOffsetAndSign(i,bottom);

            while(j<=top)
            {
                mpz_int yVal = height-1-j+consoleWindow->mainWindow->graphicsView.yOffset;
                image.setPixel(i,static_cast<int>(yVal),0xFFFFFFFF);
                j+=abs(i);
            }
        }


    QPixmap pixMap;
    pixMap.convertFromImage(image);

    consoleWindow->mainWindow->graphicsScene.addPixmap(pixMap);
*/
    //consoleWindow->mainWindow->graphicsScene.addText("Boom Diggy");
    //consoleWindow->mainWindow->graphicsScene.addEllipse(0,0,10000,10000,QPen(Qt::black),QBrush(Qt::blue));
}
