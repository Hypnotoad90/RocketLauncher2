/*  This file (hyp_commonfunc.cpp) is part of Rocket Launcher 2.0 - A cross platform
 *  front end for all DOOM engine source ports.
 *
 *  Copyright (C) Hypnotoad
 *
 *  Rocket Launcher is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Rocket Launcher is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Rocket Launcher.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hyp_commonfunc.h"

#include <QString>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QDebug>

#include "dndfilesystemlistview.h"

bool inputExists (QString &name)
{
    return (name == "" || name.isEmpty() || name.isNull());
}

bool fileExists (QString &file)
{
    QFileInfo fi(file);
    return (fi.exists());
}

bool isFile(QString &file)
{
    QFileInfo fi(file);
    return (fi.isFile());
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


bool updateDndListView(QString filepath, QStandardItemModel *model, bool checkable, bool checkstate)
{
    QFileInfo file(filepath);
    if (!file.exists())
        return false;

    QStandardItem *item = new QStandardItem();

    item->setData(file.fileName(), Qt::DisplayRole);
    item->setData(file.absoluteFilePath(), Qt::UserRole);
    item->setDragEnabled(true);
    item->setDropEnabled(false);
    
    if (checkable)
    {
        item->setCheckable(true);
        item->setCheckState(checkstate ? Qt::Checked : Qt::Unchecked);
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

QStringList splitArgs(QString string) //useful approach, found here: qtcentre.org/threads/37304-Split-strings-using-QStringList-split%28%29-but-ignore-quotes?p=213884#post213884
{
    bool inside = false;
    
    if (string.at(0) == '\"')
        inside = true; //true if the first character is "
        
    QStringList tmpList = string.split(QRegExp("\""), QString::SkipEmptyParts); // Split by " and make sure you don't have an empty string at the beginning
    QStringList retlist;
    
    foreach (QString s, tmpList)
    {
        if (inside)
        { // If 's' is inside quotes ...
            retlist.append(s.trimmed()); // ... get the whole string
        }
        else
        { // If 's' is outside quotes ...
            retlist.append(s.split(" ", QString::SkipEmptyParts)); // ... get the splitted string
        }
        inside = !inside;
    }
    
    return retlist;
}
