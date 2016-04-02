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
    ConfigSettings.remove("");
    enginelist->EngineSettings.endArray();
    enginelist->SaveEngineData();
}


void RocketLauncher2::on_listbox_engines_clicked(const QModelIndex &index)
{
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
    enginelist->addDefaultEngine(QFileDialog::getOpenFileName(this, "Locate executable."));
}

void RocketLauncher2::on_input_selEngName_returnPressed()
{
    QModelIndex index = ui->listbox_engines->selectionModel()->selectedIndexes()[0];
    enginelist->setNameFromIndex(ui->input_selEngName->text(), index);
}


void RocketLauncher2::on_button_selEngBrowse_clicked()
{
    QModelIndex index = ui->listbox_engines->selectionModel()->selectedIndexes()[0];
    QString path = QFileDialog::getOpenFileName(this, "Locate executable.");
    enginelist->setPathFromIndex(path, index);
    ui->input_selEngPath->setText(path);
}


void RocketLauncher2::on_combo_EngType_currentTextChanged(const QString &arg1)
{
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
    else if (arg1 == "GZDoom")
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
}
