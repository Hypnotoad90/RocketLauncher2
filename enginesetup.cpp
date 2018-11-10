/*  This file (enginesetup.cpp) is part of Rocket Launcher 2.0 - A cross platform
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
#include "hyp_commonfunc.h"
#include "abstractmodels.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>


void RocketLauncher2::on_button_detectEng_clicked()
{
    on_pushButton_2_clicked();
}

void RocketLauncher2::on_button_removeEng_clicked()
{
    ui->listbox_engines->setUpdatesEnabled(false);
    ui->combo_Engines->setUpdatesEnabled(false);
    QModelIndexList indexes = ui->listbox_engines->selectionModel()->selectedIndexes();
    qSort(indexes.begin(), indexes.end());

    for (int i = indexes.count() - 1; i > -1; --i)
    {
        enginelist->removeRow(indexes.at(i).row());
    }

    ui->listbox_engines->setUpdatesEnabled(true);
    ui->combo_Engines->setUpdatesEnabled(true);
    enginelist->EngineSettings.beginWriteArray("Engines");
    //enginelist->EngineSettings.remove("");
    enginelist->EngineSettings.endArray();
    enginelist->SaveEngineData();
    enginelist->setCurrentEngine(0);
    enginelist->updateComboIndex(0);
}


void RocketLauncher2::on_listbox_engines_clicked(const QModelIndex &index)
{
    ui->groupBox_4->setEnabled(true);
    ui->input_selEngName->setText(
                enginelist->data(index,Qt::DisplayRole).toString()
                );
    ui->input_selEngPath->setText(
                enginelist->data(index,Qt::UserRole).toString()
                );
    EngineType temptype = enginelist->getEngineTypeFromIndex(index);

    if (temptype == Engine_Default)
        ui->combo_EngType->setCurrentText("Default");
    else if (temptype == Engine_DosBox)
        ui->combo_EngType->setCurrentText("DosBox");
    else if (temptype == Engine_Oldschool)
        ui->combo_EngType->setCurrentText("Oldschool");
    else if (temptype == Engine_ZDoom)
        ui->combo_EngType->setCurrentText("ZDoom");

    EnginePic pic = enginelist->getEnginePicFromIndex(index);

    if (pic == Pic_Default)
        ui->combo_EngPic->setCurrentText("Default");
    else if (pic == Pic_Zandronum)
        ui->combo_EngPic->setCurrentText("Zandronum");
    else if (pic == Pic_Zdoom)
        ui->combo_EngPic->setCurrentText("Zdoom");
    else if (pic == Pic_GZdoom)
        ui->combo_EngPic->setCurrentText("GZdoom");
    else if (pic == Pic_Chocolate)
        ui->combo_EngPic->setCurrentText("Chocolate");
    else if (pic == Pic_PrBoom)
        ui->combo_EngPic->setCurrentText("PrBoom");
    else if (pic == Pic_ZDaemon)
        ui->combo_EngPic->setCurrentText("ZDaemon");
    else if (pic == Pic_Odamex)
        ui->combo_EngPic->setCurrentText("Odamex");
    else if (pic == Pic_Eternity)
        ui->combo_EngPic->setCurrentText("Eternity");
    else if (pic == Pic_Legacy)
        ui->combo_EngPic->setCurrentText("Legacy");
    else if (pic == Pic_Edge)
        ui->combo_EngPic->setCurrentText("Edge");
    else if (pic == Pic_Retro)
        ui->combo_EngPic->setCurrentText("Retro");
    else if (pic == Pic_Vavoom)
        ui->combo_EngPic->setCurrentText("Vavoom");
    else if (pic == Pic_Doomsday)
        ui->combo_EngPic->setCurrentText("Doomsday");

}

void RocketLauncher2::on_button_addCustEng_clicked()
{
    QString engine = QFileDialog::getOpenFileName(this, "Locate executable.");
    if (engine != NULL)
    {
        enginelist->addDefaultEngine(engine);
    }
}

void RocketLauncher2::on_input_selEngName_returnPressed()
{

    QModelIndex index = ui->listbox_engines->selectionModel()->selectedIndexes()[0];
    if (ui->input_selEngName->text() == enginelist->data(index, Qt::DisplayRole))
        return;

    if (getIndexOfDisplayText(enginelist,ui->input_selEngName->text()) == QModelIndex())
    {
        enginelist->setNameFromIndex(ui->input_selEngName->text(), index);
    }
    else
    {
        QMessageBox::warning(this, "Profile Name Already Exists", "There already exists an engine profile with that name, please choose another!");
    }
}


void RocketLauncher2::on_button_selEngBrowse_clicked()
{
    if (ui->listbox_engines->selectionModel()->selectedIndexes().size() > 0)
    {
        QModelIndex index = ui->listbox_engines->selectionModel()->selectedIndexes()[0];
        QString path = QFileDialog::getOpenFileName(this, "Locate executable.");
        enginelist->setPathFromIndex(path, index);
        ui->input_selEngPath->setText(path);
    }
    else
    {
        QMessageBox::information(NULL, "Select engine first!", "Please select an engine from the listbox to the left first. If you wish to add a new engine, select 'Add Custom' or 'Detect from File' on the bottom left");
    }
}


void RocketLauncher2::on_combo_EngType_currentTextChanged(const QString &arg1)
{
    if (ui->listbox_engines->selectionModel()->selectedIndexes().size() < 1)
        return;
    QModelIndex index = ui->listbox_engines->selectionModel()->selectedIndexes()[0];

    if (arg1 == "Default")
        enginelist->setTypeFromIndex(Engine_Default, index);
    else if (arg1 == "DosBox")
        enginelist->setTypeFromIndex(Engine_DosBox, index);
    else if (arg1 == "Oldschool")
        enginelist->setTypeFromIndex(Engine_Oldschool, index);
    else if (arg1 == "ZDoom")
        enginelist->setTypeFromIndex(Engine_ZDoom, index);
}

void RocketLauncher2::on_combo_EngPic_currentTextChanged(const QString &arg1)
{
    if (ui->listbox_engines->selectionModel()->selectedIndexes().size() < 1)
        return;
    QModelIndex index = ui->listbox_engines->selectionModel()->selectedIndexes()[0];

    if (arg1 == "Default")
        enginelist->setPicFromIndex(Pic_Default, index);
    else if (arg1 == "Zandronum")
        enginelist->setPicFromIndex(Pic_Zandronum, index);
    else if (arg1 == "Chocolate")
        enginelist->setPicFromIndex(Pic_Chocolate, index);
    else if (arg1 == "Doomsday")
        enginelist->setPicFromIndex(Pic_Doomsday, index);
    else if (arg1 == "Edge")
        enginelist->setPicFromIndex(Pic_Edge, index);
    else if (arg1 == "Eternity")
        enginelist->setPicFromIndex(Pic_Eternity, index);
    else if (arg1 == "GZdoom")
        enginelist->setPicFromIndex(Pic_GZdoom, index);
    else if (arg1 == "Legacy")
        enginelist->setPicFromIndex(Pic_Legacy, index);
    else if (arg1 == "Odamex")
        enginelist->setPicFromIndex(Pic_Odamex, index);
    else if (arg1 == "PrBoom")
        enginelist->setPicFromIndex(Pic_PrBoom, index);
    else if (arg1 == "Retro")
        enginelist->setPicFromIndex(Pic_Retro, index);
    else if (arg1 == "Vavoom")
        enginelist->setPicFromIndex(Pic_Vavoom, index);
    else if (arg1 == "ZDaemon")
        enginelist->setPicFromIndex(Pic_ZDaemon, index);
    else if (arg1 == "Zdoom")
        enginelist->setPicFromIndex(Pic_Zdoom, index);

    SetEnginePic(enginelist->getCurrentEngine()->EngineImage);
}

void RocketLauncher2::on_button_idExeBrowse_clicked()
{
    enginelist->setDoomExeSave();
    ui->input_idExePath->setText(enginelist->DoomExePath);
}
