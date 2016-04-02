#ifndef PWLISTVIEW_H
#define PWLISTVIEW_H

#include <QListView>


class PWListView : public QListView
{
    Q_OBJECT

public:
    PWListView(QWidget *parent = 0);
    void dropEvent(QDropEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *e);
    //void dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent);

};

#endif // PWLISTVIEW_H
