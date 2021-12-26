
.intel_syntax noprefix
.code16 # use 16 bits
.global _start
.global _init
.text
.set BOOT_DRIVE, 0

_start:
  .space 80, 0 # Some BIOSes need a BPB, therefore we fill up space for a fake one
  mov bp, _start
  jmp 0x0000, _init # in case BIOS set cs to 0x7c00. We work with cs:ip

_init:

  cld
  mov bp, _start
  mov sp, bp

  xor ax, ax
  mov ds, ax
  mov ss, ax
  mov es, ax

  movb [BOOT_DRIVE], dl

  mov bx, offset flat:start_16_str
  call print
  mov bx, offset flat:read_disk_str
  call print

  mov dh, 32
  mov bx, 0x7e00 # memory location to load disk to
  call load_disk

  mov bx, offset flat:read_disk_success_str
  call print

  
  ljmp 0x0000:0x7e00


.include "print_16.S"
.include "read_disk.S"

start_16_str:
  .asciz "Starting in 16-bit mode"
read_disk_str:
  .asciz "Loading disk into memory"

read_disk_success_str:
  .asciz "Loaded disk successfully !"


.space 510-(.-_start), 0 # add zeroes to make it 510 bytes long
.word 0xaa55 # magic bytes that tell BIOS that this is bootable

secondstage:

  call .check_CPUID
  mov bx, offset flat:enable_a20_gate_str
  call print

  mov ax, 0x2401
  int 0x15
  call switch_to_protected_mode


.check_CPUID:
  pusha

	pushfd
	pop eax
	mov ecx, eax
	xor eax, (1 << 21)
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	xor eax, ecx
	jz .no_CPUID

  movb [cpuid_support], 1
  mov bx, offset flat:cpuid_success_str
  call print

  mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb .lm_error

  jmp .check_lm


.check_lm:
  mov eax, 0x80000001 	#check if CPU supports Long Mode, abort if not
	cpuid
	test edx, (1 << 29)
	jz .lm_error

  movb [long_mode_support], 1
  mov ebx, offset flat:lm_success_str
  call print

  jmp lm_end

.no_CPUID:
  movb [cpuid_support], 0
  mov ebx, offset flat:cpuid_error_str
  call print
  jmp lm_end

.lm_error:
  movb [long_mode_support], 0
  mov ebx, offset flat:lm_error_str
  call print
  jmp lm_end

lm_end:
  popa
  ret

lm_error_str:
  .asciz "ERROR: CPU does not support Long Mode"

lm_success_str:
  .asciz "CHECK: CPU support Long mode "

cpuid_error_str:
  .asciz "ERROR: CPU does not support CPUID"

cpuid_success_str:
  .asciz "CHECK: CPU support CPUID"

enable_a20_gate_str:
  .asciz "WARNING: Enabling A20 gate"

.include "gdt.S"
.include "32bit_switch.S"
.include "32bit-print.S"

.code32
BEGIN_PM:
  mov ebx, offset flat:MSG_PROT_MODE
  call print_string_pm
  call 0x8000

  jmp . # We will never return from the call to the kernel. Only if bad thing happened...

MSG_PROT_MODE:
.asciz "[SUCCESS] Giving control to the Kernel !"


.set cpuid_support, 0
.set long_mode_support, 0

.space 512-(.-secondstage), 0