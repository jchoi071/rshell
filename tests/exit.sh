#!/bin/sh

cd ..
cd bin
./rshell <<"End"
exit
End

./rshell <<"End2"
echo something
echo another thing
exit
End2

./rshell <<"End3"
echo something
jnsdkf
iejnsdkf
jnskdf
exit
exit
exit
End3
