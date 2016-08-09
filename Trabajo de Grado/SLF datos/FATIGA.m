%-----------------------------------------------------------------
%ANALISIS DE FATIGA CON CARGA PROPORCIONAL Y AMPLITUD VARIABLE
%UTILIZANDO CURVA S-N Y ALGORITMO RAINFLOW.
%
%ULTIMA MODIFICACION: 01-02-2016
%-----------------------------------------------------------------

clear all;clc;close all
fd =fopen('resultado.txt','w');

%calcula funcion de transferencia para cada nodo en el modelo
fprintf('%s\n','-> Leyendo espectro de presion ...');
meses = 5;   %OJO OJO OJO OJO        %ventana de analisis expresada en meses
time = meses/12; %OJO OJO OJO OJO     %ventana de analisis expresada en años
pload = load('6_005_80.pres');        %datos en psi!!!!
s1min = load('s1.min');               %datos en psi!!!!
s2min = load('s2.min');               %datos en psi!!!!
s3min = load('s3.min');               %datos en psi!!!!
s1max = load('s1.max');               %datos en psi!!!!
s2max = load('s2.max');               %datos en psi!!!!
s3max = load('s3.max');               %datos en psi!!!!
smin = [s1min;s2min;s3min]; 
smax = [s1max;s2max;s3max];

%calculo de variacion von mises segun API 579
fprintf('%s\n','-> Calculando funcion de transferencia ...');
n=length(smin(:,1))/3;
s1min = smin(1:n,2);
s2min = smin(n+1:2*n,2);
s3min = smin(2*n+1:3*n,2);
s1max = smax(1:n,2);
s2max = smax(n+1:2*n,2);
s3max = smax(2*n+1:3*n,2);
ds1 = s1max-s1min;
ds2 = s2max-s2min;
ds3 = s3max-s3min;
%calcula funcion de transferencia
prmin = min(pload);
prmax = max(pload);
TF1 = ds1/(prmax-prmin);
TF2 = ds2/(prmax-prmin);
TF3 = ds3/(prmax-prmin);

fprintf('%s\n','-> Aplicando Algorithmo Rainflow ...');
% realiza conteo de ciclos
tp = sig2ext(pload);            %turning points
rf = rainflow(tp);              %rainflow
ni = rf(3,:);                   %number of cycles
DP = 2*rf(1,:);                 %Palt = 1/2(pmax-pmin)
MP = rf(2,:);                   %Pmean = 1/2(pmax+pmin)


%grafica curvas
fprintf(fd,'-> %s\n','Graficando curvas ...');

%grafica histograma conteo de ciclos
figure(1)
rfmatrix(rf)
 
%grafica histograma de presion
figure(2)
hist(pload)
xlabel('Rango de Presiones [Psi]')
ylabel('Frequencia')

%espectro de presion
figure(3)
plot(pload)
xlabel('Registros')
ylabel('Presion [Psi]')

pause(1)

%calcula daño para cada ciclo y daño acumulado
%constantes tomadas de la tabla F.13 API 579
C1a = 2.254510E+00;
C2a = -4.642236E-01;
C3a = -8.312745E-01;
C4a = 8.634660E-02;
C5a = 2.020834E-01;
C6a = -6.940535E-03;
C7a = -2.079726E-02;
C8a = 2.010235E-04;
C9a = 7.137717E-04;
C10a= 0.0;
C11a= 0.0;

C1b = 7.999502E+00;
C2b = 5.832491E-02;
C3b = 1.500851E-01;
C4b = 1.273659E-04;
C5b = -5.263661E-05;
C6b = 0.0;
C7b = 0.0;
C8b = 0.0;
C9b = 0.0;
C10b= 0.0;
C11b= 0.0;

fprintf('%s\n','-> Calculando daño acumulado ...');
%factores para modificacion de resistencia a la fatiga
Cus = 1.0;
Et = 29.4e6;
Efc = 28.3e6;
Kff = 1.0;
Kee = 1.0;
Ka = 0.45;          %factor acabado superficial
Kb = 1.00;          %Factor de Tamaño
Kc = 1.00;          %Factor de carga
Kd = 1.00;          %Factor de temperatura
Ke = 1.00;          %Factor de confiabilidad
Kf = 1.00;          %Factores misceláneos
%Sf = Ka*Kb*Kc*Kd*Ke*Kf*Sf;

