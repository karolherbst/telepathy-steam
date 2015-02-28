#pragma once

#define GLIB_CALL_PARENT(klass, method, object) \
{ \
	auto method = G_OBJECT_CLASS(klass)-> method; \
	if(method != nullptr) \
	{ \
		method(object); \
	} \
}


