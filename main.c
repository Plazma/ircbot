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
    // Code to display connecting to server
    g_printf("Connected to %s!\n", origin);
    irc_cmd_join(session, "##plazma", NULL);
}


void event_numeric(irc_session_t *session, unsigned int event, const char *origin, const char **params, unsigned int count)
{
    //placeholder
}

void dump_event(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count)
{
    char buf[512];
    int cnt = 0;

    buf[0] = '\0';

    for(cnt=0; cnt<count; cnt++)
    {
        if(cnt)
            strcat(buf, "|");

        strcat(buf, params[cnt]);
    }
}

void on_join(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count)
{
    g_printf("< %s > joined channel: %s\n", origin, params[0]);
}

void event_channel(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count)
{
    // params[0][0] = Channel
    // params[0][1] = user message
    // origin = nick who sent it
    
    g_printf("< %s > %s\n", origin, params[1] );
    
}

int main(void)
{
    irc_callbacks_t callbacks;

    memset( &callbacks, 0, sizeof(callbacks) );

    callbacks.event_connect = on_connect;
    callbacks.event_numeric = event_numeric;
    callbacks.event_join = on_join;
    callbacks.event_channel = event_channel;

    irc_session_t *session = irc_create_session( &callbacks );

    if(!session)
    {
        g_printf("\n\n*** CANNOT CONNECT TO IRC SESSION ***\n\n");
        exit(1);
    }

    g_printf("Connecting to server...\n");
    
    if(irc_connect (session, "chat.freenode.net", 6667, 0, "Fanger", "Fanger", "Fanger"))
    {
        // handle errors
    }

    if(irc_run(session) )
    {
        // handle errors
    }

    
    // say stuff
    // do coller things like prase messages

}






