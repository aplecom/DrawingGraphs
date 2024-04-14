#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <BinarySearchTree.h>
#include <QMainWindow>
#include<QVector>
#include<QTimer>
#include<qcustomplot.h>
#include<algorithm> // std:: shuffle
#include<random> // std:: random_device , std:: mt19937
#include<chrono> // для получения начального значения для генератора
#include<QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    BinarySearchTree<int> tree;
    QVector<int> generateRandomValue(int countValue);
    void addValToTree(QVector<int> vector);
    double runtime();
    void allRuntime(QVector<double> &yAxis);

};
#endif // MAINWINDOW_H
