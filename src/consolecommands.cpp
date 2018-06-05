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

class GoX : public NEConsoleCommand
{
public:
    GoX(NEConsoleWindow *consoleWindow):NEConsoleCommand(consoleWindow)
    {
        name = "x";
        description = "x n go to x coordinate n";
    }
    void command(void *data);
};

void GoX::command(void *data)
{
    QString *txt = (QString*)data;

    mpz_int xPos;
    int err = mpz_set_str(xPos.backend().data(),txt->toStdString().c_str(),10);
    if(err){consoleWindow->lineEdit.setText("failure");return;}

    consoleWindow->mainWindow->view.setXPos(xPos);

    consoleWindow->mainWindow->view.render();
    consoleWindow->mainWindow->view.update();
    consoleWindow->lineEdit.setText("");
}

class GoY : public NEConsoleCommand
{
public:
    GoY(NEConsoleWindow *consoleWindow):NEConsoleCommand(consoleWindow)
    {
        name = "y";
        description = "y n go to y coordinate n";
    }
    void command(void *data);
};

void GoY::command(void *data)
{
    QString *txt = (QString*)data;

    mpz_int yPos;
    int err = mpz_set_str(yPos.backend().data(),txt->toStdString().c_str(),10);
    if(err){consoleWindow->lineEdit.setText("failure");return;}

    consoleWindow->mainWindow->view.setYPos(yPos);

    consoleWindow->mainWindow->view.render();
    consoleWindow->mainWindow->view.update();
    consoleWindow->lineEdit.setText("");
}

class GoScale : public NEConsoleCommand
{
public:
    GoScale(NEConsoleWindow *consoleWindow):NEConsoleCommand(consoleWindow)
    {
        name = "zoom";
        alias = "z";
        description = "zoom n set scale to n";
    }
    void command(void *data);
};

void GoScale::command(void *data)
{
    QString *txt = (QString*)data;

    int scale = txt->toInt();
    if(scale<=0){scale=2;}

    consoleWindow->mainWindow->view.setScale(scale);

    consoleWindow->mainWindow->view.render();
    consoleWindow->mainWindow->view.update();
    consoleWindow->lineEdit.setText("");
}

class PrintInfo : public NEConsoleCommand
{
public:
    PrintInfo(NEConsoleWindow *consoleWindow):NEConsoleCommand(consoleWindow)
    {
        name = "p";
        description = "print various pieces of debug information";
    }
    void command(void *data);
};

void PrintInfo::command(void *data)
{
    mpz_int left;
    mpz_int right;
    mpz_int top;
    mpz_int bottom;
    std::stringstream xStream;
    std::stringstream yStream;
    consoleWindow->mainWindow->view.getScreenBounds(&top,&bottom,&left,&right);
    consoleWindow->appendText("\n");
    QString outStr = QString("scale: ");
    outStr += QN(consoleWindow->mainWindow->view.scale);
    outStr += "\n";
    outStr += QString("resolution: ");
    outStr += QN(consoleWindow->mainWindow->view.resolution);
    outStr+="\n";
    xStream.str("");
    yStream.str("");
    xStream<<top;
    yStream<<bottom;
    outStr+="top: "+QString::fromStdString(xStream.str());
    outStr+=" bottom: "+QString::fromStdString(yStream.str());
    outStr+="\n";
    xStream.str("");
    yStream.str("");
    xStream<<left;
    yStream<<right;
    outStr+="left: "+QString::fromStdString(xStream.str());
    outStr+=" right: "+QString::fromStdString(yStream.str());
    outStr+="\n";
    outStr+="xFactorialOffset: "+QN(consoleWindow->mainWindow->view.xFactorialOffset);
    outStr+="\n";
    outStr+="yFactorialOffset: "+QN(consoleWindow->mainWindow->view.yFactorialOffset);
    outStr+="\n";
    xStream.str("");
    yStream.str("");
    xStream<<consoleWindow->mainWindow->view.xOffset;
    yStream<<consoleWindow->mainWindow->view.yOffset;
    outStr+="xOffset:"+QString::fromStdString(xStream.str());
    outStr+="\n";
    outStr+="yOffset:"+QString::fromStdString(yStream.str());
    outStr+="\n";
    xStream.str("");
    yStream.str("");
    xStream<<consoleWindow->mainWindow->view.xScrollAmt;
    yStream<<consoleWindow->mainWindow->view.yScrollAmt;
    outStr+="xScrollAmt:"+QString::fromStdString(xStream.str());
    outStr+="\n";
    outStr+="yScrollAmt:"+QString::fromStdString(yStream.str());
    outStr+="\n";
    consoleWindow->appendText(outStr);
    consoleWindow->appendText("center point: ");
    consoleWindow->mainWindow->view.printScreenPoint(consoleWindow->mainWindow->view.width()/2,consoleWindow->mainWindow->view.height()/2);
    consoleWindow->appendText("\n");
    consoleWindow->lineEdit.setText("");
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

class AppKeys : public NEConsoleCommand
{
public:
    AppKeys(NEConsoleWindow *consoleWindow):NEConsoleCommand(consoleWindow)
    {
        name = "keys";
        description = "prints a list of keystrokes";
    }
    void command(void *data);
};

void AppKeys::command(void *data)
{
    consoleWindow->appendText("\n");
    consoleWindow->appendText("control + \t--- zoom in\n");
    consoleWindow->appendText("control - \t--- zoom out\n");
    //consoleWindow->appendText("alt + \t--- increase resolution\n");
    //consoleWindow->appendText("alt - \t--- decrease resolution\n");
    consoleWindow->appendText("arrow keys --- scroll around by 10 pixels\n");
    consoleWindow->appendText("arrow keys with shift  --- scroll around by 1 pixel\n");
    consoleWindow->appendText("arrow keys with control --- scroll around by 100 pixels\n");
    consoleWindow->appendText("arrow keys with control and shift --- scroll around by 500 pixels\n");
    consoleWindow->appendText("arrow keys with alt --- scroll by factorials\n");
    consoleWindow->appendText("space bar \t--- click point under crosshair\n");
    consoleWindow->lineEdit.setText("");
}

/*
class DumpData : public ConsoleCommand
{
public:
    DumpData(ConsoleWindow *consoleWindow):ConsoleCommand(consoleWindow)
    {
        name = "dump";
        description = "dump data points";
    }
    void command(void *data);
};

void DumpData::command(void *data)
{
    for(int i=0;i<cw->displayWidget->displayObjects.count();i++)
    {
        if(cw->displayWidget->displayObjects[i]->name=="PointData")
        {
            for(int j=0;j<((PointData*)cw->displayWidget->displayObjects[i])->points.count();j++)
            {
                float a = ((PointData*)cw->displayWidget->displayObjects[i])->points[j].first;
                float b = ((PointData*)cw->displayWidget->displayObjects[i])->points[j].second;
                cw->appendText(QN(a)+","+QN(b)+"\n");
            }
        }
    }
    cw->ui->lineEdit->setText("");
}
*/


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

}
