/* Copyright (c) Dovecot authors, see top-level COPYING file */

#include "lib.h"
#include "settings-parser.h"
#include "replication-settings.h"

#undef DEF
#define DEF(type, name) \
	SETTING_DEFINE_STRUCT_##type(#name, name, struct replication_settings)

static const struct setting_define replication_setting_defines[] = {
	DEF(STR, mail_replica),
	DEF(UINT, replication_sync_timeout),
	DEF(BOOL, noreplicate),

	SETTING_DEFINE_LIST_END
};

static const struct replication_settings replication_default_settings = {
	.mail_replica = "",
	.replication_sync_timeout = 0,
	.noreplicate = FALSE,
};

const struct setting_parser_info replication_setting_parser_info = {
	.name = "replication",
	.plugin_dependency = "lib20_replication_plugin",

	.defines = replication_setting_defines,
	.defaults = &replication_default_settings,

	.struct_size = sizeof(struct replication_settings),
	.pool_offset1 = 1 + offsetof(struct replication_settings, pool),
};
