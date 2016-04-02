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
    Pic_Edge
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
    EngineType getEngineType();

private:

    QList<EngineInfo> Engines_;
    EngineInfo *selectedEngine_;
    int SearchEngines(const QString name);
    QDir m_mainAppPath;
    QSettings EngineSettings;
    void SaveEngineData();
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

