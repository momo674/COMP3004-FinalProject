#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QtCharts>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "SystemInteraction.h"
#include "UserInfo.h"
#include "JSONInteractor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void goToPage(int index);            // Navigate to a specific page
    void goBack();                       // Navigate back to the previous page
    void handleLogin();                  // Slot to handle the Enter button
    void handleSaveAndCreate();          // Slot to handle Save button
    void startScanningProcess();         // Starts the 24-step scanning process
    void updateScanningStep();           // Handles each step of the scanning process
    void resetInstructionsFrame();       // Resets the instructions frame to its original state

private:
    // UI and navigation
    QLabel* completionLabel; // Track the "Scan Complete!" label

    Ui::MainWindow *ui;                  // Main UI object
    QList<UserInfo*> users;              // List of user profiles
    UserInfo* currentUser;               // Pointer to the current user
    QStack<int> pageHistory;             // Stack to store page indices for navigation

    // Scanning process variables
    int currentStep;                     // Current step (1-24)
    QTimer* stepTimer;                   // Timer for switching images during scanning
    QPushButton* homeButton;             // "Go Back to Home" button

    // Methods
    void populateUserInfoOnPage4();      // Populates user info on Page 4
    void createBarGraphLastScan(QWidget *targetPage); // Creates a bar graph in a target frame
};

#endif // MAINWINDOW_H
