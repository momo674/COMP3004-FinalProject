#ifndef SYSTEMINTERACTION_H
#define SYSTEMINTERACTION_H
#include <QString>
#include "UserInfo.h"
#include "JSONInteractor.h"

class SystemInteraction
{
public:
    static int UserRegistration(QString FirstName = "NA", QString LastName = "NA", QString Gender = "NA", float Weight = 0.0,
               float Height = 0.0, int DayOfBirth = 1, int MonthOfBirth = 1, int YearOfBirth = 1000,
               QString Country = "Canada", QString Email = "NA", QString Password = "NA");
    static bool UserLogin(QString Email, QString Password);
};

#endif // SYSTEMINTERACTION_H