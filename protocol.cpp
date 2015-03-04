#include "connection.h"
#include "glib-helpers.h"
#include "protocol.h"

#include <dbus/dbus-protocol.h>

G_DEFINE_TYPE(SteamProtocol, steam_protocol, TP_TYPE_BASE_PROTOCOL);

// allthough registering isn't possible yet, we should declare such parameters already
static TpCMParamSpec steamParams[]
{
	{
		.name = "username",
		.dtype = DBUS_TYPE_STRING_AS_STRING,
		.gtype = G_TYPE_STRING,
		.flags = TP_CONN_MGR_PARAM_FLAG_REQUIRED | TP_CONN_MGR_PARAM_FLAG_REGISTER,
		.def = nullptr,
		.offset = 0,
		.filter = nullptr,
		.filter_data = nullptr,
		.setter_data = nullptr
	},
	{
		.name = "password",
		.dtype = DBUS_TYPE_STRING_AS_STRING,
		.gtype = G_TYPE_STRING,
		.flags = TP_CONN_MGR_PARAM_FLAG_SECRET,
		.def = nullptr,
		.offset = 0,
		.filter = nullptr,
		.filter_data = nullptr,
		.setter_data = nullptr
	},
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
