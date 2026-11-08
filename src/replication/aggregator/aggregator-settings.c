/* Copyright (c) 2013-2018 Dovecot authors, see the included COPYING file */

#include "lib.h"
#include "settings-parser.h"
#include "service-settings.h"
#include "aggregator-settings.h"

struct service_settings aggregator_service_settings = {
	.name = "aggregator",
	.protocol = "",
	.type = "",
	.executable = "aggregator",
	.user = "$SET:default_internal_user",
	.group = "",
	.privileged_group = "",
	.extra_groups = ARRAY_INIT,
	.chroot = ".",

	.drop_priv_before_exec = FALSE,

	.process_min_avail = 0,
	.process_limit = 0,
	.client_limit = 0,
	.idle_kill_interval = 0,
	.vsz_limit = UOFF_T_MAX,

	.unix_listeners = ARRAY_INIT,
	.fifo_listeners = ARRAY_INIT,
	.inet_listeners = ARRAY_INIT
};

const struct setting_keyvalue aggregator_service_settings_defaults[] = {
	{ "unix_listener", "replication-notify" },
	{ "unix_listener/replication-notify/path", "replication-notify" },
	{ "unix_listener/replication-notify/mode", "0600" },
	{ "unix_listener/replication-notify/user", "" },
	{ "unix_listener/replication-notify/group", "" },
	{ "fifo_listener", "replication-notify-fifo" },
	{ "fifo_listener/replication-notify-fifo/path",
	  "replication-notify-fifo" },
	{ "fifo_listener/replication-notify-fifo/mode", "0600" },
	{ "fifo_listener/replication-notify-fifo/user", "" },
	{ "fifo_listener/replication-notify-fifo/group", "" },
	{ NULL, NULL }
};

#undef DEF
#define DEF(type, name) \
	SETTING_DEFINE_STRUCT_##type(#name, name, struct aggregator_settings)

static const struct setting_define aggregator_setting_defines[] = {
	DEF(STR, replicator_host),
	DEF(IN_PORT, replicator_port),

	SETTING_DEFINE_LIST_END
};

const struct aggregator_settings aggregator_default_settings = {
	.replicator_host = "replicator",
	.replicator_port = 0
};

const struct setting_parser_info aggregator_setting_parser_info = {
	.name = "aggregator",
	.defines = aggregator_setting_defines,
	.defaults = &aggregator_default_settings,

	.struct_size = sizeof(struct aggregator_settings),
	.pool_offset1 = 1 + offsetof(struct aggregator_settings, pool),
};

const struct aggregator_settings *aggregator_settings;
