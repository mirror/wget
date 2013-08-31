import platform
from os import getenv

T_COLORS = {
   'PURPLE' : '\033[95m',
   'BLUE'   : '\033[94m',
   'GREEN'  : '\033[92m',
   'YELLOW' : '\033[93m',
   'RED'   : '\033[91m',
   'ENDC'   : '\033[0m'
}

def printer (color, string):
   if platform.system () == 'Linux':
      if getenv ("MAKE_CHECK", "False") == "True":
         print (string)
      else:
         print (T_COLORS.get (color) + string + T_COLORS.get ('ENDC'))

   else:
      print (string)

# vim: set ts=8 sw=3 tw=0 et :
