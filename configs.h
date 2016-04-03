/*  This file (configs.h) is part of Rocket Launcher 2.0 - A cross platform
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

#ifndef CONFIGS_H
#define CONFIGS_H

#include <QStringList>
#include <QString>

class RocketFile
{
public:
    //Configs();
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
