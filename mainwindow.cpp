#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    users = JSONInteractor::loadUsers();
    currentUser = NULL;
    qDebug() << users.size();
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

    //menu to history
    connect(ui->pushButton_6, &QPushButton::clicked, this, [this]() {
        goToPage(5); // Switch to history page
    });

    //menu to home
    connect(ui->pushButton_home, &QPushButton::clicked, this, [this]() {
        goToPage(4); // Switch to home page
    });

    //menu to measure
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        goToPage(6); // Switch to create page
    });

    //menu button
    connect(ui->pushButton_menu, &QPushButton::clicked, this, [this]() {
        goToPage(3); // Switch to menu page
    });

    //back buttons
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::goBack);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::goBack);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::goBack);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::goBack);
    connect(ui->pushButton_11, &QPushButton::clicked, this, &MainWindow::goBack);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createBarGraphLastScan(QWidget *targetFrame) {
    // Clear any existing layout or widgets inside the frame
    if (targetFrame->layout()) {
        QLayoutItem *item;
        while ((item = targetFrame->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete targetFrame->layout();
    }

    // Get the data for the bar graph (24 elements)
    QList<int> dataArray = currentUser->getLastScan();
    qDebug() << dataArray;
    // Ensure the dataArray has 24 elements (for safety)
    if (dataArray.size() != 24) {
        qDebug() << "Error: Data array does not contain exactly 24 elements.";
        return;
    }

    // Create QBarSet and populate it with data
    QtCharts::QBarSet *barSet = new QtCharts::QBarSet("Last Scan");
    for (int value : dataArray) {
        *barSet << value;
    }

    // Create QBarSeries and add the QBarSet
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(barSet);

    // Create QChart and configure it
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Last Scan Results");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Configure X-axis for 1 to 24
    QStringList categories;
    for (int i = 1; i <= 24; ++i) {
        categories << QString::number(i);
    }
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configure Y-axis for range 0 to 100
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setRange(0, 100); // Set Y-axis range from 0 to 100
    axisY->setTitleText("Value (%)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create QChartView for rendering the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add QChartView to the frame's layout
    QVBoxLayout *layout = new QVBoxLayout(targetFrame);
    layout->addWidget(chartView);
    targetFrame->setLayout(layout);
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

        //Point to user
        for (UserInfo* x: users)
        {
            if (x->getEmail() == email)
            {
                currentUser = x;
//                SystemInteraction::userScan(x->getEmail(), currentUser);
                break;
            }
        }

        // Navigate to page 4
        ui->stackedWidget->setCurrentIndex(4);

        // Create the bar graph on page 4
        createBarGraphLastScan(ui->frame_2); // Replace 'ui->page4' with the appropriate widget name
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
    if (result == 0) { // Assume 0 means success
        QMessageBox::information(this, "Registration Successful", "Your profile has been created.");
        //Point to user
        this->users = JSONInteractor::loadUsers();
        for (UserInfo* x: users)
        {
            if (x->getEmail() == email)
            {
                currentUser = x;
//                SystemInteraction::userScan(x->getEmail(), currentUser);
                break;
            }
        }

        // Navigate to page 4
        ui->stackedWidget->setCurrentIndex(4);

        // Create the bar graph on page 4
        createBarGraphLastScan(ui->frame_2); // Replace 'ui->page4' with the appropriate widget name
    } else {
        QMessageBox::warning(this, "Registration Failed", "There was an error creating your profile. Please try again.");
    }
}
