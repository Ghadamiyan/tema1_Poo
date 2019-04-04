#include <iostream>
#include <fstream>

using namespace std;

class Vector
{
    int vsize;
    int* v;

public:

    Vector()
    {
        /*v=new int [100];
        for(int i=0; i<100; i++)
            v[i]=0;*/ v=NULL;
    }

    Vector(int i)
    {
        v=new int[i];
        vsize=i;
    }

    Vector(const Vector& a)
    {
        vsize=a.vsize;
        v=new int[a.vsize];
        for(int i=0; i<a.vsize; i++)
            v[i]=a.v[i];
    }

    ~Vector()
    {
        delete[] v;
    }

    void set_size(int i)
    {
        v=new int[i];
        vsize=i;
    }

    int get_size()
    {
        return vsize;
    }

    int operator [](int i)
    {
        return v[i];
    }

    Vector& operator=(const Vector& a)
    {
        if(this != &a)
        {
            vsize=a.vsize;
            delete[] v;
            v=new int[vsize];
            for(int i=0; i<a.vsize; i++)
                v[i]=a.v[i];

        }
        return *this;
    }

    bool operator!=(const Vector& a)
    {
        for(int i=0; i<vsize; i++)
        {
            if(v[i]!=a.v[i])
                return false;
        }
        return true;
    }

    int suma()
    {
        int s=0;
        for(int i=0; i<vsize; i++) s=s+v[i];
        cout<<s<<endl;
        return s;
    }

    int maxim()
    {
        int maxim=v[0];
        for(int i=0; i<vsize; i++)
        {
            if (v[i]>maxim) maxim=v[i];
        }
        cout<<maxim<<endl;
        return maxim;
    }

    void sortare()
    {
        for (int i = 0; i < vsize-1; i++)
            for (int j = 0; j < vsize-i-1; j++)
                if (v[j] > v[j+1])
                    swap(v[j], v[j+1]);
    }

    int operator*(const Vector& a)
    {
        int s=0;
        if (vsize==a.vsize)
        {
            for(int i=0; i<vsize; i++)
            {
                s=s+v[i]*a.v[i];
            }
            //  cout<<s<<endl;
        }
        return s;
    }

    friend istream& operator>>(istream &in, Vector &vec)
    {
        for(int k=0; k<vec.vsize; k++)
            in>>vec.v[k];
        return in;
    }

    friend ostream& operator<<(ostream &out, const Vector &a)
    {
        for(int i=0; i<a.vsize; i++)
            out<<a.v[i]<<" ";
        out<<endl;

        return out;
    }

    Vector operator+(const Vector &a)
    {
        Vector s;
        s.vsize = a.vsize;
        for(int i=0; i<a.vsize; i++)
            s.v[i] = v[i] + a.v[i];
        return s;
    }

    friend class Matrice;
};

class Matrice
{
    Vector *m;
    int lin, col;
public:

    void set_dimensiuni(int i, int j)
    {
        lin=i;
        col=j;
        m=new Vector[lin];
    }

    friend istream& operator>>(istream &in, Matrice &mat)
    {
        //mat.m=new Vector[mat.lin];
        mat.set_dimensiuni(mat.lin, mat.col);
        for(int i=0; i<mat.lin; i++)
        {
            mat.m[i].set_size(mat.col);
            in>>mat.m[i];
        }
        return in;
    }

    friend ostream& operator<<(ostream&g, const Matrice& m1)
    {
        for(int i=0; i<m1.lin; i++)
                g<<m1.m[i];

        return g;
    }

    Matrice& operator=(const Matrice& mat)
    {
        for(int i=0; i<lin; i++)
            m[i]=mat.m[i];
        return *this;
    }

    Matrice operator+(const Matrice& mat)
    {
        Matrice matrice;
        matrice.set_dimensiuni(mat.lin, mat.col);
        for(int i=0; i<lin; i++)
        {
            matrice.m[i].set_size(mat.col);
            for(int j=0; j<col; j++)
                matrice.m[i].v[j] = mat.m[i].v[j] + m[i].v[j];
        }
        return matrice;
    }

    Vector& operator[](int i)
    {
        return m[i];
    }

    friend void verificare(Matrice& a, Vector x, Vector y)
    {
        int ok=1;
        for(int i=0; i<a.lin; i++)
        {
            if((a.m[i]*x)!=y[i])
            {
                ok=0;
            }
        }
        if(ok)
            cout<<" Ax = y "<<endl;
        else
            cout<<" Ax!=y "<<endl;

    }


};

int main()
{
    ifstream f("tema.in");
    ofstream g("tema.out");

    Matrice m1, m2, m3;
    Vector x, y;
    int m,n;
    f>>m>>n;
    m1.set_dimensiuni(m,n);
    m2.set_dimensiuni(m,n);
    m3.set_dimensiuni(m,n);
    f>>m1>>m2;
    m3=m2+m1;
    g<<m3;
    x.set_size(n);
    y.set_size(m);
    f>>x>>y;
    verificare(m1, x, y);

    return 0;
}
