#!/bin/bash

SYSPCIPORT=/sys/bus/pci/drivers/pcieport
#SYSUHCI=/sys/bus/pci/drivers/xhci_hcd

if [[ $EUID != 0 ]] ; then
 echo This must be run as root!
 exit 1
fi

if ! cd $SYSPCIPORT ; then
 echo Weird error. Failed to change directory to $SYSUHCI
 exit 1
fi

for i in ????:??:??.? ; do
 echo -n "$i" > unbind
 echo -n "$i" > bind
done
