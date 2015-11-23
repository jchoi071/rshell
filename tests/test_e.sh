cd ..
cd bin
./rshell <<EOF
touch somefile
mkdir somedir
echo Test without -e
test somefile && echo Exists
test somedir && echo Exists
test ajosdk || echo Does not exist
echo Test with -e
test -e somefile && echo Exists
test -e somedir && echo Exists
test -e ajosdk || echo Does not exist
echo [] without -e
[ somefile ] && echo Exists
[ somedir ] && echo Exists
[ ajosdk ] || echo Does not exist
echo [] with -e
[ -e somefile ] && echo Exists
[ -e somedir ] && echo Exists
[ -e ajosdk ] || echo Does not exist
rm somefile
rmdir somedir
EOF
