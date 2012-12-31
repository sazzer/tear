#!/bin/bash


pushd `dirname $0`
TOPDIR=`pwd`
BUILDDIR=$TOPDIR/output
INSTALLDIR=$BUILDDIR/install

rm -rf $BUILDDIR
mkdir $BUILDDIR

pushd $BUILDDIR

cmake -DCMAKE_INSTALL_PREFIX=$INSTALLDIR -DCMAKE_BUILD_TYPE=Debug -Wno-dev --warn-uninitialized --warn-unused-vars  $@ $TOPDIR || exit 1
make || exit 2
make test || exit 3
make install || exit 4

popd

popd
