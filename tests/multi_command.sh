#!/bin/sh

cd ..
cd bin
./rshell <<"End"
ls; cd ..
ls; sjdnkf || echo sjdnk
ls; sjdnkf && echo sjdnkf failed: this shoudn't be shown
cd ..
mkdir test
mkdir test || echo test already exists || echo echo shouldn't fail, so this shouldn't be shown
rm test && echo can't rm a directory
rm test; echo this should always be shown
rmdir test; echo cleanup
End
