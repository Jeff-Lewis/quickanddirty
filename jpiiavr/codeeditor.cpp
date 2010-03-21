#include "codeeditor.h"
#include <QtGui>

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
 {
    DIN
         lineNumberArea = new LineNumberArea(this);
         this->highlighter = new Highlighter(this->document());

         connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
         connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));
         connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

         updateLineNumberAreaWidth(0);
         highlightCurrentLine();
    DOUT
 }



 int CodeEditor::lineNumberAreaWidth()
 {
     DIN
         int digits = 1;
         int max = qMax(1, blockCount());
         while (max >= 10) {
             max /= 10;
             ++digits;
         }

         int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
    DOUT
         return space;
 }



 void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
 {
     DIN
        setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
     DOUT
 }



 void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
 {
     DIN
         if (dy)
             lineNumberArea->scroll(0, dy);
         else
             lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

         if (rect.contains(viewport()->rect()))
             updateLineNumberAreaWidth(0);
     DOUT
 }



 void CodeEditor::resizeEvent(QResizeEvent *e)
 {
     DIN
         QPlainTextEdit::resizeEvent(e);

         QRect cr = contentsRect();
         lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
     DOUT
 }



 void CodeEditor::highlightCurrentLine()
 {
     DIN
         QList<QTextEdit::ExtraSelection> extraSelections;

         if (!isReadOnly()) {
             QTextEdit::ExtraSelection selection;

             QColor lineColor = QColor(Qt::blue).lighter(190);

             selection.format.setBackground(lineColor);
             selection.format.setProperty(QTextFormat::FullWidthSelection, true);
             selection.cursor = textCursor();
             selection.cursor.clearSelection();
             extraSelections.append(selection);
         }

         setExtraSelections(extraSelections);
     DOUT
 }



 void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
 {
     DIN
         QPainter painter(lineNumberArea);
         painter.fillRect(event->rect(), QColor(Qt::gray).lighter(140));


         QTextBlock block = firstVisibleBlock();
         int blockNumber = block.blockNumber();
         int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
         int bottom = top + (int) blockBoundingRect(block).height();

         while (block.isValid() && top <= event->rect().bottom()) {
             if (block.isVisible() && bottom >= event->rect().top()) {
                 QString number = QString::number(blockNumber + 1);
                 painter.setPen(Qt::gray);
                 painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                                  Qt::AlignRight, number);
             }

             block = block.next();
             top = bottom;
             bottom = top + (int) blockBoundingRect(block).height();
             ++blockNumber;
         }
     DOUT
 }
