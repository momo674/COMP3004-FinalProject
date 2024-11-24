#include "SystemInteraction.h"

int SystemInteraction::UserRegistration(QString FirstName, QString LastName,  QString Gender, float Weight,
float Height, int DayOfBirth, int MonthOfBirth, int YearOfBirth, QString Country, QString Email, QString Password)
{
    UserInfo newUser(FirstName, LastName, Gender, Weight, Height, DayOfBirth, MonthOfBirth, YearOfBirth, Country, Email);
    QJsonObject newUserObject = JSONInteractor::createJsonObjFromUser(&newUser, Password);
    return JSONInteractor::addUserToJson(newUserObject);
}

bool SystemInteraction::UserLogin(QString Email, QString Password)
{
    return JSONInteractor::checkIfUserInJson(Email, Password);
}
