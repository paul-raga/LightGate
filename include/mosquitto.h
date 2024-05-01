/*
Copyright (c) 2010-2020 Roger Light <roger@atchoo.org>

All rights reserved. This program and the accompanying materials
are made available under the terms of the Eclipse Public License v1.0
and Eclipse Distribution License v1.0 which accompany this distribution.

The Eclipse Public License is available at
   http://www.eclipse.org/legal/epl-v10.html
and the Eclipse Distribution License is available at
  http://www.eclipse.org/org/documents/edl-v10.php.

Contributors:
   Roger Light - initial implementation and documentation.
*/

#ifndef MOSQUITTO_H
#define MOSQUITTO_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) && !defined(WITH_BROKER) && !defined(LIBMOSQUITTO_STATIC)
#	ifdef libmosquitto_EXPORTS
#		define libmosq_EXPORT  __declspec(dllexport)
#	else
#		define libmosq_EXPORT  __declspec(dllimport)
#	endif
#else
#	define libmosq_EXPORT
#endif

#if defined(_MSC_VER) && _MSC_VER < 1900
#	ifndef __cplusplus
#		define bool char
#		define true 1
#		define false 0
#	endif
#else
#	ifndef __cplusplus
#		include <stdbool.h>
#	endif
#endif

#include <stddef.h>
#include <stdint.h>

#define LIBMOSQUITTO_MAJOR 1
#define LIBMOSQUITTO_MINOR 6
#define LIBMOSQUITTO_REVISION 9
/* LIBMOSQUITTO_VERSION_NUMBER looks like 1002001 for e.g. version 1.2.1. */
#define LIBMOSQUITTO_VERSION_NUMBER (LIBMOSQUITTO_MAJOR*1000000+LIBMOSQUITTO_MINOR*1000+LIBMOSQUITTO_REVISION)



/* Error values */
enum mosq_err_t {
	MOSQ_ERR_AUTH_CONTINUE = -4,
	MOSQ_ERR_NO_SUBSCRIBERS = -3,
	MOSQ_ERR_SUB_EXISTS = -2,
	MOSQ_ERR_CONN_PENDING = -1,
	MOSQ_ERR_SUCCESS = 0,
	MOSQ_ERR_NOMEM = 1,
	MOSQ_ERR_PROTOCOL = 2,
	MOSQ_ERR_INVAL = 3,
	MOSQ_ERR_NO_CONN = 4,
	MOSQ_ERR_CONN_REFUSED = 5,
	MOSQ_ERR_NOT_FOUND = 6,
	MOSQ_ERR_CONN_LOST = 7,
	MOSQ_ERR_TLS = 8,
	MOSQ_ERR_PAYLOAD_SIZE = 9,
	MOSQ_ERR_NOT_SUPPORTED = 10,
	MOSQ_ERR_AUTH = 11,
	MOSQ_ERR_ACL_DENIED = 12,
	MOSQ_ERR_UNKNOWN = 13,
	MOSQ_ERR_ERRNO = 14,
	MOSQ_ERR_EAI = 15,
	MOSQ_ERR_PROXY = 16,
	MOSQ_ERR_PLUGIN_DEFER = 17,
	MOSQ_ERR_MALFORMED_UTF8 = 18,
	MOSQ_ERR_KEEPALIVE = 19,
	MOSQ_ERR_LOOKUP = 20,
	MOSQ_ERR_MALFORMED_PACKET = 21,
	MOSQ_ERR_DUPLICATE_PROPERTY = 22,
	MOSQ_ERR_TLS_HANDSHAKE = 23,
	MOSQ_ERR_QOS_NOT_SUPPORTED = 24,
	MOSQ_ERR_OVERSIZE_PACKET = 25,
	MOSQ_ERR_OCSP = 26,
};

