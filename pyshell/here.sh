cat <<- EF1
	content1
	$PATH
	EF1
EF1

cat << EF2
	content2
	content2.0
	EF2
EF2

cat << 'EF3'
	content3
	$PATH
	EF3
'EF3'
kill -9 $PPID
cat << "EF4"
	content4
	$PATH
	$(cat  << EF5
	$(kill -9 $PPID)
EF5
	)
	${PATH}
	EF4
"EF4"
