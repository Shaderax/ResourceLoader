#include <cstdint>
#include <string>

template< typename T >
class Resource : public T
{
public:
		Resource();
		~Resource();

private:
	std::uint32_t mCounter = 0;
	std::string mPath;
};