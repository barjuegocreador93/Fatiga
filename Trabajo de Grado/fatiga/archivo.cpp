#include"archivo.h"




// Getter y Setter

QString archivo::getFilename() const
{
    return filename;
}

void archivo::setFilename(const QString &value)
{
    filename = value;
}

QVector<double> archivo::getPresion() const
{
    return presion;
}

void archivo::setPresion(const QVector<double> &value)
{
    presion = value;
}


