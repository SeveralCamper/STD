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



class GreatChild : public Child
{
	public:
		GreatChild() { std::cout << "Construct GreatChild" << std::endl; }
		~GreatChild() { std::cout << "Destruct GreatChild" << std::endl; }
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


class DynamicGreatChild : public DynamicChild1, public DynamicChild2
{
	public:
		DynamicGreatChild() { std::cout << "Construct DynamicGreatChild" << std::endl; }
		~DynamicGreatChild() { std::cout << "Destruct DynamicGreatChild" << std::endl; }
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


class DynamicGreatChildVirtual : public DynamicChildVirtual1, public DynamicChildVirtual2
{
	public:
		DynamicGreatChildVirtual() { std::cout << "Construct DynamicGreatChildVirtual" << std::endl; }
		~DynamicGreatChildVirtual() { std::cout << "Destruct DynamicGreatChildVirtual" << std::endl; }

		void Bang() override { std::cout << "DynamicGreatChildVirtual BANG" << std::endl; }
};


int main()
{
	// Static_cast - используется для приведения указателей и ссылок от базового класса к производному и наоборот. Downcast - от базового к производному
	// не безопасен и будет приводить к UB


	std::cout << "Upcast Child:" << std::endl;
	Child child;
	Base* base = static_cast<Base*>(&child);
	std::cout << std::endl;

	std::cout << "Downcast Base:" << std::endl;
	Base base2;
	Child* child2 = static_cast<Child*>(&base2); // некорректное преобраование, но компилятор не выдаст ошибку. Объект base2 не является объектом класса, Child
	std::cout << std::endl;						 // поэтому конструктор класса Child для него не вызвался, таким образом, мы получим UB при взаимодействии с этим экземпляром

	std::cout << "Upcast greatChild:" << std::endl;
	GreatChild greatChild;
	Base* base3 = static_cast<Base*>(&greatChild);
	std::cout << std::endl;

	// Может использоваться для привдения совместимых скалярных типов:

	int i = 42;
	float f = static_cast<float>(i);

	// Можно использовать для приведения указателей между типами, которые не находятся в иерархии классов:

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

	enum Color { Red = 97, Green, Blue };
	int colorValue = static_cast<int>(Color::Red);
	std::cout << colorValue << std::endl << std::endl;

	// Иможно использовать для преобразование пользовательских типов:

	ClassWithOperator obj;
	int value = static_cast<int>(obj);
	std::cout << value << std::endl << std::endl << std::endl;

	// Нельзя привести классы друг к дуруг, если у них нет общего предка:

	// Child child3;
	// ClassWithOperator* obj2 = static_cast<Child*>(&child3); // не скомпилируется


	// Динамическое приведение типов. dynamic_cast<>


	// Для начала разберем кейсы преобразований с невиртуальными классами.

	// Если cast не удается, dynamic_cast возвращает nullptr для указателей и вызывает исключение std::bad_cast для ссылок. Не может использоваться для преобразования
	// несвязанных типов.

	// DynamicBase* dyBase = new DynamicChild1();
	// DynamicChild1* dyChild = dynamic_cast<DynamicChild1*>(dyBase); // компилятор не дает нам произвести преобразование, т.к. может работать
	// if (dyChild)												      // только с иерархией классов, в которой есть виртуальные базовые классы.
	// {
	// 	  std::cout << "Sucsessfeul dynamic downcast!" << std::endl;
	// }

	DynamicChild1* dyBase = new DynamicChild1();
	DynamicBase* dyChild = dynamic_cast<DynamicBase*>(dyBase); // это корректное преобразование, хоть базовый класс и не виртуальный, вызоветься два деструктора
	if (dyChild)											   // из-за того, что мы выделили память под объект DynamicChild1 в указатель на DynamicChild1.
	{
		std::cout << "Sucsessfeul dynamic upcast!" << std::endl;
	}
	delete dyBase;
	std::cout << std::endl;

	// Небольшое отсупление о ромбовидном наследовании
	DynamicBase* dyBase2 = new DynamicChild1(); // а вот тут уже вызоветься только деструктор базового класса, т.к. DynamicBase не имеет виртуального деструктора.
	delete dyBase2;
	std::cout << std::endl << std::endl;

	DynamicGreatChild* dyGreatChild = new DynamicGreatChild(); // в данном примере из-за проблемы ромбовидного наследования вызовиться сначала конструктор
	delete dyGreatChild; // базовго класса 1 раз, затем конструктор DynamicChild1, базовый 2-о1 раз, DynamicChild2 и только потом конструктор DynamicGreatChild
	std::cout << std::endl; // с деструкторами та же история в обратном порядке. Решается эта проблема виртуальным базовым классом.

	
	// Динамическое приведение типов. dynamic_cast<> virtual

	DynamicGreatChildVirtual dyGreatChild2;
	std::cout << std::endl; // В отладке будет выдино верный порядок вызова конструкторов для DynamicGreatChildVirtual

	DynamicChildVirtual1 dyChildV1;
	DynamicChildVirtual2  dyChildV2;

	DynamicBaseVirtual* dyBaseV;
	DynamicChildVirtual1* pDyChildV1 = &dyChildV1;
	DynamicChildVirtual2*  pDyChildV2 = &dyChildV2;
	std::cout << std::endl;

	// Пример 1: Приведение к базовому классу (вверх по иерархии)
	DynamicBaseVirtual* basePtr = &dyGreatChild2;
	DynamicChildVirtual1* child1Ptr = dynamic_cast<DynamicChildVirtual1*>(basePtr);
	if (child1Ptr)
	{
		std::cout << "Successfully casted to DynamicChildVirtual1" << std::endl;
	}
	else
	{
		std::cout << "Failed to cast to DynamicChildVirtual1" << std::endl;
	}
	child1Ptr->Bang();
	std::cout << std::endl;

	// Пример 2: Приведение к другому производному классу (вверх по иерархии)
	DynamicChildVirtual2* child2Ptr = dynamic_cast<DynamicChildVirtual2*>(basePtr);
	if (child2Ptr)
	{
		std::cout << "Successfully casted to DynamicChildVirtual2" << std::endl;
	}
	else
	{
		std::cout << "Failed to cast to DynamicChildVirtual2" << std::endl;
	}
	child2Ptr->Bang();
	std::cout << std::endl;

	// Пример 3: Приведение к производному классу (вниз по иерархии)
	DynamicGreatChildVirtual* greatChildPtr = dynamic_cast<DynamicGreatChildVirtual*>(basePtr);
	if (greatChildPtr)
	{
		std::cout << "Successfully casted to DynamicGreatChildVirtual" << std::endl;
	}
	else
	{
		std::cout << "Failed to cast to DynamicGreatChildVirtual" << std::endl;
	}
	greatChildPtr->Bang();
	std::cout << std::endl;

	// Пример 4: Попытка неверного приведения
	// DynamicChildVirtual1* wrongChildPtr = dynamic_cast<DynamicChildVirtual2*>(basePtr); // не поддерживает cross-cast
	// if (wrongChildPtr)
	// {
	//    std::cout << "Successfully casted to DynamicChildVirtual2" << std::endl;
	// }
	// else
	// {
	//  	std::cout << "Failed to cast to DynamicChildVirtual2" << std::endl; // Ожидаемое поведение
	// }

	// Но есть проблема, при всех вызовах Bang(), мы получаем один и тот же результат из класса, которым мы поределилил greatChildPtr

	/* dyBaseV = dynamic_cast<DynamicGreatChildVirtual*>(pDyChildV1);
	dyBaseV->Bang();
	std::cout << std::endl;

	dyBaseV = dynamic_cast<DynamicGreatChildVirtual*>(pDyChildV2);
	dyBaseV->Bang();
	std::cout << std::endl;

	dyBaseV = dynamic_cast<DynamicGreatChildVirtual*>(basePtr);
	dyBaseV->Bang();
	std::cout << std::endl; */

	// Все зависит от того, указатель на какой объект мы кастуем. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ТУТ SEGFAULT - разобраться


	// Reinterpred_cast<> - дает прямую инструкцию компилятору приводить одну к другому вообще без проверок

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
	std::cout << std::endl << std::endl;

	// А reinterpret_cast поддерживает cross-cast

    DynamicBaseVirtual* basePtrRC2 = new DynamicChildVirtual1();

    DynamicChildVirtual2* derived2Ptr = reinterpret_cast<DynamicChildVirtual2*>(basePtrRC2);
	if (derived2Ptr)
	{
		std::cout << "Successfully casted to DynamicChildVirtual2" << std::endl;
	}
	else
	{
	 	std::cout << "Failed to cast to DynamicChildVirtual2" << std::endl;
	}

	return 0;
}