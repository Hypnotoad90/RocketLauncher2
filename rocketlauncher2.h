/*  This file (rocketlauncher2.h) is part of Rocket Launcher 2.0 - A cross platform
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

#ifndef ROCKETLAUNCHER2_H
#define ROCKETLAUNCHER2_H

#include <QMainWindow>
#include <QDir>
#include <QString>
#include "abstractmodels.h"
#include <QProcess>
#include <QStandardItemModel>
#include <QList>
#include <QPixmap>
#include <QSettings>
#include <QShortcut>
#include "configs.h"
#include "commandlinedialog.h"

namespace Ui {
class RocketLauncher2;
}

class RocketLauncher2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit RocketLauncher2(QWidget *parent = 0, int argc = 0, char *argv[] = 0);
    ~RocketLauncher2();

protected:
     void closeEvent(QCloseEvent *event);

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_combo_Engines_currentIndexChanged(int index);

    bool addpwad(QString filepath);

    void on_button_add_clicked();

    void on_button_pwadsclear_clicked();

    void on_button_remove_clicked();

    void setEngineSelection(const QString text);

    void setEngineSelectionIndex(int index);

    void addToFavorites(const QString filepath);

    void addToIWADs(const QString filepath);

    //void deleteFromFavorites(const int index);

    void on_button_favadd_clicked();

    void on_button_favremove_clicked();

    void copyItemToFav(QDropEvent* pEvent);

    void copyItemToPwads(QDropEvent* pEvent);

    void copyItemToIwads(QDropEvent* pEvent);

    void on_button_addiwad_clicked();

    void on_button_deliwad_clicked();

    void on_listbox_IWADs_clicked(const QModelIndex &index);

    void on_button_helpmap_clicked();

    void on_button_loadConfigExt_clicked();

    void on_button_addConfToFav_clicked();

    void on_button_loadFavConfig_clicked();

    void on_button_saveConfigExt_clicked();

    void on_button_delConfig_clicked();

    void on_button_detectEng_clicked();

    void on_button_removeEng_clicked();

    void on_listbox_engines_clicked(const QModelIndex &index);

    void on_button_addCustEng_clicked();

    void on_input_selEngName_returnPressed();

    void on_button_selEngBrowse_clicked();

    void on_combo_EngType_currentTextChanged(const QString &arg1);

    void on_combo_EngPic_currentTextChanged(const QString &arg1);

    void on_button_idExeBrowse_clicked();

    void showCommandLine();

private:
    Ui::RocketLauncher2 *ui;
    QString m_settingsfile;
    QDir m_mainAppPath;
    void loadsettings();
    bool savesettings(QString key, QString value);
    QDir m_IWADFolder;
    QStringList m_wadextfilters;
    QStandardItemModel *iwadlist;
    EngineListModel *enginelist;
    QStandardItemModel *pwadloadlist;
    QStandardItemModel *favlist;
    ConfigListModel *conflist;
    CommandLineDialog *cmdDialog;
    QStringList genCommandline(bool displayOnly);
    QProcess *process;
    void SetEnginePic(EnginePic pic);
    void initPixmaps();
    QList<QPixmap> *enginepics;
    QSettings settings;
    QMenu *RLMenu;
    QShortcut *RLOpenShortcut;
    QShortcut *RLSaveShortcut;
    QAction *rlmCmdLne;
    QAction *rlmLoadRocket;
    QAction *rlmSaveRocket;
    void parseCmdLine(int argc, char *argv[]);
    void updateFavs(QString filepath, bool save);
    void updateIWADs(QString filepath, bool save);
    void initListViews();
    void setupAdditionalUi();
    QStringList genDOSBoxcmd();

    //configs
    RocketFile makeConfigFromCurrent(QString name);
    void loadExtConfig(QString path);
    void applyConfig(RocketFile *rocket);
    void initConfigs();
    void autoLoadConfig();
    void saveToGlobal(RocketFile &rocket);
    void saveToAutoLoad();
    void saveToGlobalFromList(RocketFile *rocket, int index);
    void saveToExternal(RocketFile &rocket, QString name);
    QSettings ConfigSettings;
    QSettings AutoLoad;

    QString pwadFilter;
};

#endif // ROCKETLAUNCHER2_H
