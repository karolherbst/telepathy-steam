#pragma once

#include <glib-object.h>
#include <telepathy-glib/base-connection-manager.h>

struct SteamConnectionManager
{
	TpBaseConnectionManager parent;
};

struct SteamConnectionManagerClass
{
	TpBaseConnectionManagerClass parent_class;
};

GType steam_connection_manager_get_type();

/* TYPE MACROS */
#define STEAM_TYPE_CONNECTION_MANAGER \
  (steam_connection_manager_get_type ())
#define STEAM_CONNECTION_MANAGER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), STEAM_TYPE_CONNECTION_MANAGER, \
                              SteamConnectionManager))
#define STEAM_CONNECTION_MANAGER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), STEAM_TYPE_CONNECTION_MANAGER, \
                           SteamConnectionManagerClass))
#define STEAM_IS_CONNECTION_MANAGER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), STEAM_TYPE_CONNECTION_MANAGER))
#define STEAM_IS_CONNECTION_MANAGER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), STEAM_TYPE_CONNECTION_MANAGER))
#define STEAM_CONNECTION_MANAGER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), STEAM_TYPE_CONNECTION_MANAGER, \
                              SteamConnectionManagerClass))
