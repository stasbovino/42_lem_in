tests=`echo invalid/*`
IFS=' '
read -ra ARR <<< "$tests"
for ((i=0; i < ${#ARR[@]}; i++));
do
	echo "TEST: ${ARR[$i]}"
	./../lem-in < ${ARR[$i]}
done
