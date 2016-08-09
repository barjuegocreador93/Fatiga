#ifndef ARCHIVO
#define ARCHIVO

#include<QString>
#include<QFile>


class archivo{

public:

    QString getFilename() const;
    void setFilename(const QString &value);



    QVector<double> getPresion() const;
    void setPresion(const QVector<double> &value);

private:
    QString filename;
    QVector<double> presion;


};


#endif // ARCHIVO
