#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class FancyTabWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    void show();
    void closeEvent(QCloseEvent *);
protected slots:
    void    openProject();
    void    newProject();

    void    projectStatusChanged();
protected:
    void saveSetting();
protected:
    FancyTabWidget      *m_fancyTab;
};

#endif // MAINWINDOW_H