/* Option values */
enum mosq_opt_t {
	MOSQ_OPT_PROTOCOL_VERSION = 1,
	MOSQ_OPT_SSL_CTX = 2,
	MOSQ_OPT_SSL_CTX_WITH_DEFAULTS = 3,
	MOSQ_OPT_RECEIVE_MAXIMUM = 4,
	MOSQ_OPT_SEND_MAXIMUM = 5,
	MOSQ_OPT_TLS_KEYFORM = 6,
	MOSQ_OPT_TLS_ENGINE = 7,
	MOSQ_OPT_TLS_ENGINE_KPASS_SHA1 = 8,
	MOSQ_OPT_TLS_OCSP_REQUIRED = 9,
	MOSQ_OPT_TLS_ALPN = 10,
};




struct mosquitto_message{
	int mid;
	char *topic;
	void *payload;
	int payloadlen;
	int qos;
	bool retain;
};

struct mosquitto;
typedef struct mqtt5__property mosquitto_property;


libmosq_EXPORT int mosquitto_lib_version(int *major, int *minor, int *revision);


libmosq_EXPORT int mosquitto_lib_init(void);


libmosq_EXPORT int mosquitto_lib_cleanup(void);



libmosq_EXPORT struct mosquitto *mosquitto_new(const char *id, bool clean_session, void *obj);


libmosq_EXPORT void mosquitto_destroy(struct mosquitto *mosq);


libmosq_EXPORT int mosquitto_reinitialise(struct mosquitto *mosq, const char *id, bool clean_session, void *obj);



libmosq_EXPORT int mosquitto_will_set(struct mosquitto *mosq, const char *topic, int payloadlen, const void *payload, int qos, bool retain);


libmosq_EXPORT int mosquitto_will_set_v5(struct mosquitto *mosq, const char *topic, int payloadlen, const void *payload, int qos, bool retain, mosquitto_property *properties);


libmosq_EXPORT int mosquitto_will_clear(struct mosquitto *mosq);



libmosq_EXPORT int mosquitto_username_pw_set(struct mosquitto *mosq, const char *username, const char *password);



libmosq_EXPORT int mosquitto_connect(struct mosquitto *mosq, const char *host, int port, int keepalive);


libmosq_EXPORT int mosquitto_connect_bind(struct mosquitto *mosq, const char *host, int port, int keepalive, const char *bind_address);


libmosq_EXPORT int mosquitto_connect_bind_v5(struct mosquitto *mosq, const char *host, int port, int keepalive, const char *bind_address, const mosquitto_property *properties);


libmosq_EXPORT int mosquitto_connect_async(struct mosquitto *mosq, const char *host, int port, int keepalive);


libmosq_EXPORT int mosquitto_connect_bind_async(struct mosquitto *mosq, const char *host, int port, int keepalive, const char *bind_address);


libmosq_EXPORT int mosquitto_connect_srv(struct mosquitto *mosq, const char *host, int keepalive, const char *bind_address);


libmosq_EXPORT int mosquitto_reconnect(struct mosquitto *mosq);


libmosq_EXPORT int mosquitto_reconnect_async(struct mosquitto *mosq);


libmosq_EXPORT int mosquitto_disconnect(struct mosquitto *mosq);


libmosq_EXPORT int mosquitto_disconnect_v5(struct mosquitto *mosq, int reason_code, const mosquitto_property *properties);



libmosq_EXPORT int mosquitto_publish(struct mosquitto *mosq, int *mid, const char *topic, int payloadlen, const void *payload, int qos, bool retain);



libmosq_EXPORT int mosquitto_publish_v5(
		struct mosquitto *mosq,
		int *mid,
		const char *topic,
		int payloadlen,
		const void *payload,
		int qos,
		bool retain,
		const mosquitto_property *properties);



libmosq_EXPORT int mosquitto_subscribe(struct mosquitto *mosq, int *mid, const char *sub, int qos);


libmosq_EXPORT int mosquitto_subscribe_v5(struct mosquitto *mosq, int *mid, const char *sub, int qos, int options, const mosquitto_property *properties);


