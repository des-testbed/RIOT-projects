#!/bin/sh

if [ -z "$BOARD" ]; then
    BOARD=native
fi

if [ $# -lt 1 ]; then
    TARGET=all
else
    TARGET=$1
fi

make clean-shell

for t in 1 2 3 4 5 6 7 8; do
    for e in 1 2; do
        build_result=bin/$BOARD/6lpplugtest.elf
        filename=format$(printf "%02d" $t)-eut${e}.elf
        if ! [ -e ${filename} ]; then
            echo "Building with USE_SHELL=0 FORMAT=$t EUT=$e"
            USE_SHELL=0 FORMAT=$t EUT=$e make clean-format $TARGET || exit 1
            echo "cp ${build_result} ${filename}"
            cp "${build_result}" "${filename}" || exit 1
        fi
        if ! [ -e ${filename%.elf}.bin ]; then
            echo "cp ${build_result} ${filename%.elf}.bin"
            cp "${build_result}" "${filename%.elf}.bin" || exit 1
        fi
    done
done

make clean-format

for t in 1 2 3 4 5 6 7 8 9 10; do
    for e in 1 2; do
        build_result=bin/$BOARD/6lpplugtest.elf
        filename=hc$(printf "%02d" $t)-eut${e}.elf
        if ! [ -e ${filename} ]; then
            echo "Building with USE_SHELL=0 HC=$t EUT=$e"
            USE_SHELL=0 HC=$t EUT=$e make clean-hc $TARGET || exit 1
            echo "cp ${build_result} ${filename}"
            cp "${build_result}" "${filename}" || exit 1
        fi
        if ! [ -e ${filename%.elf}.bin ]; then
            echo "cp ${build_result} ${filename%.elf}.bin"
            cp "${build_result}" "${filename%.elf}.bin" || exit 1
        fi
    done
done

make clean-hc

for t in 1 2 3 4 5 6 7; do
    for e in 1 2; do
        build_result=bin/$BOARD/6lpplugtest.elf
        filename=nd$(printf "%02d" $t)-eut${e}.elf
        if ! [ -e ${filename} ]; then
            echo "Building with USE_SHELL=0 ND=$t EUT=$e"
            USE_SHELL=0 ND=$t EUT=$e make clean-nd $TARGET || exit 1
            echo "cp ${build_result} ${filename}"
            cp "${build_result}" "${filename}" || exit 1
        fi
        if ! [ -e ${filename%.elf}.bin ]; then
            echo "cp ${build_result} ${filename%.elf}.bin"
            cp "${build_result}" "${filename%.elf}.bin" || exit 1
        fi
    done
done

make clean-nd

# for t in 1 2 3 4; do
#     for e in 1 2; do
#         build_result=bin/$BOARD/6lpplugtest.elf
#         filename=nd_hc$(printf "%02d" $t)-eut${e}.elf
#         if ! [ -e ${filename} ]; then
#             echo "Building with USE_SHELL=0 ND_HC=$t EUT=$e"
#             USE_SHELL=0 ND_HC=$t EUT=$e make clean-nd $TARGET || exit 1
#             echo "cp ${build_result} ${filename}"
#             cp "${build_result}" "${filename}" || exit 1
#         fi
#         if ! [ -e ${filename%.elf}.bin ]; then
#             echo "cp ${build_result} ${filename%.elf}.bin"
#             cp "${build_result}" "${filename%.elf}.bin" || exit 1
#         fi
#     done
# done
