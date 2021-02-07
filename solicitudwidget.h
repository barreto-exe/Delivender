#ifndef SOLICITUDWIDGET_H
#define SOLICITUDWIDGET_H

#include <QWidget>
#include "solicitud.h"

namespace Ui {
class solicitudWidget;
}

class solicitudWidget : public QWidget
{
    Q_OBJECT

public:
    explicit solicitudWidget(QWidget *parent = nullptr, Solicitud *s = nullptr);
    ~solicitudWidget();

private slots:
    void on_btnAceptar_clicked();

    void on_btnRechazar_clicked();

private:
    Ui::solicitudWidget *ui;
    Solicitud solicitud;
};

#endif // SOLICITUDWIDGET_H
