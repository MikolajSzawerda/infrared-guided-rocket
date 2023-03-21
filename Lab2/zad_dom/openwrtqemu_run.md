wget -q https://downloads.openwrt.org/releases/18.06.1/targets/armvirt/32/openwrt-18.06.1-armvirt-32-zImage -O zImage

wget -q https://downloads.openwrt.org/releases/18.06.1/targets/armvirt/32/openwrt-18.06.1-armvirt-32-rootfs.cpio.gz -O rootfs.cpio.gz

gunzip rootfs.cpio.gz

wget -q https://downloads.openwrt.org/releases/18.06.1/targets/armvirt/32/openwrt-18.06.1-armvirt-32-root.squashfs.gz -O root.squashfs.gz

gunzip root.squashfs.gz

qemu-system-arm -M virt-2.9 \
 -kernel zImage \
 -no-reboot -nographic \
 -device virtio-net-pci \
 -netdev user,id=net1,hostfwd=tcp::2222-:22 -device virtio-net-pci,netdev=net1 \
 -drive file=root.squashfs,if=virtio,format=raw \
 -append "root=/dev/vda"

 /etc/init.d/firewall stop

opkg update
opkg install python3
opkg install python3-pip
pip3 install gpio4
pip3 install numpy
