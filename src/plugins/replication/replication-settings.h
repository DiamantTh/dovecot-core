#ifndef REPLICATION_SETTINGS_H
#define REPLICATION_SETTINGS_H

struct replication_settings {
	pool_t pool;

	const char *mail_replica;
	unsigned int replication_sync_timeout;
	bool noreplicate;
};

extern const struct setting_parser_info replication_setting_parser_info;

#endif
