/*  This file (configs.cpp) is part of Rocket Launcher 2.0 - A cross platform
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

#include "configs.h"
#include "rocketlauncher2.h"
#include "ui_rocketlauncher2.h"
#include "dndfilesystemlistview.h"
#include "hyp_commonfunc.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

void RocketLauncher2::on_button_loadConfigExt_clicked()
{
    QString settingsDir = QFileDialog::getOpenFileName(this,"Load a configuration file.", QString(),"Rocket Files (*.rocket)");
    if (settingsDir != NULL)
    {
        loadExtConfig(settingsDir);
    }
}

void RocketLauncher2::autoLoadConfig(){
    AutoLoad.beginReadArray("configs");
    if (AutoLoad.contains("name"))
    {
        RocketFile *rocket = new RocketFile();
        rocket->name = AutoLoad.value("name").toString();
        rocket->engName = AutoLoad.value("engName").toString();
        rocket->iwadName = AutoLoad.value("iwadName").toString();
        rocket->filePaths = AutoLoad.value("filePaths").toStringList();
        rocket->map = AutoLoad.value("map").toString();
        rocket->skill = AutoLoad.value("skill").toInt();
        rocket->addCmd = AutoLoad.value("addCmd").toString();
        rocket->demo = AutoLoad.value("demo").toBool();
        rocket->demoName = AutoLoad.value("demoName").toString();
        rocket->noMonsters = AutoLoad.value("noMonsters").toBool();
        rocket->noMusic = AutoLoad.value("noMusic").toBool();

        foreach( QVariant v, AutoLoad.value("filesChecked").toList())
        {
            rocket->filesChecked << v.toBool();
        }

        applyConfig(rocket);
        delete rocket;
    }
}


void RocketLauncher2::initConfigs()
{
    conflist = new ConfigListModel();
    ui->listbox_configFavs->setModel(conflist);

    int asize = ConfigSettings.beginReadArray("configs");
    for (int i = 0; i < asize; i++)
    {
        ConfigSettings.setArrayIndex(i);
        RocketFile rocket;
        rocket.name = ConfigSettings.value("name").toString();
        rocket.engName = ConfigSettings.value("engName").toString();
        rocket.iwadName = ConfigSettings.value("iwadName").toString();
        rocket.filePaths = ConfigSettings.value("filePaths").toStringList();
        rocket.map = ConfigSettings.value("map").toString();
        rocket.skill = ConfigSettings.value("skill").toInt();
        rocket.addCmd = ConfigSettings.value("addCmd").toString();
        rocket.demo = ConfigSettings.value("demo").toBool();
        rocket.demoName = ConfigSettings.value("demoName").toString();
        rocket.noMonsters = ConfigSettings.value("noMonsters").toBool();
        rocket.noMusic = ConfigSettings.value("noMusic").toBool();
        foreach(QVariant v, ConfigSettings.value("filesChecked").toList()) {
          rocket.filesChecked << v.toBool();
        }
        conflist->addRocket(rocket);
    }

    ConfigSettings.endArray();
}

void RocketLauncher2::on_button_addConfToFav_clicked()
{
    QString name = ui->input_confName->text();

    if (!inputExists(name))
    {
        QMessageBox::information(this,"Input Name", "Please input a name for this config to be saved");
        return;
    }

    if (getIndexOfDisplayText(conflist,ui->input_confName->text()) != QModelIndex())
    {
        QMessageBox::information(this, "Change Name" , "A profile of this name already exists!");
        return;
    }

    RocketFile rocket = makeConfigFromCurrent(name);
    conflist->addRocket(rocket);
    saveToGlobal(rocket);
}

RocketFile RocketLauncher2::makeConfigFromCurrent(QString name)
{
    RocketFile rocket;
    rocket.name = name;
    rocket.engName = enginelist->getCurrentEngine()->name;
    rocket.iwadName = returnSelectedDndViewItemData(ui->listbox_IWADs, Qt::DisplayRole);

    for (int row = 0; row < pwadloadlist->rowCount(); row++)
    {
        rocket.filePaths.append(pwadloadlist->item(row)->data(Qt::UserRole).toString());
    }

    rocket.map = ui->input_map->text();
    rocket.skill = ui->combo_skill->currentIndex();
    rocket.addCmd = ui->input_argbox->text();
    rocket.demo = ui->check_record->isChecked();
    rocket.demoName = ui->input_record->text();
    rocket.noMonsters = ui->check_nomonsters->isChecked();
    rocket.noMusic = ui->check_nomusic->isChecked();

    for (int i = 0; i < pwadloadlist->rowCount(); i++)
    {
        if (pwadloadlist->item(i)->checkState() == Qt::Checked)
            rocket.filesChecked.append(QVariant(true));
        else
            rocket.filesChecked.append(QVariant(false));
    }

    return rocket;
}

void RocketLauncher2::applyConfig(RocketFile *rocket)
{
    if (rocket->name == "fail")
        return;

    if (ui->combo_Engines->findText(rocket->engName) > -1)
    {
        ui->combo_Engines->setCurrentText(rocket->engName);
        //enginelist->s
    }
    else
    {
        QMessageBox::information(this, "Engine not found!", QString("Warning, %1 engine could not be found.").arg(rocket->engName));
    }

    QModelIndexList indexes = iwadlist->match(iwadlist->index(0,0),Qt::DisplayRole,QVariant::fromValue(rocket->iwadName));
    if (indexes.count() > 0)
    {
        //ui->listbox_IWADs->
        ui->listbox_IWADs->setCurrentIndex(indexes.at(0));
    }
    else
    {
        QMessageBox::information(this, "IWAD not found!", QString("Warning, %1 IWAD could not be found.").arg(rocket->iwadName));
    }

    pwadloadlist->clear();

    if (rocket->filePaths.count() == rocket->filesChecked.count())
    {
        for (int i = 0; i < rocket->filePaths.count(); i++)
        {
            addpwad(rocket->filePaths.at(i));
            if (rocket->filesChecked.at(i).toBool() == true)
                pwadloadlist->item(i)->setCheckState(Qt::Checked);
            else
                pwadloadlist->item(i)->setCheckState(Qt::Unchecked);
        }
    }

    else
    {
        for (int i = 0; i < rocket->filePaths.count(); i++)
        {
            addpwad(rocket->filePaths.at(i));
        }
    }

    ui->input_map->setText(rocket->map);
    ui->combo_skill->setCurrentIndex(rocket->skill);
    ui->input_argbox->setText(rocket->addCmd);

    ui->check_record->setChecked(rocket->demo);
    ui->check_nomonsters->setChecked(rocket->noMonsters);
    ui->check_nomusic->setChecked(rocket->noMusic);
    ui->input_record->setText(rocket->demoName);

    //QMessageBox::information(this, "Success", QString("%1 configuration loaded.").arg(rocket->name));

    ui->tabWidget_rlauncher->setCurrentIndex(0);
}


void RocketLauncher2::on_button_loadFavConfig_clicked()
{
    if (ui->listbox_configFavs->selectionModel()->selectedRows().count() > 0)
        applyConfig(conflist->getSelectedRocket( ui->listbox_configFavs->selectionModel()->selectedRows().at(0)));
}

void RocketLauncher2::saveToExternal(RocketFile &rocket, QString name)
{
    QString settingsDir = QFileDialog::getSaveFileName(this,"Choose where you wish to save the configuration.", m_mainAppPath.filePath(name + ".rocket"),"Rocket Files (*.rocket)");
    QSettings rocketSetting(settingsDir,QSettings::IniFormat);
    rocketSetting.setValue("name", rocket.name);
    rocketSetting.setValue("engName",rocket.engName);
    rocketSetting.setValue("iwadName",rocket.iwadName);
    rocketSetting.setValue("filePaths",rocket.filePaths);
    rocketSetting.setValue("map",rocket.map);
    rocketSetting.setValue("skill",rocket.skill);
    rocketSetting.setValue("addCmd",rocket.addCmd);
    rocketSetting.setValue("demo",rocket.demo);
    rocketSetting.setValue("demoName",rocket.demoName);
    rocketSetting.setValue("noMonsters",rocket.noMonsters);
    rocketSetting.setValue("noMusic",rocket.noMusic);
    QVariantList filesCheckedVariant;

    foreach (auto v, rocket.filesChecked)
    {
        filesCheckedVariant << v;
    }

    rocketSetting.setValue("filesChecked", filesCheckedVariant);
}

void RocketLauncher2::on_button_saveConfigExt_clicked()
{
    QString name = ui->input_confName->text();

    if (!inputExists(name))
    {
        QMessageBox::information(this,"Input Name", "Please input a name for this config to be saved");
        return;
    }

    RocketFile rocket = makeConfigFromCurrent(name);
    saveToExternal(rocket, name);

}

void RocketLauncher2::saveToAutoLoad()
{
    RocketFile rocket = RocketLauncher2::makeConfigFromCurrent("AutoLoad");
    AutoLoad.setValue("name", rocket.name);
    AutoLoad.setValue("engName",rocket.engName);
    AutoLoad.setValue("iwadName",rocket.iwadName);
    AutoLoad.setValue("filePaths",rocket.filePaths);
    AutoLoad.setValue("map",rocket.map);
    AutoLoad.setValue("skill",rocket.skill);
    AutoLoad.setValue("addCmd",rocket.addCmd);
    AutoLoad.setValue("demo",rocket.demo);
    AutoLoad.setValue("demoName",rocket.demoName);
    AutoLoad.setValue("noMonsters",rocket.noMonsters);
    AutoLoad.setValue("noMusic",rocket.noMusic);
    QVariantList filesCheckedVariant;

    foreach (auto v, rocket.filesChecked)
    {
        filesCheckedVariant << v;
    }

    AutoLoad.setValue("filesChecked", filesCheckedVariant);
    AutoLoad.endArray();
}

void RocketLauncher2::saveToGlobal(RocketFile &rocket)
{
    int fsize = ConfigSettings.beginReadArray("configs");
    ConfigSettings.endArray();
    ConfigSettings.beginWriteArray("configs");
    ConfigSettings.setArrayIndex(fsize);
    ConfigSettings.setValue("name", rocket.name);
    ConfigSettings.setValue("engName",rocket.engName);
    ConfigSettings.setValue("iwadName",rocket.iwadName);
    ConfigSettings.setValue("filePaths",rocket.filePaths);
    ConfigSettings.setValue("map",rocket.map);
    ConfigSettings.setValue("skill",rocket.skill);
    ConfigSettings.setValue("addCmd",rocket.addCmd);
    ConfigSettings.setValue("demo",rocket.demo);
    ConfigSettings.setValue("demoName",rocket.demoName);
    ConfigSettings.setValue("noMonsters",rocket.noMonsters);
    ConfigSettings.setValue("noMusic",rocket.noMusic);
    QVariantList filesCheckedVariant;

    foreach (auto v, rocket.filesChecked)
    {
        filesCheckedVariant << v;
    }

    ConfigSettings.setValue("filesChecked", filesCheckedVariant);
    ConfigSettings.endArray();
}

void RocketLauncher2::saveToGlobalFromList(RocketFile *rocket, int index)
{
    ConfigSettings.setArrayIndex(index);
    ConfigSettings.setValue("name", rocket->name);
    ConfigSettings.setValue("engName",rocket->engName);
    ConfigSettings.setValue("iwadName",rocket->iwadName);
    ConfigSettings.setValue("filePaths",rocket->filePaths);
    ConfigSettings.setValue("map",rocket->map);
    ConfigSettings.setValue("skill",rocket->skill);
    ConfigSettings.setValue("addCmd",rocket->addCmd);
    ConfigSettings.setValue("demo",rocket->demo);
    ConfigSettings.setValue("demoName",rocket->demoName);
    ConfigSettings.setValue("noMonsters",rocket->noMonsters);
    ConfigSettings.setValue("noMusic",rocket->noMusic);

    QVariantList filesCheckedVariant;
    foreach (auto v, rocket->filesChecked)
    {
        filesCheckedVariant << v;
    }

    ConfigSettings.setValue("filesChecked", filesCheckedVariant);
}

void RocketLauncher2::on_button_delConfig_clicked()
{
    ui->listbox_configFavs->setUpdatesEnabled(false);
    QModelIndexList indexes = ui->listbox_configFavs->selectionModel()->selectedIndexes();
    qSort(indexes.begin(), indexes.end());

    for (int i = indexes.count() - 1; i > -1; --i)
    {
        conflist->removeRow(indexes.at(i).row());
    }

    ui->listbox_configFavs->setUpdatesEnabled(true);
    ConfigSettings.beginWriteArray("configs");
    ConfigSettings.remove("");

    for (int i = 0; i < conflist->rowCount(); i++)
    {
        saveToGlobalFromList(conflist->getRocketFromRow(i),i);
    }

    ConfigSettings.endArray();
}

void RocketLauncher2::loadExtConfig(QString path)
{
    QSettings rocketSetting(path,QSettings::IniFormat);
    if (rocketSetting.contains("name"))
    {
        RocketFile *rocket = new RocketFile();
        rocket->name = rocketSetting.value("name").toString();
        rocket->engName = rocketSetting.value("engName").toString();
        rocket->iwadName = rocketSetting.value("iwadName").toString();
        rocket->filePaths = rocketSetting.value("filePaths").toStringList();
        rocket->map = rocketSetting.value("map").toString();
        rocket->skill = rocketSetting.value("skill").toInt();
        rocket->addCmd = rocketSetting.value("addCmd").toString();
        rocket->demo = ConfigSettings.value("demo").toBool();
        rocket->demoName = ConfigSettings.value("demoName").toString();
        rocket->noMonsters = ConfigSettings.value("noMonsters").toBool();
        rocket->noMusic = ConfigSettings.value("noMusic").toBool();

        foreach( QVariant v, ConfigSettings.value("filesChecked").toList())
        {
            rocket->filesChecked << v.toBool();
        }

        applyConfig(rocket);
        delete rocket;
    }
    else
        QMessageBox::information(this,"Error","Invalid Rocket File");
}
