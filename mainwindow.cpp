#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    users = JSONInteractor::loadUsers();
    currentUser = nullptr;
    ui->setupUi(this);

    currentStep = 0; // Initialize the current step
    stepTimer = new QTimer(this); // Create a timer for the scanning process

    // Create the "Go Back to Home" button and hide it initially
    homeButton = new QPushButton("Go Back to Home", this);
    homeButton->setGeometry(200, 400, 200, 50); // Adjust the position as needed
    homeButton->hide();

    // Connect the "Continue" button to start the scanning process
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::startScanningProcess);

    // Connect the timer to the function that updates the step
    connect(stepTimer, &QTimer::timeout, this, &MainWindow::updateScanningStep);

    // Connect the "Go Back to Home" button to reset the frame
    connect(homeButton, &QPushButton::clicked, this, [this]() {
        goToPage(4);            // Navigate to home page (Page 4)
        resetInstructionsFrame(); // Reset the frame to its original state
    });

    // Your existing connections and initializations
    connect(ui->pushButton_create, &QPushButton::clicked, this, [this]() {
        goToPage(2); // Switch to create page
    });

    connect(ui->pushButton_login, &QPushButton::clicked, this, [this]() {
        goToPage(1); // Switch to login page
    });

    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->pushButton_enter, &QPushButton::clicked, this, &MainWindow::handleLogin);
    connect(ui->pushButton_save, &QPushButton::clicked, this, &MainWindow::handleSaveAndCreate);

    connect(ui->pushButton_6, &QPushButton::clicked, this, [this]() {
        goToPage(5); // Switch to history page
    });

    connect(ui->pushButton_home, &QPushButton::clicked, this, [this]() {
        populateUserInfoOnPage4(); // Populate user info before navigating
        goToPage(4);              // Switch to Page 4
    });

    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        goToPage(6); // Switch to measure page
    });

    connect(ui->pushButton_menu, &QPushButton::clicked, this, [this]() {
        goToPage(3); // Switch to menu page
    });

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

void MainWindow::startScanningProcess()
{
    resetInstructionsFrame(); // Clear the frame
    currentStep = 1;          // Start from step 1
    stepTimer->start(5000);   // Start the timer (5 seconds per step)
    updateScanningStep();     // Show the first step
}

void MainWindow::updateScanningStep()
{
    if (currentStep > 24) {
        stepTimer->stop(); // Stop the timer after the last step
        homeButton->show(); // Show the "Go Back to Home" button
        return;
    }

    // Load the pixmap for the current step
    QPixmap pixmap(QString(":/images/image%1.png").arg(currentStep));
    if (pixmap.isNull()) {
        qDebug() << "Error: Could not load image for step" << currentStep;
        stepTimer->stop();
        return;
    }

    // Clear the layout
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->frame_3->layout());
    if (!layout) {
        layout = new QVBoxLayout(ui->frame_3);
        ui->frame_3->setLayout(layout);
    }

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Add the image to the layout
    QLabel* imageLabel = new QLabel(ui->frame_3);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel);

    currentStep++; // Move to the next step
}

void MainWindow::resetInstructionsFrame()
{
    // Ensure frame_3 exists
    if (!ui->frame_3) {
        qDebug() << "Error: ui->frame_3 is null.";
        return;
    }

    // Get the existing layout or create a new one if none exists
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->frame_3->layout());
    if (!layout) {
        layout = new QVBoxLayout(ui->frame_3);
        ui->frame_3->setLayout(layout); // Set the layout only if it doesn't exist
    }

    // Clear all widgets in the layout
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget(); // Delete any widgets
        }
        delete item; // Delete the layout item itself
    }

    // Add original instructions back to the frame
    QLabel* instructionsLabel = new QLabel(ui->frame_3);
    instructionsLabel->setWordWrap(true);
    layout->addWidget(instructionsLabel); // Add to the existing layout

    // Reset scanning-related elements
    homeButton->hide();
    stepTimer->stop();
    currentStep = 0;
}


void MainWindow::populateUserInfoOnPage4() {
    if (currentUser) {
        // Update text boxes on Page 4 with currentUser details
        ui->fname->setText(currentUser->getFirstName());
        ui->height->setText(QString::number(currentUser->getWeight()));
        ui->weight->setText(QString::number(currentUser->getHeight()));
    } else {
        QMessageBox::warning(this, "No User Data", "No user is currently logged in.");
    }
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

    // Get the data for the bar graph (8 elements)
    QList<int> dataArray = currentUser->getLastScan();
    QList<int> scores = SystemInteraction::calculateCategoryScores(dataArray);

    if (scores.size() != 8) {
        qDebug() << "Error: Scores array does not contain exactly 8 elements.";
        return;
    }

    // Create QBarSet and populate it with scores
    QtCharts::QBarSet *barSet = new QtCharts::QBarSet("Last Scan");
    for (int value : scores) {
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

    // Configure X-axis with custom labels (8 categories)
    QStringList categories;
    categories << "Heart" << "Lungs" << "Gut" << "Liver" << "Kidney"
               << "Stomach" << "Bladder" << "Lymph";

    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsVisible(true); // Ensure all labels are visible
    axisX->setLabelsAngle(45);     // Rotate labels to prevent overlap
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configure Y-axis for range 0 to 100
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Score");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Adjust chart margins for better fit
    chart->setMargins(QMargins(10, 10, 10, 10));
    chart->legend()->setVisible(false); // Hide legend if not needed

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
        populateUserInfoOnPage4(); // Populate user info before navigating
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
        populateUserInfoOnPage4(); // Populate user info before navigating

        ui->stackedWidget->setCurrentIndex(4);

        // Create the bar graph on page 4
        createBarGraphLastScan(ui->frame_2); // Replace 'ui->page4' with the appropriate widget name
    } else {
        QMessageBox::warning(this, "Registration Failed", "There was an error creating your profile. Please try again.");
    }
}
