#!/usr/bin/env bash 
echo "Script executed from: ${PWD}"

BASEDIR=$(dirname $0)
echo "Script releative-location: ${BASEDIR}"


DIR="$( cd "$( dirname "$0" )" && pwd )"
echo "Script location: ${DIR}"
