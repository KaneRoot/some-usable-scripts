ZRAMDIR ?= /tmp/zram

# Currently not working with alpine linux.
zram: zram-mkdir zram-module zram-create zram-format zram-mount
unzram: zram-umount zram-free

btrzram: zram-mkdir zram-module zram-create btrzram-format zram-mount

zram-mkdir:; -mkdir $(ZRAMDIR) 2>/dev/null

zram-module:; modprobe zram
zram-create:; zramctl --find --size 50000M -a zstd

# -b 2048    block size, cannot be used (mkfs.ext4 wants 4k blocks minimum)
# -N xxx     nb of inodes
# -i xxx     higher inode ratio
zram-format:; mkfs.ext4 -N 50000000 /dev/zram0
zram-mount:; mount /dev/zram0 $(ZRAMDIR)

zram-umount:; -umount $(ZRAMDIR)
zram-free:; -zramctl -r /dev/zram0

### BTRFS

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

### EXT4

EXT4_DIR ?= /tmp/ext4
EXT4_IMG ?= /tmp/ext4.img
EXT4_SIZ ?= 5000
EXT4_SECTOR_SIZE ?= 1024
EXT4_INODE_NUMBER ?= 10000000
#EXT4_SECTOR_SIZE ?= 4096
#EXT4_INODE_NUMBER ?= 1500000
EXT4_INODE_SIZE ?= 256
EXT4_LOOP ?= /dev/loop1000

ext4: ext4-mkdir ext4-create ext4-loop ext4-format ext4-mount ext4-chown
ext4-mkdir:; [ ! -d $(EXT4_DIR) ] && mkdir $(EXT4_DIR) 2>/dev/null || :
ext4-create:
	[ ! -f $(EXT4_IMG) ] && su karchnu -c "dd if=/dev/zero of=$(EXT4_IMG) bs=1M count=$(EXT4_SIZ)" || :
ext4-loop:; losetup --sector-size $(EXT4_SECTOR_SIZE) $(EXT4_LOOP) $(EXT4_IMG)
ext4-format:; mkfs.ext4 -b $(EXT4_SECTOR_SIZE) -I $(EXT4_INODE_SIZE) -N $(EXT4_INODE_NUMBER) -L EXT4DATA $(EXT4_LOOP)
ext4-mount:; mount $(EXT4_LOOP) $(EXT4_DIR)
ext4-chown:; chown karchnu $(EXT4_DIR)

unext4: ext4-umount ext4-unloop ext4-rm
ext4-unloop:; [ -b $(EXT4_LOOP) ] && losetup -d $(EXT4_LOOP) || :
ext4-umount:; umount $(EXT4_DIR) || :
ext4-rm:; rm $(EXT4_IMG) || :
