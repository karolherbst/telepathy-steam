#pragma once

template<typename M, typename K>
auto GLIB_CALL_PARENT(M * method, K * object) -> decltype(method(object))
{
	if(method != nullptr)
	{
		return method(object);
	}
	return decltype(method(object))();
}
