#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: record_mem_leak.sh <exefile>"
    exit 1
fi

exefile="$1"
"$exefile" &
proc_pid=$!

trap finish SIGINT
finish() {
    kill $proc_pid
    gnuplot plot_mem_leak.plt
    exit
}

rm /tmp/mem.log

while true
do
    ps -p $proc_pid -o pid=,%mem=,vsz= >> /tmp/mem.log
    if [ $? -ne 0 ]
    then
        break
    fi
    sleep 1
done


