OUTPUT_FORMAT(binary);

SECTIONS
{

	. = 0x10000;
	.kmain : {
		KEEP(*(.kmain*))
	}
    .text : {
        KEEP(*(.text*))
    }

}
