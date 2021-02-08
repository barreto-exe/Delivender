#ifndef ENTREGAWIDGET_H
#define ENTREGAWIDGET_H

#include <QWidget>
#include "solicitud.h"

namespace Ui {
class entregaWidget;
}

class entregaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit entregaWidget(QWidget *parent = nullptr, Solicitud *s = nullptr, bool realizada = false);
    ~entregaWidget();

private slots:
    void on_btnAceptar_clicked();

private:
    Ui::entregaWidget *ui;
    Solicitud solicitud;
};

#endif // ENTREGAWIDGET_H
