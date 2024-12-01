#ifndef HEALTHDATA_H
#define HEALTHDATA_H
#include "SystemInteraction.h"

//interacts with healthdatauser.json to
class HealthData
{
public:
    HealthData(QString Email);
    HealthData(const HealthData& c);
    int updateHistory(int day, const QList<int>& arr);
    QString Email;
    int last30Days[30][24]; //all of the data (including dummy)
    int validDays; //the number of days where valid data exists
private:
//    QString Email;
//    int last30Days[30][24]; //all of the data (including dummy)
//    int validDays; //the number of days where valid data exists
};

#endif // HEALTHDATA_H
