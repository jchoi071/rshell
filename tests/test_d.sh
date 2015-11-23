cd ..
cd bin
./rshell <<EOF
touch somefile
mkdir somedir
echo Test with -d
test -d somefile || echo This will display if input is not a directory
test -d somedir && echo This will display if input is a directory
echo [] with -d
[ -d somefile ] || echo This will display if input is not a directory 
[ -d somedir ] && echo This will display if input is a directory
EOF
