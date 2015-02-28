#include "glib-helpers.h"
#include "protocol.h"

static const TpCMParamSpec * get_parameters(TpBaseProtocol * self)
{
	return nullptr;
}

static TpBaseConnection * new_connection(TpBaseProtocol * self, GHashTable * asv, GError ** error)
{
	return nullptr;
}

G_DEFINE_TYPE(SteamProtocol, steam_protocol, TP_TYPE_BASE_PROTOCOL);

void steam_protocol_class_init(SteamProtocolClass * klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	klass->parent_class.get_parameters = get_parameters;
	klass->parent_class.new_connection = new_connection;
}

void steam_protocol_init(SteamProtocol * sp){}

TpBaseProtocol *
steam_protocol_new()
{
	return TP_BASE_PROTOCOL(g_object_new(STEAM_TYPE_PROTOCOL, "name", "steam", nullptr));
}
