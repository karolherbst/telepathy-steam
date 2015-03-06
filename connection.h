#pragma once

#include <glib-object.h>
#include <telepathy-glib/base-connection.h>
#include <telepathy-glib/contacts-mixin.h>

struct SteamConnection
{
	TpBaseConnection parent;
	TpContactsMixin contacts;
};

struct SteamConnectionClass
{
	TpBaseConnectionClass parent_class;
	TpContactsMixinClass contacts_class;
};

GType steam_connection_get_type();

/* TYPE MACROS */
#define STEAM_TYPE_CONNECTION \
  (steam_connection_get_type ())
#define STEAM_CONNECTION(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), STEAM_TYPE_CONNECTION, \
                              SteamConnection))
#define STEAM_CONNECTION_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), STEAM_TYPE_CONNECTION, \
                           SteamConnectionClass))
#define STEAM_IS_CONNECTION(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), STEAM_TYPE_CONNECTION))
#define STEAM_IS_CONNECTION_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), STEAM_TYPE_CONNECTION))
#define STEAM_CONNECTION_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), STEAM_TYPE_CONNECTION, \
                              SteamConnectionClass))
