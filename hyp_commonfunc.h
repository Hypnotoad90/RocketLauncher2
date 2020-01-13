/*  This file (hyp_commonfunc.h) is part of Rocket Launcher 2.0 - A cross platform
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

#ifndef HYP_COMMONFUNC_H
#define HYP_COMMONFUNC_H

#include <QString>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QSettings>

#include "dndfilesystemlistview.h"

bool inputExists (QString &name);

bool fileExists (QString &file);

bool isFile(QString &file);

void removeSelectedFromDnDListView(DndFileSystemListView *listview, QStandardItemModel *model);

bool updateDndListView(QString filepath, QStandardItemModel *model, bool checkable, bool checksate = true);

void saveListviewPath(QString ArrayName, QString key, QString Path, QSettings &settings);

void removeSelectedFromDnDListViewSave(DndFileSystemListView *listview, QStandardItemModel *model, QString ArrayName, QString key, QSettings &settings);

void copyItemToDndListView(DndFileSystemListView *source, QStandardItemModel *DestinationModel, bool checkable);
void moveItemWithinDndListView(DndFileSystemListView *source, QStandardItemModel *DestinationModel, bool moveDown);

void copyItemToDndListViewSave(DndFileSystemListView *source, QStandardItemModel *DestinationModel, bool checkable, QString array, QString key, QSettings &settings);
void moveItemWithinDndListViewSave(DndFileSystemListView *source, QStandardItemModel *DestinationModel, QString array, QString key, QSettings &settings, bool moveDown = false);
QString returnSelectedDndViewItemData(DndFileSystemListView *listview, int role = Qt::UserRole);

QModelIndex getIndexOfDisplayText(QAbstractItemModel *model, QString text);

QStringList splitArgs(QString string);


#endif // HYP_COMMONFUNC_H
