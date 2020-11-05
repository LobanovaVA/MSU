#!/bin/bash

dir="../nv"

if [ $# -eq 1 ]
then
	n=${1}
else
	n=100000
fi

data="\
a${n}.txt \
a${n}_sort_g.txt \
a${n}_sort_n.txt \
a${n}_sort_v.txt \
"
commands="\
commands0.txt \
commands1.txt \
commands2.txt \
commands3.txt \
commands4.txt \
commands5.txt \
"

for data in ${data}
do \
	for cmd in ${commands}
	do \
		data_file="${dir}/${data}"
		cmd_file="${dir}/${cmd}"
		echo "Data=${data_file} Commands=${cmd_file}"
		result=`cat ${cmd_file} | ./client 127.0.0.1 5555 | tr -d '\0'`
		answer=`echo "${result}" | grep '^ *Student' | wc -l`
		time=`echo "${result}" | grep  '::'`
		echo "Answer = ${answer}"
		echo "${time}"
		echo "------------------------------------------------------------"
	done
done
