qemu-system-arm -M virt-2.9  \
    -kernel zImage  \
    -no-reboot \
    -nographic  \
    -device virtio-net-pci \
    -netdev user,id=net1,hostfwd=tcp::2222-:22 \
    -device virtio-net-pci,netdev=net1 \
    -drive file=rootfs.ext4,if=virtio,format=raw \
    -append "root=/dev/vda"