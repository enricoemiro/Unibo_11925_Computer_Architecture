#!/bin/bash

path=""
commands=(
  "-h, --help\t\t\t\tPrint the list of all available commands"
  "-p, --path YOUR_PATH\t\t\tChange the path on which to run the debug"
)

# Colors
red="\033[0;31m"
blue="\033[0;34m"

exiterr() {
  echo "Error: $1" >&2
  exit 1
}

debug() {
  # Counter variables
  error=0
  success=0

  # Find all .tst files in $path
  files=($(find $path -maxdepth 1 -type f -name "*.tst"))

  # No files found
  if [ ${#files[@]} -eq 0 ]; then
    exiterr "No .tst files found in path '$path'"
  fi

  # Run HardwareSimulator.sh to each file
  for file in ${files[*]}; do
    output=$(eval "HardwareSimulator.sh $file" 2>&1)

    # Current file has not failed the test
    if [[ $output == @(End of script - Comparison ended successfully) ]]; then
      status=$blue
      ((++success))
      output=""
    else
      status=$red
      ((++error))
    fi

    echo -e "$status $file $output"
  done

  if [[ $success -eq 0 ]]; then
    echo "All $error files failed the test"

  elif [[ $error -eq 0 ]]; then
    echo "All $success files passed the test"

  else
    echo -e "$blue $success file(s) failed the test"
    echo -e "$red $error file(s) failed the test"
  fi

  exit 1
}

# Ask to set path as current path
if [[ $# -eq 0 ]]; then
  read -p "Do you want to use '$(pwd)' as path? [Y/n]: " answer

  if [[ $answer != @(Y|y) ]]; then
    exiterr "No path specified"
  fi

  path=$(pwd)
fi

# Print on screen the command list
if [[ $1 == @(-h|--help) ]]; then
  echo "List of available commands:"

  for command in "${commands[@]}"; do
    echo -e "$command"
  done

  exit 1
fi

# Set the new path
if [[ $1 == @(-p|--path) ]]; then
  if [[ -z $2 ]]; then
    exiterr "No path specified"
  fi

  if [[ ! -d $2 ]]; then
    exiterr "The path '$2' entered does not exist"
  fi

  path=$2
fi

# Run the debug
debug
