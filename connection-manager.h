#pragma once

#include <glib-object.h>
#include <telepathy-glib/base-connection-manager.h>

class SteamConnectionManagerPriv;
struct SteamConnectionManager
{
	TpBaseConnectionManager parent;
	SteamConnectionManagerPriv * priv;
};

struct SteamConnectionManagerClass
{
	TpBaseConnectionManagerClass parent_class;
};

GType steam_connection_manager_get_type();
