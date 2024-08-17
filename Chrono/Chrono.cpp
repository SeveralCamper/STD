#include <chrono>
#include <thread>
#include <iostream>
#include <functional>

// Библиотека std::crono предназначена для работы со временем и таймерами. Она реализует следующие концепции: интервалы времени - duration,
// моменты времени - time_point, таймеры - clock.

// Начнем с std::ratio, это шаблонный класс, реализующий compile-time обыкновенную дробь (m/n). Не является частью библиотеки, но активно ей используется.

/* template<
    std::intmax_t Num,       //Числитель
    std::intmax_t Denom = 1  //Знаменатель
> class ratio; */

// Оба параметра класса имеют спецификатор constexpr, который обозначает константность и позволяет формировать тип на этапе компиляции.
// Этот класс необходим для эффективногоперевода едениц измерения. Пример на ед. расстояний:

using Mm = std::ratio<1>; //Знаменатель == 1
//Также пользователь может определить те, которые ему нужны:
using Inches = std::ratio<254, 10>;
using Metre = std::ratio<1000, 1>;

template<class _Ratio>
class Length
{
    double length_;
public:
    explicit Length(double length) : length_(length) { }
    double length() const { return length_; }
};

template<class _Ratio1, class _Ratio2>
Length<Mm> operator+(const Length<_Ratio1> &left, const Length<_Ratio2> &right)
{
    double len =
        left.length() / _Ratio1::den * _Ratio1::num +
        right.length() / _Ratio2::den * _Ratio2::num;
    return Length<Mm>((int)len);
}

// duration — интервал времени

// Шаблонный класс std::chrono::duration является типом интервала времени. Интервал времени в chrono - это некоторое количество периодов.
// Это количество характерихуется, например типом int64_t илил float. Продолжительность периода измеряется в виде натуральной дроби с
// помощью std::ration и измеряется в секундах.

// Некоторые популярные интервалы уже определены в библиотеке. Типы могут немного различаться в различных реализациях

// using nanoseconds = std::chrono::duration<long long, nano>;
// using microseconds  = std::chrono::duration<long long, micro>;
// using milliseconds = std::chrono::duration<long long, milli>;
// using seconds = std::chrono::duration<long long>;
// using minutes = std::chrono::duration<int, std::ratio<60> >;
// using hours = std::chrono::duration<int, std::ratio<3600> >;

//Приставки nano, micro, milli:
// using nano = std::ratio<1, 1000000000>;
// using micro = std::ratio<1, 1000000>;
// using milli = std::ratio<1, 1000>;

// Также можно поределять свои типы:

// 3-минутные песочные часы
using Hourglass = std::chrono::duration<long, std::ratio<180>>;
// или можно определить тип с помощью std::ratio_multiply(класс R1, класс R2), который возвращает результат перемножения двух точных рациональных дробей.
using Hourglass =
  std::chrono::duration<long, std::ratio_multiply<std::ratio<3>, std::chrono::minutes::period>>;

// Другие примеры:
using MyTimeUnit = std::chrono::duration<long, std::ratio<11, 4>>;
using fseconds = std::chrono::duration<float>;
using seconds16 = std::chrono::duration<uint16_t>;

// Приступим к разбору использования данного класса
// 1. Неявная инициализация запрещена.
// Разрешена только яваня:

void foo(std::chrono::minutes) {};

// 2. В C++14 добавлены пользовательские литералы для основных единиц, которые можно вычитать складывать и сравнивать:
// h - часы (std::chrono::hours)
// min - минуты (std::chrono::minutes)
// s - секунды (std::chrono::seconds)
// ms - миллисекунды (std::chrono::milliseconds)
// us - микросекунды (std::chrono::microseconds)
// ns - наносекунды (std::chrono::nanoseconds)

// 3. Чтобы вывести значение интервала на экран или в файл, нужно использовать count().


// time_point — момент времени

// Класс time_point предназначен для представления моментов времени.
// Момент времени может быть охарактеризован как интервал времени, измеренным на каком-либо таймере, начиная с некоторой точки отсчета

//  В библиотеке 3 таймера:

// 1. system_clock – представляет время системы. Обычно этот таймер не подходит для измерения интервалов, так как во
// время измерения время может быть изменено пользователем или процессом синхронизации. Обычно основывается на количестве времени,
// прошедших с 01.01.1970, но это не специфицировано.

// 2. steady_clock – представляет так называемые устойчивые часы, то есть ход которых не подвержен внешним изменениям.
// Хорошо подходит для измерения интервалов. Обычно его реализация основывается на времени работы системы после включения.

// 3. high_resolution_clock – таймер с минимально возможным периодом отсчетов, доступным системе. Может являться
// псевдонимом для одного из рассмотренных (почти наверняка это steady_clock).

