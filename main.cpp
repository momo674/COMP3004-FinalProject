#include "mainwindow.h"

#include <QApplication>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QDir>
#include <iostream>
#include <string>
#include "UserInfo.h"
#include <typeinfo>
#include "SystemInteraction.h"

using namespace std;

int main(int argc, char *argv[])
{

//    test 1: Create a new user, scan 4 times
    UserInfo* output;
    int result = SystemInteraction::UserRegistration("Mohamad", "Radaideh", "M", 100, 180, 15, 9, 2004, "Canada", "mohparrot@gmail.com", "123poop", &output);
    int result2 = SystemInteraction::userScan("mohparrot@gmail.com", output);
    int result3 = SystemInteraction::userScan("mohparrot@gmail.com", output);
    int result4 = SystemInteraction::userScan("mohparrot@gmail.com", output);
    int result5 = SystemInteraction::userScan("mohparrot@gmail.com", output);

    qDebug() << output->getValidDays();

//    test 2: log in
//    bool result2 = SystemInteraction::UserLogin("mohparrot@gmail.com", "123poop");
//    qDebug() << result2;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
//    return 0;

}
