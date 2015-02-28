#include "connection.h"
#include "glib-helpers.h"
#include "protocol.h"

#include <new>

G_DEFINE_TYPE(SteamProtocol, steam_protocol, TP_TYPE_BASE_PROTOCOL);

static TpCMParamSpec steamParams[]
{
	{ 0 }
};

static const TpCMParamSpec * get_parameters(TpBaseProtocol * self)
{
	return steamParams;
}

static TpBaseConnection * new_connection(TpBaseProtocol * self, GHashTable * asv, GError ** error)
{
	SteamConnection * conn = STEAM_CONNECTION(g_object_new(STEAM_TYPE_CONNECTION,
		"protocol", "steam",
		nullptr));
	return TP_BASE_CONNECTION(conn);
}

void steam_protocol_class_init(SteamProtocolClass * klass)
{
	GObjectClass * object_class = G_OBJECT_CLASS(klass);
	klass->parent_class.get_parameters = get_parameters;
	klass->parent_class.new_connection = new_connection;
}

void steam_protocol_init(SteamProtocol * sp){}

TpBaseProtocol *
steam_protocol_new()
{
	return TP_BASE_PROTOCOL(g_object_new(STEAM_TYPE_PROTOCOL, "name", "steam", nullptr));
}
