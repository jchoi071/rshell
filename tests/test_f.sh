cd ..
cd bin
./rshell <<EOF
touch somefile
mkdir somedir
echo Test with -f
test -f somefile && echo This will display if input is a file
test -f somedir || echo This will display if input is not a file
echo [] with -f
[ -f somefile ] && echo This will display if input is a file
[ -f somedir ] || echo This will display if input is not a file
EOF
