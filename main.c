#include <stdio.h>
#include <stdlib.h>
#include <libircclient.h>
#include <libirc_rfcnumeric.h>
#include <glib.h>
#include <glib/gstring.h>
#include <glib/gprintf.h>
#include <string.h>

void consolePrint(const char **string)
{

}

// move to utils.c and make smarter.
int wordCount (const char *string)
{
    int i = 0;
    int wc = 0;

    for(i=0;  string[i] != '\0'; i++)
    {
        if(string[i] == ' ')
            wc++;
    }

    // libircclient indexes at 1, so add one to keep in alignment with what libircclient expects
    return wc;

}

int parseWord(const char *word)
{
     if(word == NULL)
          return -1;
     
     const char *nonoWords[] = {"fuck", "shit", "nigger", "kike"};
    
     int sz_nonoWords = (sizeof(nonoWords) / sizeof(const char *));

     int i = 0;

     for(i = 0; i<sz_nonoWords; i++)
     {
          if(strcmp(nonoWords[i], word) == 0)
          {
               
               return 1;
          }
     }   

     return 0;
}

int parseCmd(const char *nick, const char *cmd)
{
     if(nick == NULL || cmd == NULL)
          return -1;
     
     int i = 0;
     int authorized = 0;
     const char *cmdptr;
     
     const char *authUsers = {"plazma"};
     size_t sz_authUsers = (sizeof(authUsers) / sizeof (const char *));
                            
     const char *commands = {"quit", "bacon", "beer", "stab", "dickpunch", "cuntstab"};
     size_t sz_commands = (sizeof(commands) / sizeof(const char *));
     char nickbuf[128];

     //check for authoirzed users
     for(i=0; i<sz_authUsers; i++)
     {
          // See if user is authorized
          if(!strcmp(authUsers[i], nick))
          {
               authorized = 1;
               break;
          }
             
     }

     // first character of command should be @
     if(cmd[0] != '@')
          return -1;

     cmdptr = cmd[1];

     // get cmdptr to the end of the word starting after the @
     for(cmdptr = cmd[1]; cmdptr != '\0'; cmdptr++)
          ;;

     // go through commands
     for(i=0; i<sz_commands; i++)
     {
          // it's a valid command
          if(strcmp(commands[i], cmdptr) == 0)
          {
               
              if(strcmp(cmdptr, "quit") == 0 && authorized == 1)
              {
               // command to display bye
               // command to quit
              }
              else if(strcmp(cmdptr, "quit") == 0 && authorized == 0)
              {
               // command to display fuck you not authorized
              }
              else if(strcmp(cmdptr, "beer") == 0)
              {
                   // display command to console
                   // irc send cmd gives "user" a beer"
              }
                                
          }
          
     }

     
     
}
  


void on_connect(irc_session_t *session, const char *event, const char *origin, const char **params, unsigned int count)
{
    // Code to display connecting to server
    g_printf("Connected to %s!\n", origin);
    irc_cmd_join(session, "##plazma", 0);
    g_printf("Joining channel ##plazma\n");

    
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

    int wc = wordCount(params[1]);
    int i = 0;

    //ptr to current word 
    const char *paramptr;
    const char *cw;
    char nickbuf[129];

    // Get nick into nickbuf
    irc_target_get_nick(origin, nickbuf, 128);

    paramptr = params[1];

    // outer loop for how many words there are
    for(i=0; i<=wc; i++)
    {
         // Inner loop to get one word at a time
         for(cw = paramptr; *paramptr != ' '; paramptr++)
              ;

         // It either matches or it deosnt'
         if(parseWord(cw))
         {
              g_printf("<ME>: Watch your fucking mouth!\n");
              irc_cmd_msg(session, params[0], "Watch your fucking mouth!\n");
              break;
         }
         
         // move on to next word
         paramptr++;
         
    }
    g_printf("<%s>: %s\n", nickbuf, params[1] );

  
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
    
    if(irc_connect (session, "adams.freenode.net", 6667, 0, "Fanger", "Fanger", "Fanger"))
    {
        // handle errors
    }

   
    //Event Loop Start
    if(irc_run(session) )
    {
        // handle errors
    }


}






