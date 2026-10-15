#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

class mycomplex{		//Анатолий
    
    double a, b;
    
    public:
    
    mycomplex() : a(0), b(0) {}
    
    mycomplex(double a, double b) : a(a), b(b) {}
    
    void set_a(double x) {a=x;}
    void set_b(double x) {b=x;}
    
    double mod() {return sqrt(a*a+b*b);}
    
    mycomplex operator+(const mycomplex &ob);
    mycomplex operator*(const mycomplex &ob);
    friend ostream &operator<<(ostream &out, const mycomplex &ob);
	friend istream &operator>>(istream &in, mycomplex &ob);
};

ostream &operator<<(ostream &out, const mycomplex &ob)		//Анатолий
{
	out<<" ("<<ob.a;
    
    if(ob.b<0) out<<ob.b<<"i"<<")";
    else out<<"+"<<ob.b<<"i"<<")";
    
	return out;
}

istream &operator>>(istream &in, mycomplex &ob)			//Анатолий
{
	in >> ob.a;
	in >> ob.b;
	
	return in;
}

mycomplex mycomplex::operator+(const mycomplex &ob)			//Вусал
{
	mycomplex temp;
	
	temp.a = a + ob.a;
	temp.b = b + ob.b;
	
	return temp;
}

mycomplex mycomplex::operator*(const mycomplex &ob)			//Вусал
{
	mycomplex temp;
	
	temp.a = a * ob.a - b * ob.b;
	temp.b = a * ob.b + b * ob.a;
	
	return temp;
}

class matrix{		//Анатолий
    
    int n, k;
    
    mycomplex **z;
    
    public :
    
    matrix (int n, int k) : n(n), k(k)
    {	
		try {z=new mycomplex*[n];}
		
		catch(...) {cout<<"Память не выделена"<<endl; exit(1);}
		
    	for (int j=0; j<n; j++)
    	{
	        try {z[j]=new mycomplex [k];}
	        catch(...) {cout<<"Память не выделена"<<endl; exit(1);}
	     }   	
    }
    
    matrix (const matrix &m_tmp)
    {
        this->n=m_tmp.n;
        this->k=m_tmp.k;
        
        try {this->z=new mycomplex*[n];}
        catch(...) {cout<<"Память не выделена"<<endl; exit(1);}
		
    	for (int j=0; j<n; j++)
    	{
	        try {this->z[j]=new mycomplex [k];}
	        catch(...) {cout<<"Память не выделена"<<endl; exit(1);}
		}
	        
		for (int i=0; i<n; i++)
		{
			for (int j=0; j<k; j++)
				this->z[i][j]=m_tmp.z[i][j];	
		} 
    }
	
    void set(int i, int j, mycomplex a) 
    {
		if(i<n && j<k && i>=0 && j>=0)
		{
			z[i][j] = a;
		}
		
		else cout<<"Выход за границы массива"<<endl;
    }
    
    int get_n() {return n;}
    
    int get_k() {return k;}
    
    mycomplex get(int i, int j) {return z[i][j];}
    
    ~matrix() 
	{
       for(int i=0; i<n; i++) 
            delete [] z[i];
        
       delete [] z;
    }
    
    mycomplex max_mod();
    mycomplex tr();
    matrix operator+(matrix &ob);
    matrix operator*(matrix &ob);
    matrix& operator=(matrix &ob);
    friend ostream &operator<<(ostream &out, const matrix &ob);
	friend istream &operator>>(istream &in, matrix &ob);
 
};

ostream &operator<<(ostream &out, const matrix &ob)		//Анатолий
{
	for (int i=0; i<ob.n; i++)
	{
		for (int j=0; j<ob.k; j++)
			out << ob.z[i][j];
		
		out<<endl;
	}
	
	return out;
}

istream &operator>>(istream &in, matrix &ob)		//Анатолий
{
	for (int i=0; i<ob.n; i++)
		for (int j=0; j<ob.k; j++)
		{
			mycomplex c;
			
		    if (in >> c)
				ob.z[i][j] = c;
			
			else {cout<<"Input error"<<endl; exit(5);}
		}
	
	return in;
}

matrix matrix::operator+(matrix &m)			//Вусал
{
	matrix summ(n, k);
	mycomplex tmp, x, y;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			x = get(i, j); y = m.get(i, j);
			tmp = x + y;
			
			summ.set(i, j, tmp);
		}
	}
	
	return summ;
}

