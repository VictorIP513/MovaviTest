#ifndef PYRAMIDIMAGE_H
#define PYRAMIDIMAGE_H

#include <QPixmap>
#include <QSize>

class PyramidImage
{
public:
    PyramidImage(QPixmap image, double layerCoefficient);
    ~PyramidImage();
    QPixmap getCompressedImage();
    QSize getCompressedSize();
    void enableSmoothTransformation(bool value);
    static int getMaxLayersForSize(QSize imageSize, double layerCoefficient);

private:
    QPixmap image;
    double layerCoefficient;
    bool enabledSmoothTransformation = false;
    QSize originalImageSize;
};

#endif // PYRAMIDIMAGE_H
