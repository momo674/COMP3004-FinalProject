#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include "SystemInteraction.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
//#include <QtCharts>

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
    void goToPage(int index);
    void goBack();
    void handleLogin(); // Slot to handle the Enter button
    void handleSaveAndCreate(); // Slot to handle Save button



private:
    Ui::MainWindow *ui;
    QStack<int> pageHistory; // Stack to store page indices for navigation
};

#endif // MAINWINDOW_H
