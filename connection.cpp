#include "connection.h"
#include "glib-helpers.h"

#include <thread>

#include <telepathy-glib/handle-repo-dynamic.h>

G_DEFINE_TYPE(SteamConnection, steam_connection, TP_TYPE_BASE_CONNECTION);

static GPtrArray * create_channel_managers(TpBaseConnection *self)
{
	return g_ptr_array_new();
}

static void create_handle_repos(TpBaseConnection *self, TpHandleRepoIface *repos[TP_NUM_HANDLE_TYPES])
{
	repos[TP_HANDLE_TYPE_CONTACT] = tp_dynamic_handle_repo_new(TP_HANDLE_TYPE_CONTACT, nullptr, nullptr);
}

static void finalize(GObject * obj)
{
	tp_contacts_mixin_finalize(obj);
}

static GPtrArray * get_interfaces_always_present(TpBaseConnection *self)
{
	return GLIB_CALL_PARENT(TP_BASE_CONNECTION_CLASS(steam_connection_parent_class)->get_interfaces_always_present, self);
}

static gchar * get_unique_connection_name(TpBaseConnection *self)
{
	return g_strdup("steam");
}

static void shut_down(TpBaseConnection *self)
{
	tp_base_connection_finish_shutdown(self);
}

static gboolean start_connecting(TpBaseConnection *self, GError **error)
{
	// the steam id is trivially to get, because we know it already
	gchar sid[] = "";
	tp_base_connection_set_self_handle(self,
		tp_handle_ensure(
			tp_base_connection_get_handles(self, TP_HANDLE_TYPE_CONTACT),
			sid, nullptr, nullptr)
		);
	std::thread([self](){
		std::this_thread::sleep_for(std::chrono::seconds(2));
		tp_base_connection_change_status(self, TP_CONNECTION_STATUS_CONNECTED, TP_CONNECTION_STATUS_REASON_REQUESTED);
	}).detach();
	return true;
}

void steam_connection_class_init(SteamConnectionClass * klass)
{
	GObjectClass * object_class = G_OBJECT_CLASS(klass);

	object_class->finalize = finalize;

	klass->parent_class.create_channel_factories = nullptr;
	klass->parent_class.create_channel_managers = create_channel_managers;
	klass->parent_class.create_handle_repos = create_handle_repos;
	klass->parent_class.get_interfaces_always_present = get_interfaces_always_present;
	klass->parent_class.get_unique_connection_name = get_unique_connection_name;
	klass->parent_class.shut_down = shut_down;
	klass->parent_class.start_connecting = start_connecting;

	tp_contacts_mixin_class_init(object_class, G_STRUCT_OFFSET(SteamConnectionClass, contacts_class));
}

void steam_connection_init(SteamConnection * sc)
{
	GObject * obj = G_OBJECT(sc);
	tp_contacts_mixin_init(obj, G_STRUCT_OFFSET(SteamConnection, contacts));
}
