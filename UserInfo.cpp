#include "UserInfo.h"
#include <QList>
#include <QDebug>

// Constructor
UserInfo::UserInfo(QString FirstName, QString LastName, QString Gender, float Weight,
                   float Height, int DayOfBirth, int MonthOfBirth, int YearOfBirth,
                   QString Country, QString Email)
    : FirstName(FirstName), LastName(LastName), Gender(Gender), Weight(Weight), Height(Height),
      DayOfBirth(DayOfBirth), MonthOfBirth(MonthOfBirth), YearOfBirth(YearOfBirth),
      Country(Country), Email(Email) {
    // Initialize the HealthData pointer

    this->validDays = 1;
    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 24; j++)
            this->last30Days[i][j] = -1;

}

// Copy Constructor
UserInfo::UserInfo(const UserInfo& other)
    : FirstName(other.FirstName), LastName(other.LastName), Gender(other.Gender),
      Weight(other.Weight), Height(other.Height), DayOfBirth(other.DayOfBirth),
      MonthOfBirth(other.MonthOfBirth), YearOfBirth(other.YearOfBirth),
      Country(other.Country), Email(other.Email) {

    this->validDays = 1;
}
int UserInfo::updateHistory(int day, const QList<int>& arr)
{
    qDebug() << day;
    for (int i = 0; i < 24; i++)
        this->last30Days[day][i] = arr[i];
    this->validDays = day;

    return 0;

}
QList<int> UserInfo::getLastScan() const
{
    QList<int> list;
    for (int x: last30Days[this->validDays])
        list.append(x);
    return list;

}

// Destructor (to avoid memory leaks)
UserInfo::~UserInfo() {

}

// Getters and Setters Implementation
int UserInfo::getValidDays() const { return this->validDays;}
QString UserInfo::getFirstName() const { return FirstName; }
QString UserInfo::getLastName() const { return LastName; }
QString UserInfo::getGender() const { return Gender; }
float UserInfo::getWeight() const { return Weight; }
float UserInfo::getHeight() const { return Height; }
int UserInfo::getDayOfBirth() const { return DayOfBirth; }
int UserInfo::getMonthOfBirth() const { return MonthOfBirth; }
int UserInfo::getYearOfBirth() const { return YearOfBirth; }
QString UserInfo::getCountry() const { return Country; }
QString UserInfo::getEmail() const { return Email; }

// Setters omitted for brevity
