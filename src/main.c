#include <efi.h>
#include <efilib.h>

void hvisor_bin_start();
void hvisor_bin_end();

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
  InitializeLib(ImageHandle, SystemTable);
  Print(L"\n");
  Print(L"Hello! This is the UEFI bootloader of hvisor(loongarch)...\n");
  Print(L"hvisor binary stored in .data, from 0x%lx to 0x%lx\n",
        hvisor_bin_start, hvisor_bin_end);

  // set up 0x8 and 0x9 DMW
  set_dmw();
  arch_init();

  // the entry is the same as the load address

  UINTN hvisor_bin_size = &hvisor_bin_end - &hvisor_bin_start;

  const UINTN hvisor_bin_addr = 0x9000000080000000ULL;

  // store 2333 to hvisor_bin_addr
  *(UINTN *)hvisor_bin_addr = 2333;

  Print(L"Value at 0x%lx is 0x%lx\n", hvisor_bin_addr,
        *(UINTN *)hvisor_bin_addr);

  Print(L"Value at 0x%lx is 0x%08lx\n", hvisor_bin_start,
        *(UINT32 *)hvisor_bin_start);

  Print(L"Copying hvisor binary to 0x%lx, size is %d\n", hvisor_bin_addr,
        hvisor_bin_size);

  CopyMem((void *)hvisor_bin_addr, (void *)hvisor_bin_start, hvisor_bin_size);

  Print(L"==============================================\n");
  Print(L"Done! now jump to hvisor entry...\n");
  Print(L"==============================================\n");

  void *hvisor_entry = (void *)hvisor_bin_addr;
  ((void (*)(void))hvisor_entry)();

  while (1) {
  }

  return EFI_SUCCESS;
}