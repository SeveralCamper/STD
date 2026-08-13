#include <iostream>
#include <typeinfo>
#include <type_traits>

// Ключевое слово auto направляет компилятору использовать выражение инициализации объявленной переменной или лямбда параметра выражения
// чтобы вывести его тип. Гарантирует отсутсвтвие преобразований и может повыстить эффективность кода

int main()
{
	// 1. [const] [volatile] auto - никогда не будет ссылкой, никакие cv-квалификаторы автоматически не добавляются.
	const int x1 = 10;
	auto y1 = x1; // y будет int (const игнорируется)

	volatile int z1 = 20;
	auto w1 = z1; // w будет int (volatile игнорируется)

	// 2. Если использовать список инициализации ({}) с auto, компилятор выводит тип как std::initializer_list<T> с возможными const или volatile
	auto x2 = {1, 2, 3}; // x будет std::initializer_list<int>
	const auto y2 = {1, 2, 3}; // y будет const std::initializer_list<int>
	volatile auto z2 = {1, 2, 3}; // z будет volatile std::initializer_list<int>

	// 3. Если создать ссылку (&) или указатель (*) с использованием auto на объект, имеющий cv-квалификаторы, то мы получим ссылку или указатель,
	// соответсвенно, со всем cv-квалификаторами исходного объекта.
	const int x3 = 10;
	auto& y3 = x3; // y будет const int& (const сохраняется)
	auto* z3 = &x3; // z будет const int* (const сохраняется)

	volatile int w3 = 20;
	auto& v3 = w3; // v будет volatile int& (volatile сохраняется)
	auto* u3 = &w3; // u будет volatile int* (volatile сохраняется)

	// 4. Если инициализировать rvalue (временным объектом), то без указания const будет ошибка.
	// auto& x4 = 10; // Ошибка: нельзя создать неконстантную ссылку на rvalue
	const auto& y4 = 10; // OK: y будет const int&

	// Указатель нельзя создать никакой с помощью auto на rvalue объект.
	// auto* z4 = 10; // Ошибка
	// const auto* w4 = 10; // Ошибка

	// 5. Универсальные ссылки (perfect forwarding): При использовании auto&&, компилятор способен выводить как lvalue-, так и rvalue-ссылки.
	int x5 = 10;
	auto&& ref5_1 = x5; // ref5_1 будет int& (ссылка на lvalue)
	auto&& ref5_2 = 10; // ref5_2 будет int&& (ссылка на rvalue)

	// 6. decltype(auto) выводит тип на основе выражения, включая ссылки и модификаторы.
	int x6 = 10;
	int& ref6 = x6;
	decltype(auto) y6 = ref6; // y будет int&

    const int* pPtr = nullptr;
    auto smth = pPtr;

    if (std::is_same_v<decltype(smth), const int*>) {
        std::cout << "Smth is of type const int*." << std::endl;
    } else {
        std::cout << "Type is different." << std::endl;
    }

	return 0;
}