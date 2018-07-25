#include "utils.h"

Utils::Utils() {}

QString Utils::getFilenameFromPath(QString path)
{
    return path.right(path.size() - path.lastIndexOf("/") - 1);
}

double Utils::getDiagonalFromSize(QSize imageSize)
{
    int height = imageSize.rheight();
    int width = imageSize.rwidth();
    return sqrt(width * width + height * height);
}
