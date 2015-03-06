#include "connection-manager.h"
#include "glib-helpers.h"
#include "protocol.h"

G_DEFINE_TYPE(SteamConnectionManager, steam_connection_manager, TP_TYPE_BASE_CONNECTION_MANAGER);

static void stema_connection_manager_constructed (GObject * object)
{
	GLIB_CALL_PARENT(G_OBJECT_CLASS(steam_connection_manager_parent_class)->constructed, object);

	TpBaseProtocol * p = steam_protocol_new();
	tp_base_connection_manager_add_protocol(TP_BASE_CONNECTION_MANAGER(object), p);
	g_object_unref(p);
}

void steam_connection_manager_class_init(SteamConnectionManagerClass * klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->constructed = stema_connection_manager_constructed;
	klass->parent_class.cm_dbus_name = "steam";
}

void steam_connection_manager_init(SteamConnectionManager * scm)
{

}
