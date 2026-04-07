#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

int rangestrcpy (char *r, int x, int y, char *d){                            //// COPY n-th ELEMENT FROM A STRING TO ANOTHER, NOT MEMORY SAFE

 int accel  = 0;
 while (x <= y ){
  d[accel] = *(r + x);

  accel++;
  x++;	
 }

 d[accel] = '\0';
 return 0;
	
}

int readtonewline (char *c, FILE *t){                                        //// READ TO END OF LINE IN A FILE STREAM

 while (*c != '\n'){
 *c = fgetc(t);	
 }
 *c = fgetc(t);
 return 0;
	
}

int readcharnext (char *c, FILE *t){                                         //// READ TO NEXT CHARACTER IN A FILE STREAM
 *c = fgetc(t);
 return 0;	
}


///////////////////////////////////////////////////////////////

int main () {
  
/////////////// FILE PARSING /////////////////////////////////

/////////////// CONFIG.TXT ///////////////////////////////////
 FILE *config =  fopen("config.txt" , "r");

 if (config == NULL){
  printf("Failed to open config.txt! Exiting\n");
  return 1;	
 }
 
 char c = fgetc(config);
 int elementno_conf = 0;
 
 while (c != EOF){

   if (c == 'F' || c == 'L' || c == 'S' || c == 'E' || c == 'W'|| c == 'C'){ //// COUNT VALID ENTRIES              
   elementno_conf++;
   readtonewline(&c, config);
   
  }else if (c == '#'){                                                       //// SKIP COMMENTS
   readtonewline(&c, config);
   	
  }else if (c == '\n' || c == ' '){                                          //// SKIP SPACES AND EMPTY LINES
   readcharnext(&c, config);
    	
  }
 } 

 char **configarray = calloc(elementno_conf, sizeof(char* ));
 rewind(config);
 c = fgetc(config);
 int accel = 0;

 while (c != EOF){
 int elementlen = 0;

  if (c == 'F' || c == 'L' || c == 'S' || c == 'E' || c == 'W' || c == 'C'){
   if (c == 'F' || c == 'L' || c == 'S' || c == 'E' || c == 'W'){           //// ONLY FOR 'F' 'L' 'S' 'E' and 'W' ENTRIES
    while (c != '='){;                                                      //// c = '=' AT END OF LOOP
    c = fgetc(config);

    }
    c = fgetc(config);                                                      //// c = CONSECUTIVE CHAR AFER '='

   } 

   while (c != '%'){
   elementlen++;                                                           
   c = fgetc(config);
    }

   elementlen++;                                                            //// elementlen NOW INCLUDES '%'

   if (elementlen == 1){                                                   //// CHECK FOR DISABLED OPTION(S) ONLY FOR 'F' 'L' 'S' 'E'
   configarray[accel] = "echo";
   	
  }else{                                                                   //// CHECK FOR ENABLED OPTION(S) ONLY FOR 'F' 'L' 'S' 'E'
   int posoffset = (0 - elementlen);                                           
   fseek(config, posoffset, SEEK_CUR);                                     //// MOVE FILE POSITION INDICATOR TO FIRST CHAR AFTER '=' OR TO THE START OF LINE
   configarray[accel] = calloc(elementlen, sizeof(char));
   fgets(configarray[accel], elementlen, config);
   	
   }

   accel++;
   readtonewline(&c, config);
   	  	
  }else if (c == '#'){                                                     
   readtonewline(&c, config);
   
  }else if (c == '\n' || c == ' '){                                        
   readcharnext(&c, config);	

  }else{
   printf("Typo detected in config! Exiting\n");
   return 1;
 	
  }

 }


 fclose(config);

///////////////////////////////////////////////////////////////

/////////////// GAMELIST.TXT /////////////////////////////////
 FILE *txt = fopen("gamelist.txt" , "r");
 if (txt == NULL){
  printf("failed to open gamelist.txt!\n");
  return 1;
 	
 }
 
 int elementno_gamelist = 0;
 c = fgetc(txt);

 while (c != EOF){

   if (c == '/'){
   elementno_gamelist++;
   readtonewline(&c, txt);

  }else if (c == '#'){
   readtonewline(&c, txt);
    	
  }else if (c == '\n' || c == ' '){
   readcharnext(&c, txt);
 	
  }
 }     

 char **gamelist = calloc(elementno_gamelist, sizeof(char*) );
 rewind(txt);
 c = fgetc(txt);
 accel = 0;

 while (c != EOF){
 int elementlen = 0;

   if (c == '/'){
    while (c != '%'){
    elementlen++;
    c = fgetc(txt);	

    }
   elementlen++;            
   gamelist[accel] = calloc(elementlen, sizeof(char) );
   int posoffset = (0 - elementlen);
   fseek(txt, posoffset, SEEK_CUR);                                             
   fgets( gamelist[accel], elementlen, txt);

   accel++;
   readtonewline(&c, txt);
   
  }else if (c == '#'){
   readtonewline(&c, txt);
  	
  }else if (c == '\n' || c == ' '){
   readcharnext(&c, txt);
  	
  }else{
   printf("Invalid gamelist! Typo! Exiting!\n");
   return 1;
        	
  }  
 }

 fclose(txt);
//////////////////////////////////////////////////////////////  

 int *last_slashpos = calloc(elementno_gamelist, sizeof(int) );
 int *last_charpos = calloc(elementno_gamelist, sizeof(int) );
 int net_elementno_gamelist = 0;
 int FIRST_SLASHCHECK_GAMENAME = atoi(configarray[4]);
 int LAST_SLASHCHECK_GAMENAME = atoi(configarray[5]); 

////////////////// PRINT GAMENAME ////////////////////////////  


  while (net_elementno_gamelist < elementno_gamelist){
   int slashno = 0;
   accel = 0;
   int name_first_charpos;
   int name_last_charpos;
      
   while ( *(gamelist[net_elementno_gamelist] + accel) != '\0'){
     if ( *(gamelist[net_elementno_gamelist] + accel) == '/'){
     slashno++;
     last_slashpos[net_elementno_gamelist] = accel;
      if (slashno == FIRST_SLASHCHECK_GAMENAME){
      name_first_charpos = (accel + 1);   
 
     }else if (slashno == LAST_SLASHCHECK_GAMENAME){
      name_last_charpos = (accel - 1);
               	
      }           	
    }else{
     last_charpos[net_elementno_gamelist] = accel;
  
    }
    accel++;

  }

  int namelen = ( (name_last_charpos - name_first_charpos) + 2);                 //// +1 FOR NULL TERMINATOR AND +1 FOR FIRST CHARACTER
  char *gamename = calloc(namelen, sizeof(char) );
  rangestrcpy(gamelist[net_elementno_gamelist], name_first_charpos, name_last_charpos, gamename);

  printf("-*%d. %s\n", net_elementno_gamelist, gamename);  
  net_elementno_gamelist++;
 }                                                                              //// net_elementno NOW EQUALS elementno_gamelist after end of LOOP

 net_elementno_gamelist--;                                                      //// net_elementno NOW EQUALS elementno_gamelist - 1
//////////////////////////////////////////////////////////////  
///////////////// TAKE USER INPUT ////////////////////////////

/////////////////GET PATH AND EXEC ///////////////////////////  

 char game_inputstr[5];
 printf("Enter game index no (0 to %d): ", net_elementno_gamelist );
 fgets(game_inputstr, 5, stdin); 
 int game_input = atoi(game_inputstr);
 
 if (game_input < 0 || game_input > net_elementno_gamelist ){
 	printf("invalid value!\n");
    return 1;
 }
 
 int  exec_first_charpos = (last_slashpos[game_input] + 1);
 int *exec_last_charpos  = &last_charpos[game_input];
 int  execlen = ( (*exec_last_charpos - exec_first_charpos) + 2);              //// +1 FOR NULL TERMINATOR AND +1 FOR FIRST CHARACTER
 char *exec = calloc(execlen, sizeof(char) );
 rangestrcpy(gamelist[game_input], exec_first_charpos, *exec_last_charpos, exec);

 int  path_last_charpos = (last_slashpos[game_input] - 1);
 int  pathlen = (last_slashpos[game_input] + 1); 
 char *path = calloc(pathlen, sizeof(char) );
 rangestrcpy(gamelist[game_input], 0, path_last_charpos, path);


//////////////////// GET PREFIX //////////////////////////////

 printf("Choose WINEPREFIX flavor:\n");
 printf("-*0. DXVK with WINEDLLOVERRIDES(Default)\n");
 printf("-*1. DXVK without WINEDLLOVERRIDES\n");
 printf("-*2. Vanilla with WINEDLLOVERRIDES\n");
 printf("-*3. Vanilla without WINEDLLOVERRIDES\n");
 printf("Enter flavor index no: ");

 char *prefix_inputstr = game_inputstr;
 fgets(prefix_inputstr, 5, stdin);
 int prefix_input = atoi(prefix_inputstr);

 if (prefix_input < 0 || prefix_input > 3){
 	 printf("invalid value!\n");
 	 return 1;
 }

//////////////////////////////////////////////////////////////  
////////// COMMAND ASSEMBLY AND EXECUTION ////////////////////  

 char *winevkprefix = configarray[0];                                            //// MAP ARRAY ELEMENTS TO CERTAIN POINTER VARIABLES(IMPROVES READIBILITY) 
 char *winevanprefix = configarray[1];
 char *winepath = configarray[2];
 char *winedll = configarray[3];
 char *startexec = configarray[6];
 char *endexec = configarray[7];


 accel = 8; 
 char placeholder[] = "echo";                                                    //// PLACEHOLDER VALUE IF NO CUSTOM CONFIGURATION IS FOUND
 char *custom_startexec = placeholder;
 char *custom_endexec = placeholder;
 int net_elementno_conf = (elementno_conf - 1);

 while (accel <= net_elementno_conf ){                                           //// CHECK FOR THE PRESENCE OF CUSTOM CONFIGURATION OPTIONS
 char indexcheck_str[5];
 int posoffset = 15;                                                             //// OFFSET FOR THE DETECTION OF INDEX NUMBER IN A CUSTOM CONFIGURATION DEFINITION

  while ( *(configarray[accel] + posoffset ) != '_' ){
  posoffset++;

  }
  posoffset++;
  int posoffset_prev = posoffset;
  while ( *(configarray[accel] + posoffset ) != '='){
  posoffset++;

  }
  rangestrcpy(configarray[accel], posoffset_prev, (posoffset-1), indexcheck_str);//// COPY INDEX NUMBER INTO indexcheck_str
  int indexcheck = atoi(indexcheck_str);                                         

  if (indexcheck == game_input){                                                 //// CHECK IF CUSTOM CONFIGURATION INDEX NO IS APPLICABLE TO SELECTED GAME
  posoffset++;
  posoffset_prev = posoffset;
   while (*(configarray[accel] + posoffset ) != '\0'){                           //// posoffset = '\0' AT END OF LOOP
   posoffset++;

   }
  posoffset--;                                                                   //// posoffset NOW EQUALS LAST CHAR BEFORE '\0'
 
  int len = ( (posoffset - posoffset_prev) + 2 );

    if ( *(configarray[accel] + 7) == 'S'){                                      //// CHECK IF CUSTOM CONFIGURATION IS FOR STARTEXEC
    custom_startexec = calloc(len, sizeof(char));
    rangestrcpy(configarray[accel], posoffset_prev, posoffset, custom_startexec);

   }else if ( *(configarray[accel] + 7) == 'E'){                                 //// CHECK IF CUSTOM CONFIGURATION IS FOR ENDEXEC
    custom_endexec = calloc(len, sizeof(char));
    rangestrcpy(configarray[accel], posoffset_prev, posoffset, custom_endexec);
   
    }
  }
  accel++;
	
 }
 
 size_t cmd_vk_dll_len = ( strlen(winevkprefix) + strlen(winepath) + strlen(winedll) + execlen + 3 + 11 + 17);     //// +3 FOR SPACE +1 FOR NULL TERMINATOR from execlen +17 FOR "WINEDLLOVERRIDES=" +11 FOR "WINEPREFIX="
 size_t cmd_vk_len = ( strlen(winevkprefix) + strlen(winepath) + execlen + 2 + 11);                                //// +2 FOR SPACE +1 FOR NULL TERMINATOR from execlen +11 FOR "WINEPREFIX="
 size_t cmd_van_dll_len = ( strlen(winevanprefix) + strlen(winepath) + strlen(winedll) + execlen + 3 + 11 + 17);   //// +3 FOR SPACE +1 FOR NULL TERMINATOR from execlen +17 FOR "WINEDLLOVERRIDES=" +11 FOR "WINEPREFIX="
 size_t cmd_van_len = ( strlen(winevanprefix) + strlen(winepath) + execlen + 2 + 11);                              //// +2 FOR SPACE +1 FOR NULL TERMINATOR from execlen +11 FOR "WINEPREFIX="

 size_t startexeclen = strlen(startexec);
 size_t endexeclen = strlen(endexec);
 size_t custom_startexeclen = strlen(custom_startexec);
 size_t custom_endexeclen = strlen(custom_endexec);

 size_t cmd_vk_dll_len_full = (startexeclen + 1 + 1 + custom_startexeclen + 1 + 1 + cmd_vk_dll_len + 1 + 1 + custom_endexeclen + 1 + 1 + endexeclen + 1);   //// +1 FOR ';' AND +1 FOR SPACE
 size_t cmd_vk_len_full = (startexeclen + 1 + 1 + custom_startexeclen + 1 + 1 + cmd_vk_len + 1 + 1 + custom_endexeclen + 1 + 1 + endexeclen + 1);           //// +1 FOR ';' AND +1 FOR SPACE
 size_t cmd_van_dll_len_full = (startexeclen + 1 + 1 + custom_startexeclen + 1 + 1 + cmd_van_dll_len + 1 + 1 + custom_endexeclen + 1 + 1 + endexeclen + 1); //// +1 FOR ';' AND +1 FOR SPACE
 size_t cmd_van_len_full = (startexeclen + 1 + 1 + custom_startexeclen + 1 + 1 + cmd_van_len + 1 + 1 + custom_endexeclen + 1 + 1 + endexeclen + 1);         //// +1 FOR ';' AND +1 FOR SPACE

 char **finalcmd = calloc(4, sizeof(char*) );
 finalcmd[0] = calloc(cmd_vk_dll_len_full, sizeof(char) );
 finalcmd[1] = calloc(cmd_vk_len_full, sizeof(char) );
 finalcmd[2] = calloc(cmd_van_dll_len_full, sizeof(char));
 finalcmd[3] = calloc(cmd_van_len_full, sizeof(char) );
             
 snprintf(finalcmd[0], cmd_vk_dll_len_full, "%s; %s; WINEDLLOVERRIDES=%s WINEPREFIX=%s %s %s; %s; %s&", startexec, custom_startexec, winedll, winevkprefix, winepath, exec, custom_endexec, endexec);  	
 snprintf(finalcmd[1], cmd_vk_len_full, "%s; %s; WINEPREFIX=%s %s %s; %s; %s&", startexec, custom_startexec, winevkprefix, winepath, exec, custom_endexec, endexec);

 snprintf(finalcmd[2], cmd_van_dll_len_full, "%s; %s; WINEDLLOVERRIDES=%s WINEPREFIX=%s %s %s; %s; %s&", startexec, custom_startexec, winedll, winevanprefix, winepath, exec, custom_endexec, endexec);
 snprintf(finalcmd[3], cmd_van_len_full, "%s; %s; WINEPREFIX=%s %s %s; %s; %s&", startexec, custom_startexec, winevanprefix, winepath, exec, custom_endexec, endexec);

 chdir(path);
 system(finalcmd[prefix_input]);

// printf("%s\n", winevkprefix); 
// printf("%s\n", winevanprefix);
// printf("%s\n", winedll);
// printf("%s\n", startexec);
// printf("%s\n", endexec);
// printf("%s\n", FIRST_SLASHCHECK_GAMENAME_STR);
// printf("%s\n", LAST_SLASHCHECK_GAMENAME_STR);
// printf("%d\n", FIRST_SLASHCHECK_GAMENAME);
// printf("%d\n", LAST_SLASHCHECK_GAMENAME);

// printf("%s\n", finalcmd[prefix_input]);

 return 0;
 
}
