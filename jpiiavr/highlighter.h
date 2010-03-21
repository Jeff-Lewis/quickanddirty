#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

//http://qt.nokia.com/doc/4.6/richtext-syntaxhighlighter-highlighter-cpp.html

 #include <QSyntaxHighlighter>
#include "common.h"

 #include <QHash>
 #include <QTextCharFormat>

 class QTextDocument;

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
