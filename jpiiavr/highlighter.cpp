#include "highlighter.h"
#include <QtGui>

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
 DIN
     HighlightingRule rule;

     keywordFormat.setForeground(Qt::darkBlue);
     keywordFormat.setFontWeight(QFont::Bold);
     QStringList keywordPatterns;
     keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                     << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                     << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                     << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                     << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                     << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                     << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                     << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                     << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                     << "\\bvoid\\b" << "\\bvolatile\\b"

                     << "\\b__volatile__\\b" << "\\b__asm__\\b" << "\\uint16_t\\b"
                     << "\\bint16_t\\b" << "\\bdo\\b" << "\\b__const__\\b"
                     << "\\bif\\b" << "\\basm\\b" << "\\bint32_t\\b" << "\\breturn\\b"
                     << "\\buint32_t\\b" << "\\bextern\\b" << "\\bsize_t\\b"
                     << "\\belse\\b" << "\\bwhile\\b" << "#[ ]*define\\b"
                     << "#[ ]*include\\b" << "#[ ]*if\\b" << "#[ ]*endif\\b"
                     << "#[ ]*elseif\\b" << "#[ ]*else\\b" << "#[ ]*ifndef\\b"
                     << "#[ ]*ifdef\\b" << "\\b__inline__\\b" << "#[ ]*elif\\b"
                     << "\\bPCMSK\\b" << "\\bMCUCR\\b" << "\\bTCCR[0-9]+\\b"
                     << "\\bDDR[A,B,C,D]+\\b" << "\\bOCR[0-9]+[A,B]+\\b"
                     << "\\bPIN[A,B,C,D]+[0-9]+\\b" << "\\bISC[0-9]+\\b"
                     << "\\bGIMSK\\b" << "\\bINT[0-9]+\\b" << "\\bP[A,B,C,D]+[0-9]+\\b"
                     << "\\bTCCR[0-9]+[A,B]+\\b" << "\\bCOM[0-9]+[A,B]+[0-9]+\\b"
                     << "\\bWGM[0-9]+\\b" << "\\bF_CPU\\b" << "\\bCS[0-9]+\\b"
                     << "\\bPORT[A,B,C,D]+[0-9]?\\b" << "\\bICR[0-9]+\\b" << "\\bINT[0-9]+_vect\\b"
                     << "\\bFILE\\b" << "\\bUDR\\b" << "\\bint8_t\\b" << "\\buint8_t\\b"
                     << "\\bEOF\\b" << "\\bstdout\\b" << "\\bstderr\\b" << "\\bstdin\\b"
                     << "\\bva_list\\b" << "\\bCOM[0-9]+\\b" << "\\bOCR[0-9]+\\b"
                     << "\\bTIMSK\\b" << "\\bDD[A,B,C,D]+[0-9]+\\b" << "\\bTCNT[0-9]+\\b"
                     << "\\bTOIE[0-9]+\\b" << "\\bfor\\b" << "\\bTIMER[0-9]_OVF_vect\\b";

     foreach (const QString &pattern, keywordPatterns) {
         rule.pattern = QRegExp(pattern);
         rule.format = keywordFormat;
         highlightingRules.append(rule);
     }

     classFormat.setFontWeight(QFont::Bold);
     classFormat.setForeground(Qt::darkMagenta);
     rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
     rule.format = classFormat;
     highlightingRules.append(rule);

     singleLineCommentFormat.setForeground(Qt::darkGreen);
     rule.pattern = QRegExp("//[^\n]*");
     rule.format = singleLineCommentFormat;
     highlightingRules.append(rule);

     multiLineCommentFormat.setForeground(Qt::darkGreen);

     quotationFormat.setForeground(Qt::darkGreen);
     rule.pattern = QRegExp("\".*\"");
     rule.format = quotationFormat;
     highlightingRules.append(rule);

     quotationFormat.setForeground(Qt::darkGreen);
     rule.pattern = QRegExp("<.*>");
     rule.format = quotationFormat;
     highlightingRules.append(rule);

     functionFormat.setFontItalic(true);
     functionFormat.setForeground(Qt::blue);
     rule.pattern = QRegExp("\\b[A-Za-z0-9_ ]+(?=\\()");
     rule.format = functionFormat;
     highlightingRules.append(rule);


     operatorFormat.setFontItalic(true);
     operatorFormat.setForeground(QColor(Qt::gray));
     QStringList operatorPatterns;
     operatorPatterns << "[+-&^/\*!~|]?=" << "<<" << ">>" << "&&";

     foreach (const QString &pattern, operatorPatterns) {
         rule.pattern = QRegExp(pattern);
         rule.format = operatorFormat;
         highlightingRules.append(rule);
     }

     operatorFormat.setForeground(Qt::red);
     rule.pattern = QRegExp("[~!]+");
     rule.format = operatorFormat;
     highlightingRules.append(rule);

     commentStartExpression = QRegExp("/\\*");
     commentEndExpression = QRegExp("\\*/");
DOUT
}

void Highlighter::highlightBlock(const QString &text)
{
 //DIN
     foreach (const HighlightingRule &rule, highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = commentStartExpression.indexIn(text);

     while (startIndex >= 0) {
         int endIndex = commentEndExpression.indexIn(text, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex
                             + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, multiLineCommentFormat);
         startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
     }
 //DOUT
}
