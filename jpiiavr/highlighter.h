/*******************************************************************************
  Application name: jpiiAVR
  Filename: highlighter.h
  Author: Juhapekka Piiroinen
  License: GNU/GPLv3
  Description:
      This is a quick-and-dirty application for avrdude.

  (C) 2010 Juhapekka Piiroinen
  http://code.google.com/p/quickanddirty
  juhapekka.piiroinen@gmail.com
*******************************************************************************/
#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

//more information about syntax highting
//http://qt.nokia.com/doc/4.6/richtext-syntaxhighlighter-highlighter-cpp.html

#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>
#include <QTextDocument>

#include "common.h"

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;
    QRegExp commentStartExpression;
    QRegExp commentEndExpression;
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat operatorFormat;
};

#endif // HIGHLIGHTER_H
