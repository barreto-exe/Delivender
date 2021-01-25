#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Frontend
#include <pantalla_principal.h>
#include <pantalla_registro.h>
#include <qstackedwidget.h>

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
    void on_btnInicioSesion_clicked();

    void on_btnRegistrarse_clicked();
    void IrAInicio();

private:
    Ui::MainWindow *ui;

    // Frontend
    pantalla_principal menu;
    pantalla_registro registro;
    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
