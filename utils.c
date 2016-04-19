#include "utils.h"

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
}{
    // params[0][0] = Channel
    // params[0][1] = user message
    // origin = nick who sent it
    
    g_printf("< %s > %s\n", origin, params[1] );
    
}
