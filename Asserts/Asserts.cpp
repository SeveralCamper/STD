#include <type_traits>
#include <assert.h>
#include <iostream>

// В C++ std::assert и std::static_assert — это два механизма для проверки каких либо условий в коде в RunTime и на этапе компиляции, соотвественно

// assert — это макрос, который используется для проверки условий во время выполнения программы.
// Если условие не выполняется, программа вызывает abort().

// static_assert — это конструкция, доступная в C++11 и более поздних версиях.
// Она используется для выполнения проверок на этапе компиляции. Если условие не выполняется, компилятор выдает ошибку с соответствующим сообщением.
// В C++17 можно выдавать static_assert ошибку и без сообщения.

class Process
{
	public:
	Process() { std::cout << "Here i'am" << std::endl; }
	~Process() { std::cout << "I'am die :c" << std::endl; }
};


class ProcessV
{
	public:
	ProcessV() { std::cout << "Here i'am" << std::endl; }
	~ProcessV() = delete;
};


template<typename T>
void process(T value) {
	static_assert(std::is_integral<T>::value, "T must be an integral type");
	// Функция выполняется только для целочисленных типов, таким образом можно сделать множество проверок доя шаблонных классов.
	std::cout << "Processing integer: " << value << std::endl;
}


template<typename T>
void processClass(T value) {
	static_assert(std::is_default_constructible<T>::value, "T must be an default_constractable type");
	static_assert(std::is_destructible<T>::value, "T must be an default_destructable type");
	std::cout << "Processing Class: " << value << std::endl;
}


template<typename T>
void processClassV(T value) {
	static_assert(std::is_default_constructible_v<T>);
	static_assert(std::is_nothrow_destructible<T>::value, "T must be an is_nothrow_destructible type");
	std::cout << "Processing ClassV: " << value << std::endl;
}


void divide(int a, int b) {
	assert(b != 0);
	std::cout << "Result: " << (a / b) << std::endl;
}


int main() {
	process(42);
	// process(10.01); // Ошибка компиляции
	divide(10, 2);
	// divide(10, 0);  // Приведёт к завершению программы
	processClass(new Process);
	processClassV(new ProcessV);
	return 0;
}
