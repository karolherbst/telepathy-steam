#include "connection-manager.h"
#include "glib-helpers.h"
#include "protocol.h"

G_DEFINE_TYPE(SteamConnectionManager, steam_connection_manager, TP_TYPE_BASE_CONNECTION_MANAGER);

static void stema_connection_manager_constructed (GObject * object)
{
	GLIB_CALL_PARENT(steam_connection_manager_parent_class, constructed, object);
	tp_base_connection_manager_add_protocol(TP_BASE_CONNECTION_MANAGER(object), steam_protocol_new());
}

static void steam_connection_manager_finalize (GObject * object)
{
	GLIB_CALL_PARENT(steam_connection_manager_parent_class, finalize, object);
}

void steam_connection_manager_class_init(SteamConnectionManagerClass * klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->constructed = stema_connection_manager_constructed;
	object_class->finalize = steam_connection_manager_finalize;
	klass->parent_class.cm_dbus_name = "steam";
}

void steam_connection_manager_init(SteamConnectionManager * scm)
{

}
