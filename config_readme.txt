# This is a example comment
#
# Defining values:
#
# Values must be defined as follows:
# OPTION=VALUE
# OPTION = VALUE or OPTION= VALUE, etc are invalid syntax and will cause errors/SEGFAULTS
#
# Each value must be terminated with a '%'
# OPTION=VALUE%
#
# Available options:
#
# WINEPREFIX_DXVK=/your/path/here%
# WINEPREFIX_VAN=/your/path/here%
# WINEPATH=/your/path/here%
# WINEDLLOVERRIDES="foo.dll=n,b"%
# 
# FIRST_SLASHCHECK_GAMENAME=positive_integer_value_here%
# LAST_SLASHCHECK_GAMENAME=positive_integer_value_here%
#
# START_EXEC=your_command_here%
# END_EXEC=your_command_here%
#
# CUSTOM_START_EXEC_indexnohere=your_command_here%
# CUSTOM_END_EXEC_indexnohere=your_command_here%
#
# NOTE---- While creating a config.txt file in the same folder as the wrapper, make sure to 
#          save the option definitions IN THE EXACT SAME ORDER AS ABOVE !
#-----------------------------------------------------------------------------------------------
#
# Some options are explained below while others are self explanatory:
#
# FIRST_SLASHCHECK_GAMENAME and LAST_SLASHCHECK_GAMENAME define a number of slashes after/before which a game directory's name is found in its absolute path as defined in gamelist.txt
# for /home/fooninja/foo.game, FIRST_SLASHCHECK_GAMENAME=2%, LAST_SLASHCHECK_GAMENAME=3%
# since the game directory name which is assumed to be the gamename, lies between the 2nd slash and the 3rd slash.
# The directory name convention described above must hold true for all entries in gamelist.txt for the wrapper to function sanely.
#
# START_EXEC defines a custom command which is run before launching the game, and vice-versa for END_EXEC. These two commands are run globally for each game.
# Multiple commands can be chained together with shell control operators like:
# START_EXEC=command1 && command2% or vice-versa for END_EXEC
# But the last command must not be terminated with a shell control operator(see man page for bash for more details). It must only be terminated with a '%'
#
# CUSTOM_START_EXEC_indexnohere is same as START_EXEC but for a certain game, and is run after START_EXEC
# CUSTOM_END_EXEC_indexnohere is similar to CUSTOM_START_EXEC, but is run before END_EXEC
# indexnohere refers to the index number which is assigned to the entries/games in gamelist.txt upon runtime and are used to select them for execution.
# To obtain the index number for a certain game for CUSTOM_START_EXEC,etc, run the wrapper first, and note the index numbers displayed beside the gamename(game directory name)
# For a game with index number 8, the custom option would be CUSTOM_START_EXEC_8=command% or CUSTOM_END_EXEC_8=command%
# Defining these custom parameters: CUSTOM_START_EXEC_indexnohere or CUSTOM_END_EXEC_indexnohere is purely optional and they can be omitted.
#------------------------------------------------------------------------------------------------
#
# Disabling options:
# Not all options can be disabled, options that are compulsory to be defined but can be disabled are as follows:
#
# WINEDLLOVERRIDES=%
# START_EXEC=%
# END_EXEC=%
# 
# By putting the '%' just after '='
#
# NOTE---- While creating a config.txt file in the same folder as the wrapper, make sure to save the 
#          option definitions IN THE EXACT SAME ORDER AS DESCRIBED IN THE SECTION "Available Options" above!
#
#
# END OF README----------------------------------------------------------------



 
