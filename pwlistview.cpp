#include "pwlistview.h"

#include <QListView>
#include <QMessageBox>
#include <QDragEnterEvent>

PWListView::PWListView(QWidget *parent) :
    QListView(parent)

{
    setAcceptDrops(true);
}

void PWListView::dropEvent(QDropEvent *e)
{
    e->acceptProposedAction();
    QMessageBox::information(this,"congrats!","You just dropped an item!");
    //QListView::dropEvent(e);
}

void PWListView::dragMoveEvent(QDragMoveEvent *e){
    e->acceptProposedAction();
}

void PWListView::dragEnterEvent(QDragEnterEvent *event)
{
   event->acceptProposedAction();
}


