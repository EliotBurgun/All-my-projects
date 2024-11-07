#ifndef nuagepoint_HPP
#define nuagepoint_HPP
#include<iostream>
#include<cmath>


template <class T> class nuagepoint
{
    int nbrepnts;
    T * tabpnts;
    double (*distance)(T,T);

    public:
    

    //constructeurs
    nuagepoint() 
    {
        nbrepnts = 0;
        tabpnts = nullptr;
        distance = nullptr;

    }

    nuagepoint(int i)
    {
        nbrepnts = i;
        tabpnts = new T[i];
        distance = nullptr;
    }
    nuagepoint(const nuagepoint & np)
    {
        nbrepnts = np.nbrepnts;
        tabpnts = new T[nbrepnts];
        for(int i = 0; i<nbrepnts; i++)
        {
            tabpnts[i]=np.tabpnts[i];
        }
        distance = np.distance;

    }


    ~nuagepoint()
    {
        delete[] tabpnts;
    }



    int get_nbrepnts () ;
    T get_tabpnts (int i); 
    double get_distance (T,T);
    void set_nbrepnts(int i);
    void set_distance(double (*d)(T,T));
    void set_tabpnts(int i, T t);


    nuagepoint & operator = (const nuagepoint &);
    nuagepoint operator + (const nuagepoint &);
    T operator [] (int);

    
    static int testu();

}; 

//opérateurs =/+ et [] 

template<class T> nuagepoint<T> & nuagepoint<T> ::operator = (const nuagepoint<T> &N)
{
        if (&N != this)
        {
        nbrepnts = N.nbrepnts;
        tabpnts = new T[nbrepnts];
        for(int i = 0; i<nbrepnts; i++)
        {
            tabpnts[i] = N.tabpnts[i];
        }
        distance = N.distance;
        }
        return *this;

}


// 
template<class T> nuagepoint<T> nuagepoint<T> ::operator +(const nuagepoint<T> &N)
{
    int M=0; 
    M = nbrepnts + N.nbrepnts; //on calcul le nouveau nombre de points
    this->set_nbrepnts(M); // 
    for(int i = 0 ; i<N.nbrepnts ; i++)
    {
        tabpnts[nbrepnts + i] = N.tabpnts[i]; // on copie les nouveaux points a la suite du premier tableau de points
    }
    return *this;

}



template<class T> T nuagepoint<T> ::operator [] (int i)
{
   return tabpnts[i]; //
}


//accesseurs et mutateurs

template <class T> 
int nuagepoint<T>::get_nbrepnts()
{
   return nbrepnts;
}

template <class T> 
T nuagepoint<T>::get_tabpnts(int i)
{
   return tabpnts[i];
}

template <class T> 
double nuagepoint<T>::get_distance(T a ,T b)
{
   return distance(a,b);
}

/*
template <class T> 
void nuagepoint<T>::set_nbrepnts(int i)
{   
   int n = nbrepnts; 
   if (n<i)
   {
       for(int j = n ; j<i;j++)
       {
           tabpnts[j] = 0;
       }
   }
   else
   {
   T * nevv = new T[i];
       for(int k = 0; k<i ;k++)
       {
           nevv[k] = tabpnts[k];
        }

   }     
}
*/ //en commentaire car j'ai créer un constructeur qui prenait directement un nombre de points 

template <class T> 
void nuagepoint<T>::set_distance(double (*d)(T,T))
{
   distance = d;
}

template <class T> 
void nuagepoint<T>::set_tabpnts(int i, T t)
{
   tabpnts[i]= t;
}


//test unitaire (mutateurs, accesseurs, constructeurs, destructeurs et opérateurs)
template <class T> 
int nuagepoint <T>::testu() 
{ 
    int res = 0;
    nuagepoint<int> m1;
    nuagepoint<int> m3;
    m1 = nuagepoint(2);
    m1.set_tabpnts(0,0);
    m1.set_tabpnts(1,1);
    nuagepoint<int> m2;
    m2 = m1;
    if (m2.nbrepnts != m1.nbrepnts)
    {
        res += 1;
    }
    if ((m2[0] != 0) || (m2[1]!=1))
    {
        res += 1;
    }
    //std::cout<< m1[0]<<m1[1]<<m1[2]<<m1.get_nbrepnts()<<"\n"<<std::endl;
    //std::cout<<m2[0]<<m2[1]<<m2.get_nbrepnts()<<"\n"<<std::endl;
    //std::cout<<"\n"<<std::endl;
    //std::cout<<res<<std::endl; 
    if(res == 0)
    {
        std::cout<<"test unitaire réussi"<<std::endl;
    }
    return res;
}


#endif