#include "abstractmodels.h"
#include "rocketlauncher2.h"
#include "ui_rocketlauncher2.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QString>
#include <QtDebug>

//=========================ENGINES================================

EngineListModel::EngineListModel(QObject *parent) :
    QAbstractListModel(parent),
    EngineSettings(QSettings::IniFormat,QSettings::UserScope,"RocketLauncher2","Engines")
{
    EngineSet = false;
    m_mainAppPath = QApplication::applicationDirPath();
}

int EngineListModel::rowCount(const QModelIndex &parent) const {
    return Engines_.count();
}

void EngineListModel::setCurrentEngine(const int index)
{
    qDebug() << "Udating Engine at index " << index;
    qDebug().quote();
    if (index >= Engines_.size()) return;
    else
    {
        selectedEngine_ = &Engines_[index];
        if (!EngineSet)
            EngineSet = true;
    }
    EngineSettings.setValue("Last Index", index);
}

EngineInfo* EngineListModel::getCurrentEngine()
{
    return selectedEngine_;
}

QString EngineListModel::addEngine(QFileInfo file)
{
    if (!file.exists())
        return "Error";
    qDebug() << "Adding Engine";
    qDebug().quote();
    if (file.baseName().compare( QString("zandronum"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("Zandronum", file.absoluteFilePath(), Engine_ZDoom, Pic_Zandronum, true);
    }
    else if (file.baseName().compare( QString("zdoom"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("ZDoom", file.absoluteFilePath(), Engine_ZDoom, Pic_Zdoom, true);
    }
    else if (file.baseName().compare( QString("gzdoom"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("GZDoom", file.absoluteFilePath(), Engine_ZDoom, Pic_GZdoom, true);
    }
    else if (file.baseName().compare( QString("chocolate-doom"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("Chocolate Doom", file.absoluteFilePath(), Engine_Oldschool, Pic_Chocolate, true);
    }
    else if (file.baseName().compare( QString("prboom-plus"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("PrBoom+", file.absoluteFilePath(), Engine_Oldschool, Pic_PrBoom, true);
    }
    else if (file.baseName().compare( QString("prboom"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("PrBoom", file.absoluteFilePath(), Engine_Oldschool, Pic_PrBoom, true);
    }
    else if (file.baseName().compare( QString("glboom"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("GLBoom", file.absoluteFilePath(), Engine_Oldschool, Pic_PrBoom, true);
    }
    else if (file.baseName().compare( QString("glboom-plus"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("GLBoom+", file.absoluteFilePath(), Engine_Oldschool, Pic_PrBoom, true);
    }
    else if (file.baseName().compare( QString("zdaemon"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("ZDaemon", file.absoluteFilePath(), Engine_ZDoom, Pic_ZDaemon, true);
    }
    else if (file.baseName().compare( QString("odamex"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("Odamex", file.absoluteFilePath(), Engine_Oldschool, Pic_Odamex, true);
    }
    else if (file.baseName().compare( QString("eternity"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("Eternity Engine", file.absoluteFilePath(), Engine_Oldschool, Pic_Eternity, true);
    }
    else if (file.baseName().compare( QString("legacy"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("Legacy", file.absoluteFilePath(), Engine_Oldschool, Pic_Legacy, true);
    }
    else if (file.baseName().compare( QString("doomsday"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("Doomsday Engine", file.absoluteFilePath(), Engine_Default, Pic_Doomsday, true);
    }
    else if (file.baseName().compare( QString("vavoom"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("Vavoom", file.absoluteFilePath(), Engine_Default, Pic_Vavoom, true);
    }
    else if (file.baseName().left(4).compare( QString("edge"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("EDGE", file.absoluteFilePath(), Engine_Default, Pic_Edge, true);
    }
    else if (file.baseName().compare( QString("doomretro"), Qt::CaseInsensitive) == 0)
    {
        return updateEngine("Doom Retro", file.absoluteFilePath(), Engine_Default, Pic_Retro, true);
    }
    else
    {
        return updateEngine(file.baseName(), file.absoluteFilePath(), Engine_Default, Pic_Default, false);
    }
}

QString EngineListModel::updateEngine(QString engine, QString path, EngineType type, EnginePic pic, bool known)
{
    int searchResult;
    searchResult = SearchEngines(engine);
    if (searchResult > -1)
    {
        Engines_[searchResult].path = path;
        QMessageBox::information(NULL,"Executable Updated", QString("%1 engine updated!").arg(engine));
        emit updateCombo(engine);
        emit dataChanged(QModelIndex(),QModelIndex());
        SaveEngineData();

        return "Success";
    }
    EngineInfo newengine = {path, engine, type, pic};
    Engines_ << newengine;
    if (known)
        QMessageBox::information(NULL,"Executable Added",QString("%1 engine added!").arg(engine));
    else
        QMessageBox::information(NULL,"Unkown executable","Unrecognized engine added!");
    emit updateCombo(engine);
    emit dataChanged(QModelIndex(),QModelIndex());
    SaveEngineData();

    return "Success";
}

QVariant EngineListModel::data(const QModelIndex& index, int role) const {
    // Check that the index is valid and within the correct range first:
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= Engines_.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        // Only returns something for the roles you support (DisplayRole is a minimum)
        return QVariant(Engines_.at(index.row()).name);
    } else {
        return QVariant();
    }
}


int EngineListModel::SearchEngines(const QString name)
{
    for (const EngineInfo &engine : Engines_)
    {
        if (engine.name == name)
        {
            return Engines_.indexOf(engine);
        }
    }
    return -1;
}

void EngineListModel::LoadEngineData()
{
    int size = EngineSettings.beginReadArray("Engines");
    for (int i = 0; i < size; i++)
    {
        EngineSettings.setArrayIndex(i);
        EngineInfo newengine = { EngineSettings.value("path").toString(),
                                 EngineSettings.value("name").toString(),
                                 static_cast<EngineType>(EngineSettings.value("type").toInt()),
                                 static_cast<EnginePic>(EngineSettings.value("image").toInt())
                               };
        Engines_.append(newengine);
    }
    EngineSettings.endArray();
    emit dataChanged(QModelIndex(),QModelIndex());
    int lastIndex = EngineSettings.value("Last Index").toInt();
    setCurrentEngine(lastIndex);
    emit updateComboIndex(lastIndex);
}

void EngineListModel::SaveEngineData()
{
    EngineSettings.beginWriteArray("Engines");
    for (int i = 0; i < Engines_.count(); i++)
    {
        EngineSettings.setArrayIndex(i);
        EngineSettings.setValue("path", Engines_.at(i).path);
        EngineSettings.setValue("name", Engines_.at(i).name);
        EngineSettings.setValue("type", static_cast<int>(Engines_.at(i).type));
        EngineSettings.setValue("image", static_cast<int>(Engines_.at(i).EngineImage));
    }
    EngineSettings.endArray();
}

EngineType EngineListModel::getEngineType()
{
    return selectedEngine_->type;
}
//========================Configs=======================



ConfigListModel::ConfigListModel(QObject *parent) :QAbstractListModel(parent)
{
    failRocket = RocketFile();
    failRocket.name = "fail";
}

void ConfigListModel::addRocket(const RocketFile &file)
{
    rockets.append(file);
    emit dataChanged(QModelIndex(),QModelIndex());
}

int ConfigListModel::rowCount(const QModelIndex &) const {
    return rockets.count();
}

QVariant ConfigListModel::data(const QModelIndex& index, int role) const {
    // Check that the index is valid and within the correct range first:
    if (!index.isValid()) return QVariant();
    if (index.row() >= rockets.size()) return QVariant();

    if (role == Qt::DisplayRole) {
        // Only returns something for the roles you support (DisplayRole is a minimum)

        return QVariant(rockets.at(index.row()).name);
    }
    else {
        return QVariant();
    }
}

RocketFile *ConfigListModel::getSelectedRocket(const QModelIndex &index)
{
    if (!index.isValid()) return &failRocket;
    if (index.row() >= rockets.size()) return &failRocket;

    else
    {
        return &rockets[index.row()];
    }
}

RocketFile *ConfigListModel::getRocketFromRow(int row)
{
    if (row > rockets.count())
        return &failRocket;
    else
        return &rockets[row];
}

void ConfigListModel::removeRow(int row, const QModelIndex &parent)
{
    rockets.removeAt(row);
    QAbstractListModel::removeRow(row, parent);
}
