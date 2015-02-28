#include "defines.h"

#include "connection-manager.h"

#include <cstdlib>

#include <telepathy-glib/debug.h>
#include <telepathy-glib/run.h>

int main(int argc, char *argv[])
{
	if (std::getenv("STEAM_PERSIST") != nullptr)
	{
		tp_debug_set_persistent(true);
	}

	return tp_run_connection_manager(TP_CM_ID, TP_STEAM_VERSION, []()
	{
		return static_cast<TpBaseConnectionManager*>(g_object_new(STEAM_TYPE_CONNECTION_MANAGER, NULL));
	}, argc, argv);
}