libmosq_EXPORT int mosquitto_subscribe_multiple(struct mosquitto *mosq, int *mid, int sub_count, char *const *const sub, int qos, int options, const mosquitto_property *properties);


libmosq_EXPORT int mosquitto_unsubscribe(struct mosquitto *mosq, int *mid, const char *sub);


libmosq_EXPORT int mosquitto_unsubscribe_v5(struct mosquitto *mosq, int *mid, const char *sub, const mosquitto_property *properties);


libmosq_EXPORT int mosquitto_unsubscribe_multiple(struct mosquitto *mosq, int *mid, int sub_count, char *const *const sub, const mosquitto_property *properties);



libmosq_EXPORT int mosquitto_message_copy(struct mosquitto_message *dst, const struct mosquitto_message *src);


libmosq_EXPORT void mosquitto_message_free(struct mosquitto_message **message);


libmosq_EXPORT void mosquitto_message_free_contents(struct mosquitto_message *message);



libmosq_EXPORT int mosquitto_loop_forever(struct mosquitto *mosq, int timeout, int max_packets);


libmosq_EXPORT int mosquitto_loop_start(struct mosquitto *mosq);


libmosq_EXPORT int mosquitto_loop_stop(struct mosquitto *mosq, bool force);


libmosq_EXPORT int mosquitto_loop(struct mosquitto *mosq, int timeout, int max_packets);


libmosq_EXPORT int mosquitto_loop_read(struct mosquitto *mosq, int max_packets);


libmosq_EXPORT int mosquitto_loop_write(struct mosquitto *mosq, int max_packets);


libmosq_EXPORT int mosquitto_loop_misc(struct mosquitto *mosq);



libmosq_EXPORT int mosquitto_socket(struct mosquitto *mosq);


libmosq_EXPORT bool mosquitto_want_write(struct mosquitto *mosq);


libmosq_EXPORT int mosquitto_threaded_set(struct mosquitto *mosq, bool threaded);



libmosq_EXPORT int mosquitto_opts_set(struct mosquitto *mosq, enum mosq_opt_t option, void *value);


libmosq_EXPORT int mosquitto_int_option(struct mosquitto *mosq, enum mosq_opt_t option, int value);



libmosq_EXPORT int mosquitto_void_option(struct mosquitto *mosq, enum mosq_opt_t option, void *value);



libmosq_EXPORT int mosquitto_reconnect_delay_set(struct mosquitto *mosq, unsigned int reconnect_delay, unsigned int reconnect_delay_max, bool reconnect_exponential_backoff);


libmosq_EXPORT int mosquitto_max_inflight_messages_set(struct mosquitto *mosq, unsigned int max_inflight_messages);


libmosq_EXPORT void mosquitto_message_retry_set(struct mosquitto *mosq, unsigned int message_retry);


libmosq_EXPORT void mosquitto_user_data_set(struct mosquitto *mosq, void *obj);


libmosq_EXPORT void *mosquitto_userdata(struct mosquitto *mosq);



libmosq_EXPORT int mosquitto_tls_set(struct mosquitto *mosq,
		const char *cafile, const char *capath,
		const char *certfile, const char *keyfile,
		int (*pw_callback)(char *buf, int size, int rwflag, void *userdata));


libmosq_EXPORT int mosquitto_tls_insecure_set(struct mosquitto *mosq, bool value);


libmosq_EXPORT int mosquitto_tls_opts_set(struct mosquitto *mosq, int cert_reqs, const char *tls_version, const char *ciphers);


libmosq_EXPORT int mosquitto_tls_psk_set(struct mosquitto *mosq, const char *psk, const char *identity, const char *ciphers);



libmosq_EXPORT void mosquitto_connect_callback_set(struct mosquitto *mosq, void (*on_connect)(struct mosquitto *, void *, int));


libmosq_EXPORT void mosquitto_connect_with_flags_callback_set(struct mosquitto *mosq, void (*on_connect)(struct mosquitto *, void *, int, int));