// У Clock есть статическая переменная is_steady, по который вы можете узнать, является ли таймер монотонным. Также у Clock есть
// функция now, возвращающая текущий момент времени в виде time_point. Сам по себе объект класса time_point не очень интересен, так
//как момент его начала отсчета не специфирован и имеет мало смысла. Но к нему можно прибавлять интервалы времени и сравнивать
// с другими моментами времени:

// time_point нельзя сложить с time_point, зато можно вычесть, что полезно для засечения времени:

using namespace std::chrono_literals;

class Benchmark
{
	public:
    template <typename Func, typename... Args>
    static void MeasureExecutionTime(Func func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        
        func(std::forward<Args>(args)...);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        
        std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;
    }
};

void test_func(int a, double b)
{
	auto res = a + b;
	std::this_thread::sleep_for(5s);
}

int main()
{
	std::cout << "Ratio:" << std::endl;
	Length<Mm> len1(127.0);
	Length<Inches> len2(5.0);
	Length<Mm> len3 = len1 + len2;

	std::cout << len1.length() << std::endl;
	std::cout << len2.length() << std::endl;
	std::cout << len3.length() << std::endl;
	std::cout << std::endl;

	
	std::cout << "Duration:" << std::endl;
	// 1. Неявная инициализация запрещена.
	// seconds s = 5; - Ошибка компиляции
	// void foo(minutes);
	// foo(42); - Ошибка компиляции

	// Яваня инициализация допустима
	std::chrono::seconds s1(8);
	foo(std::chrono::minutes(42));

	// Важно запомнить, что инициализация фигурными скобками используется для избежания неявного преобразования интегральных типов с потерями
	// Инициализация круглыми допустима, но может привести к ошибкам вычисления.

	std::chrono::seconds s2{8};
	foo(std::chrono::minutes{42});

	std::cout << std::endl;
	std::cout << "Std::chrono_literals:" << std::endl;

	// 2. В C++14 добавлены пользовательские литералы для основных единиц, которые можно вычитать складывать и сравнивать:
	std::chrono::seconds time1 = 5min + 17s;
	std::chrono::minutes time2 = 2h - 15min;
	bool less = 59s < 1min;
	std::cout << less << std::endl;

	// Как в примере выше, можно неявно преобразовывать часы в минуты, минуты в секунды, секунды в миллисекуну и т. д., но не наоборот:
	// minutes time3 = 20s; //Ошибка при компиляции
	// seconds time4 = 2s + 500ms; //Ошибка при компиляции

	// В общем случае, неявное преобразование для целочисленных типов разрешено если отношение периодов является целым числом:
	std::chrono::duration<long, std::ratio<1, 3>> t1 = std::chrono::duration<long, std::ratio<20, 15>>{ 1 };

	// В противном случае есть 2 способа: округление и преобразование к float-типу.

	//Отбрасывание дробной части - округление в сторону нуля
	std::chrono::minutes m1 = std::chrono::duration_cast<std::chrono::minutes>(-100s); //-1m

	//C++17. Округление в сторону ближайшего целого
	std::chrono::minutes m2 = std::chrono::round<std::chrono::minutes>(-100s); //-2m

	//C++17. Округление в сторону плюс бесконечности
	std::chrono::minutes m3 = std::chrono::ceil<std::chrono::minutes>(-100s); //-1m

	//C++17. Округление в сторону минус бесконечности
	std::chrono::minutes m4 = std::chrono::floor<std::chrono::minutes>(-100s); //-2m

	// Чтобы вывести значение интервала на экран или в файл, нужно использовать count():
	std::chrono::seconds s3 = 15s;
	std::cout << s3.count() << "s\n";

	std::cout << std::endl;
	std::cout << "Time Point" << std::endl;

	// Варианты инициализации.
	std::chrono::time_point<std::chrono::steady_clock> start1 = std::chrono::steady_clock::now();
	//или
	std::chrono::steady_clock::time_point start2 = std::chrono::steady_clock::now();
	//или
	auto start3 = std::chrono::steady_clock::now();

	if (std::chrono::steady_clock::now() < start1 + 1s)
		std::cout << "Less than a second!\n";

	// time_point нельзя сложить с time_point, зато можно вычесть, что полезно для засечения времени:

	auto start = std::chrono::steady_clock::now();
	
	std::this_thread::sleep_for(std::chrono::seconds(2));
	// можно еще так std::this_thread::sleep_for(2000ms);

	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	if (elapsed < std::chrono::seconds(3))
	{
		std::cout << "Elapsed less than a 3 second" << std::endl;
	}

	std::cout << "Elapsed time in ms: " << start.time_since_epoch().count() << ' ' << end.time_since_epoch().count() << ' ' << elapsed.count() << std::endl;

	Benchmark::MeasureExecutionTime(test_func, 5, 5.0);

	return 0;
}