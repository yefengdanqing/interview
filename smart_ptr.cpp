// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <regex>
using namespace std;
class Point                                       
{
public:
	Point(int xVal = 0, int yVal = 0) :x(xVal), y(yVal) { }
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int xVal) { x = xVal; }
	void setY(int yVal) { y = yVal; }

private:
	int x, y;

};
class U_Ptr                                  
{
private:
	
	friend class SmartPtr;      
	U_Ptr(Point *ptr) :p(ptr), count(1) { }
	~U_Ptr() { delete p; }
	
	int count;   
	Point *p;                                                      
};
class SmartPtr
{
public:
	SmartPtr(Point *ptr) :rp(new U_Ptr(ptr)) { }    
	
	SmartPtr(const SmartPtr &sp) :rp(sp.rp) { ++rp->count; }
	  
	SmartPtr& operator=(const SmartPtr& rhs) {    
		++rhs.rp->count;    
		if (--rp->count == 0)    
			delete rp;
		rp = rhs.rp;
		return *this;
	}
	
	~SmartPtr() {       
		if (--rp->count == 0)   
			delete rp;
		else 
		cout << "还有" << rp->count << "个指针指向基础对象" << endl;
	}
	
private:
        U_Ptr *rp;  
};


int main()
{
	//定义一个基础对象类指针
	Point *pa = new Point(10, 20);

	//定义三个智能指针类对象，对象都指向基础类对象pa
	//使用花括号控制三个指针指针的生命期，观察计数的变化

	{
		SmartPtr sptr1(pa);//此时计数count=1
		{
			SmartPtr sptr2(sptr1); //调用复制构造函数，此时计数为count=2
			{
				SmartPtr sptr3=sptr1; //调用赋值操作符，此时计数为conut=3
			}
			//此时count=2
		}
		//此时count=1；
	}
	//此时count=0；pa对象被delete掉

	cout << pa->getX ()<< endl;

	system("pause");
	return 0;
}

// GCC reference:
//   https://gcc.gnu.org/

// C++ language references:
//   https://cppreference.com/
//   https://isocpp.org/
//   http://www.open-std.org/jtc1/sc22/wg21/

// Boost libraries references:
//   https://www.boost.org/doc/
