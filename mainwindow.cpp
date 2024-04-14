#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // инициализируем вектора
    x1.resize(10), y1.resize(10),y2.resize(10);

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

     // заполняем 10 координат по оси Y временем МНК
     MNK(y2);

    // фиксируем ось x с шагом 100
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    ui->widget->xAxis->setTicker(fixedTicker);
    fixedTicker->setTickStep(100.0);

    // настраиваем шрифт
    QFont font;
    font.setFamily("sans");
    font.setPointSize(12);
    font.setBold(true);

    // добавляем график 1 на виджет с осями
    QCPGraph *graph1 = ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis);
    //стиль разброса точек
    graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    // цвет линии графа 1
    graph1->setPen(QPen(Qt::green));
    // имя графика 1
    graph1->setName("Runtime");

    // добавляем график 2 на виджет с осями
    QCPGraph *graph2 = ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis);
    //стиль разброса точек
    graph2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    // цвет линии графа 2
    graph2->setPen(QPen(Qt::red));
    // имя графика 2
    graph2->setName("Theoretical Time");

    // ставим шрифт на оси
    ui->widget->xAxis->setLabelFont(font);
    ui->widget->yAxis->setLabelFont(font);

    // стрелочки
    ui->widget->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->widget->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);


    // заголовок
    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Runtime vs Theoretical Time", QFont("sans", 12, QFont::Bold)));

    // Называем оси
    ui->widget->xAxis->setLabel("Input Size");
    ui->widget->yAxis->setLabel("Time");

    // Устанавливаем отрезок от 100 до 1000 для X оси
    ui->widget->xAxis->setRange(0, 1100);
    // Устанавливаем отрезок от 0 до maxY для Y оси
    ui->widget->yAxis->setRange(0, maxY+0.000001);

    // избавляемся от научной нотации
    ui->widget->yAxis->setNumberFormat("f");
    ui->widget->yAxis->setNumberPrecision(8);

    // Включаю легенду и её положение
    ui->widget->legend->setVisible(true);
    ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);

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
    using namespace std::chrono;

    steady_clock::time_point start, end;
    duration<double> totalTime(0);
    double minTime = std::numeric_limits<double>::max();
    double maxTime = 0;

    for(int i = 0; i < 12; ++i){
        start = steady_clock::now();
        int count = tree.countNodesWithTwoChildren();
        end = steady_clock::now();
        duration<double> elapsedTime = end - start; // затрачееное время
        totalTime += elapsedTime;
        minTime = std::min(minTime, elapsedTime.count());
        maxTime = std::max(maxTime, elapsedTime.count());
    }
    totalTime -= duration<double>(minTime);
    totalTime -= duration<double>(maxTime);



    double averageTime = totalTime.count() / 10.0;

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

void MainWindow::MNK(QVector<double> &yAxis2)
{
    // Получаем количество элементов в векторе
    int n = x1.size();

    // Вычисляем суммы и средние значения
    double sumXY = 0, sumXX = 0;
    for (int i = 0; i < n; ++i) {
        sumXY += x1[i] * y1[i];
        sumXX += x1[i] * x1[i];
    }
    double meanX = std::accumulate(x1.begin(), x1.end(), 0.0) / n;
    double meanY = std::accumulate(y1.begin(), y1.end(), 0.0) / n;

    // Вычисляем коэффициенты МНК
    double m = (sumXY - n * meanX * meanY) / (sumXX - n * meanX * meanX);
    double b = meanY - m * meanX;

    // Рассчитываем значения y2 с использованием линии регрессии
    for (int i = 0; i < n; ++i) {
        yAxis2[i] = m * x1[i] + b;
    }
}


void MainWindow::on_pushButton_clicked()
{

    QTimer* timer = new QTimer(this);
    timer->setInterval(100);
    static int dataIndex  = 0;

    connect(timer,&QTimer::timeout,[=](){
        if(dataIndex<y1.size()){
            ui->widget->graph(0)->addData(x1[dataIndex],y1[dataIndex]);
            ui->widget->graph(1)->addData(x1[dataIndex],y2[dataIndex]);
            ui->widget->replot();
            dataIndex++;}
            else
                timer->stop();
                   });
        timer->start();
}
