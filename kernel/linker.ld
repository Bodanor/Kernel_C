ENTRY(main)

SECTIONS
{
	. = 0x8000;

    .text : {
        KEEP(*(.text*))
    }

}