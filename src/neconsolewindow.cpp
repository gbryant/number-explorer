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


#include "neconsolewindow.h"
#include "nemainwindow.h"

#include "consolecommands.cpp"

NEConsoleWindow::NEConsoleWindow(QWidget *parent) : QWidget(parent)
{
    textEdit.setReadOnly(true);
    textEdit.setFocusPolicy(Qt::NoFocus);
    layout.addWidget(&textEdit);
    layout.addWidget(&lineEdit);
    setLayout(&layout);
    QObject::connect(&lineEdit,&QLineEdit::returnPressed,this,&NEConsoleWindow::returnPressedSlot);
    appendText("Type h for help\n");
}

void NEConsoleWindow::init()
{
    commands.append(new QuitApp(this));
    commands.append(new TestCommand(this));
    commands.append(new ToggleBoolean(this,&(mainWindow->view.showCrossHairs),"showCrossHairs","sch"));
    commands.append(new ToggleBoolean(this,&(mainWindow->view.showClickPoints),"showClickPoints","scp"));
}

void NEConsoleWindow::returnPressedSlot()
{
    QString text = lineEdit.text();
    if(text==""){return;}

    if(text=="h"||text=="help"||text=="?")
    {
        appendText("\n");
        appendText("help/h/?\tfor list of commands\n");
        for( int i=0; i<commands.count(); i++ )
        {
            appendText(commands[i]->name+"\t"+commands[i]->description+"\n");
        }
        appendText("\n");
        lineEdit.setText("");
    }
    else
    {
        bool handled=false;
        for( int i=0; i<commands.count(); i++ )
        {
            if(commands[i]->name==text || commands[i]->alias==text){commands[i]->command(0);handled=true;}
        }
        if(!handled)
        {
            QStringList cmdTxts = text.split(' ');
            for( int i=0; i<commands.count(); i++ )
            {
                if(commands[i]->name==cmdTxts[0]||commands[i]->alias==cmdTxts[0]){commands[i]->command(&cmdTxts[1]);handled=true;}
            }
        }
    }

}

void NEConsoleWindow::appendText(QString text)
{
    textEdit.moveCursor(QTextCursor::End);
    textEdit.insertPlainText(text);
    textEdit.ensureCursorVisible();
}
