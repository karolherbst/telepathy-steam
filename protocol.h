#pragma once

#include <glib-object.h>
#include <telepathy-glib/base-protocol.h>

struct SteamProtocol
{
	TpBaseProtocol parent;
};

struct SteamProtocolClass
{
	TpBaseProtocolClass parent_class;
};

GType steam_protocol_get_type();

/* TYPE MACROS */
#define STEAM_TYPE_PROTOCOL \
  (steam_protocol_get_type ())
#define STEAM_PROTOCOL(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), STEAM_TYPE_PROTOCOL, \
                              SteamProtocol))
#define STEAM_PROTOCOL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), STEAM_TYPE_PROTOCOL, \
                           SteamProtocolClass))
#define STEAM_IS_PROTOCOL(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), STEAM_TYPE_PROTOCOL))
#define STEAM_IS_PROTOCOL_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), STEAM_TYPE_PROTOCOL))
#define STEAM_PROTOCOL_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), STEAM_TYPE_PROTOCOL, \
                              SteamProtocolClass))

TpBaseProtocol * steam_protocol_new();
