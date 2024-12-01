#include "SystemInteraction.h"

int SystemInteraction::UserRegistration(QString FirstName, QString LastName, QString Gender, float Weight, float Height, int DayOfBirth, int MonthOfBirth, int YearOfBirth, QString Country, QString Email, QString Password, UserInfo** output)
{
    UserInfo* userInfo = new UserInfo(FirstName, LastName, Gender, Weight, Height, DayOfBirth, MonthOfBirth, YearOfBirth, Country, Email);

    // If output is not null, assign the created UserInfo object to it
    if (output != nullptr)
    {
        *output = userInfo;
        QJsonObject newUserObject = JSONInteractor::createJsonObjFromUser(userInfo, Password);
        return JSONInteractor::addUserToJson(newUserObject);


    }
    else
    {
        QJsonObject newUserObject = JSONInteractor::createJsonObjFromUser(userInfo, Password);
        delete userInfo; // Free the memory since it's not being returned
        return JSONInteractor::addUserToJson(newUserObject);

    }
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

int SystemInteraction::userScan(QString Email, UserInfo* user)
{
    QList<int> healthData;
    for (int i = 0; i < 24; i++)
        healthData.append(rand() % 101);

    //call function to update json
    return JSONInteractor::updateUserHealthData(Email, healthData, user);
}
