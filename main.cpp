#include "defines.h"

#include <telepathy-glib/run.h>

int main(int argc, char *argv[])
{
	return tp_run_connection_manager(TP_CM_ID, TP_STEAM_VERSION, []() -> TpBaseConnectionManager *
	{
		return nullptr;
	}, argc, argv);
}
