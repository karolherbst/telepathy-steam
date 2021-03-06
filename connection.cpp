#include "connection.h"
#include "glib-helpers.h"

#include <thread>

#include <telepathy-glib/handle-repo-dynamic.h>
#include <telepathy-glib/interfaces.h>
#include <telepathy-glib/svc-generic.h>

G_DEFINE_TYPE_WITH_CODE(SteamConnection, steam_connection, TP_TYPE_BASE_CONNECTION,
	G_IMPLEMENT_INTERFACE(TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACTS, tp_contacts_mixin_iface_init);
	G_IMPLEMENT_INTERFACE(TP_TYPE_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE, tp_presence_mixin_simple_presence_iface_init);
	G_IMPLEMENT_INTERFACE(TP_TYPE_SVC_DBUS_PROPERTIES, tp_dbus_properties_mixin_iface_init);
);

static const gchar * const interfaces_always_present[] =
{
	//TP_IFACE_CONNECTION_INTERFACE_CONTACTS,
	TP_IFACE_CONNECTION_INTERFACE_SIMPLE_PRESENCE
};

/*
 * the steam chat has the following states:
 *
 * Online
 * Away
 * Busy
 * Looking to Play
 * Looking to Trade
 * Offline
 *
 * there is no status with a custom message!
 */
static TpPresenceStatusSpec const presence_statuses[] =
{
	{
		.name = "Online",
		.presence_type = TP_CONNECTION_PRESENCE_TYPE_AVAILABLE,
		.self = true,
	},
	{
		.name = "Away",
		.presence_type = TP_CONNECTION_PRESENCE_TYPE_AWAY,
		.self = true,
	},
	{
		.name = "Busy",
		.presence_type = TP_CONNECTION_PRESENCE_TYPE_BUSY,
		.self = true,
	},
	{
		.name = "Looking to Play",
		.presence_type = TP_CONNECTION_PRESENCE_TYPE_AVAILABLE,
		.self = true,
	},
	{
		.name = "Looking to Trade",
		.presence_type = TP_CONNECTION_PRESENCE_TYPE_AVAILABLE,
		.self = true,
	},
	{
		.name = "Offline",
		.presence_type = TP_CONNECTION_PRESENCE_TYPE_OFFLINE,
		.self = true,
	},
	{
		.name = nullptr
	}
};

static void constructed(GObject * self)
{
	GLIB_CALL_PARENT(G_OBJECT_CLASS(steam_connection_parent_class)->constructed, self);
	tp_presence_mixin_simple_presence_register_with_contacts_mixin(self);
}

static GPtrArray * create_channel_managers(TpBaseConnection * self)
{
	return g_ptr_array_new();
}

static void create_handle_repos(TpBaseConnection * self, TpHandleRepoIface * repos[TP_NUM_HANDLE_TYPES])
{
	repos[TP_HANDLE_TYPE_CONTACT] = tp_dynamic_handle_repo_new(TP_HANDLE_TYPE_CONTACT, nullptr, nullptr);
}

static void finalize(GObject * obj)
{
	tp_presence_mixin_finalize(obj);
	tp_contacts_mixin_finalize(obj);
	GLIB_CALL_PARENT(G_OBJECT_CLASS(steam_connection_parent_class)->finalize, obj);
}

static GHashTable * get_contact_statuses(GObject * self, const GArray * contacts, GError * * error)
{
	GHashTable * contact_statuses = g_hash_table_new_full(g_direct_hash, g_direct_equal, nullptr, (GDestroyNotify)tp_presence_status_free);
	for(guint i = 0; i < contacts->len; i++)
	{
		TpHandle h = g_array_index(contacts, TpHandle, i);
		g_hash_table_insert(contact_statuses, GUINT_TO_POINTER(h), tp_presence_status_new(4, nullptr));
	}
	return contact_statuses;
}

static GPtrArray * get_interfaces_always_present(TpBaseConnection * self)
{
	GPtrArray * arr = GLIB_CALL_PARENT(TP_BASE_CONNECTION_CLASS(steam_connection_parent_class)->get_interfaces_always_present, self);
	for(auto i : interfaces_always_present)
	{
		g_ptr_array_add(arr, g_strdup(i));
	}
	return arr;
}

static gchar * get_unique_connection_name(TpBaseConnection * self)
{
	return g_strdup("steam");
}

static gboolean set_own_status(GObject * self, const TpPresenceStatus * status, GError * * error)
{
	if(status != nullptr)
	{
		tp_presence_mixin_emit_one_presence_update(self, tp_base_connection_get_self_handle(TP_BASE_CONNECTION(self)), status);
		return true;
	}

	return false;
}

static void shut_down(TpBaseConnection * self)
{
	tp_base_connection_finish_shutdown(self);
}

static gboolean start_connecting(TpBaseConnection * self, GError * * error)
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

	object_class->constructed = constructed;
	object_class->finalize = finalize;

	klass->parent_class.create_channel_factories = nullptr;
	klass->parent_class.create_channel_managers = create_channel_managers;
	klass->parent_class.create_handle_repos = create_handle_repos;
	klass->parent_class.get_interfaces_always_present = get_interfaces_always_present;
	klass->parent_class.get_unique_connection_name = get_unique_connection_name;
	klass->parent_class.shut_down = shut_down;
	klass->parent_class.start_connecting = start_connecting;

	tp_dbus_properties_mixin_class_init(object_class, G_STRUCT_OFFSET(SteamConnectionClass, properties_class));
	tp_contacts_mixin_class_init(object_class, G_STRUCT_OFFSET(SteamConnectionClass, contacts_class));
	tp_presence_mixin_class_init(object_class, G_STRUCT_OFFSET(SteamConnectionClass, presence_class),
		nullptr,
		get_contact_statuses,
		set_own_status,
		presence_statuses);

	tp_presence_mixin_simple_presence_init_dbus_properties(object_class);
}

void steam_connection_init(SteamConnection * sc)
{
	GObject * obj = G_OBJECT(sc);
	tp_contacts_mixin_init(obj, G_STRUCT_OFFSET(SteamConnection, contacts));
	tp_presence_mixin_init(obj, G_STRUCT_OFFSET(SteamConnection, presence));
}
