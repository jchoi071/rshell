#!/bin/sh

cd ..
cd bin
./rshell <<"End"
echo wejoksdf jnsidfk isjdnkfms dsjinfk #This shouldn't show up
#Neither should this
#############################
#exit
echo But this should #jskfd
End
