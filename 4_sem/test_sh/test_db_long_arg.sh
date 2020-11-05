#!/bin/bash

dir="/usr/data"

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

size=1000000

commands="\
commands_${size}_g.txt \
commands_${size}_n.txt \
commands_${size}_v.txt \
"

for data in ${data}
do \
	for cmd in ${commands}
	do \
		data_file="${dir}/${data}"
		cmd_file="${dir}/${cmd}"
		echo "Data=${data_file} Commands=${cmd_file}"
		result=`cat ${cmd_file} | ./a.out ${data_file} | tr -d '\0'`
		answer=`echo "${result}" | grep -a -v ':' | wc -l`
		time=`echo "${result}" | grep -a ':'`
		echo "Answer = ${answer}"
		echo "${time}"
		echo "------------------------------------------------------------"
	done
done
