#ifndef USER_H
#define USER_H
#include "UserInfo.h"
#include "HealthData.h"

//this class is to combine both UserInfo and Data Class.
class User
{
public:
    User(QString FirstName = "NA", QString LastName = "NA", QString Gender = "NA", float Weight = 0.0,
         float Height = 0.0, int DayOfBirth = 1, int MonthOfBirth = 1, int YearOfBirth = 1000,
         QString Country = "Canada", QString Email = "NA");
private:
    UserInfo info;
    HealthData data;
};

#endif // USER_H
