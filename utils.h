#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QSize>
#include <QtMath>

class Utils
{
public:
    Utils();
    static QString getFilenameFromPath(QString path);
    static double getDiagonalFromSize(QSize imageSize);
};

#endif // UTILS_H
