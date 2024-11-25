#include "SystemInteraction.h"

int SystemInteraction::UserRegistration(QString FirstName, QString LastName,  QString Gender, float Weight, float Height, int DayOfBirth, int MonthOfBirth, int YearOfBirth, QString Country, QString Email, QString Password)
{
    UserInfo newUser(FirstName, LastName, Gender, Weight, Height, DayOfBirth, MonthOfBirth, YearOfBirth, Country, Email);
    QJsonObject newUserObject = JSONInteractor::createJsonObjFromUser(&newUser, Password);
    return JSONInteractor::addUserToJson(newUserObject);
}

bool SystemInteraction::UserLogin(QString Email, QString Password)
{
    return JSONInteractor::checkIfUserInJson(Email, Password);
}

int SystemInteraction::getHealthDataofUser(QString Email, int (&array)[30][24])
{
    QJsonObject user = JSONInteractor::healthDataOfUserJsonObject(Email);
//    qDebug() << user;
    if (user["Email"].toString() != Email)
        return -1;

    QJsonArray log = user["Log"].toArray();
//    qDebug() << log;

    for (int i = 0; i < 30; i++)
    {
        QJsonObject iObj = log[i].toObject();
        QString day = QStringLiteral("Day%1").arg(i + 1);
        QJsonArray points = iObj[day].toArray();

        for (int j = 0; j < 24; j++)
        {
            array[i][j] = points[i].toInt();
        }
    }

    return user["Days"].toInt();
}
