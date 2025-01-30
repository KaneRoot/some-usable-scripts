PDNSDIR ?= /tmp/zram

# Currently not working with alpine linux.
zram: mkdir zram-module zram-create zram-format zram-mount
unzram: zram-umount zram-free

btrzram: mkdir zram-module zram-create btrzram-format zram-mount

mkdir:; -mkdir $(PDNSDIR) 2>/dev/null

zram-module:; modprobe zram
zram-create:; zramctl --find --size 50000M -a zstd

# -b 2048    block size, cannot be used (mkfs.ext4 wants 4k blocks minimum)
# -N xxx     nb of inodes
# -i xxx     higher inode ratio
zram-format:; mkfs.ext4 -N 50000000 /dev/zram0
zram-mount:; mount /dev/zram0 $(PDNSDIR)

zram-umount:; -umount $(PDNSDIR)
zram-free:; -zramctl -r /dev/zram0

BTRFS_DIR ?= /tmp/btrfs
BTRFS_IMG ?= /tmp/btrfs.img
BTRFS_SIZ ?= 5000
BTRFS_SECTOR_SIZE ?= 4096
BTRFS_NODE_SIZE ?= 4096  # Minimal accepted value.
BTRFS_LOOP ?= /dev/loop100
BTRFS_COMP ?= zstd:8

# apt install btrfs-progs
btrfs: btrfs-mkdir btrfs-create btrfs-loop btrfs-format btrfs-mount btrfs-chown
btrfs-mkdir:; [ ! -d $(BTRFS_DIR) ] && mkdir $(BTRFS_DIR) 2>/dev/null || :
btrfs-create:
	[ ! -f $(BTRFS_IMG) ] && su karchnu -c "dd if=/dev/zero of=$(BTRFS_IMG) bs=1M count=$(BTRFS_SIZ)" || :
btrfs-loop:; losetup --sector-size $(BTRFS_SECTOR_SIZE) $(BTRFS_LOOP) $(BTRFS_IMG)
btrfs-format:; mkfs.btrfs -s $(BTRFS_SECTOR_SIZE) -n $(BTRFS_NODE_SIZE) -L BTRDATA $(BTRFS_LOOP)
btrfs-mount:; mount -o compress=$(BTRFS_COMP) $(BTRFS_LOOP) $(BTRFS_DIR)
btrfs-chown:; chown karchnu $(BTRFS_DIR)

unbtrfs: btrfs-umount btrfs-unloop btrfs-rm
btrfs-unloop:; [ -b $(BTRFS_LOOP) ] && losetup -d $(BTRFS_LOOP) || :
btrfs-umount:; umount $(BTRFS_DIR)
btrfs-rm:; rm $(BTRFS_IMG)
