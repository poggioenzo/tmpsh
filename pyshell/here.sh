cat <<- EF1
	content1
	$PATH
	EF1

cat << EF2
	content2
	$PATH
	EF2
EF2

cat <<- 'EF3'
	content3
	$PATH
	EF3

cat << "EF4"
	content4
	$PATH
EF4

# cat << $(EF5)
# 	content5
# 	$PATH
# $(EF5)
