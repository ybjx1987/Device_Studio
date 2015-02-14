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
    void    saveProject();
    void    closeProject();

    void    projectStatusChanged();
    void    projectModifiedChanged();
protected:
    void saveSetting();
    void updateTitle();
protected:
    FancyTabWidget      *m_fancyTab;
};

#endif // MAINWINDOW_H
