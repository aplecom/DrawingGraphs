#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // создаем векторы осей
    QVector<double> x1(10), y1(10);

    // заполняем 10 координат по оси Y временем выполнения
    allRuntime(y1);

    // максимальное время для маакс значения в графике
    double maxY = *std::max_element(y1.constBegin(), y1.constEnd());

    // заполняем 10 координат по оси X от 100 до 1000
    double xBegin = 0;
    for(int i = 0 ; i < x1.size();++i)
    {
        x1[i] = xBegin+=100;
    }


    // добавляем график на виджет с осями
    ui->widget->addGraph(ui->widget->xAxis,ui->widget->yAxis);
    // устанавливаем данные для графика - > оси
    ui->widget->graph(0)->setData(x1,y1);

    // Называем оси
    ui->widget->xAxis->setLabel("Input Size");
    ui->widget->yAxis->setLabel("Time");

    // Устанавливаем отрезок от 100 до 1000 для X оси
    ui->widget->xAxis->setRange(100, 1000);
    // Устанавливаем отрезок от 0 до maxY для Y оси
    ui->widget->yAxis->setRange(0, maxY);



    ui->widget->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}


QVector<int> MainWindow::generateRandomValue(int countValue)
{
    QVector<int> result;

    for (int i = 1 ; i < 1001; ++i)
        result.append(i);

    std::random_device rd; // устройство для генерации сл.чисел
    std::mt19937 g(rd()); // генератор

    std::shuffle(result.begin(),result.end(),g); // переупорядочивает элементы в заданном диапазоне

    result.resize(countValue);
    return result;
}

void MainWindow::addValToTree(QVector<int> vector)
{
    tree.clear();
    for(auto value:vector)
        tree.insert(value);
}

double MainWindow::runtime()
{
    QElapsedTimer timer;
    qint64 totalTime = 0;
    qint64 times[12];

    for(int i = 0; i<12; ++i){
        timer.start();
        int count = tree.countNodesWithTwoChildren();
        times[i]=timer.elapsed();
        totalTime+=times[i];
    }

    qint64 minTime = *std::min_element(times, times + 12);
    qint64 maxTime = *std::max_element(times, times + 12);

    totalTime-=minTime;
    totalTime-=maxTime;

    double averageTime = static_cast<double>(totalTime) / (10.0 * 1000.0);

    return averageTime;
}

void MainWindow::allRuntime( QVector<double> &yAxis)
{
    int N = 100; // количесвто случайных чисел
    int i = 0;
    while(N<=1000){

        // генерируем N случайных чисел
        QVector<int> vector = generateRandomValue(N);

        //Добавили случайные числа в дерево
        addValToTree(vector);
        double time = runtime();

        yAxis[i] = time;
        N+=100;
        i++;
    }
}



void MainWindow::on_pushButton_clicked()
{
    // сделать постепенное построение по таймеру
}
