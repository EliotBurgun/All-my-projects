#ifndef kmoyenne_HPP
#define kmoyenne_HPP
#include "nuagepoint.hpp"
#include "clustering.hpp"
#include<iostream>
#include<cmath>
#include<random>
#include<cstdlib>

using namespace std;


template <class T>
class kmoyenne : public clustering<T>
{
    protected:
    int niter;
    T * centre;

    public:

    //constructeurs par defaut et par copie 
    kmoyenne() : clustering<T>()
    {
        niter = 0;
        centre = nullptr;
    }    

    kmoyenne(const kmoyenne & k): clustering<T>(k)
    {
        niter = k.niter;
        if (centre!=nullptr)
        {
        centre = new T[k.nbrecluster];
        for (int i=0; i<k.nbrecluster;i++)
            {
                centre[i]=k.centre[i];
            }
        }
    }


    kmoyenne(int n) : clustering<T>()
    {
        this->nbrecluster = n;
        centre = new T[n];
    }

    //destructeurs
    ~kmoyenne()
    {
        delete centre;
    }


    int get_niter();
    T get_centre(int);
    void set_niter(int);
    void set_centre(T, int);


    kmoyenne & operator = (const kmoyenne &);
    template<class O>
    friend::ostream & operator << (std::ostream &, const kmoyenne<O> &);


    void initialise();
    void cluster();
    void cumpute_cluster();

};

// opérateurs = et de sortie

template<class T> kmoyenne<T> & kmoyenne<T>:: operator = (const kmoyenne &k)
{
    if (&k != this)
    {
        niter = k.niter;
        if (centre != nullptr)
        {
            delete [] centre ;
        }
        if(k.centre != nullptr)
        {
            centre = new T[k.nbrecluster];
            for(int i = 0; i<k.nbrecluster ; i++)
            {
                centre[i] = k.centre[i];
            }
        }
        

    }
    return *this;
}



template <class T>
std::ostream & operator << (std::ostream & out, const kmoyenne<T> & k)
{
    out << "nombre d'iteration: "<< k.niter;

    for(int i = 0; i<k.nbrecluster; i++)
    {
        out << "centre numero "<< i << " : "<< k.centre[i];
    }
    return out;

}



//fonctions clusters, initialise et cumpute clusters



template<class T> 
void kmoyenne<T>::initialise()
{
   default_random_engine generator(5); 
   uniform_int_distribution<int> distrib(1,this->nuage->get_nbrepnts()); //distributions de loi uniforme 
   int re;
   for(int i = 0; i<this->get_nbrecluster();i++)
   {
       re = distrib(generator);
       centre[i]= this->nuage->get_tabpnts(re); // prends un centre aléatoirement parmis les points du nuage
   }
}






template<class T> 
void kmoyenne<T>::cluster()
{
    int k=0; //compteur de points du cluster
    for(int i = 0; i<this->get_nbrecluster();i++)
    {
        for (int j = 0; j<this->nuage->get_nbrepnts();j++)
        {
            if(this->get_num(j)==i) //on regarde si le point appartient au clusters
            {
                centre[i] = centre[i] + this->nuage->get_tabpnts(j); 
                k++;
            }
            
        }
        centre[i] = (1/k) * centre[i]; //calcul des nouveaux centres
    }
}    
// accesseurs, mutateurs 

template<class T> 
void kmoyenne<T>::cumpute_cluster()
{
    initialise(); // on initialise les centres 
    for(int i = 0; i<niter; i++) 
    {
        for(int j = 0; j<this->get_nbrecluster();j++) 
        {
            for(int k = 0; k<this->get_nbrecluster();k++) // on fait deux boucles sur les clusters pour parcourir les clusters 
            {
                for(int l = 0; k<this->nuage->get_nbrepnts();j++) // on parcourt les points du nuage 

                {
                    if(this->nuage->get_distance(this->nuage->get_tabpnts(l),get_centre(j))>this->nuage->get_distance(this->nuage->get_tabpnts(l),get_centre(k))) // on regarde lequel centre est le plus proche du points
                    {
                        this->set_num(l,k); // on associe le numero de cluster au point
                    }
                    else
                    {
                        this->set_num(l,j); 
                    }
                }

            }
        }
        cluster(); //on recalcul les centres 
    }

}

// accesseurs & mutateurs 


template <class T>
int kmoyenne<T>::get_niter()
{
    return this->niter;
} 

template <class T>
T kmoyenne<T>::get_centre(int i)
{
    return this->centre[i];
} 

template<class T>
void kmoyenne<T>::set_niter(int i)
{
    niter = i;
}

template<class T>
void kmoyenne<T>::set_centre(T p, int i)
{
    centre[i] = p;
}


#endif