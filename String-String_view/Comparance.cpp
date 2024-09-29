#include <array>
#include <string>
#include <random>
#include <chrono>
#include <chrono>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string_view>

// std::string - обертка для страндартных char массивов, которая хранит, за некоторым исключением, данные в куче, а также предоставляет некоторое API для взаимодействия
// с хранимой строкой. Этот класс автоматически управляет память при изменении строки и может ее переаспределить. Std::string представляет интерфейс для взаимодействия
// с изменяемой строкой. В базовом классе std::basic_string реализован механизм оптимизации малых строк - SSO - данный механизм позволяет оптимизировать работу
// со строками, меньше определенного размера, взависимости от реализации от 15 до 20 символов. Он проверяет размер строки и если размер больше, чем максимально возможный
// для использования SSO, то память выделяется на куче, иначе - в заранее выделенном массиве.

// Нультерменированность строк std::string. Нул-терминатор необходим для того, чтобы в стандартном C компилятор мог определить конец строки. Строки в std::string тоже
// являются нуль-терменированными, но по большей части это сделано для обеспечения совместимости с C-строками и методами стандартной библиотеки, которые работают с 
// С-строками. Т.к. в std::string есть специальный член, определяющий размер массива, то для взаимодействия между std::string нуль-терминатор не нужен, более того,
// в С-строках для определения размера всегда необходимо пройти всю строку от начала и до конца, тем самым определить размер строки, что является  O(n), когда
// в std::string операция получения размера выполняется за константное время.

// std::string_view - это невладеющая ссылка на строку, которую нельзя модифицировать. Std::string_view содержит в себе только указатель на начло строки и дилнну строки.
// Таким образом, std::string_view не нужно выделять память при инициализрации, т.к. view работает только с память, которая уже пренадлежит кому-то и это еще не все преймущества.
// Если мы заранее знаем, что строка не будет изменяться походу выполнения некоторого метода и будет испольваоться только для чтения, то отличным вариантом убдет использовать
// std::string_view. Даже если мы будем работать с const std::string& при передаче в метод, то в случае получения на вход метода строковго литерала, мы будем неявно 
// копировать данные для преобразования информации, std::string_view передаст аднные в метод без копирования даже если мы будем использовать стркоове литералы или char массивы.

int main() {
	std::ifstream inFile("text.txt");
	std::stringstream strStream;
	strStream << inFile.rdbuf();
	std::string str_1 = strStream.str();
	std::string_view strW{str_1.c_str(), str_1.size()};
	size_t size = str_1.size();

	std::cout << "Text size: " << size << std::endl;
	std::cout << std::endl;

	// std::string и std::string_view оба содержат метод substr. Метод std::string возвращает подстроку, а метод std::string_view возвращает
	// представление подстроки. Между этими методами есть существенная разница. std::string::substr имеет линейную сложность, а std::string_view::substr — константную сложность

	const int access = 10000000;
	for (int count = 10; count < 100000; count *= 10)
	{
		std::random_device generatedNum;
		std::mt19937 engine(generatedNum());
		std::uniform_int_distribution<> normalDistribution(0, size - count - 2); // получаем случаный целые числа в диапозоне
		std::vector<int> vec_1;
		for (auto i = 0; i <  access; ++i) vec_1.push_back(normalDistribution(engine));

		auto start = std::chrono::steady_clock::now();
		for (auto i = 0; i  < access; ++i )
		{
			str_1.substr(vec_1[i], count);
		}
		std::chrono::duration<double> durString= std::chrono::steady_clock::now() - start;
		std::cout << "Std::string::substr:      " << durString.count() << " seconds" << std::endl;

		std::string_view grimmsTalesView{str_1.c_str(), size};
		start = std::chrono::steady_clock::now();
		for (auto i = 0; i  < access; ++i )
		{
			grimmsTalesView.substr(vec_1[i], count);
		}
		std::chrono::duration<double> durStringView= std::chrono::steady_clock::now() - start;
		std::cout << "Std::string_view::substr: " << durStringView.count() << " seconds" << std::endl;

		std::cout << std::endl;

		std::cout << "Duration string / Duration string_view: " << durString.count()/durStringView.count() << std::endl;
		std::cout << std::endl;
	}

	// Если использовать обычную компиляцию, то разница в среднем в 4 раза, что уже вяляется хорошим результатом. Но если использовать оптимизацию -O3,
	// то в таком случае мы уже получим прирост в производительности в более чем 14 раз для самого первого прохода, где мы берем минимальны размер подстрок
	// а при максимальном размере - более чем в 440 раз.

	return 0;
}
