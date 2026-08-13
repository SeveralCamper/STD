#include <iostream>

// static_cast

class Base 
{
	public:
		Base() { std::cout << "Construct Base" << std::endl; }
		~Base() { std::cout << "Destruct Base" << std::endl; }
};


class Child : public Base
{
	public:
		Child() { std::cout << "Construct Child" << std::endl; }
		~Child() { std::cout << "Destruct Child" << std::endl; }
};


class Child2 : public Base
{
	public:
		Child2() { std::cout << "Construct Child2" << std::endl; }
		~Child2() { std::cout << "Destruct Child2" << std::endl; }
};



class GrandChild : public Child
{
	public:
		GrandChild() { std::cout << "Construct GrandChild" << std::endl; }
		~GrandChild() { std::cout << "Destruct GrandChild" << std::endl; }
};


class ClassWithOperator {
public:
	operator int() const { return 42; }
};


// dynamic_cast


class DynamicBase 
{
	public:
		DynamicBase() { std::cout << "Construct DynamicBase" << std::endl; }
		~DynamicBase() { std::cout << "Destruct DynamicBase" << std::endl; }
};


class DynamicChild1 : public DynamicBase
{
	public:
		DynamicChild1() { std::cout << "Construct DynamicChild1" << std::endl; }
		~DynamicChild1() { std::cout << "Destruct DynamicChild1" << std::endl; }
};



class DynamicChild2 : public DynamicBase
{
	public:
		DynamicChild2() { std::cout << "Construct DynamicChild2" << std::endl; }
		~DynamicChild2() { std::cout << "Destruct DynamicChild2" << std::endl; }
};


class DynamicGrandChild : public DynamicChild1, public DynamicChild2
{
	public:
		DynamicGrandChild() { std::cout << "Construct DynamicGrandChild" << std::endl; }
		~DynamicGrandChild() { std::cout << "Destruct DynamicGrandChild" << std::endl; }
};


// dynamic_cast virtual


class DynamicBaseVirtual 
{
	public:
		DynamicBaseVirtual() { std::cout << "Construct DynamicBaseVirtual" << std::endl; }
		virtual ~DynamicBaseVirtual() { std::cout << "Destruct DynamicBaseVirtual" << std::endl; }

		virtual void Bang() = 0;
};


class DynamicChildVirtual1 : public virtual DynamicBaseVirtual
{
	public:
		DynamicChildVirtual1() { std::cout << "Construct DynamicChildVirtual1" << std::endl; }
		~DynamicChildVirtual1() { std::cout << "Destruct DynamicChildVirtual1" << std::endl; }
	
		void Bang() override { std::cout << "DynamicChildVirtual1 BANG" << std::endl; }
};



class DynamicChildVirtual2 : public virtual DynamicBaseVirtual
{
	public:
		DynamicChildVirtual2() { std::cout << "Construct DynamicChildVirtual2" << std::endl; }
		~DynamicChildVirtual2() { std::cout << "Destruct DynamicChildVirtual2" << std::endl; }

		void Bang() override { std::cout << "DynamicChildVirtual2 BANG" << std::endl; }
};


class DynamicGrandChildVirtual : public DynamicChildVirtual1, public DynamicChildVirtual2
{
	public:
		DynamicGrandChildVirtual() { std::cout << "Construct DynamicGrandChildVirtual" << std::endl; }
		~DynamicGrandChildVirtual() { std::cout << "Destruct DynamicGrandChildVirtual" << std::endl; }

		void Bang() override { std::cout << "DynamicGrandChildVirtual BANG" << std::endl; }
};


