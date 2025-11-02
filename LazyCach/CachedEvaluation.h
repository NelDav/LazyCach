#include <utility>
#include <optional>
#include <tuple>

template<typename ReturnType, typename ...Args>
class CachedEval
{
public:
    using Callable = ReturnType(*)(Args...);

	CachedEval(Callable function, Args... arguments)
		: m_function(function)
		, m_arguments(std::make_tuple(std::move(arguments)...))
	{}

	ReturnType operator()(void)
	{
		if (!m_result.has_value())
			m_result = std::apply(std::forward<Callable>(m_function), m_arguments);

		return m_result.value();
	}

private:
	Callable m_function;
	std::optional<ReturnType> m_result;
	std::tuple<Args...> m_arguments;
};
