#include <tuple>
#include <iostream>

// std::tuple - это контейнер, который позволяет хранить набор элементов разных типов данных - кортеж. Типы элементов std::tuple известны во время компиляции, что
// дает возможность использовать шаблоны для std::tuple. Прямой возможности итерирования по контейнеру нет, но можно использовать развертывание кортежа std::apply
// таким образом передав в std::aply параметры кортежа, !можно взаимодействовать с каждым из них как с отдельной переменной!.
// Доступ до элементов осуществляется с помощью  std::get<index>(tuple) - возвращает неизменяемый элемент с индексом index из кортежа. Также распаковать данные из
// кортежа можно с помощью std::tie(...), передав туда все переменные, в которые надо будет распокавать кортеж.

template<typename... Args>
class TupleHolder
{
public:
    TupleHolder(const Args&... args) : data(std::make_tuple(args...)) {}

    void Print() const
    {
        std::apply([](const auto&... args)
        {
            ((std::cout << args << ' '), ...); // fold-выражения - позволяет применять бинарную операцию к параметрам, переданным в качестве аргумента лямбды или др. функции
        }, data);
    }

    template<std::size_t Index>
    auto GetElement() const
    {
        return std::get<Index>(data);
    }

	std::tuple<Args...> GetData()
	{
		return data;
	}

private:
    std::tuple<Args...> data;
};

int main() {
    int a;
    double b;
    std::string c;
    TupleHolder<int, double, const char*> Holder(10, 20.5, "Hello");
    Holder.Print();

	std::cout << std::endl;
	std::cout << "GetElemnt: " << std::endl;
    auto myTuple = std::make_tuple(10, 10.01, "Hello");
	std::tie(a, b, c) = myTuple;
    std::cout << Holder.GetElement<0>() << std::endl;
	std::cout << Holder.GetElement<1>() << std::endl;
	std::cout << Holder.GetElement<2>() << std::endl;
    std::cout << a << ' ' << b << ' ' << c << std::endl;
	a = 15;
	b = 20.02;
	c = "Olleh";

	std::cout << std::get<0>(myTuple) << " ";
	std::cout << std::get<1>(myTuple) << " ";
	std::cout << std::get<2>(myTuple) << std::endl; // итерироваться с использование std::get<index>() нельзя, т.к. std::get необходим сатический индекс, чтобы знать его на этапе компиляции

	std::cout << a << " " << b << " " << c << std::endl;

	// Кортежи можно сравнивать:

	std::cout << "Tuple comparance: " << std::endl;
	std::cout << (Holder.GetData() < myTuple) << std::endl;
	std::cout << (Holder.GetData() > myTuple) << std::endl;

	auto myTuple2 = std::make_tuple(10, 10.01, "Hello");

	std::cout << "Tuple comparance ==: " << std::endl;
	std::cout << (myTuple == myTuple2) << std::endl;

	// С помощью метода std::tuple_element и decltype() можно определеить тип элемента в кортеже 

	using ElementType0 = std::tuple_element<0, decltype(myTuple2)>::type; // Получение типа первого элемента (int)
	using ElementType1 = std::tuple_element<1, decltype(myTuple2)>::type; // Получение типа второго элемента (double)
	using ElementType2 = std::tuple_element<2, decltype(myTuple2)>::type; // Получение типа третьего элемента (const char*)

    return 0;
}