#include "hyp_commonfunc.h"

#include <QString>
#include <QFileInfo>
#include <QStandardItemModel>

#include "dndfilesystemlistview.h"

bool inputExists (QString &name)
{
    if (name == "" || name.isEmpty() || name.isNull())
        return false;
    else return true;
}

bool fileExists (QString &file)
{
    QFileInfo fi(file);
    if (fi.exists())
        return true;
    else
        return false;
}

bool isFile(QString &file)
{
    QFileInfo fi(file);
    if (fi.isFile())
        return true;
    else
        return false;
}
void removeSelectedFromDnDListView(DndFileSystemListView *listview, QStandardItemModel *model)
{
    listview->setUpdatesEnabled(false);
    QModelIndexList indexes = listview->selectionModel()->selectedIndexes();
    qSort(indexes.begin(), indexes.end());
    for (int i = indexes.count() - 1; i > -1; --i)
    {
        model->removeRow(indexes.at(i).row());

    }
    listview->setUpdatesEnabled(true);
}

void removeSelectedFromDnDListViewSave(DndFileSystemListView *listview, QStandardItemModel *model, QString ArrayName, QString key, QSettings &settings)
{
    listview->setUpdatesEnabled(false);
    QModelIndexList indexes = listview->selectionModel()->selectedIndexes();
    qSort(indexes.begin(), indexes.end());
    for (int i = indexes.count() - 1; i > -1; --i)
    {
        model->removeRow(indexes.at(i).row());

    }
    settings.beginWriteArray(ArrayName);
    settings.remove("");
    for (int i = 0; i < model->rowCount(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue(key, model->item(i)->data(Qt::UserRole).toString());
    }
    settings.endArray();
    listview->setUpdatesEnabled(true);
}


bool updateDndListView(QString filepath, QStandardItemModel *model, bool checkable, bool checksate)
{
    QFileInfo file(filepath);
    if (!file.exists())
        return false;

    QStandardItem *item = new QStandardItem();

    item->setData(file.fileName(),Qt::DisplayRole);
    item->setData(file.absoluteFilePath(),Qt::UserRole);
    item->setDragEnabled(true);
    item->setDropEnabled(false);
    if (checkable)
    {
        item->setCheckable(true);
        if (checksate)
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
    }
    if (model->match(model->index(0,0) , Qt::UserRole, file.absoluteFilePath()).size() > 0)
        return false;
    model->appendRow(item);
    return true;
}

void saveListviewPath(QString ArrayName, QString key, QString Path, QSettings &settings)
{
    int fsize = settings.beginReadArray(ArrayName);
    settings.endArray();
    settings.beginWriteArray(ArrayName);
    settings.setArrayIndex(fsize);
    settings.setValue(key, Path);
    settings.endArray();
}

void copyItemToDndListView(DndFileSystemListView *source, QStandardItemModel *DestinationModel, bool checkable)
{
    QModelIndexList indexes = source->selectionModel()->selectedIndexes();
    qSort(indexes.begin(), indexes.end());
    for (int i = indexes.count() - 1; i > -1; --i)
      updateDndListView(indexes.at(i).data(Qt::UserRole).toString(), DestinationModel, checkable);
}

void copyItemToDndListViewSave(DndFileSystemListView *source, QStandardItemModel *DestinationModel, bool checkable, QString array, QString key, QSettings &settings)
{
    QModelIndexList indexes = source->selectionModel()->selectedIndexes();
    qSort(indexes.begin(), indexes.end());
    for (int i = indexes.count() - 1; i > -1; --i)
    {
        if (updateDndListView(indexes.at(i).data(Qt::UserRole).toString(), DestinationModel, checkable))
            saveListviewPath(array, key, indexes.at(i).data(Qt::UserRole).toString(), settings);
    }
}

QString returnSelectedDndViewItemData(DndFileSystemListView *listview, int role)
{
    QModelIndexList indexes = listview->selectionModel()->selectedIndexes();
    if (indexes.count() < 1)
        return "";
    qSort(indexes.begin(), indexes.end());
    return indexes.at(0).data(role).toString();
}

QModelIndex getIndexOfDisplayText(QAbstractItemModel *model, QString text)
{
    QModelIndexList indexes = model->match(model->index(0,0),Qt::DisplayRole,QVariant::fromValue(text));
    if (indexes.count()> 0)
        return indexes.at(0);
    else
        return QModelIndex();
}