ndp = length(DP);
Sa = zeros(ndp,1);
Dk = zeros(n,1);

kkk=0;
for i = 1 : ndp
    %calcula la amplitud del esfuerzo para cada ciclo para cada nodo
    for j = 1 : n
        Sa(i,j) = 1/sqrt(2)*sqrt((TF1(j)-TF2(j)).^2 + ...
            (TF2(j)-TF3(j)).^2 + (TF3(j)-TF1(j)).^2)*DP(i);
        Sa(i,j) = Kff*Kee*Sa(i,j)/2;
        Sa(i,j) = Sa(i,j)/1e3;                          % convierte a kpsi 

        %las siguientes ecuaciones están en kpsi
        sc = Sa(i,j)/Cus;
        if (Sa(i,j)<=31 && Sa(i,j)>=7)
             X = (C1a + C3a*sc + C5a*sc^2 + C7a*sc^3 + C9a*sc^4 + C11a*sc^5)/...
             (1 + C2a*sc + C4a*sc^2 + C6a*sc^3 + C8a*sc^4 + C10a*sc^5);                  
        else      
            X = (C1b + C3b*sc + C5b*sc^2 + C7b*sc^3 + C9b*sc^4 + C11b*sc^5)/...
             (1 + C2b*sc + C4b*sc^2 + C6b*sc^3 + C8b*sc^4 + C10b*sc^5); 
        end
        %calcula el daño acumulado y vida para cada nodo para cada grupo de carga
        Nkji = 10^X*(Et/Efc);           %vida acumulada en el ciclo DPi en el nodo "j"
        dkji = ni(i)/Nkji;              %daño generado en el ciclo  DPi en el nodo "j"
        Dk(j) = Dk(j) + dkji;           %daño acumulado en el nodo "j"
    end
end

%determina el nodo con major daño acumulado (vida minima)
[val,nd] = max(Dk);

fprintf('\t\t %s\n','-------------------------------------------------------');
fprintf('\t\t %s %f\n','Nodo con mayor daño acumulado   = ',nd);
fprintf('\t\t %s %f\n','Daño total acumulado            = ',val);
fprintf('\t\t %s %i\n','Vida remanente a la fatiga      = ',floor(time/val));
fprintf('\t\t %s %i\n',' Meses en el espectro           = ',meses);
fprintf('\t\t %s %i\n',' Años en el espectro            = ',time);
fprintf('\t\t %s\n','-------------------------------------------------------');

fprintf(fd,'%s\n','Calculando curva de sensibilidad ...');
%grafica de sensibilidad de la vida a la variación de DP
k = 0;
Dfac = zeros(length([0.5:0.05:1.5]),1);
for fac = 0.5 : 0.05 : 1.5
    k = k + 1;
    for i = 1 : ndp
        sc = Sa(i,nd)*fac/Cus;
        if (Sa(i,j)<=31 && Sa(i,j)>=7)
             X = (C1a + C3a*sc + C5a*sc^2 + C7a*sc^3 + C9a*sc^4 + C11a*sc^5)/...
             (1 + C2a*sc + C4a*sc^2 + C6a*sc^3 + C8a*sc^4 + C10a*sc^5);                  
        else    
            X = (C1b + C3b*sc + C5b*sc^2 + C7b*sc^3 + C9b*sc^4 + C11b*sc^5)/...
             (1 + C2b*sc + C4b*sc^2 + C6b*sc^3 + C8b*sc^4 + C10b*sc^5); 
        end
        %calcula el daño acumulado para un factor de presion 
        %dado para el nodo mas critico
        Dfac(k) = Dfac(k) + ni(i)/(10^X*(Et/Efc));        
    end
end

figure(4)
h=plot([0.5 : 0.05 : 1.5],time./Dfac,'r-s');
xlabel('P-Factor')
ylabel('Available Life [Years]');
set(h,'linewidth',2.0);
grid on

%grafica histograma Sa
figure(5)
hist(Sa(:,nd))
xlabel('Maximo Esfuerzo Alternante Sa [kPsi]')
ylabel('Frequencia')

fprintf(fd,'-> %s\n','Hecho!');

