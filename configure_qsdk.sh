#!/bin/bash
make clean

qemu_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [[ ! -e device-repo ]]; then
    echo device-repo not found - setting up
    git clone https://github.com/gabriel-cr/device-repo.git
fi

cd device-repo
./make_prj.sh
cd $qemu_dir

if [[ ! -e lib ]]; then
    ln -s device-repo/lib lib
fi

if [[ ! -e pgback ]]; then
    git clone https://github.com/gabriel-cr/pgback
fi

cd pgback
./make_prj.sh
cd $qemu_dir

./configure --target-list=arm-softmmu --enable-debug --disable-werror --extra-cflags="-rdynamic -fPIC"
