#include "UserInfo.h"
#include "HealthData.h" // Include only in the .cpp file

// Constructor
UserInfo::UserInfo(QString FirstName, QString LastName, QString Gender, float Weight,
                   float Height, int DayOfBirth, int MonthOfBirth, int YearOfBirth,
                   QString Country, QString Email)
    : FirstName(FirstName), LastName(LastName), Gender(Gender), Weight(Weight), Height(Height),
      DayOfBirth(DayOfBirth), MonthOfBirth(MonthOfBirth), YearOfBirth(YearOfBirth),
      Country(Country), Email(Email) {
    // Initialize the HealthData pointer
    data = new HealthData(Email);
}

// Copy Constructor
UserInfo::UserInfo(const UserInfo& other)
    : FirstName(other.FirstName), LastName(other.LastName), Gender(other.Gender),
      Weight(other.Weight), Height(other.Height), DayOfBirth(other.DayOfBirth),
      MonthOfBirth(other.MonthOfBirth), YearOfBirth(other.YearOfBirth),
      Country(other.Country), Email(other.Email) {
    // Deep copy the HealthData pointer
    data = new HealthData(*other.data);
}

// Destructor (to avoid memory leaks)
UserInfo::~UserInfo() {
    delete data;
}

// Getters and Setters Implementation
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
