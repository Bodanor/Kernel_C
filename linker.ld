SECTIONS
{
   .stage1 0x7c00 : AT(0) {
       *(.stage1)
       *(.common_rountines)
       FILL(0x0)
       . = 0x1FE;
       SHORT(0xaa55)
   }
    .stage2 0x8000 : AT(0x200) {
       *(.stage2)
   }
}

