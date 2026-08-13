#include <iostream>

struct A
{
	A():a(0), b(0){}

	virtual int getA() = 0;
	int a;
	int b;
};

struct B : A
{
	B():g(0){}

	int getA() { return g; };
	int g;
};

struct D
{
	D():f(0){}

	int getA() { return f; };
	float f;
};

struct C : A, D
{
	C():d(0){}

	int getA() { return d; };
	double d;
};


int main()
{
	// static_cast при работе с иерархией классов определяет значения указателей так, чтобы обращение к переменным класса через указатель было корректным.

	/* C* pC = new C;
	A* pA = pC;
	D* pD = static_cast<D*> (pC); 
	std::cout << pC << " " << pD << " " << pA << std::endl; */

	// При преобразовании static_cast проверяет, что такая иерархия действительно имеет место быть (т.е. что класс B является наследником класса A),
	// но он не проверяет, что объект, на который указывает указатель pA, действительно является объектом типа B.

	/* C* pC = new C;
	A* pA = static_cast<A*>(pC);
	D* pD = static_cast<D*> (pC);
	B* pB = static_cast<B*> (pA);
	std::cout << &(pB->g) << " " << pD << " " << pA << " " << pC << std::endl;
	pB->g = 100;
	std::cout << pC->a << " " << pC->b << " " << pC->f << std::endl; */

	// Наглядно можно заметить, что преобразование не удалось и каст не был завершен успешно, вернулся nullptr
	C* pC = new C;
	A* pA = pC;
	if(D* pD = dynamic_cast<D*> (pC))
		std::cout << " OK " << std::endl;
	else
		std::cout << " not OK " << std::endl;
	if(B* pB = dynamic_cast<B*> (pA))
		std::cout << " OK " << std::endl;
	else
		std::cout << " not OK " << std::endl;

	return 0;
}

/*

dynamic_cast:

Выполняет проверку типов во время выполнения (runtime).
Используется для безопасного приведения указателей или ссылок на полиморфные типы (те, которые имеют хотя бы одну виртуальную функцию).
Если приведение невозможно, возвращает nullptr для указателей или выбрасывает исключение std::bad_cast для ссылок.

*/

/*

static_cast:

Не выполняет проверок типов во время выполнения.
Используется для приведения между совместимыми типами, таких как базовые и производные классы, но без проверки корректности приведения.


*/