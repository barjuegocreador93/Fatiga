#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

//void findext(float[],float[]);
//void diff(float[], int, float[]);
void findext(float*,float*,int);
void diff(float*, int, float*);

int main()
{

    float data[30000],matrix_ext[30000];
    int npres=0;

    //abre archivo de datos
    ifstream fp("prueba.pres");

    while (!fp.eof())
    {
        fp >> data[npres];
        npres = npres + 1;
    }

    npres = npres-1;

    findext(data,matrix_ext,npres);

    for(int i = 0; i < 19; i++)
    {
            cout <<i <<' '<< matrix_ext[i] << endl;
    }

    //rf3(array_ext,array_out);

    //fclose(fp);

    return 0;

}

void findext(float *matrix_in,float *matrix_out, int npres)
{
    int no=0;
    float w1[npres],data[npres];

    //extrae los máximos y ptos de inflexion
    diff(matrix_in,npres,w1);

    data[0] = matrix_in[0];
    for(int i = 0; i < npres-2; i++)
    {
        if(w1[i]*w1[i+1] <= 0)
        {
            no = no + 1;
            data[no] = matrix_in[i+1];
        }
    }

    data[no+1] = matrix_in[npres-1];
    no=no + 2;        //son 2 pq hay que contar el 1ro y el ultm.

    //elimina puntos de inflexión
    if(no!=0)
    {
        npres = no;
        no = 0;
    }
    matrix_in = data;
    diff(data,npres,w1);

    for(int i = 0; i < npres-1; i++)
    {
        if (!((w1[i]==0) && (w1[i+1]==0)))
        {
            no = no + 1;
            data[no] = matrix_in[i+1];
        }
    }

    no = no + 1;    //se agrega por el ultimo

    //retira los datos repetidos
    if(no!=0)
    {
        npres = no;
        no = 0;
    }

    matrix_in = data;

    for(int i = 0; i < npres; i++)
    {
        if(!(matrix_in[i] == matrix_in[i+1]))
        {
            data[no] = matrix_in[i];
            no = no + 1;
        }
    }

    //extrae los maximos
    if(no!=0)
    {
        npres = no;
        no = 0;
    }

    if (sizeof(data)>2)
    {
        diff(data,npres,w1);
        for(int i = 0; i < npres; i++)
        {
            if(w1[i]*w1[i+1] < 0)
            {
                no = no + 1;
                data[no] = matrix_in[i+1];
            }
        }
    }

    //almacena datos en MATRIX_OUT
    for(int i = 0; i < no; i++)
    {
        *(matrix_out+i) = data[i];
    }
}

//DEFINE LA FUNCION DFF

void diff(float *matrix_in, int ni, float *w1)
{
    for(int i = 0; i < ni-1; i++)
    {
        w1[i] = matrix_in[i+1]-matrix_in[i];
    }
}

//DEFINE LA FUNCION RF3

//*  RAINFLOW $ Revision: 1.1 $ */
//*  by Adam Nieslony, 2009     */

//* ++++++++++ BEGIN RF3 [ampl ampl_mean nr_of_cycle] */
//* ++++++++++ Rain flow without time analysis */


//void rf3(mxArray *array_ext, mxArray *hs[]) {
//    double *pr, *po, a[16384], ampl, mean;
//    int tot_num, index, j, cNr;
//    mxArray *array_out;

//    tot_num = mxGetM(array_ext) * mxGetN(array_ext);
//    pr = (double *)mxGetPr(array_ext);

//    array_out = mxCreateDoubleMatrix(3, tot_num-1, mxREAL);
//    po = (double *)mxGetPr(array_out);

//    j = -1;
//    cNr = 1;
//    for (index=0; index<tot_num; index++) {
//        a[++j]=*pr++;
//        while ( (j >= 2) && (fabs(a[j-1]-a[j-2]) <= fabs(a[j]-a[j-1])) ) {
//            ampl=fabs( (a[j-1]-a[j-2])/2 );
//            switch(j)
//{
//                case 0: { break; }
//                case 1: { break; }
//                case 2: {
//                    mean=(a[0]+a[1])/2;
//                    a[0]=a[1];
//                    a[1]=a[2];
//                    j=1;
//                    if (ampl > 0) {
//                        *po++=ampl;
//                        *po++=mean;
//                        *po++=0.50;
//                    }
//                    break;
//                }
//                default: {
//                    mean=(a[j-1]+a[j-2])/2;
//                    a[j-2]=a[j];
//                    j=j-2;
//                    if (ampl > 0) {
//                        *po++=ampl;
//                        *po++=mean;
//                        *po++=1.00;
//                        cNr++;
//                    }
//                    break;
//                }
//            }
//        }
//    }
//    for (index=0; index<j; index++) {
//        ampl=fabs(a[index]-a[index+1])/2;
//        mean=(a[index]+a[index+1])/2;
//        if (ampl > 0){
//            *po++=ampl;
//            *po++=mean;
//            *po++=0.50;
//        }
//    }
//  /* you can free the allocated memeory */
//  /* for array_out data                 */
//    mxSetN(array_out, tot_num - cNr);
//    hs[0]=array_out;
//}



