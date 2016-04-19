#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstring.h>
#include <glib/gprintf.h>

void dump_event(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count);

