#include <iostream>
#include<deque>
using namespace std;
template<typename T>
class Queue{
    private:
        deque<T> a;
    public:
        void add(T v){
            a.push_back(v);
        }
        void remove(){
            a.pop_front();
        }
        void display(){
            for (auto i = a.begin(); i<=a.end();i++)
            {
                cout<<* i<<"\t";
            }
            
        }
};
int main(){
    Queue<int> b;
    b.add(10);
    b.display();
}
