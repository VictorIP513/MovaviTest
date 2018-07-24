#ifndef PYRAMID_H
#define PYRAMID_H

#include <QMainWindow>

namespace Ui {
class Pyramid;
}

class Pyramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pyramid(QWidget *parent = nullptr);
    ~Pyramid();

private:
    Ui::Pyramid *ui;
};

#endif // PYRAMID_H