matrix matrix::operator*(matrix &m)			//Вусал
{
	matrix pro(n, m.k);
		
	for (int i = 0; i < pro.n; i++)
	{
		for (int j = 0; j < pro.k; j++)
		{
			mycomplex tmp, x, y;
			
			for (int l = 0; l < k; l++)
			{
				x = get(i, l); y = m.get(l, j);
				tmp = tmp + x * y;
			}
			
			pro.set(i, j, tmp);
		}
	}
	
	return pro;
}

matrix &matrix::operator=(matrix &m)			//Вусал
{
	if (this==&m) return *this;
	
	for(int i=0; i<n; i++) 
            delete [] z[i];
        
    delete [] z;
    
    this->n=m.get_n(); this->k=m.get_k();
	
	try {this->z=new mycomplex*[n];}
        catch(...) {cout<<"Память не выделена"<<endl; exit(1);}
		
    for (int j=0; j<n; j++)
    {
		try {this->z[j]=new mycomplex [k];}
		catch(...) {cout<<"Память не выделена"<<endl; exit(1);}
	}
	
	for (int i=0; i<n; i++)
		{
			for (int j=0; j<k; j++)
				this->z[i][j]=m.get(i, j);
		}
	
	return *this;
	
}

mycomplex matrix::tr()			//Вусал
{
	mycomplex tr, x;
	
	for (int i = 0; i < n; i++)
	{
		x = get(i,i);
		tr = tr + x;
	}
	
	return tr;
}

mycomplex matrix::max_mod()			//Вусал
{
	mycomplex max_m = get(0, 0);
	double x, max = get(0, 0).mod();
	
	for (int i = 0; i < get_n(); i++)
	{
		for (int j = 0; j < get_k(); j++)
		{
			x = get(i, j).mod();
			
			if (max < x)
			{
				max = x;
				max_m = get(i, j);
			}
		}
	}
	
	return max_m;
}

int main()		//Анатолий
{  
    ifstream fin1("input1.txt");
    if(!fin1.is_open()) {cout<<"File 1 not open"<<endl; return 1;}
    
    ifstream fin2("input2.txt");
    if(!fin2.is_open()) {cout<<"File 2 not open"<<endl; return 2;}
    
    int n1, k1, n2, k2;
    
    if(!(fin1>>n1>>k1) || n1 <= 0 || k1 <= 0) {cout << "Input error 1" << endl; return 3;}
    
    matrix m1(n1, k1);
    fin1 >> m1;
    
    if(!(fin2>>n2>>k2) || n2 <= 0 || k2 <= 0) {cout << "Input error 2" << endl; return 4;}
    
    matrix m2(n2, k2);
    fin2 >> m2;
    
    cout<<"m1:"<<endl << m1 <<endl; 
    cout<<"m2:"<<endl << m2 <<endl;
    
    if(m1.get_k()!=m2.get_k() || m1.get_n()!=m2.get_n()) cout<<"Эти матрицы нельзя сложить"<<endl;
		else {matrix sum(m1+m2); cout<<"m1+m2:"<<endl << sum <<endl;}
    
    if(m1.get_k()!=m2.get_n()) cout<<"Эти матрицы нельзя перемножить"<<endl;
		else {matrix pro(m1*m2); cout<<"m1*m2:"<<endl << pro <<endl;}
		
	if(m1.get_k()!=m1.get_n())cout<<"Матрица не квадратная, невозможно вычислить след"<<endl;
		else {cout<<"trace m1:"<<endl << m1.tr() <<endl;}
		
	if(m2.get_k()!=m2.get_n())cout<<"Матрица не квадратная, невозможно вычислить след"<<endl;
		else {cout<<"trace m2:"<<endl << m2.tr() <<endl;}
		
	cout<<"Максимальное по модулю число в первой матрице:"<<endl << m1.max_mod() <<endl;
	
	matrix m3(m2);
	cout<<"m3:"<<endl << m3 <<endl;
	
	m3=m2=m1;
	cout<<endl<<endl; 
	cout<<"m1:"<<endl << m1 <<endl; 
    cout<<"m2:"<<endl << m2 <<endl;
    cout<<"m3:"<<endl << m3 <<endl;
   
    return 0;
}
