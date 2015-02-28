#include "connection-manager.h"

#include <cassert>

#define GLIB_CALL_PARENT(klass, method, object) \
{ \
	auto method = G_OBJECT_CLASS(steam_connection_manager_parent_class)-> method; \
	if(method != nullptr) \
	{ \
		method(object); \
	} \
}

class SteamConnectionManagerPriv
{

};

G_DEFINE_TYPE(SteamConnectionManager, steam_connection_manager, TP_TYPE_BASE_CONNECTION_MANAGER);

static void stema_connection_manager_constructed (GObject * object)
{
	GLIB_CALL_PARENT(steam_connection_manager_parent_class, constructed, object);
	SteamConnectionManager * self = STEAM_CONNECTION_MANAGER(object);
	assert(self->priv == nullptr);
	self->priv = new SteamConnectionManagerPriv();
}

static void steam_connection_manager_finalize (GObject * object)
{
	SteamConnectionManager * self = STEAM_CONNECTION_MANAGER(object);
	assert(self->priv != nullptr);
	delete self->priv;
	GLIB_CALL_PARENT(steam_connection_manager_parent_class, finalize, object);
}

void steam_connection_manager_class_init(SteamConnectionManagerClass * klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->constructed = stema_connection_manager_constructed;
	object_class->finalize = steam_connection_manager_finalize;
	klass->parent_class.cm_dbus_name = "steam";
	g_type_class_add_private(klass, sizeof(SteamConnectionManagerPriv));
}

void steam_connection_manager_init(SteamConnectionManager * scm)
{

}
