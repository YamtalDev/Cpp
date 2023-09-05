#!/bin/bash
mkfs.ext4 /dev/nbd0 >> buse.log
mount /dev/nbd0 /mnt >> buse.log
