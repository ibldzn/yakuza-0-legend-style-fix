#!/usr/bin/env bash

options=("Debug" "Release" "RelWithDebInfo" "MinSizeRel")
if [[ " ${options[*]} " == *" $1 "* ]] ; then
  compile_mode="$1"
  rest_args="${@:2}"
else
  compile_mode="Debug"
  rest_args="$@"
fi

echo "Mode: $compile_mode"

build_dir=_build
cur_dir=$(dirname $(realpath -s $0))

cmake -S $cur_dir -B $cur_dir/$build_dir -DCMAKE_BUILD_TYPE=$compile_mode $rest_args && \
cmake --build $cur_dir/$build_dir --config $compile_mode
