cd ..
cd bin
./rshell <<EOF
echo Test with wrong flag
touch somefile
test -a somefile
test -g somefile
echo Test with no file
test -e
test -f
test -d
echo [] with wrong flag
[ -a somefile ]
[ -g somefile ]
echo [] with no file
[ -e ]
[ -f ]
[ -d ]
echo Bad [] syntax
[-e somefile]
[ -e somefile
[ -e somefile]

EOF
