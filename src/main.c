#include <efi.h>
#include <efilib.h>

extern void *hvisor_bin_start;
extern void *hvisor_bin_end;

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
  InitializeLib(ImageHandle, SystemTable);
  Print(L"Hello! This is the UEFI bootloader of hvisor(loongarch)...\n");
  Print(L"hvisor binary stored in .data, from 0x%lx to 0x%lx\n",
        &hvisor_bin_start, &hvisor_bin_end);

  // set up 0x8 and 0x9 DMW

  // setting up MMU

  // copy hvisor.bin to 0x9000_0001_0000_0000
  // the entry is the same as the load address

  UINTN hvisor_bin_size = &hvisor_bin_end - &hvisor_bin_start;
  const UINT64 hvisor_bin_addr = 0x9000000100000000;
  Print(L"Copying hvisor binary to 0x%lx, size is %d\n", hvisor_bin_addr,
        hvisor_bin_size);
  CopyMem((void *)hvisor_bin_addr, &hvisor_bin_start, hvisor_bin_size);
  Print(L"Copying done, now jump to hvisor entry\n");

  void *hvisor_entry = (void *)hvisor_bin_addr;
  ((void (*)(void))hvisor_entry)();

  while (1) {
  }
  return EFI_SUCCESS;
}