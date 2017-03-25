/*
 * Copyright (c) 2015 Sunil Nimmagadda <sunil@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/param.h>
#include <sys/types.h>

#include <netdb.h>
#include <stdarg.h>
#include <stdio.h>

#include "compat.h"

#define MAX_LINE	4096
#define TMPBUF_LEN	131072

#define	S_HTTP	0
#define S_HTTPS	1
#define S_FTP	2
#define S_FILE	3

enum {
	IMSG_STAT,
	IMSG_OPEN
};

struct tls;
struct imsg;
struct imsgbuf;

struct url {
	char		 host[MAXHOSTNAMELEN+1];
	char		 port[NI_MAXSERV];
	char		 basic_auth[BUFSIZ];
	const char	*fname;
	const char	*path;
	off_t		 file_sz;
	off_t		 offset;
	int		 scheme;
};

struct open_req {
	char	fname[FILENAME_MAX];
	int	flags;
};

/* file.c */
void	file_connect(struct imsgbuf *, struct imsg *, struct url *);
void	file_request(struct imsgbuf *, struct imsg *, struct url *);
void	file_save(struct url *, int);

/* ftp.c */
void	ftp_connect(struct url *, int);
void	ftp_get(struct url *);
void	ftp_quit(struct url *);
void	ftp_save(struct url *, int);

/* http.c */
void	http_connect(struct url *, int);
void	http_get(struct url *);
void	http_save(struct url *, int);
void	https_init(void);

/* io.c */
ssize_t	buffer_drain(int);
ssize_t	readline(int, void *, size_t);
ssize_t	writeline(int, const char *, ...)
	    __attribute__((__format__ (printf, 2, 3)))
	    __attribute__((__nonnull__ (2)));
ssize_t	vwriteline(int, const char *, va_list);
ssize_t	tls_readline(struct tls *, char *, size_t);
ssize_t	tls_vwriteline(struct tls *, const char *, va_list);

/* main.c */
extern const char	*scheme_str[];
extern char		 tmp_buf[TMPBUF_LEN];
extern char		*tls_options;
extern const char	*ua;
extern const char	*title;
extern struct url	*proxy;
extern int		 http_debug;
extern int		 progressmeter;
extern int		 verbose;

void	url_parse(struct url *, const char *);

/* progressmeter.c */
void	start_progress_meter(const char *, off_t, off_t *);
void	stop_progress_meter(void);

/* util.c */
char	*url_encode(const char *);
int	 tcp_connect(const char *, const char *, int);
void	 proxy_connect(struct url *, int);
char	*xstrdup(const char *, const char *);
off_t	 stat_request(struct imsgbuf *, struct imsg *, const char *, int *);
int	 fd_request(struct imsgbuf *, struct imsg *, const char *, int);
int	 read_message(struct imsgbuf *, struct imsg *);
void	 send_message(struct imsgbuf *, int, uint32_t, void *, size_t, int);
void	 log_info(const char *, ...)
	    __attribute__((__format__ (printf, 1, 2)))
	    __attribute__((__nonnull__ (1)));
void	 log_request(struct url *, const char *);
