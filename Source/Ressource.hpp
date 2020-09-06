#include <cstdint>

namespace Soon
{
	class Ressource
	{
		public:
			Ressource();
			~Ressource();

		private:
			std::uint32_t m_Counter;
	};
}