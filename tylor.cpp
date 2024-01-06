#include<iostream>
#include<sstream>
#include<math.h>
using namespace std;
class Tailor
{
    private:
        int x;
    public:
        void setDegr(int d){x = d;}
        int getDegr(){return x;}
        double radians(int x){
            return(x*3.14159)/180;
        }
        int fact(int x){
            if(x==0){
                return 1;
            }
            else{
                return x*fact(x-1);
            }
        }
        float sinx(float x){
            double xrad = radians(x);
            float sinc = 0.0;
            int n = 0; 
            while(n < 10)
            {
                int dn = 2*n+1;
                sinc +=pow(-1,n)*pow(xrad,dn)/fact(dn);
                n++;
            }
            return sinc;
        }
        float cosx(float x){
            double xrad = radians(x);
            float csx =0;
            for(int n = 0; n < 10; n++){
                csx+=pow(-1,n)*pow(xrad,(2*n))/fact(2*n);
            }
            return csx;
        }
        void display(int x){
        cout<<"Angle in degree: "<< x <<endl;
        cout<<"Angle in radians: "<<radians(x )<<endl;
        cout<< "Sin("<<x<<") = "<<sinx(x)<<endl;
        cout<< "Cos("<<x<<") = "<<cosx(x)<<endl;
    }
};

int main(){
    Tailor b;
    b.display(60);
}

