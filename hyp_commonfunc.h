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

void copyItemToDndListViewSave(DndFileSystemListView *source, QStandardItemModel *DestinationModel, bool checkable, QString array, QString key, QSettings &settings);

QString returnSelectedDndViewItemData(DndFileSystemListView *listview, int role = Qt::UserRole);

QModelIndex getIndexOfDisplayText(QAbstractItemModel *model, QString text);


#endif // HYP_COMMONFUNC_H
