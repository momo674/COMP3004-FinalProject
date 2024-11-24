#include "UserInfo.h"

UserInfo::UserInfo(QString FirstName, QString LastName,  QString Gender, float Weight,
float Height, int DayOfBirth, int MonthOfBirth, int YearOfBirth, QString Country, QString Email)
{
  this->FirstName = FirstName;
  this->LastName = LastName;
  this->Gender = Gender;
  this->Weight = Weight;
  this->Height = Height;
  this->DayOfBirth = DayOfBirth;
  this->MonthOfBirth = MonthOfBirth;
  this->YearOfBirth = YearOfBirth;
  this->Country = Country;
  this->Email = Email;
}

UserInfo::UserInfo(const UserInfo& c)
{
    this->FirstName = c.FirstName;
    this->LastName = c.LastName;
    this->Gender = c.Gender;
    this->Weight = c.Weight;
    this->Height = c.Height;
    this->DayOfBirth = c.DayOfBirth;
    this->MonthOfBirth = c.MonthOfBirth;
    this->YearOfBirth = c.YearOfBirth;
    this->Country = c.Country;
    this->Email = c.Email;
}

//Getters
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

// Setters
void UserInfo::setFirstName(const QString& firstName) { FirstName = firstName; }
void UserInfo::setLastName(const QString& lastName) { LastName = lastName; }
void UserInfo::setGender(const QString& gender) { Gender = gender; }
void UserInfo::setWeight(float weight) { Weight = weight; }
void UserInfo::setHeight(float height) { Height = height; }
void UserInfo::setDayOfBirth(int dayOfBirth) { DayOfBirth = dayOfBirth; }
void UserInfo::setMonthOfBirth(int monthOfBirth) { MonthOfBirth = monthOfBirth; }
void UserInfo::setYearOfBirth(int yearOfBirth) { YearOfBirth = yearOfBirth; }
void UserInfo::setCountry(const QString& country) { Country = country; }
void UserInfo::setEmail(const QString& email) { Email = email; }
