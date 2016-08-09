#include <math.h>
#include <fstream>
#include <iostream>
#include "rainflow.h"

using namespace std;

//void findext(double*,double*,int,int*);
//void diff(double*, int, double*);
//void rainflow(double*,int*,double*,int*);

int main()
{

    double data[30000],data_out[30000],matrix_out[90000];
    int npres=0,ndat[0],cols[0];



    //abre archivo de datos
    fstream fp;
    fp.open("/Users/andrescoulson/Desktop/Trabajo de Grado/fatiga/presion.pres");

    if (fp.good())
    {
        cout <<"ok, proceed with output"<<endl;
    }
    else
    {
        cout <<"fatal error!, file not found" << endl;
        return 0;
    }

    while (!fp.eof())
    {
        fp >> data[npres];
        npres = npres + 1;
    }

    npres = npres-1;

    //determina extremos en datos de presion
    findext(data,data_out,npres,ndat);

//    for(int i = 0; i < ndat[0]; i++)
//    {
//            cout << i <<" "<< data_out[i] << endl;
//    }

    cout << ndat[0] << endl;
    cout << " " << endl;

    //realiza conteo de ciclos usando rainflow algorithm
    rflow(data_out,ndat,matrix_out,cols);

    int k=0;
    for(int i = 0; i < cols[0]; i++)
    {
        cout << i+1 << endl;
        for(int j = 0; j<3; j++)
        {
            cout << matrix_out[k] << endl;
            k=k+1;
        }
        cout << " " << endl;
    }

    fp.close();

    return 0;

}

//FUNCION FINDEXT

//void findext(double *matrix_in,double *matrix_out, int npres, int *ndat)
//{
//    int no=0;
//    double w1[npres],data[npres];

//    //extrae los máximos y ptos de inflexion
//    diff(matrix_in,npres,w1);

//    data[0] = matrix_in[0];
//    for(int i = 0; i < npres-2; i++)
//    {
//        if(w1[i]*w1[i+1] <= 0)
//        {
//            no = no + 1;
//            data[no] = matrix_in[i+1];
//        }
//    }

//    data[no+1] = matrix_in[npres-1];
//    no=no + 2;        //son 2 pq hay que contar el 1ro y el ultm.

//    //elimina puntos de inflexión
//    if(no!=0)
//    {
//        npres = no;
//        no = 0;
//    }
//    matrix_in = data;
//    diff(data,npres,w1);

//    for(int i = 0; i < npres-1; i++)
//    {
//        if (!((w1[i]==0) && (w1[i+1]==0)))
//        {
//            no = no + 1;
//            data[no] = matrix_in[i+1];
//        }
//    }

//    no = no + 1;    //se agrega por el ultimo

//    //retira los datos repetidos
//    if(no!=0)
//    {
//        npres = no;
//        no = 0;
//    }

//    matrix_in = data;

//    for(int i = 0; i < npres; i++)
//    {
//        if(!(matrix_in[i] == matrix_in[i+1]))
//        {
//            data[no] = matrix_in[i];
//            no = no + 1;
//        }
//    }

//    //extrae los maximos
//    if(no!=0)
//    {
//        npres = no;
//        no = 0;
//    }

//    if (sizeof(data)>2)
//    {
//        diff(data,npres,w1);
//        for(int i = 0; i < npres; i++)
//        {
//            if(w1[i]*w1[i+1] < 0)
//            {
//                no = no + 1;
//                data[no] = matrix_in[i+1];
//            }
//        }
//    }

//    //almacena datos en MATRIX_OUT
//    for(int i = 0; i < no; i++)
//    {
//        *(matrix_out+i) = data[i];
//    }
//    *ndat = no;
//}

//DEFINE LA FUNCION DFF

//void diff(double *matrix_in, int ni, double *w1)
//{
//    for(int i = 0; i < ni-1; i++)
//    {
//        w1[i] = matrix_in[i+1]-matrix_in[i];
//    }
//}

//DEFINE LA FUNCION RAINFLOW

//void rainflow(double *pr,int *ndat,double *po, int *col)
//{
//    double a[30000],ampl=0,mean=0;
//    int tot_num = ndat[0]; cout<<tot_num<<endl;
//    int j=-1,cNr=1,k=0;

//    for (int index=0; index<tot_num; index++) {
//        a[++j]=*pr++;
//        while ( (j >= 2) && (fabs(a[j-1]-a[j-2]) <= fabs(a[j]-a[j-1])) ) {
//            ampl=fabs( (a[j-1]-a[j-2])/2 );
//            switch(j)
//            {
//            case 0: { break; }
//            case 1: { break; }
//            case 2: {
//                mean=(a[0]+a[1])/2;
//                a[0]=a[1];
//                a[1]=a[2];
//                j=1;
//                if (ampl > 0) {
//                    *po++=ampl;
//                    *po++=mean;
//                    *po++=0.50;
//                    k=k+1;
//                }
//                break;
//            }
//            default: {
//                mean=(a[j-1]+a[j-2])/2;
//                a[j-2]=a[j];
//                j=j-2;
//                if (ampl > 0) {
//                    *po++=ampl;
//                    *po++=mean;
//                    *po++=1.00;
//                    cNr++;
//                    k=k+1;
//                }
//                break;
//            }
//            }
//        }
//    }
//    for (int index=0; index<j; index++) {
//        ampl=fabs(a[index]-a[index+1])/2;
//        mean=(a[index]+a[index+1])/2;
//        if (ampl > 0){
//            *po++=ampl;
//            *po++=mean;
//            *po++=0.50;
//            k=k+1;
//        }
//    }
//    *col=k;
//}



