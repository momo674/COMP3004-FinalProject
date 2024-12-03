#include "SystemInteraction.h"

int SystemInteraction::UserRegistration(QString FirstName, QString LastName, QString Gender, float Weight, float Height, int DayOfBirth, int MonthOfBirth, int YearOfBirth, QString Country, QString Email, QString Password, UserInfo** output)
{
    UserInfo* userInfo = new UserInfo(FirstName, LastName, Gender, Weight, Height, DayOfBirth, MonthOfBirth, YearOfBirth, Country, Email);

    // If output is not null, assign the created UserInfo object to it
    if (output != nullptr)
    {
        *output = userInfo;
        QJsonObject newUserObject = JSONInteractor::createJsonObjFromUser(userInfo, Password);
        return JSONInteractor::addUserToJson(newUserObject);


    }
    else
    {
        QJsonObject newUserObject = JSONInteractor::createJsonObjFromUser(userInfo, Password);
        delete userInfo; // Free the memory since it's not being returned
        return JSONInteractor::addUserToJson(newUserObject);

    }
}


bool SystemInteraction::UserLogin(QString Email, QString Password)
{
    return JSONInteractor::checkIfUserInJson(Email, Password);
}

int SystemInteraction::getHealthDataofUser(QString Email, int (&array)[30][24])
{
    QJsonObject user = JSONInteractor::healthDataOfUserJsonObject(Email);
//    qDebug() << user;
    if (user["Email"].toString() != Email)
        return -1;

    QJsonArray log = user["Log"].toArray();
//    qDebug() << log;

    for (int i = 0; i < 30; i++)
    {
        QJsonObject iObj = log[i].toObject();
        QString day = QStringLiteral("Day%1").arg(i + 1);
        QJsonArray points = iObj[day].toArray();

        for (int j = 0; j < 24; j++)
        {
            array[i][j] = points[i].toInt();
        }
    }

    return user["Days"].toInt();
}

int SystemInteraction::userScan(QString Email, UserInfo* user)
{
    QList<int> healthData;
    for (int i = 0; i < 24; i++)
        healthData.append(rand() % 101);

    //call function to update json
    return JSONInteractor::updateUserHealthData(Email, healthData, user);
}

QList<int> SystemInteraction::calculateCategoryScores(const QList<int>& inputPoints) {
    // Ensure inputPoints has 24 values
    if (inputPoints.size() != 24) {
        throw std::invalid_argument("Input list must contain exactly 24 points.");
    }

    // Mapping of 24 points to the 8 categories
    QList<QList<int>> categoryMappings = {
        {4, 5},          // Heart: H3L, H3R
        {0, 1},          // Lungs: H1L, H1R
        {10, 11},        // Gut: H6L, H6R
        {20, 21},        // Liver: F2L, F2R
        {22, 23},        // Kidney: F3L, F3R
        {8, 9},          // Stomach: F6L, F6R
        {16, 17},        // Bladder: F4L, F4R
        {6, 7}           // Lymph: H5L, H5R
    };

    QList<int> categoryScores;

    // Calculate average score for each category
    for (const auto& category : categoryMappings) {
        int sum = 0;
        for (int pointIndex : category) {
            sum += inputPoints[pointIndex];
        }
        int average = sum / category.size(); // Average the values for the category
        categoryScores.append(average);     // Add to the output list
    }

    return categoryScores;
}
