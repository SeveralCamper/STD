#include <iostream>
#include <vector>
#include <map>

template <typename T>
void func(T text)
{
	std::cout << text << std::endl;
	int var = 2;
	//  abort();
	// throw std::runtime_error("Negative value not allowed.");
}

void recursive(int& num)
{
	if (num < 10)
	{
		num++;
		recursive(num);
	}
}

class Test
{
	public:
		Test()
		{
			std::cout << "Build test" << std::endl;
			m_vector.push_back(1);
			m_map[0] = 1;
		}

		template <typename T>
		void Print(T text)
		{
			try
			{
				{
					func(text);
				}
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		void PrintAbort()
		{
			std::cout << "abort" << std::endl;
			m_vector[5] = 1200;
		}
	
	private:
		std::vector<int> m_vector;
		std::map<int, int> m_map;
};

int main()
{
	int m = 0;
	Test test = Test();
	test.Print(2);
	test.Print("simple");

	int num = 0;

	recursive(num);

	test.PrintAbort();

	return 0;
}
