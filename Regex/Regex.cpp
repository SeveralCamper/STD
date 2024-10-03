#include <regex>
#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

// std::regex - реализация регулярных выражений и взаимодействия с ними в С++.

int main() {
	std::string text = "Hello, world!";
	std::regex pattern("world");
	
	if (std::regex_search(text, pattern))
	{
		std::cout << "Catch alignment!" << std::endl;
	} 
	else
	{
		std::cout << "No alignment" << std::endl;
	}

	// Классы символов: Позволяют определить набор допустимых символов:

	// [abc] — любой из символов a, b или c
	// [a-z] — любой символ в диапазоне от a до z
	// [^abc] — любой символ, кроме a, b или c
	// Группировка: Используйте круглые скобки для группировки выражений и управления порядком операций. Например, (abc)+ будет искать одну или более последовательностей "abc".

	std::vector<std::string> strVec;
	for (int i = 0; i < 10; i++)
	{
		strVec.push_back("STRING_[" + std::to_string(i) + "]_VECTOR");
		
		if (std::regex_search(strVec[i], std::regex(R"(STRING_\[.\]_VECTOR)"))) { std::cout << "Catch strVec[i]: " << strVec[i] << std::endl; }
	}

	std::string text1 = "HI, Barby, gm Kent!";
	std::string text2 = "Hello, Barby, gm Kent!";
	std::string text3 = "Good morning, Barby, gm Kent!";

	// с помощью символа | можно искать вхождения разных слов и словосочетаний
	std::regex pattern1(R"(HI|Hello|Good morning)");

	if (std::regex_search(text1, pattern1))
	{
		std::cout << "Catch alignment Hi!" << std::endl;
	}
	else
	{
		std::cout << "No alignment" << std::endl;
	}

	if (std::regex_search(text2, pattern1))
	{
		std::cout << "Catch alignment Hello!" << std::endl;
	}
	else
	{
		std::cout << "No alignment" << std::endl;
	}

	if (std::regex_search(text3, pattern1))
	{
		std::cout << "Catch alignment Good morning!" << std::endl;
	}
	else
	{
		std::cout << "No alignment" << std::endl;
	}

	std::string replaced = std::regex_replace(text, pattern, "home");
	std::cout << replaced << std::endl;

	// с помощью модификатора * можно написать выражение, которое будет отлавливать n вхождений символа x: x*, n >= 0.
	std::regex pattern2(R"(a*)"); // поймает вхождения "", "a", "aa" и т.д.
	std::regex pattern3(R"( *)"); // поймает вхождения "", " ", "  " и т.д.
	std::regex pattern4(R"((Good morning)*)"); // поймает вхождения "", "Good morning", "Good morningGood morning" и т.д.
	// По факту вообще где угодно паймет все эти вхождения, т.к. если их не будет, то это ""
	
	std::string text4 = "03.04.2002";
	std::string text5 = "31.14.2002";
	std::string text6 = "25.04.2002";
	std::string text7 = "05.99.9999";

	std::regex pattern5(R"(0[1-9]|[12][0-9]|3[01])"); // Можно получить дату с валидным днем

	if (std::regex_search(text4, pattern5) && std::regex_search(text5, pattern5)
				&& std::regex_search(text6, pattern5) && std::regex_search(text7, pattern5))
	{
		std::string replaced1 = std::regex_replace(text4, pattern5, "xx");
		std::string replaced2 = std::regex_replace(text5, pattern5, "xx");
		std::string replaced3 = std::regex_replace(text6, pattern5, "xx");
		std::string replaced4 = std::regex_replace(text7, pattern5, "xx");
		std::cout << replaced1 << " " << replaced2 << " " << replaced3 << " " << replaced4 << std::endl;
	}
	else
	{
		std::cout << "No alignment" << std::endl;
	}

	try
	{
		static const auto r = std::regex(R"(\)"); // Escape sequence error
	}
	catch (const std::regex_error &e)
	{
		assert(strcmp(e.what(), "Unexpected end of regex when escaping.") == 0);
		assert(e.code() == std::regex_constants::error_escape);
	}

	// Есть скоращения, используемые в регулярных выражениях.

	// \d [0-9] - Цифровой символ
	// \D [^0-9] - Нецифровой символ
	// \s [ \f\n\r\t\v] - Пробельный символ
	// \S [^ \f\n\r\t\v] - Непробельный символ
	// \w [[:word:]] - Буквенный или цифровой символ или знак подчёркивания
	// \W [^[:word:]] - Любой символ, кроме буквенного или цифрового символа или знака подчёркивания
	// . - Вообще любой символ

	// К пробельным символам относятся

	// \r - Возврат каретки (Carriage return, CR)
	// \n - Перевод строки (Line feed, LF)
	// \t - Табуляция (Tab)
	// \v - Вертикальная табуляция (vertical tab)
	// \f - Конец страницы (Form feed)
	// [\b] - Возврат на 1 символ (Backspace)

	std::string text8 = "AaA";

	std::regex pattern6(R"(\D)");

	if (std::regex_search(text8, pattern6))
	{
		std::cout << "Catch alignment!" << std::endl;
	}
	else
	{
		std::cout << "No alignment" << std::endl;
	}
	std::cout << std::endl;

	// Квантификаторы — так называют специальные символы в регулярных выражениях, которые указывают количество повторений текста

	// . — любой символ (кроме новой строки)
	// * — ноль или более повторений предыдущего символа
	// + — одно или более повторений
	// ? — ноль или одно повторение
	// ^ — начало строки
	// $ — конец строки

	// {n} — ровно n повторений
	// {n,} — n или более повторений
	// {n,m} — от n до m повторений

	std::string text9 = "mikha.alkhimovich@mail.ru";
	std::string text10 = "hehe+hoho-mail.ru";

	std::regex pattern7(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"); // Проверка на email

	std::cout << "Valid email:" << std::endl;
	if (std::regex_search(text9, pattern7))
	{
		std::cout << "Catch alignment with correct email!" << std::endl;
	}
	else
	{
		std::cout << "No alignment" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Invalid email:" << std::endl;
	if (std::regex_search(text10, pattern7))
	{
		std::cout << "Catch alignment!" << std::endl;
	}
	else
	{
		std::cout << "No alignment - incorrect email" << std::endl;
	}
	std::cout << std::endl;

	// std::regex_match - сопоставляет полностью строку с регулярным выражением	
	std::cout << "Matching:" << std::endl;
	if (std::regex_match(text9, pattern7))
	{
		std::cout << "Catch alignment - mathced regex!" << std::endl;
	}
	else
	{
		std::cout << "No alignment" << std::endl;
	}
	std::cout << std::endl;
	std::string text11 = "mikha.alkhimovich@mail.ru lnisha@student.21-school.ru alkhimovich@protei-lab.ru";

	// std::smatch может хранить в себе первое вхождение регулряного выражения из строки
	std::smatch match;
	std::regex_search(text11, match, pattern7);
	
	for (int i = 0; i < match.size(); i++)
	{
		std::cout << match[i] << std::endl;
	}
	std::cout << std::endl;

	// так можно сразу итерироваться по совпадениям
	std::sregex_iterator it(text11.begin(), text11.end(), pattern7);
	std::sregex_iterator end;

	std::cout << "Found emails:" << std::endl;
	for (; it != end; ++it)
	{
		std::cout << it->str() << std::endl;
	}
	std::cout << std::endl;

	std::sregex_token_iterator itT(text11.begin(), text11.end(), pattern7);
	std::sregex_token_iterator endT;

	std::vector<std::string> emails;
	while (itT != endT)
	{
		emails.push_back(*itT);
		++itT;
	}

	std::cout << "Found emails:" << std::endl;
	for (const auto& email : emails) {
		std::cout << email << std::endl;
	}
	std::cout << std::endl;

	// Если нужно выделить токены, которые не соотвествуют регулярному выражению, то нужно добавить -1 последним параметром:

	std::string text12 = "mikha.alkhimovich@mail.ru hehehe lnisha@student.21-school.ru   alkhimovich@protei-lab.ru 2";

	std::sregex_token_iterator itOtherT(text12.begin(), text12.end(), pattern7, -1);
	std::sregex_token_iterator endOtherT;

	std::vector<std::string> otherToken;
	while (itOtherT != endOtherT)
	{
		otherToken.push_back(*itOtherT);
		++itOtherT;
	}

	std::cout << "Found otherToken:" << std::endl;
	for (const auto& otherToken : otherToken) {
		std::cout << otherToken << std::endl;
	}
	std::cout << std::endl;

	return 0;
}