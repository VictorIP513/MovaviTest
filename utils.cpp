#include "utils.h"

Utils::Utils() {}

QString Utils::getFilenameFromPath(QString path)
{
    return path.right(path.size() - path.lastIndexOf("/") - 1);
}
