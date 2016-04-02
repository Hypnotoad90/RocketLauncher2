#ifndef CONFIGS_H
#define CONFIGS_H

#include <QStringList>
#include <QString>

class RocketFile
{
public:
    Configs();
    QString name;
    QString engName;
    QString iwadName;
    QStringList resPaths;
    QStringList filePaths;
    QString map;
    int skill;
    QString addCmd;
};

#endif // CONFIGS_H
