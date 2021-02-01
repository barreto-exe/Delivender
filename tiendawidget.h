#ifndef TIENDAWIDGET_H
#define TIENDAWIDGET_H

#include <QWidget>
#include <string>

using std::string;

namespace Ui {
class tiendaWidget;
}

class tiendaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit tiendaWidget(QWidget *parent = nullptr, string nombre = "", string descripcion = "");
    ~tiendaWidget();

private:
    Ui::tiendaWidget *ui;
};

#endif // TIENDAWIDGET_H
