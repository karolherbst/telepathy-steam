#include "glib-helpers.h"
#include "protocol.h"

G_DEFINE_TYPE(SteamProtocol, steam_protocol, TP_TYPE_BASE_PROTOCOL);

void steam_protocol_class_init(SteamProtocolClass * klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
}

void steam_protocol_init(SteamProtocol * sp){}

TpBaseProtocol *
steam_protocol_new()
{
	return TP_BASE_PROTOCOL(g_object_new(STEAM_TYPE_PROTOCOL, "name", "steam", nullptr));
}
