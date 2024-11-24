#ifndef JSONINTERACTOR_H
#define JSONINTERACTOR_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "UserInfo.h"

class JSONInteractor {
public:
    // Converts a QJsonObject to a UserInfo pointer
    static UserInfo* createUserFromJsonObj(QJsonObject obj);

    // Converts a UserInfo pointer and password to a QJsonObject
    static QJsonObject createJsonObjFromUser(UserInfo* user, QString password);

    // Reads and parses the JSON document from the file
    static QJsonDocument getUsersJson();

    //Returns true if user/password is valid
    static bool checkIfUserInJson(QString Email, QString Password);

    // Adds a new user to the JSON file, replacing a temporary user
    static int addUserToJson(QJsonObject newObj);

    // Loads users from the JSON file into an array of UserInfo pointers
    static int loadUsers(UserInfo** arr);
private:
    // Writes a JSON document to the file
    static int writeToUsersJson(QJsonDocument doc);
};

#endif // JSONINTERACTOR_H
