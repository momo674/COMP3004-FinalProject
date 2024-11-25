#include "User.h"

User::User(QString FirstName, QString LastName,  QString Gender, float Weight,
           float Height, int DayOfBirth, int MonthOfBirth, int YearOfBirth, QString Country, QString Email)
    : info(UserInfo(FirstName, LastName, Gender, Weight, Height, DayOfBirth,  MonthOfBirth, YearOfBirth, Country, Email)), data(Email)
{
    //1. Create UserInfo object
    //2. Create HealthData object

}
