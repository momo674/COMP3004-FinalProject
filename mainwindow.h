#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

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

private:
    Ui::MainWindow *ui;
    QStack<int> pageHistory; // Stack to store page indices for navigation
};

#endif // MAINWINDOW_H