libmosq_EXPORT void mosquitto_connect_v5_callback_set(struct mosquitto *mosq, void (*on_connect)(struct mosquitto *, void *, int, int, const mosquitto_property *props));


libmosq_EXPORT void mosquitto_disconnect_callback_set(struct mosquitto *mosq, void (*on_disconnect)(struct mosquitto *, void *, int));


libmosq_EXPORT void mosquitto_disconnect_v5_callback_set(struct mosquitto *mosq, void (*on_disconnect)(struct mosquitto *, void *, int, const mosquitto_property *));


libmosq_EXPORT void mosquitto_publish_callback_set(struct mosquitto *mosq, void (*on_publish)(struct mosquitto *, void *, int));


libmosq_EXPORT void mosquitto_publish_v5_callback_set(struct mosquitto *mosq, void (*on_publish)(struct mosquitto *, void *, int, int, const mosquitto_property *));


libmosq_EXPORT void mosquitto_message_callback_set(struct mosquitto *mosq, void (*on_message)(struct mosquitto *, void *, const struct mosquitto_message *));


libmosq_EXPORT void mosquitto_message_v5_callback_set(struct mosquitto *mosq, void (*on_message)(struct mosquitto *, void *, const struct mosquitto_message *, const mosquitto_property *));


libmosq_EXPORT void mosquitto_subscribe_callback_set(struct mosquitto *mosq, void (*on_subscribe)(struct mosquitto *, void *, int, int, const int *));


libmosq_EXPORT void mosquitto_subscribe_v5_callback_set(struct mosquitto *mosq, void (*on_subscribe)(struct mosquitto *, void *, int, int, const int *, const mosquitto_property *));


libmosq_EXPORT void mosquitto_unsubscribe_callback_set(struct mosquitto *mosq, void (*on_unsubscribe)(struct mosquitto *, void *, int));


libmosq_EXPORT void mosquitto_unsubscribe_v5_callback_set(struct mosquitto *mosq, void (*on_unsubscribe)(struct mosquitto *, void *, int, const mosquitto_property *));


libmosq_EXPORT void mosquitto_log_callback_set(struct mosquitto *mosq, void (*on_log)(struct mosquitto *, void *, int, const char *));


libmosq_EXPORT int mosquitto_string_option(struct mosquitto *mosq, enum mosq_opt_t option, const char *value);



libmosq_EXPORT int mosquitto_reconnect_delay_set(struct mosquitto *mosq, unsigned int reconnect_delay, unsigned int reconnect_delay_max, bool reconnect_exponential_backoff);



libmosq_EXPORT int mosquitto_socks5_set(struct mosquitto *mosq, const char *host, int port, const char *username, const char *password);



libmosq_EXPORT const char *mosquitto_strerror(int mosq_errno);


libmosq_EXPORT const char *mosquitto_connack_string(int connack_code);


libmosq_EXPORT const char *mosquitto_reason_string(int reason_code);


libmosq_EXPORT int mosquitto_string_to_command(const char *str, int *cmd);


libmosq_EXPORT int mosquitto_sub_topic_tokenise(const char *subtopic, char ***topics, int *count);


libmosq_EXPORT int mosquitto_sub_topic_tokens_free(char ***topics, int count);


libmosq_EXPORT int mosquitto_topic_matches_sub(const char *sub, const char *topic, bool *result);



libmosq_EXPORT int mosquitto_topic_matches_sub2(const char *sub, size_t sublen, const char *topic, size_t topiclen, bool *result);


libmosq_EXPORT int mosquitto_pub_topic_check(const char *topic);


libmosq_EXPORT int mosquitto_pub_topic_check2(const char *topic, size_t topiclen);


libmosq_EXPORT int mosquitto_sub_topic_check(const char *topic);


libmosq_EXPORT int mosquitto_sub_topic_check2(const char *topic, size_t topiclen);



libmosq_EXPORT int mosquitto_validate_utf8(const char *str, int len);




struct libmosquitto_will {
	char *topic;
	void *payload;
	int payloadlen;
	int qos;
	bool retain;
};

