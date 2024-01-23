#ifndef HTTP_SERVER_DEMO_NGX_CODE_H
#define HTTP_SERVER_DEMO_NGX_CODE_H

#include <sys/types.h>
#include <stdint.h>

/* Type of Escape algorithms to be used */
#define NGX_ESCAPE_URI            (0)
#define NGX_ESCAPE_ARGS           (1)
#define NGX_ESCAPE_URI_COMPONENT  (2)
#define NGX_ESCAPE_HTML           (3)
#define NGX_ESCAPE_REFRESH        (4)
#define NGX_ESCAPE_MEMCACHED      (5)
#define NGX_ESCAPE_MAIL_AUTH      (6)

/* Type of Unescape algorithms to be used */
#define NGX_UNESCAPE_URI          (1)
#define NGX_UNESCAPE_REDIRECT     (2)

uintptr_t ngx_escape_uri(uint8_t *dst, uint8_t *src, size_t size, unsigned int type);
void ngx_unescape_uri(uint8_t **dst, uint8_t **src, size_t size, unsigned int type);

#endif