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
#include "configs.h"

namespace Ui {
class RocketLauncher2;
}

class RocketLauncher2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit RocketLauncher2(QWidget *parent = 0, int argc = 0, char *argv[] = 0);
    ~RocketLauncher2();

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_combo_Engines_currentIndexChanged(int index);

    void addpwad(QString filepath);

    void on_button_add_clicked();

    void on_button_pwadsclear_clicked();

    void on_button_remove_clicked();

    void setEngineSelection(const QString text);

    void setEngineSelectionIndex(int index);

    void addToFavorites(const QString filepath);

    void addToIWADs(const QString filepath);

    void addToRes(const QString filepath);

    //void deleteFromFavorites(const int index);

    void on_button_favadd_clicked();

    void on_button_favremove_clicked();

    void copyItemToFav(QDropEvent* pEvent);

    void copyItemToPwads(QDropEvent* pEvent);

    void copyItemToIwads(QDropEvent* pEvent);

    void copyItemToRes(QDropEvent* pEvent);

    void on_button_addiwad_clicked();

    void on_button_deliwad_clicked();

    void on_button_addres_clicked();

    void on_button_delres_clicked();

    void on_listbox_IWADs_clicked(const QModelIndex &index);

    void on_button_helpmap_clicked();

    void on_button_loadConfigExt_clicked();

    void on_button_addConfToFav_clicked();

    void on_button_loadFavConfig_clicked();

    void on_button_saveConfigExt_clicked();

    void on_button_delConfig_clicked();

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
    QStandardItemModel *reslist;
    ConfigListModel *conflist;
    QStringList genCommandline();
    QProcess *process;
    void SetEnginePic(EnginePic pic);
    void initPixmaps();
    QList<QPixmap> *enginepics;
    QSettings settings;
    void parseCmdLine(int argc, char *argv[]);
    void updateFavs(QString filepath, bool save);
    void updateIWADs(QString filepath, bool save);
    void updateres(QString filepath, bool save);
    void initListViews();

    //configs
    RocketFile makeConfigFromCurrent(QString name);
    void loadExtConfig(QString path);
    void applyConfig(RocketFile *rocket);
    void initConfigs();
    void saveToGlobal(RocketFile &rocket);
    void saveToGlobalFromList(RocketFile *rocket, int index);
    void saveToExternal(RocketFile &rocket, QString name);
    QSettings ConfigSettings;
};

#endif // ROCKETLAUNCHER2_H
