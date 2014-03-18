#!/bin/sh

if [ ${#} -lt 2 ]; then
    echo "Usage: ${0} {format|hc|nd|nd_hc} <number>" >&2
    exit 1
fi

GROUP=$(echo ${1} | tr '[:lower:]' '[:upper:]')
NUMBER=${2}

if ! echo ${NUMBER} | grep '^[0-9]\+$' 2>&1 > /dev/null; then
    echo "Usage: ${0} {format|hc|nd|nd_hc} <number>" >&2
    exit 1
fi

make clean-shell

case "${GROUP}" in
    FORMAT) USE_SHELL=0 FORMAT=${NUMBER} EUT=1 make clean-format flash
            read -p "Change device and press [Enter] to continue..."
            USE_SHELL=0 FORMAT=${NUMBER} EUT=2 make clean-format flash
            ;;
    HC)     USE_SHELL=0 HC=${NUMBER} EUT=1 make clean-hc flash
            read -p "Change device and press [Enter] to continue..."
            USE_SHELL=0 HC=${NUMBER} EUT=2 make clean-hc flash
            ;;
    ND)     USE_SHELL=0 ND=${NUMBER} EUT=1 make clean-nd flash
            read -p "Change device and press [Enter] to continue..."
            USE_SHELL=0 ND=${NUMBER} EUT=2 make clean-nd flash
            ;;
    ND_HC)  USE_SHELL=0 ND_HC=${NUMBER} EUT=1 make clean-nd_hc flash
            read -p "Change device and press [Enter] to continue..."
            USE_SHELL=0 ND_HC=${NUMBER} EUT=2 make clean-nd_hc flash
            ;;
    *)      echo "Usage: ${0} {format|hc|nd|nd_hc} <number>" >&2
            exit 1
            ;;
esac
