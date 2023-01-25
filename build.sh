#!/usr/bin/env bash

script_dir="$(printf "%q " "$(realpath -s "$0")")"
cur_dir="${script_dir%/*}"
rest_args=()

while [[ $# -gt 0 ]]; do
  case "$1" in
    --dbg) build_type="Debug";          shift ;;
    --rel) build_type="Release";        shift ;;
    --msr) build_type="MinSizeRel";     shift ;;
    --rwd) build_type="RelWithDebInfo"; shift ;;
       -b) shift; build_folder="$1";    shift ;;
        *) rest_args+=("$1");           shift ;;
  esac
done

[[ -z "$build_type" ]]   && build_type="Debug"
[[ -z "$build_folder" ]] && build_folder="_build"

cmake -S "$cur_dir" -B "$cur_dir/$build_folder" -DCMAKE_BUILD_TYPE="$build_type" "${rest_args[@]}"
cmake --build "$cur_dir/$build_folder" --config "$build_type" --parallel
