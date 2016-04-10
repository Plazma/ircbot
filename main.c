#include <stdio.h>
#include <stdlib.h>
#include <libircclient.h>
#include <libirc_rfcnumeric.h>
#include <glib.h>
#include <glib/gstring.h>
#include <glib/gprintf.h>
#include <string.h>

void on_connect(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count)
{
    //placeholder
}


void event_numeric(irc_session_t *session, unsigned int event, const char *origin, const char **params, unsigned int count)
{
    //placeholder
}

irc_callbacks_t callbacks;

memset( &callbacks, 0 sizeof(callbacks) );

callbacks.event_connect = on_connect;
callbacks.event_numeric = event_numeric;

irc_session_t *session = irc_create_session( &callbacks );

if(!session) {
    g_printf("\n\n*** CANNOT CONNECT TO SESSION ***\n\n");
    exit(1);
 }






