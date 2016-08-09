#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QtGui/QFont>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QPointer>
#include <QtCore/QPropertyAnimation>





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_LoadButton_clicked();

    //void on_pushButton_3_clicked();

    void on_closeButtom_clicked();

    void on_RCCButton_clicked();
    void ShowContextMenu(const QPoint& pos);

    void on_SLFButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
