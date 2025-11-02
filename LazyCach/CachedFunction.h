#include <utility>
#include <map>
#include <tuple>

template<typename ReturnType, typename ...Args>
class CachedFunc
{
public:
	using Callable = ReturnType(*)(Args...);

	CachedFunc(Callable function)
		: m_function(function)
	{}

	ReturnType operator()(Args... arguments)
	{
	    std::tuple<Args...> key = std::make_tuple(std::move(arguments)...);
		auto search = m_result.find(key);
		if (search != m_result.end())
		    return search->second;

		auto value = std::apply(std::forward<Callable>(m_function), key);
		m_result[key] = value;
		return value;
	}

	void clear()
	{
        m_result.clear();
	}

	size_t caches()
	{
	    return m_result.size();
	}

private:
	Callable m_function;
	std::map<std::tuple<Args...>, ReturnType> m_result;
};