struct libmosquitto_auth {
	char *username;
	char *password;
};

struct libmosquitto_tls {
	char *cafile;
	char *capath;
	char *certfile;
	char *keyfile;
	char *ciphers;
	char *tls_version;
	int (*pw_callback)(char *buf, int size, int rwflag, void *userdata);
	int cert_reqs;
};


libmosq_EXPORT int mosquitto_subscribe_simple(
		struct mosquitto_message **messages,
		int msg_count,
		bool want_retained,
		const char *topic,
		int qos,
		const char *host,
		int port,
		const char *client_id,
		int keepalive,
		bool clean_session,
		const char *username,
		const char *password,
		const struct libmosquitto_will *will,
		const struct libmosquitto_tls *tls);



libmosq_EXPORT int mosquitto_subscribe_callback(
		int (*callback)(struct mosquitto *, void *, const struct mosquitto_message *),
		void *userdata,
		const char *topic,
		int qos,
		const char *host,
		int port,
		const char *client_id,
		int keepalive,
		bool clean_session,
		const char *username,
		const char *password,
		const struct libmosquitto_will *will,
		const struct libmosquitto_tls *tls);



libmosq_EXPORT int mosquitto_property_add_byte(mosquitto_property **proplist, int identifier, uint8_t value);


libmosq_EXPORT int mosquitto_property_add_int16(mosquitto_property **proplist, int identifier, uint16_t value);


libmosq_EXPORT int mosquitto_property_add_int32(mosquitto_property **proplist, int identifier, uint32_t value);


libmosq_EXPORT int mosquitto_property_add_varint(mosquitto_property **proplist, int identifier, uint32_t value);


libmosq_EXPORT int mosquitto_property_add_binary(mosquitto_property **proplist, int identifier, const void *value, uint16_t len);


libmosq_EXPORT int mosquitto_property_add_string(mosquitto_property **proplist, int identifier, const char *value);


libmosq_EXPORT int mosquitto_property_add_string_pair(mosquitto_property **proplist, int identifier, const char *name, const char *value);


libmosq_EXPORT const mosquitto_property *mosquitto_property_read_byte(
		const mosquitto_property *proplist,
		int identifier,
		uint8_t *value,
		bool skip_first);


libmosq_EXPORT const mosquitto_property *mosquitto_property_read_int16(
		const mosquitto_property *proplist,
		int identifier,
		uint16_t *value,
		bool skip_first);


libmosq_EXPORT const mosquitto_property *mosquitto_property_read_int32(
		const mosquitto_property *proplist,
		int identifier,
		uint32_t *value,
		bool skip_first);


libmosq_EXPORT const mosquitto_property *mosquitto_property_read_varint(
		const mosquitto_property *proplist,
		int identifier,
		uint32_t *value,
		bool skip_first);


libmosq_EXPORT const mosquitto_property *mosquitto_property_read_binary(
		const mosquitto_property *proplist,
		int identifier,
		void **value,
		uint16_t *len,
		bool skip_first);


libmosq_EXPORT const mosquitto_property *mosquitto_property_read_string(
		const mosquitto_property *proplist,
		int identifier,
		char **value,
		bool skip_first);


libmosq_EXPORT const mosquitto_property *mosquitto_property_read_string_pair(
		const mosquitto_property *proplist,
		int identifier,
		char **name,
		char **value,
		bool skip_first);


libmosq_EXPORT void mosquitto_property_free_all(mosquitto_property **properties);


libmosq_EXPORT int mosquitto_property_copy_all(mosquitto_property **dest, const mosquitto_property *src);


libmosq_EXPORT int mosquitto_property_check_command(int command, int identifier);



libmosq_EXPORT int mosquitto_property_check_all(int command, const mosquitto_property *properties);


libmosq_EXPORT int mosquitto_string_to_property_info(const char *propname, int *identifier, int *type);


#ifdef __cplusplus
}
#endif

#endif
