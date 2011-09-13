#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->showMaximized();
    this->create_sidemenu();
}

void MainWindow::create_sidemenu()
{
    this->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
    this->create_dock_areas();

}
