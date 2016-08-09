#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "archivo.cpp"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QtGlobal>
#include<algorithm>
#include"../rainflow/rainflow.cpp"


using namespace std;

archivo archiv ;

void SavePlot(QWidget *widget,QWidget *plt);
void ClasificaY(double nClases,double longClases, QVector<double>& vector, QVector<double> data);
void ClasificaX(double nClases,double longClases,double pmin, QVector<double>& vector);
int ClassMax (double nClases , QVector<double> vector);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lbl_rflow->setVisible(false);
    ui->HistRainflow->setVisible(false);
    ui->HistSmRainflow->setVisible(false);
    ui->lbl_SmRainflow->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadButton_clicked()
{
    ui->lbl_rflow->setVisible(false);
    ui->HistRainflow->setVisible(false);
    ui->HistSmRainflow->setVisible(false);
    ui->lbl_SmRainflow->setVisible(false);

    QVector<double> pres(70000);
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home/usuario/fatiga/",
                "Pressure Files (*.pres);; All Files (*.*)"
                );


    archiv.setFilename(filename);

    // Si existe el archivo lo abre sino el proceso se detiene
    QFile filepres(filename);
    if(filepres.exists()){

        filepres.open(QIODevice::ReadOnly);


        //carga los datos del archivo al vector
        QTextStream in(&filepres);
        int npre=0;
        while (!in.atEnd())
        {
            in >> pres[npre];
            npre = npre + 1;
        }

        npre = npre-1;
        pres.resize(npre);
        archiv.setPresion(pres);

        //carga de archivo fin

        // determina pmax y pmin
        double pmax=-1.E9, pmin=1.E9;

        for(int i=0;i<npre;++i)
        {
            if(pres[i]>pmax)
            {
                pmax = pres[i];
            }
            if(pres[i]<pmin)
            {
                pmin = pres[i];
            }
        }

        // generate some data:
        QVector<double> x(npre);
        for (int i=0; i<npre; ++i)
        {
            x[i] = i;
        }
        //crea grafico del espectro de presion:

        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setData(x,pres);

        // give the axes some labels:
        ui->customPlot->xAxis->setLabel("Time [Hours]");
        ui->customPlot->yAxis->setLabel("Pressure [Psi]");

        // set axes ranges, so we see all data:
        ui->customPlot->xAxis->setRange(0, npre);
        ui->customPlot->yAxis->setRange(pmin,pmax);
        ui->customPlot->replot();


        //crea histograma del espectro de presion:
        qSort(pres);
        int nclass = sqrt(pres.size());
        cout<<endl<<" clases"<<nclass<<endl;
        cout<<endl<<" datos numero "<<pres.size()<<endl;

        double dpres = (pmax-pmin) / nclass;

        QVector<double> classpx(nclass), classpy(nclass);

        for (int i=0; i<nclass; ++i)
        {
            classpx[i]=pmin+i*dpres;
            for(int j=0; j<npre; ++j)
            {
                if(pres[j]>=(pmin+(i*dpres)) && pres[j]<=(pmin+(i+1)*dpres))
                {
                    classpy[i]=classpy[i]+1;
                }
            }
        }

        //determina valor maximo de classpy:
        int classmax=-1.E-9;
        for (int i=0; i<nclass; ++i)
        {
            if(classpy[i]>classmax)
                classmax=classpy[i];
        }

        //dibuja histograma de presion:

        QCPBarsGroup *group1 = new QCPBarsGroup(ui->HistPressPlot);
        QCPBars *bars = new QCPBars(ui->HistPressPlot->xAxis, ui->HistPressPlot->yAxis);

        ui->HistPressPlot->addPlottable(bars);

        bars->setData(classpx, classpy);
        bars->setBrush(QColor(0, 0, 255, 50));
        bars->setPen(QColor(0, 0, 255));
        bars->setWidth(1.);
        bars->setBarsGroup(group1);

        ui->HistPressPlot->xAxis->setRange(pmin, pmax);
        ui->HistPressPlot->yAxis->setRange(0,classmax);

        ui->HistPressPlot->replot();




    }else{ return;}





}

