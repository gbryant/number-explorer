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
    /*
    float xPos = (width-1)/2+xOffset;
    xPos=floor((float)xPos/(float)scale);
    xPos/=(float)pow(10,resolution);
    return xPos;
    */
    mpz_int xPos;
    int err = mpz_set_str(xPos.backend().data(),txt->toStdString().c_str(),10);
    if(err){consoleWindow->lineEdit.setText("failure");return;}

    consoleWindow->mainWindow->view.setXPos(xPos);

    //int xPos = txt->toInt();
    /*
    xPos*=(float)pow(10,cw->displayWidget->display->resolution);
    xPos=(float)xPos*(float)cw->displayWidget->display->scale;
    xPos -= (cw->displayWidget->display->width-1)/2;
    cw->displayWidget->display->xOffset=xPos;
    cw->displayWidget->render();
    cw->displayWidget->update();
    */
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
    consoleWindow->appendText("\n");
    QString outStr = QString("scale: ");
    outStr += QN(consoleWindow->mainWindow->view.scale);
    outStr += "\n";
    outStr += QString("resolution: ");
    outStr += QN(consoleWindow->mainWindow->view.resolution);
    outStr+="\n";
    outStr+="xFactorialOffset: "+QN(consoleWindow->mainWindow->view.xFactorialOffset);
    outStr+="\n";
    outStr+="yFactorialOffset: "+QN(consoleWindow->mainWindow->view.yFactorialOffset);
    outStr+="\n";
    std::stringstream xStream;
    xStream<<consoleWindow->mainWindow->view.xOffset;
    std::stringstream yStream;
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
