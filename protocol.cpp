#include "glib-helpers.h"
#include "protocol.h"

#include <new>

G_DEFINE_TYPE(SteamProtocol, steam_protocol, TP_TYPE_BASE_PROTOCOL);

class SteamProtocolPriv
{

};

static void constructed(GObject *object)
{
	GLIB_CALL_PARENT(steam_protocol_parent_class, constructed, object)
	SteamProtocol * self = STEAM_PROTOCOL(object);
	self->priv = G_TYPE_INSTANCE_GET_PRIVATE(object, STEAM_TYPE_PROTOCOL, SteamProtocolPriv);
	new (self->priv) SteamProtocolPriv();
}

static void finalize(GObject *object)
{
	SteamProtocol * self = STEAM_PROTOCOL(object);
	self->priv->~SteamProtocolPriv();
	GLIB_CALL_PARENT(steam_protocol_parent_class, finalize, object)
}

static const TpCMParamSpec * get_parameters(TpBaseProtocol * self)
{
	return nullptr;
}

static TpBaseConnection * new_connection(TpBaseProtocol * self, GHashTable * asv, GError ** error)
{
	return nullptr;
}

void steam_protocol_class_init(SteamProtocolClass * klass)
{
	GObjectClass * object_class = G_OBJECT_CLASS(klass);
	object_class->constructed = constructed;
	object_class->finalize = finalize;
	klass->parent_class.get_parameters = get_parameters;
	klass->parent_class.new_connection = new_connection;

	g_type_class_add_private(klass, sizeof(SteamProtocolPriv));
}

void steam_protocol_init(SteamProtocol * sp){}

TpBaseProtocol *
steam_protocol_new()
{
	return TP_BASE_PROTOCOL(g_object_new(STEAM_TYPE_PROTOCOL, "name", "steam", nullptr));
}
