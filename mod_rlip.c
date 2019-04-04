#include "ap_release.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_vhost.h"
#include "apr_strings.h"

#include <ctype.h>

module AP_MODULE_DECLARE_DATA rlip_module;

/*

mod_rlip.c - (mode remote local IP) Apache2.4 module that
	fixes SERVER_ADDR, REMOTE_ADDR then web server
	is used as backend, behind reverse-proxy.

docs - https://ci.apache.org/projects/httpd/trunk/doxygen/group__APR__Util__Hook.html

for nginx when used as reverse proxy:
...
	proxy_hide_header X-Server-IP;
	proxy_set_header X-Server-IP $server_addr;

	proxy_hide_header X-Real-IP;
	proxy_set_header X-Real-IP $remote_addr;
...
*/

static int common_vars_override(request_rec *r) {

	const char *xServerIP, *xRealIP;
	xServerIP = apr_table_get(r->headers_in, "X-Server-IP");
	xRealIP = apr_table_get(r->headers_in, "X-Real-IP");

	if (xServerIP) {
		r->connection->local_ip = (char *)xServerIP;
	}

	if (xRealIP) {
		r->useragent_ip = (char *)xRealIP;
	}

	return DECLINED;
}

static void register_hooks(apr_pool_t *p) {
	ap_hook_post_read_request(common_vars_override, NULL, NULL, APR_HOOK_REALLY_FIRST);
}

module AP_MODULE_DECLARE_DATA rlip_module = {
	STANDARD20_MODULE_STUFF,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	register_hooks,
};
