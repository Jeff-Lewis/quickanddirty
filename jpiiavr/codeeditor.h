/*******************************************************************************
  Application name: jpiiAVR
  Filename: codeeditor.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application for avrdude.

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
*******************************************************************************/
#ifndef CODEEDITOR_H
#define CODEEDITOR_H

//more information about codeeditor
//http://pepper.troll.no/s60prereleases/doc/widgets-codeeditor.html

#include <QPlainTextEdit>
#include <QObject>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>

#include "common.h"
#include "highlighter.h"


class LineNumberArea;

///////////////////////////////////////////////////////////////////
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void addErrorLine(int line)     { this->errorLines.append(line); }
    void clearErrorLines()          { this->errorLines.clear(); }
    void addWarningLine(int line)   { this->warningLines.append(line); }
    void clearWarningLines()        { this->warningLines.clear(); }

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
    Highlighter* highlighter;
    QList<int> errorLines;
    QList<int> warningLines;
};

/////////////////////////////////////////////////////////////////////
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor)
    {
        this->codeEditor = editor;
    }

    QSize sizeHint() const
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

#endif // CODEEDITOR_H
