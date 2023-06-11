scripts/feeds install -p thermo_guide -a
make package/thermo_guide/compile -j8
cp bin/packages/arm_arm1176jzf-s_vfp/base/*.ipk ../../ipks/thermo_guide_rpi.ipk