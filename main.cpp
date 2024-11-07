#include<iostream>
#include<cmath>
#include<valarray>
#include<random>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<cassert>
#include "nuagepoint.hpp"
#include "clustering.hpp"
#include "kmoyenne.hpp"
#include "dbscan.hpp"




// ATTENTION // j'ai mis une conclusion en commentaires à la fin du main




double dist(valarray<double> x, valarray<double> y)
{
    return sqrt(pow(x[0]-y[0],2)+pow(x[1]-y[1],2)); //definition de la distance
}


int main()
{
    default_random_engine re(time(0));
    normal_distribution <double> d1(1,0.05);
    normal_distribution <double> d2(3,0.05);
    normal_distribution <double> d3(-2,0.05);
    normal_distribution <double> d4(4,0.05);
    normal_distribution <double> d5(2,0.05);
    normal_distribution <double> d6(-1,0.05);
    normal_distribution <double> d7(-9,0.05);
    normal_distribution <double> d8(-6,0.05);
    //definition des distribution pour répartir les points 

    nuagepoint<valarray<double>> E1(40); // creation nuage de point de taille 40


    E1.set_distance(dist);
    for(int i = 0; i<10 ; i++)
    {
        valarray <double> x(2);
        x[0]=d1(re);
        x[1]=d2(re);
        E1.set_tabpnts(i,x);
    {
    //cout<<E1.get_tabpnts(i)[0]<<endl; //verifications des points
    //cout<<E1.get_tabpnts(i)[1]<<endl; 
    }


    }
    for(int i = 10; i<20 ; i++)
    {
        valarray <double> x1(2);
        x1[0]=d3(re);
        x1[1]=d4(re);
        E1.set_tabpnts(i,x1);

    {
    //cout<<E1.get_tabpnts(i)[0]<<endl; //verifications des points
    //cout<<E1.get_tabpnts(i)[1]<<endl; //verifications des points
    }    
    }
    for(int i = 20; i<30 ; i++)
    {
        valarray <double> x2(2);
        x2[0]=d5(re);
        x2[1]=d6(re);
        E1.set_tabpnts(i,x2);

    {
    //cout<<E1.get_tabpnts(i)[0]<<endl; //verifications des points
    //cout<<E1.get_tabpnts(i)[1]<<endl; //verifications des points
    }    

    }
    for(int i = 30; i<40 ; i++)
    {
        valarray <double> x3(2);
        x3[0]=d7(re);
        x3[1]=d8(re);
        E1.set_tabpnts(i,x3);
       

    {
    //cout<<E1.get_tabpnts(i)[0]<<endl; //verifications des points
    //cout<<E1.get_tabpnts(i)[1]<<endl; //verifications des points
    }

    }

    kmoyenne<valarray<double>> K1; //definition de K1
    K1.set_nuage(&E1);  //attribution du nuage
    dbscan<valarray<double>> D1(40); //definition de D1
    D1.set_nbrecluster(4); 
    D1.set_nuage(&E1);
    D1.set_e(0.5);
    D1.set_taille_visite(40);
    K1.set_niter(3);
    //on defini les variables

    // K1.cumpute_cluster(); test de la fonctions (erreur de segmentation)
    D1.set_min(8);
    // D1.cumpute(); test de la fonctions (erreur de segmentation) 
    //K1.initialise(); //test de fonction


    //EXemples 2

    default_random_engine re1; 
    uniform_int_distribution<int> teta(0,2*M_PI); //on prend un nombre aléatoire en 0 et 2PI 
    normal_distribution <double> bruit(0,0.01); // nombre aléatoirepour le bruit
    //definition des distribution pour répartir les points 

    nuagepoint<valarray<double>> E2(40); //nouveau nuage
    E2.set_distance(dist);

    for(int i = 0; i<20 ; i++)
    {
        valarray <double> y(2);
        y[0]=2*cos(teta(re1)) +bruit(re1) ; // x = R*cos(teta) R = 2
        y[1]=2*sin(teta(re1)) +bruit(re1) ; // y = R* sin(teta)R = 2
        E2.set_tabpnts(i,y);
    }
    //creation du cercle de rayon 2

    for(int i = 20; i<40; i++)
    {
        valarray <double> y1(2);
        y1[0]=0.5*cos(teta(re1)) +bruit(re1) ; // x = R*cos(teta) R = 0.5 
        y1[1]=0.5*sin(teta(re1)) +bruit(re1) ; // x = R*sin(teta) R = 0.5
        E2.set_tabpnts(i,y1);

    }
    //creation du cercle de rayon 0.5

    kmoyenne<valarray<double>> K2;
    dbscan<valarray<double>> D2(40);
    K2.set_nuage(&E2);
    K2.set_niter(3);
    D2.set_min(5);
    D2.set_nbrecluster(4);
    D2.set_nuage(&E2);
    D2.set_taille_visite(40);
    K2.set_niter(3);
    //on defini les variables


    //K2.cluster(); test de la fonctions (erreur de segmentation)
    D2.set_min(8);
    for(int i = 0;i<20;i++)
    {
    //cout<<E2.get_tabpnts(i)[0]<<endl;
    //cout<<E2.get_tabpnts(i)[1]<<endl; //regarder les valeurs
    }
    // D2.cluster(); test de la fonctions (erreur de segmentation)
    //K2.cluster(); test de la fonctions (erreur de segmentation)

    return 0;

}


//                                                  
// CONCLUSION 
//
//
//
//
// Le projet était trés intéressant, je n'ai malheureusement pas réussi a bien coder mes fonctions pour créer mes clusteurs, j'avais pleins d'erreurs de segmentations
// malgré plusieurs " valgrind./run " je n'ai pas réussi a faire débugger mes fonctions pourtant elle me semblait proches des méthodes.
// 
//
// Eliot Burgun 