int main()
{
	// Static_cast - используется для приведения указателей и ссылок от базового класса к производному и наоборот, для преобразования одного ститического
	// типа к другому, Для преобразования перечислений к статическим типам. Нельзя кастовать между собой типы не в одной иерархии наследования.
	// Downcast - от базового к производному не безопасен и будет приводить к UB. Static_cast<type>(obj) возвращает значение типа type.

	// Приведение статических типов, ссылок и указателей на статические типы.

	// Приведение одинаковых типов

	int sa = 5;
	int sb = 0;

	std::cout << "Static cast with eq types:" << std::endl;
	std::cout << "After cast a: " << sa << " b: " << sb << std::endl;

	sb = static_cast<int>(sa);

	std::cout << "Before cast a: " << sa << " b: " << sb << std::endl << std::endl;

	// Указатели

	int* pSa = &sa;
	sb = 10;
	int* pSb = &sb;

	std::cout << "Static cast with eq ptr types:" << std::endl;
	std::cout << "After cast a: " << *pSa << " b: " << *pSb << std::endl;

	pSa = static_cast<int*>(pSb);

	std::cout << "Before cast a: " << *pSa << " b: " << *pSb << std::endl << std::endl;

	// Ссылки

	int& lsa = sa;
	int& lsb = sb;

	std::cout << "Static cast with eq link types:" << std::endl;
	std::cout << "After cast a: " << lsa << " b: " << lsb << std::endl;

	lsb = static_cast<int&>(lsa);

	std::cout << "Before cast a: " << lsa << " b: " << lsb << std::endl << std::endl;

	// Сссылка к указателю / указатель к ссылке.

	// pSa = static_cast<int*>(lsa); // ошибка компиляции - неверной приведение типов.
	// lsa = static_cast<int&>(pSa); // ошибка компиляции - неверной приведение типов.


	// Приведение разных типов


	int sc = 12;
	char sd = 'c';

	std::cout << "Static cast with different types:" << std::endl;
	std::cout << "After cast c: " << sc << " d: " << sd << std::endl;

	sc = static_cast<int>(sd);

	std::cout << "Before cast c: " << sc << " d: " << sd << std::endl << std::endl;


	std::cout << "Static cast with different types:" << std::endl;
	std::cout << "After cast c: " << sc << " d: " << sd << std::endl;

	sd = static_cast<char>(sc);

	std::cout << "Before cast c: " << sc << " d: " << sd << std::endl << std::endl;

	// Указатели

	int* pSc = &sc;
	sc = 10;
	char* pSd = &sd;

	std::cout << "Static cast with different ptr types is invalid:" << std::endl << std::endl;

	// pSc = static_cast<int*>(pSd); // ошибка компиляции - неверной приведение типов.
	// pSd = static_cast<char*>(pSc); // ошибка компиляции - неверной приведение типов.

	// Ссылки

	int& lsc = sc;
	char& lsd = sd;

	std::cout << "Static cast with different link types is invalid:" << std::endl << std::endl;

	// lsc = static_cast<int&>(lsd); // ошибка компиляции - неверной приведение типов.
	// lsd = static_cast<char&>(lsc); // ошибка компиляции - неверной приведение типов.


	// Преобразования в рамках иерархий наследования


	// Преобразования в рамках одной иерархии

	// Upcast - cast класса наследника к родителю.
	// Downcast - cast класса родителя к классу наслденику.
	// Crosscast - cast от класса к классу на одном уровне иерархии наследования.

	Base base = Base();
	Child child = Child();
	Child2 child2 = Child2();

	//  Upcast с экземплярами.

	std::cout << "Casts with examples:" << std::endl;
	std::cout << "Upcast form Child to Base with = to Base: " << std::endl;
	Base baseB = static_cast<Base>(child);
	std::cout << std::endl;

	std::cout << "Upcast form Child to Base with = to Child is invalid: " << std::endl;
	// Child childB = static_cast<Base>(child); // не существует подходящего пользовательского преобразования из Base в Child
	std::cout << std::endl;

	//  Downcast с экземплярами.

	std::cout << "Downcast form Base to Child with = to Base is invalid: " << std::endl;
	// Base baseB = static_cast<Child>(base); // не существует подходящего пользовательского преобразования из Base в Child
	std::cout << std::endl;

	std::cout << "Downcast form Base to Child with = to Child is invalid: " << std::endl;
	// Child childB = static_cast<Child>(base); // не существует подходящего пользовательского преобразования из Base в Child
	std::cout << std::endl;

	// Crosscast с экземпляром

	std::cout << "All crosscast with examples is invalid: " << std::endl;
	// base = static_cast<Child2>(child); // не существует подходящего пользовательского преобразования из Child в Child2
	// base = static_cast<Child>(child2); // не существует подходящего пользовательского преобразования из Child в Child2
	std::cout << std::endl;

	Base* pBase = &base;
	Child* pChild = &child;
	Child2* pChild2 = &child2;

	// Upcast указаталей

	std::cout << "Casts with pointers:" << std::endl;
	std::cout << "Upcast form Child* to Base* with = to Base*: " << std::endl;
	Base* pBaseB = static_cast<Base*>(pChild);
	std::cout << std::endl;

	std::cout << "Upcast form Child* to Base* with = to Child* is invalid: " << std::endl;
	// Child* childB = static_cast<Base*>(pChild); // значение типа Base* нельзя использовать для инициализации сущности типа Child*
	std::cout << std::endl;

	//  Downcast указателей.

	std::cout << "Downcast form Base* to Child* with = to Base*: " << std::endl;
	pBaseB = static_cast<Child*>(pBase); // приведет к неопределенному поведению, т.к. в указателе под pBase не будет выделена память для Child
	std::cout << std::endl;

	std::cout << "Downcast form Base to Child with = to Child: " << std::endl;
	Child* pChildB = static_cast<Child*>(pBase); // приведет к неопределенному поведению, т.к. в указателе под pBase не будет выделена память для Child
	std::cout << std::endl;

	// Crosscast с экземпляром

	std::cout << "All crosscast with ptr is invalid: " << std::endl;
	// pBaseB = static_cast<Child2*>(pChild); // ошибка компиляции - неверной приведение типов.
	// pBaseB = static_cast<Child*>(pChild2); // ошибка компиляции - неверной приведение типов.
	std::cout << std::endl;

	Base& lBase = base;
	Child& lChild = child;
	Child2& lChild2 = child2;

	// Upcast ссылок

	std::cout << "Casts with references:" << std::endl;
	std::cout << "Upcast form Child& to Base& with = to Base&: " << std::endl;
	lBase = static_cast<Base&>(lChild);
	std::cout << std::endl;

	//  Downcast указателей.

	std::cout << "Downcast form Base& to Child& with = to Base&: " << std::endl;
	lBase = static_cast<Child&>(lBase);
	std::cout << std::endl;

	// Crosscast с экземпляром

	std::cout << "All crosscast with references is invalid: " << std::endl;
	// lBase = static_cast<Child2&>(lChild); // ошибка компиляции - неверной приведение типов.
	// lBase = static_cast<Child&>(lChild2); // ошибка компиляции - неверной приведение типов.

	// Можно использовать для приведения указателей между типами, которые не находятся в иерархии классов:

	std::cout << "Can be used to cast pointers between types that are not in the class hierarchy" << std::endl;
	void* ptr = nullptr;
	int* intPtr = static_cast<int*>(ptr);

	float* floatPtr = static_cast<float*>(calloc('0', 10 * sizeof(float)));
	for (int i = 0; i < 10; i++)
	{
		std::cout << floatPtr[i] << " ";
	}
	std::cout << std::endl;
	free(floatPtr);

	// Можно преобразовывать перечисления:

	std::cout << "Enumerations can be converted" << std::endl;

	enum Color { Red = 97, Green, Blue };
	int colorValue = static_cast<int>(Color::Red);
	std::cout << colorValue << std::endl << std::endl;

	// Можно использовать для преобразование пользовательских типов:

	std::cout << "Can be used to convert custom types" << std::endl;

	ClassWithOperator obj;
	int value = static_cast<int>(obj);
	std::cout << value << std::endl << std::endl << std::endl;

	// Нельзя привести классы друг к дуруг, если у них нет общего предка:

	// Child child3;
	// ClassWithOperator* obj2 = static_cast<Child*>(&child3); // не скомпилируется


	// Динамическое приведение типов - dynamic_cast<type>(obj). Безопасное преобразование указателей и ссылок на классы вверх, вниз и вбок по иерархии наследования.
	// dynaic_cast работает в сочетании с двумя механизмами С++: RTTI(RunimeTypeInfo) и vtable (virtual table).
	// RTTI - это механизм, который предоставляет информацию о типах объектов во время выполнения. В C++ RTTI позволяет программам идентифицировать тип объекта
	// (например, базового или производного класса) в момент выполнения. Чтобы использовать RTTI класс должен иметь хотя бы одну виртуальную функцию.
	// Также класс будет использовать RTTI с том случае, если его родителем является интерфейс с чисто виртуальными функциями, которые наследник переопределит.

	// vtable - это структура данных, которая хранит указатели на виртуальные функции для конкретного класса. Каждый объект класса, имеющего виртуальные функции,
	// имеет указатель на свою vtable. При применении dynamic_cast, компилятор проверяет, есть ли у объекта соответствующий тип, используя информацию,
	// содержащуюся в vtable. Если проверка проходит успешно, dynamic_cast возвращает указатель на соответствующий тип; если нет, возвращается nullptr
	// (для указателей) или генерируется исключение std::bad_cast (для ссылок).

	// Использование dynamic_cast с указателями на неполиморфные классы и указателями на ститические типамы.

	// Преобразование указателей на статические типы

	int e = 5;
	int g = 1;

	int* pE = &e;
	int* pG = &g;

	int& rE = e;
	int& rG = g;

	std::cout << "Dynamic_cast of staitc types is invalid" << std::endl;
	// pE = dynamic_cast<int*>(pG); // Не может быть использован для каста между указателями статических типов.
	// rE = dynamic_cast<int*>(rG); // Не может быть использован для каста между ссылками статических типов.
	std::cout << std::endl;

	// Преобразваоние указателей на неполиморфные типы в одной иерархии

	DynamicBase* dynamBase = new DynamicBase();
	DynamicChild1* dynamChild = new DynamicChild1();
	DynamicChild2* dynamChild2 = new DynamicChild2();
	DynamicGrandChild* dynamGrandChild = new DynamicGrandChild();

	std::cout << "Dynamic_cast of unpolimorfic ptr types is invalid" << std::endl;
	// В строке DynamicBase* dynamBase1 = dynamic_cast<DynamicBase*>(dynamChild); // компилятор не сможет гарантировать корректность приведения.
	// Это может привести к неопределенному поведению (UB), но код скомилируется
	DynamicBase* dynamBase1 = dynamic_cast<DynamicBase*>(dynamChild);
	// dynamChild = dynamic_cast<DynamicChild1*>(dynamBase); // dynamic_cast должен преобразовывать тип полиморфного класса в такой конструкции, а мы работаем с неполиморфным типом
	std::cout << std::endl;

	// Преобразваоние ссылок на неполиморфные типы в одной иерархии

    DynamicBase dynamBase2;
    DynamicChild1 dynamChild12;
    DynamicChild2 dynamChild22;
    DynamicGrandChild dynamGrandChild2;

	std::cout << "Dynamic_cast of unpolimorfic ref types is invalid" << std::endl;
    DynamicBase& redDynamBase2 = dynamic_cast<DynamicBase&>(dynamChild12); // из-за неполиморфности классов приведет к UB
    //  DynamicChild1& refChild1 = dynamic_cast<DynamicChild1&>(redDynamBase2); // Ошибка, если refBase не указывает на DynamicChild1
	std::cout << std::endl;

	// Преобразование указателей на полиморфные типы в одной иерархии

	DynamicBaseVirtual* dynamBaseV;
	DynamicBaseVirtual* dynamBaseV2;
	DynamicChildVirtual1* dynamChildV = new DynamicChildVirtual1();
	DynamicChildVirtual2* dynamChildV2 = new DynamicChildVirtual2();
	DynamicGrandChildVirtual* dynamGrandChildV = new DynamicGrandChildVirtual();	

	std::cout << "Dynamic_cast of polymorphic ptr types:" << std::endl;

	// Приведение к базовому типу
	dynamBaseV = dynamic_cast<DynamicBaseVirtual*>(dynamChildV);
	if (dynamBaseV) {
		std::cout << "Successfully casted to DynamicBaseVirtual" << std::endl;
	}

	// Приведение к дочернему типу
	DynamicChildVirtual1* child1Ptr = dynamic_cast<DynamicChildVirtual1*>(dynamBaseV);
	if (child1Ptr) {
		std::cout << "Successfully casted to DynamicChildVirtual1" << std::endl;
	}

	dynamBaseV2 = dynamic_cast<DynamicBaseVirtual*>(child1Ptr);
	if (dynamBaseV2) {
		std::cout << "Successfully casted to DynamicBaseVirtual from child" << std::endl;
	}

	// Приведение к неправильному типу
	DynamicChildVirtual2* child2Ptr = dynamic_cast<DynamicChildVirtual2*>(dynamBaseV2);
	if (child2Ptr) {
		std::cout << "Successfully casted to DynamicChildVirtual2" << std::endl;
	}
	else
	{
		std::cout << "Incorrect cast to DynamicChildVirtual2" << std::endl;
	}

	// Приведение к родительскому типу
	DynamicChildVirtual1* grandChildPtr = dynamic_cast<DynamicChildVirtual1*>(dynamGrandChildV);

	// попробуем сделать cross-каст:

	DynamicChildVirtual2* grandChild2Ptr = dynamic_cast<DynamicChildVirtual2*>(grandChildPtr);
	if (grandChild2Ptr)
	{
		std::cout << "Cross-cast by dynamic_cast" << std::endl;
	}

	// Очистка памяти
	delete dynamChildV;
	delete dynamChildV2;
	delete dynamGrandChildV;

	// Reinterpred_cast<> - дает прямую инструкцию компилятору приводить одну к другому вообще без проверок. Используется только для указателей и ссылок
	// Reinterpred_cast<> возвращает nullptr только в том случае, если кастует к nullptr.
	// Можно использовать когда из произвольного указателя на указатель типа char*. То есть reinterpret_cast позволяет представить произвольный объект в виде
	// последовательности байт (так как стандартом гарантируется однобайтовая длина char-а).

	// Приведение указателя на A к указателю на B
	struct A
	{
		int x;
	};

	struct B
	{
		double y;
	};

	// Приведение к void* и обратно к int*
	A a;
	B* b = reinterpret_cast<B*>(&a);

	int x = 42;
	void* ptrRC = reinterpret_cast<void*>(&x);
	int* intPtr2 = reinterpret_cast<int*>(ptrRC);

	 // Работа с байтами
	long long value2 = 0x1122334455667788;
	char* bytePtrRC = reinterpret_cast<char*>(&value2);
	for (size_t i = 0; i < sizeof(value2); ++i) {
		std::cout << std::hex << static_cast<int>(bytePtrRC[i]) << " ";
	}
	std::cout << std::dec << std::endl << std::endl;

	// reinterpret_cast поддерживает cross-cast, но в результате будет UB

    DynamicBaseVirtual* basePtrRC2 = new DynamicChildVirtual1();

    DynamicChildVirtual2* derived2Ptr = reinterpret_cast<DynamicChildVirtual2*>(basePtrRC2);
	if (derived2Ptr)
	{
		std::cout << "Successfully reinterpret_cast to DynamicChildVirtual2" << std::endl;
	}
	else
	{
	 	std::cout << "Failed to cast to DynamicChildVirtual2" << std::endl;
	}

	basePtrRC2 = nullptr;
	derived2Ptr = reinterpret_cast<DynamicChildVirtual2*>(basePtrRC2);
	if (!derived2Ptr)
	{
		std::cout << "Nullptr reinterpret_cast!" << std::endl;
	}

	// const_cast<> - удаляет квалификаторы const и volotile

    const int valueConst = 10;
    const int* constPtr = &valueConst;

	std::cout << "Value: " << valueConst << std::endl;
    int* modifiablePtr = const_cast<int*>(constPtr);
    *modifiablePtr = 20;

    std::cout << "Value: " << valueConst << std::endl; // может вызвать сбои в программе, т.к. константные данные могут распологаться в сегменте постоянных данных
													   // также компилятор может хранить эту переменную в каком-нибудь регистре думая, что она 10 и поменять ее также будет невозможно

	// С-stle cast - не использовать :) В зависимости от типа преобразования использует либо static_cast, либо reinterpret_cast, либо const_cast

	return 0;
}