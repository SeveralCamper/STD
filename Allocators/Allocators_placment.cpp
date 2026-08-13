#include <iostream>
#include <new>

class MyClass {
public:
    MyClass() { std::cout << "MyClass constructed\n"; }
    ~MyClass() { std::cout << "MyClass destructed\n"; }
};

int main() {
    // Выделяем буфер памяти
    void* buffer = ::operator new(sizeof(MyClass));

    // Создаём объект в выделенной памяти
    MyClass* obj = new (buffer) MyClass();

	// Вызываем деструктор объекта
    obj->~MyClass();
    ::operator delete(buffer);

	
	// Вариант с массивом классов


    char buffer2[10 * sizeof(MyClass)];

    // Конструируем объекты MyClass в выделенном буфере
    MyClass* ptr = reinterpret_cast<MyClass*>(buffer2);
    for (int i = 0; i < 10; ++i) {
        new (&ptr[i]) MyClass(); // Используем placement new для конструирования объектов
    }

    // Вызываем деструкторы объектов
    for (int i = 0; i < 10; ++i) {
        ptr[i].~MyClass(); // Явный вызов деструктора
    }

    return 0;
}