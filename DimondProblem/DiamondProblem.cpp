#include <iostream>

// Проблема ромбовидного наследования.
// Заключается в том, что при обычном наследовании по схеме A->B, A->C, B->D, C->D экземпляр класса D
// получит 2 копии объекта A

// Решается это проблема виртуальным наследованием класса B и C от A. Таким образом мы сообщаем компилятору,
// что если кто-то будет наследоваться от двух этих методов, то нужно создавать только одну копию объекта внутри
// наслденика

class A
{
public:
    A() { std::cout << "A()\n"; }
	~A() { std::cout << "~A()\n\n"; }
};

class B : public A
{
public:
    B(int x) { std::cout << "B()\n"; }
	~B() { std::cout << "~B()\n"; }
};

class C : public A
{
public:
    C(int x) { std::cout << "C()\n"; }
	~C() { std::cout << "~C()\n"; }
};

class D : public B, public C
{
public:
    D(int x) : B(x), C(x) { std::cout << "D()\n"; }
	~D() { std::cout << "~D()\n"; }
};


class VirtualA
{
public:
    VirtualA(int x) { std::cout << "VirtualA(" << x << ")\n"; }
    ~VirtualA() { std::cout << "~VirtualA()\n"; }
};

class VirtualB : virtual public VirtualA
{
public:
    VirtualB(int x) : VirtualA(0) { std::cout << "VirtualB()\n"; } // A не вызывается, но нужен заглушечный вызов
    ~VirtualB() { std::cout << "~VirtualB()\n"; }
};

class VirtualC : virtual public VirtualA
{
public:
    VirtualC(int x) : VirtualA(0) { std::cout << "VirtualC()\n"; } // A не вызывается, но нужен заглушечный вызов
    ~VirtualC() { std::cout << "~VirtualC()\n"; }
};

class VirtualD : public VirtualB, public VirtualC
{
public:
    VirtualD(int x) : VirtualA(x), VirtualB(x), VirtualC(x) { std::cout << "VirtualD()\n"; } // Только тут вызываем A(x)
    ~VirtualD() { std::cout << "~VirtualD()\n"; }
};


int main()
{
	D obj1(6);
	std::cout << std::endl;
	VirtualD obj(5);
	std::cout << std::endl;

	return 0;
}
