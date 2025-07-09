#!/bin/bash

if [[ $# != 1 ]]
then
    echo "Usage: mir2x-server.sh install-path"
    exit 1
fi

BIN_DIR=$1
LOG_DIR=${PWD}

echo "Profiling server installed at: ${BIN_DIR}"
echo "Profiling result generated at: ${LOG_DIR}"

# when profiling, disable libasan
# menas we need to rebuild the whole project
# otherwise the profiler also samples libasan for result

cd ${BIN_DIR};
env CPUPROFILE=${LOG_DIR}/mir2x-server.log LD_PRELOAD="/usr/lib/x86_64-linux-gnu/libtcmalloc_and_profiler.so.4.6.11" ./server --auto-launch --disable-monster-idle-wait

cd ${LOG_DIR};
google-pprof --svg ${BIN_DIR}/server ${LOG_DIR}/mir2x-server.log > ${LOG_DIR}/mir2x-server.svg
