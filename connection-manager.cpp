#include "connection-manager.h"

class SteamConnectionManagerPriv
{

};

G_DEFINE_TYPE(SteamConnectionManager, steam_connection_manager, TP_TYPE_BASE_CONNECTION_MANAGER);

void steam_connection_manager_class_init(SteamConnectionManagerClass * klass)
{
	klass->parent_class.cm_dbus_name = "steam";
	g_type_class_add_private(klass, sizeof(SteamConnectionManagerPriv));
}

void steam_connection_manager_init(SteamConnectionManager * scm)
{

}
