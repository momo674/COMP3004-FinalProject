#include "HealthData.h"

HealthData::HealthData(QString Email) : Email(Email)
{
//    for (int i = 0; i < 30; i++)
//        for (int j = 0; j < 24; j++)
//            this->last30Days[i][j] = 0;
    this->validDays = SystemInteraction::getHealthDataofUser(this->Email, this->last30Days);


    for (int i = 0; i < 10; i++)
        qDebug() << this->last30Days[i][0];
}

HealthData::HealthData(const HealthData& c)
{
    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 24; j++)
            this->last30Days[i][j] = 0;
    this->Email = c.Email;
    this->validDays = SystemInteraction::getHealthDataofUser(this->Email, this->last30Days);
}
