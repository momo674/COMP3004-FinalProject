#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the "Create Profile" button to switch to create page
    connect(ui->pushButton_create, &QPushButton::clicked, this, [this]() {
        goToPage(2); // Switch to create page
    });

    // Connect the "Create Profile" button to switch to create page
    connect(ui->pushButton_login, &QPushButton::clicked, this, [this]() {
        goToPage(1); // Switch to create page
    });

    // Optionally set the initial page index (if not set in the UI file)
    ui->stackedWidget->setCurrentIndex(0);

    // Connect the Enter button to the handleLogin slot
    connect(ui->pushButton_enter, &QPushButton::clicked, this, &MainWindow::handleLogin);

    // Connect the Save button to the handleSaveAndCreate slot
    connect(ui->pushButton_save, &QPushButton::clicked, this, &MainWindow::handleSaveAndCreate);

    //menu button
    connect(ui->pushButton_menu, &QPushButton::clicked, this, [this]() {
        goToPage(3); // Switch to create page
    });

    //back buttons
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::goBack);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::goBack);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::goBack);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to navigate to a page and save the previous page in history
void MainWindow::goToPage(int index){
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex != index) {
        pageHistory.push(currentIndex); // Save the current index in history
        ui->stackedWidget->setCurrentIndex(index); // Navigate to the target page
    }
}

// Function to navigate back to the previous page
void MainWindow::goBack(){
    if (!pageHistory.isEmpty()) {
        int previousIndex = pageHistory.pop(); // Retrieve the previous page index
        ui->stackedWidget->setCurrentIndex(previousIndex); // Navigate to the previous page
    }
}

// Function to check if user can login
void MainWindow::handleLogin(){
    // Get email and password from the input fields
    QString email = ui->lineEdit_6->text();
    QString password = ui->lineEdit_7->text();

    // Call the UserLogin function from SystemInteraction
    bool success = SystemInteraction::UserLogin(email, password);

    // Handle login success or failure
    if (success) {
        QMessageBox::information(this, "Login Successful", "Welcome!");
        // Optionally navigate to another page
        ui->stackedWidget->setCurrentIndex(4); // Example: Switch to a new page
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid email or password.");
    }
}


void MainWindow::handleSaveAndCreate()
{
    // Retrieve input values from the form
    QString firstName = ui->lineEdit->text();
    QString lastName = ui->lineEdit_2->text();
    QString gender = ui->lineEdit_3->text();
    QString weightStr = ui->lineEdit_4->text();
    QString heightStr = ui->lineEdit_5->text();
    QString dayOfBirthStr = ui->lineEdit_11->text();
    QString monthOfBirthStr = ui->lineEdit_12->text();
    QString yearOfBirthStr = ui->lineEdit_13->text();
    QString country = ui->lineEdit_14->text();
    QString email = ui->lineEdit_15->text();
    QString password = ui->lineEdit_16->text();

    // Validate that all fields are filled
    if (firstName.isEmpty() || lastName.isEmpty() || gender.isEmpty() ||
        weightStr.isEmpty() || heightStr.isEmpty() || dayOfBirthStr.isEmpty() ||
        monthOfBirthStr.isEmpty() || yearOfBirthStr.isEmpty() || country.isEmpty() ||
        email.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Missing Information", "Please fill in all required fields.");
        return; // Stop further execution if validation fails
    }

    // Validate and convert inputs to appropriate data types
    bool weightOk, heightOk, dayOk, monthOk, yearOk;

    float weight = weightStr.toFloat(&weightOk);
    float height = heightStr.toFloat(&heightOk);
    int dayOfBirth = dayOfBirthStr.toInt(&dayOk);
    int monthOfBirth = monthOfBirthStr.toInt(&monthOk);
    int yearOfBirth = yearOfBirthStr.toInt(&yearOk);

    // Check if any conversion failed
    if (!weightOk || !heightOk || !dayOk || !monthOk || !yearOk) {
        QMessageBox::warning(this, "Invalid Input", "Please ensure that:\n"
                                                    "- Weight and Height are valid numbers.\n"
                                                    "- Day, Month, and Year of Birth are valid integers.");
        return; // Stop further execution if validation fails
    }

    // Call the UserRegistration function from SystemInteraction
    int result = SystemInteraction::UserRegistration(firstName, lastName, gender, weight, height, dayOfBirth, monthOfBirth, yearOfBirth, country, email, password);

    // Handle the result of registration
    if (result == -1) { // Assume 0 means success
        QMessageBox::information(this, "Registration Successful", "Your profile has been created.");
        // Optionally navigate to another page
        ui->stackedWidget->setCurrentIndex(4); // Example: Navigate to a different page
    } else {
        QMessageBox::warning(this, "Registration Failed", "There was an error creating your profile. Please try again.");
    }
}




