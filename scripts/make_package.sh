scripts/feeds install -p thermo_guide -a
make package/thermo_guide/compile -j8
cp bin/packages/arm_cortex-a15_neon-vfpv4/base/*.ipk ../../ipks/thermo_guide.ipk