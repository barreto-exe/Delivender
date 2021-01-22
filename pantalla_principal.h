#ifndef PANTALLA_PRINCIPAL_H
#define PANTALLA_PRINCIPAL_H

#include <QWidget>

namespace Ui {
class pantalla_principal;
}

class pantalla_principal : public QWidget
{
    Q_OBJECT

public:
    explicit pantalla_principal(QWidget *parent = nullptr);
    ~pantalla_principal();

private:
    Ui::pantalla_principal *ui;
};

#endif // PANTALLA_PRINCIPAL_H
