#include <stdio.h>
#include <stdlib.h>
#include <libircclient.h>
#include <libirc_rfcnumeric.h>
#include <glib.h>
#include <glib/gstring.h>
#include <glib/gprintf.h>
#include <string.h>

// move to utils.c and make smarter.
int wordCount (const char *string)
{
    int i = 0;
    int wc = 0;

    for(i=0; string[i] != '\0'; i++)
    {
        if(string[i] == ' ')
            wc++;
    }

    return wc;

}

void on_connect(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count)
{
    // Code to display connecting to server
    g_printf("Connected to %s!\n", origin);
    
}


void event_numeric(irc_session_t *session, unsigned int event, const char *origin, const char **params, unsigned int count)
{
    //place
    //holder
}

void on_join(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count)
{
     //placeholder
     g_printf("< %s > has joined %s.\n", origin, params[0]);
}

void event_channel(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count)
{
    // params[0][0] = Channel
    // params[0][1] = user message
    // origin = nick who sent it
    
    g_printf("< %s > %s\n", origin, params[1] );

    //parseMsg(params[11]);

    int wordNum = wordCount(params[1]);
    int i = 0;

    for(i = 0; i<wordNum; i++)
    {
         // compare words in string, to see if it matches
         if(strcmp("fuck", params[wordNum]) == 0)
         {
              irc_cmd_msg(session, params[0], "Watch your fucking mouth!\n");
         }
    } 
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

    if(irc_is_connected(session) )
        irc_cmd_join(session, "##plazma", NULL);

    //Event Loop Start
    if(irc_run(session) )
    {
        // handle errors
    }


}






