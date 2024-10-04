#include <new>
#include <iostream>
#include <memory>
#include <vector>

// Общая структура памяти

// Общая структура памяти:

// Текстовый сегмент (.text):

// Содержит исполняемый код программы.
// Этот сегмент обычно имеет только для чтения и выполняется. Изменения в этом сегменте не допускаются.

// Сегмент данных:

// Делится на две части:
// Инициализированный сегмент (.data): Содержит глобальные и статические переменные, которые инициализированы явно. int a = 5;

// Неинициализированный сегмент (.bss): Содержит глобальные и статические переменные, которые не были инициализированы. int b;
// Важно, что .bss не занимает места в исполняемом файле, так как его размер известен, и он инициализируется нулями при загрузке.

// Куча (Heap):

// Используется для динамического выделения памяти во время выполнения программы с помощью операторов new, malloc и т.д.
// Память в куче управляется вручную. Эта память может быть выделена и освобождена в любое время.
// Куча растет вверх, и доступ к ней может быть фрагментирован из-за частого выделения и освобождения памяти.

// Стек (Stack):

// Используется для хранения локальных переменных, параметров функции и адресов возврата.
// Каждый раз, когда вызывается функция, для нее создается новый фрейм стека, который включает в себя локальные переменные и параметры.
// Стек растет вниз, и управление памятью происходит автоматически — когда функция завершается, ее фрейм стека удаляется.


int global_var = 10;				// .data
static int static_var;				// .bss

void func() {
	int local_var = 20;				// стек
	int* dynamic_var = new int(30); // куча
	delete dynamic_var;
}


class Test
{
	public:
		Test() { std::cout << "Construct Test" << std::endl; }
		~Test() { std::cout << "Distruct Test" << std::endl; }

	private:
};


class Test2
{
	public:
		Test2() { std::cout << "Construct Test2" << std::endl; }
		~Test2() { std::cout << "Distruct Test2" << std::endl; }

	private:
};


class Test3 : public Test2
{
	public:
		Test3() { std::cout << "Construct Test3" << std::endl; }
		~Test3() { std::cout << "Distruct Test3" << std::endl; }

	private:
		int member = 0;
};

int main()
{
	// malloc - mem allocation - функция выделения памяти, которая возвращает нам выделенную область памяти, равную размеру * на размер типа, либо NULL
	// если выделения памяти не смогло произойти.
	int* p = (int*) malloc(5 * sizeof(int));
	if (p != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			p[i] = i;
			std::cout << p[i] << std::endl;
		}
	}
	std::cout << std::endl;

	free(p);

	// calloc еще инициализирует выделенную память, также возвращает NULL, в случае неверной аллокации.
	int* p1 = (int*) calloc('0', 10 * sizeof(int));
	if (p1 != NULL)
	{
		for (int i = 0; i < 10; i++)
		{
			std::cout << p1[i] << std::endl;
		}
	}
	std::cout << std::endl;

	// new выделяет память для одного объекта и вызывает его конструктор

	Test* t = new Test();
	delete t;

	Test* testArr;
	testArr = new Test[5];

	delete[] testArr;
	std::cout << std::endl;
	
	void* buffer = operator new(sizeof(Test)); // выделяем память
	Test* obj = new (buffer) Test(); // размещаем объект в выделенной памяти

	// Когда объект больше не нужен, нужно явно вызвать деструктор, так как при вызове operator delete конструктор вызван не будет
	obj->~Test();
	operator delete(buffer);

	// Если new не может выделить память, он выбрасывает исключение:
	try
	{
		int* timeArr = new int[50]; 
	}
	catch(const std::exception& e) // если память не может быть выделена или будет выделена некорректно - std::bad_alloc
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;

	// По идее, если количетсво выделяемой памяти для классов равно, ним ничего не мешает выделить туда другой класс.
	// Поэтому, в случае, если они будут не равны
	
	void* buffer2 = operator new(sizeof(Test2)); // выделяем память
	Test* obj2 = new (buffer2) Test(); // размещаем другой объект того же размера	

	obj2->~Test();
	operator delete(buffer2);
	std::cout << std::endl;

	void* buffer3 = operator new(sizeof(Test2)); // выделяем память
	Test3* obj3 = new (buffer3) Test3(); // размещаем другой объект большего размера - UB	

	obj3->~Test3();
	operator delete(buffer3);

	return 0;
}