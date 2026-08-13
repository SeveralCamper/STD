#include <memory>
#include <iostream>

int main()
{
	std::unique_ptr<int> spUniquePtr = std::make_unqie<int>(10);
	std::shared_ptr<int> spSharedPtr = std::make_unqie<int>(10);

	return 0;
}