void MainWindow::on_RCCButton_clicked()
{

    double data[40000],data_out[40000],matrix_out[90000];
    int ndat[0],cols[0];

    QVector<double> Esfuerzo_alternante,Esfuerzo_medio;

    // ........... obteniendo los valores del archivo y pasandolos al vector........//
    for(int i=0;i<archiv.getPresion().size();i++){

        //cout<<" presion "+i<<archiv.getPresion().value(i);
        data[i] = archiv.getPresion().value(i);
    }
    //determina extremos en datos de presion
    findext(data,data_out,archiv.getPresion().size(),ndat);

    //realiza conteo de ciclos usando rainflow algorithm
    rflow(data_out,ndat,matrix_out,cols);

    int k=0;
    for(int i = 0; i < cols[0]; i++)
        for(int j = 0; j<3; j++)
        {
            switch (j) {
            case 0:
                Esfuerzo_alternante.append(matrix_out[k]);
                break;
            case 1:
                Esfuerzo_medio.append(matrix_out[k]);
            default:
                break;
            }
            k=k+1;
        }

    qSort(Esfuerzo_alternante);
    qSort(Esfuerzo_medio);

    /* ************** Construyendo histograma de esfuerzo alternate ************* */

    double pmin = Esfuerzo_alternante.first();
    double rango_datos = (Esfuerzo_alternante.last() - Esfuerzo_alternante.first());
    int numero_clases = sqrt(Esfuerzo_alternante.size());
    double longitud_clases = rango_datos / numero_clases;
    QVector<double> classpx(numero_clases), classpy(numero_clases);

    ClasificaX(numero_clases,longitud_clases,pmin,classpx);
    ClasificaY(numero_clases,longitud_clases,classpy,Esfuerzo_alternante);

    int classmax = ClassMax(numero_clases,classpy);



    ui->HistRainflow->setVisible(true);
    ui->lbl_rflow->setVisible(true);

    QCPBarsGroup *group1 = new QCPBarsGroup(ui->HistRainflow);
    QCPBars *bars = new QCPBars(ui->HistRainflow->xAxis, ui->HistRainflow->yAxis);

    ui->HistRainflow->addPlottable(bars);

    bars->setData(classpx,classpy);
    bars->setBrush(QColor(0, 0, 255, 50));
    bars->setPen(QColor(0, 0, 255));
    bars->setWidth(1.);
    bars->setBarsGroup(group1);


    ui->HistRainflow->xAxis->setRange(Esfuerzo_alternante.first(), Esfuerzo_alternante.last());
    ui->HistRainflow->yAxis->setRange(0,classmax);

    ui->HistRainflow->replot();

    // **************** Construyendo histograma de Esfuerzo medio *****************//
    double pmin_sm = Esfuerzo_medio.first();
    double rango_datos_sm = (Esfuerzo_medio.last() - Esfuerzo_medio.first());
    int numero_clases_sm = sqrt(Esfuerzo_medio.size());
    double longitud_clases_sm = rango_datos_sm / numero_clases_sm;

    QVector<double> classpx_sm(numero_clases_sm), classpy_sm(numero_clases_sm);



    ClasificaX(numero_clases_sm,longitud_clases_sm,pmin_sm,classpx_sm);
    ClasificaY(numero_clases_sm,longitud_clases_sm,classpy_sm,Esfuerzo_medio);


    int classmax_sm = ClassMax(numero_clases_sm,classpy_sm);

    ui->HistSmRainflow->setVisible(true);
    ui->lbl_SmRainflow->setVisible(true);

    QCPBarsGroup *groupp1 = new QCPBarsGroup(ui->HistSmRainflow);
    QCPBars *barss = new QCPBars(ui->HistSmRainflow->xAxis, ui->HistSmRainflow->yAxis);

    ui->HistSmRainflow->addPlottable(barss);

    barss->setData(classpx_sm,classpy_sm);
    barss->setBrush(QColor(0, 0, 255, 50));
    barss->setPen(QColor(0, 0, 255));
    barss->setWidth(1.);
    barss->setBarsGroup(groupp1);


    ui->HistSmRainflow->xAxis->setRange(Esfuerzo_medio.first(), Esfuerzo_medio.last());
    ui->HistSmRainflow->yAxis->setRange(0,classmax_sm);



    ui->HistSmRainflow->replot();


}


void MainWindow::on_closeButtom_clicked()
{
    close();
}


void SavePlot(QWidget *widget,QWidget *plt){

    QString saveFilename = QFileDialog::getSaveFileName(widget, "Save as", "Choose a filename", " TIFF(*.tiff *.tif);; PNG(*.png);; JPEG(*.jpg *.jpeg)");

    QString saveExtension = "TIFF";
    int pos = saveFilename.lastIndexOf('.');
    if (pos >= 0)
        saveExtension = saveFilename.mid(pos + 1);

    if(!QPixmap::grabWidget(plt).save(saveFilename, qPrintable(saveExtension)))
    {
        // since you have a widget, just use grabWidget() here. winId() would possibly have
        // portability issues on other platforms.  qPrintable(saveExtension) is effectively
        // the same as saveExtension.toLocal8Bit().constData()

        QMessageBox::warning(widget, "File could not be saved", "ok", QMessageBox::Ok);
    }

}


void MainWindow::ShowContextMenu(const QPoint& pos) // this is a slot
{
    // for most widgets
    QPoint globalPos = ui->HistPressPlot->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("Guardar imagen");
    // ...

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        // something was chosen, do stuff
        SavePlot(this,ui->HistPressPlot);
    }
    else
    {
        // nothing was chosen
    }


}

int ClassMax (double nClases , QVector<double> vector)
{
    int classmax=-1.E-9;
    for (int i=0; i<nClases; ++i)
    {
        if(vector[i]>classmax)
            classmax=vector[i];
    }

    return classmax;
}

void ClasificaX(double nClases,double longClases,double pmin, QVector<double>& vector){

    for (int i=0; i<nClases; ++i)
    {
        vector[i]=pmin+i*longClases;

    }


}

void ClasificaY(double nClases,double longClases, QVector<double>& vector, QVector<double> data){

    double pmin = data.first();

    for (int i=0; i<nClases; ++i)
    {

        for(int j=0; j<data.size(); ++j)
        {
            if(data[j]>=(pmin+(i*longClases)) && data[j]<=(pmin+(i+1)*longClases))
            {
                vector[i]=vector[i]+1;
            }
        }
    }


}



void MainWindow::on_SLFButton_clicked()
{
    close();
}
