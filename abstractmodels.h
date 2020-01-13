/*  This file (abstractmodels.h) is part of Rocket Launcher 2.0 - A cross platform
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

#ifndef ABSTRACTMODELS_H
#define ABSTRACTMODELS_H

#include <QAbstractListModel>
#include <QStringList>
#include <QFileInfoList>
#include <QList>
#include <QPixmap>
#include <QDir>
#include <QSettings>

#include "configs.h"

enum EngineType
{
    Engine_Default,
    Engine_ZDoom,
    Engine_Oldschool,
    Engine_DosBox
};

enum EnginePic
{
    Pic_Default,
    Pic_Zandronum,
    Pic_Zdoom,
    Pic_GZdoom,
    Pic_Chocolate,
    Pic_Eternity,
    Pic_PrBoom,
    Pic_Odamex,
    Pic_ZDaemon,
    Pic_Legacy,
    Pic_Retro,
    Pic_Vavoom,
    Pic_Doomsday,
    Pic_Edge,
    Pic_LZdoom
};

struct EngineInfo
{
    QString path;
    QString name;
    EngineType type;
    EnginePic EngineImage;
};

inline bool operator==(const EngineInfo &e1, const EngineInfo &e2)
{
    return e1.name == e2.name;
}

//==================ENGINES===========================

class EngineListModel : public QAbstractListModel {

    Q_OBJECT

signals:
     void updateCombo(const QString text);
     void updateComboIndex(int index);

public:

    explicit EngineListModel(QObject* parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    void setCurrentEngine(const int index);
    QString addEngine(QFileInfo file);
    EngineInfo *getCurrentEngine();
    QString updateEngine(QString engine, QString path, EngineType type, EnginePic pic, bool known);
    bool EngineSet;
    void LoadEngineData();
    bool isEmpty();
    EngineType getEngineType();
    QString DoomExePath;
    void removeRow(int row, const QModelIndex &parent = QModelIndex());
    void moveRowDown(int row, const QModelIndex &parent = QModelIndex());
    void moveRowUp(int row, const QModelIndex &parent = QModelIndex());
    QSettings EngineSettings;
    void SaveEngineData();
    EngineType getEngineTypeFromIndex(const QModelIndex &index);
    EnginePic getEnginePicFromIndex(const QModelIndex &index);
    void addDefaultEngine(QString path);
    void setNameFromIndex(QString name, const QModelIndex &index);
    void setPathFromIndex(QString path, const QModelIndex &index);
    void setTypeFromIndex(EngineType type, const QModelIndex &index);
    void setPicFromIndex(EnginePic pic, const QModelIndex &index);
    void setDoomExeSave();

private:

    QList<EngineInfo> Engines_;
    EngineInfo *selectedEngine_;
    int SearchEngines(const QString name);
    QDir m_mainAppPath;
    void setupDosbox(QString path);
    void setDoomExe();
};

//================Configs=================


class ConfigListModel : public QAbstractListModel {

    Q_OBJECT

public:

    explicit ConfigListModel(QObject* parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    void addRocket(const RocketFile &file);
    void removeRow(int row, const QModelIndex &parent = QModelIndex());
    RocketFile *getSelectedRocket(const QModelIndex &index);
    RocketFile failRocket;
    RocketFile *getRocketFromRow(int row);

private:

    QList<RocketFile> rockets;
};

#endif // ABSTRACTMODELS_H

