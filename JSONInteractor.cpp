#include "JSONInteractor.h"

UserInfo* JSONInteractor::createUserFromJsonObj(QJsonObject obj)
{
    QString FirstName = obj["FirstName"].toString();
    QString LastName = obj["LastName"].toString();
    QString Gender = obj["Gender"].toString();
    float Weight = (float) obj["Weight"].toDouble();
    float Height = (float) obj["Height"].toDouble();
    int DayOfBirth = obj["DayOfBirth"].toInt();
    int MonthOfBirth = obj["MonthOfBirth"].toInt();
    int YearOfBirth = obj["YearOfBirth"].toInt();
    QString Country = obj["Country"].toString();
    QString Email = obj["Email"].toString();
    return new UserInfo(FirstName, LastName, Gender, Weight, Height, DayOfBirth, MonthOfBirth, YearOfBirth, Country, Email);
}

QJsonObject JSONInteractor::createJsonObjFromUser(UserInfo* user, QString password)
{
    QJsonObject obj;
    obj["FirstName"] = user->getFirstName();
    obj["LastName"] = user->getLastName();
    obj["Gender"] = user->getGender();
    obj["Weight"] = user->getWeight();
    obj["Height"] = user->getHeight();
    obj["DayOfBirth"] = user->getDayOfBirth();
    obj["MonthOfBirth"] = user->getMonthOfBirth();
    obj["YearOfBirth"] = user->getYearOfBirth();
    obj["Country"] = user->getCountry();
    obj["Email"] = user->getEmail();
    obj["Password"] = password;
    return obj;
}

bool JSONInteractor::checkIfUserInJson(QString Email, QString Password)
{
    QJsonDocument doc = getUsersJson();
    QJsonObject rootObj = doc.object();
    QJsonArray usersArray = rootObj["Users"].toArray();

    for (QJsonValue x: usersArray)
    {
        QJsonObject xObj = x.toObject();

        if ((xObj["Email"].toString() == Email) && (xObj["Password"].toString() == Password))
            return true;

    }

    return false;
}


QJsonDocument JSONInteractor::getUsersJson()
{
    QString localPath = QDir::currentPath();
    QString filePath = localPath + "/test.json";

    QFile file(filePath);

    // Open the file in ReadOnly mode
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return QJsonDocument(); // Return an empty QJsonDocument
    }

    // Read the file content and close the file
    QByteArray fileContent = file.readAll();
    file.close();

    // Parse and return the JSON document
    return QJsonDocument::fromJson(fileContent);
}


int JSONInteractor::writeToUsersJson(QJsonDocument doc)
{
    QString localPath = QDir::currentPath();
    QString filePath = localPath + "/test.json";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return -1;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return 0;
}

int JSONInteractor::addUserToJson(QJsonObject newObj)
{
    QJsonDocument doc = getUsersJson();
    QJsonObject rootObj = doc.object();
    QJsonArray usersArray = rootObj["Users"].toArray();

    for (int i = 0; i < 5; i++)
    {
        QJsonObject xObj = usersArray[i].toObject();
        if (xObj["Email"].toString().contains("tmp_Email"))
        {
            usersArray[i] = newObj;
            int userCountUpdated = rootObj["currentUsers"].toInt() + 1;
            rootObj["currentUsers"] = userCountUpdated; // Correct: Update with the integer value
            rootObj["Users"] = usersArray; // Add the updated usersArray back to rootObj

            writeToUsersJson(QJsonDocument(rootObj));
            return 0;

        }
    }

    return -1;
}
int JSONInteractor::loadUsers(UserInfo** arr)
{
    UserInfo** arrPtr = arr;
    QJsonDocument doc = getUsersJson();
    QJsonObject root_obj = doc.object();
    int currentUsers = root_obj["currentUsers"].toInt();
    QJsonArray userArray = root_obj["Users"].toArray();

    for (QJsonValue x : userArray)
    {
        QJsonObject xObj = x.toObject();

        QString email = xObj["Email"].toString();

        if (!email.contains(QString("tmp_Email")))
        {
            *arrPtr = createUserFromJsonObj(xObj);
            arrPtr++;
        }

    }
    return currentUsers;
}