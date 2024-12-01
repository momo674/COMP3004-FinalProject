#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
class UserInfo
{
public:
    // Constructors
    UserInfo(QString FirstName = "NA", QString LastName = "NA", QString Gender = "NA", float Weight = 0.0,
             float Height = 0.0, int DayOfBirth = 1, int MonthOfBirth = 1, int YearOfBirth = 1000,
             QString Country = "Canada", QString Email = "NA");
    UserInfo(const UserInfo& other);
    ~UserInfo();
    // Getters
    QString getFirstName() const;
    QString getLastName() const;
    QString getGender() const;
    float getWeight() const;
    float getHeight() const;
    int getDayOfBirth() const;
    int getMonthOfBirth() const;
    int getYearOfBirth() const;
    QString getCountry() const;
    QString getEmail() const;
    int getValidDays() const;

    // Setters
    void setFirstName(const QString& firstName);
    void setLastName(const QString& lastName);
    void setGender(const QString& gender);
    void setWeight(float weight);
    void setHeight(float height);
    void setDayOfBirth(int dayOfBirth);
    void setMonthOfBirth(int monthOfBirth);
    void setYearOfBirth(int yearOfBirth);
    void setCountry(const QString& country);
    void setEmail(const QString& email);
    int updateHistory(int day, const QList<int>& arr);

private:
    QString FirstName;
    QString LastName;
    QString Gender;
    float Weight;
    float Height;
    int DayOfBirth;
    int MonthOfBirth;
    int YearOfBirth;
    QString Country;
    QString Email;


    int last30Days[30][24]; //all of the data (including dummy)
    int validDays; //the number of days where valid data exists

};

#endif // USERINFO_H
