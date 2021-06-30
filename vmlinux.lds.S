OUTPUT_ARCH(aarch64)
ENTRY(_text)

#define VA_START	(0xffff000000000000)
#define TEXT_OFFSET	(0x80000)
#define HEAD_FLAGS	((1 << 1) | (0 << 3))

SECTIONS
{
	/DISCARD/ : {
		*(.discard)
		*(.discard.*)
		*(.interp .dynamic)
		*(.dynsym .dynstr .hash .gnu.hash)
		*(.eh_frame)
    }

	. = VA_START + TEXT_OFFSET;
	.head.text : {
		_text = .;
		*(.head.text)
	}

	. = ALIGN(0x1000);
	.text : {
		_stext = .;
		*(.text)
	}
	.data : {
		*(.data)
		. = ALIGN(0x1000);
		stack_top = .;
		. = . + 0x4000;
	}
	.bss : {
		*(.bss)
	}
	.rodata : {
		*(.rodata)
	}
	_end = .;

	kernel_offset = TEXT_OFFSET;
	kernel_size = _end - _text;
	kernel_flag = HEAD_FLAGS;
}
