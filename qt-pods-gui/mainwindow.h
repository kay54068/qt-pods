///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of qt-pods.                                          //
//    Copyright (C) 2015 Jacob Dawid, jacob@omg-it.works                     //
//                                                                           //
//    qt-pods is free software: you can redistribute it and/or modify        //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    qt-pods is distributed in the hope that it will be useful,             //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with qt-pods. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#pragma once

// Own includes
#include "podsmodel.h"
#include "podmanager.h"

// Qt includes
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QSystemTrayIcon>
#include <QSocketNotifier>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupStdOutRedirect();

public slots:
    void on_toolButtonRepository_clicked();
    void on_pushButtonRemoveRepository_clicked();

    void on_lineEditSearchLocal_textChanged(QString text);
    void on_lineEditSearchRemote_textChanged(QString text);

    void on_comboBoxCurrentRepository_currentTextChanged(QString text);

    void on_pushButtonUpdateLocalPods_clicked();
    void on_pushButtonRefreshLocalPods_clicked();
    void on_pushButtonRemoveLocalPods_clicked();

    void on_pushButtonRefreshAvailablePods_clicked();
    void on_pushButtonInstallPods_clicked();

protected:
    void closeEvent(QCloseEvent *closeEvent);

private slots:
    void stdOutActivated(int fileDescriptor);

private:
    void loadSettings();
    void saveSettings();

    void refreshLocalPods();
    void refreshAvailablePods();


    QSocketNotifier *_stdOutSocketNotifier;
    QSystemTrayIcon _systemTrayIcon;

    PodManager _podManager;
    PodsModel *_localPods;
    PodsModel *_remotePods;

    QSortFilterProxyModel *_localPodsProxyModel;
    QSortFilterProxyModel *_remotePodsProxyModel;

    QNetworkAccessManager _networkAccessManager;

    Ui::MainWindow *ui;
};