#include "defines.h"

#include "connection-manager.h"

#include <telepathy-glib/run.h>

int main(int argc, char *argv[])
{
	return tp_run_connection_manager(TP_CM_ID, TP_STEAM_VERSION, []()
	{
		return static_cast<TpBaseConnectionManager*>(g_object_new(steam_connection_manager_get_type(), NULL));
	}, argc, argv);
}
