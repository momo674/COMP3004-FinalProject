#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    // Connect the "Back" button on page_3 to navigate back
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::goBack);

    //Connect the "Back" button on page_4 to navigate back
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::goBack);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to navigate to a page and save the previous page in history
void MainWindow::goToPage(int index)
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if (currentIndex != index) {
        pageHistory.push(currentIndex); // Save the current index in history
        ui->stackedWidget->setCurrentIndex(index); // Navigate to the target page
    }
}

// Function to navigate back to the previous page
void MainWindow::goBack()
{
    if (!pageHistory.isEmpty()) {
        int previousIndex = pageHistory.pop(); // Retrieve the previous page index
        ui->stackedWidget->setCurrentIndex(previousIndex); // Navigate to the previous page
    }
}
