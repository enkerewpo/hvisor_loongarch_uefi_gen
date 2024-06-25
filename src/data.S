.section .hvisor.bin
.global hvisor_bin_start, hvisor_bin_end
hvisor_bin_start:
.incbin "/mnt/d/Github/hvisor/target/loongarch64-unknown-none/debug/hvisor.bin"
hvisor_bin_end: