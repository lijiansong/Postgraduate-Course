#include "utils.h"

/* Main entry point of elf-parser */
int32_t main (int32_t argc, char *argv[])
{

	int32_t fd;
	Elf32_Ehdr eh;				/* elf-header is fixed size */
	Elf32_Shdr *sh_tbl;			/* section-header table is variable size */

	if (argc != 2)
	{
		printf ("Usage: elf-parser <ELF-file>\n");
		return 0;
	}

	fd = open (argv[1], O_RDONLY | O_SYNC);
	if (fd < 0)
	{
		printf ("Error %d Unable to open %s\n", fd, argv[1]);
		return 0;
	}

	/* ELF header : at start of file */
	read_elf_header (fd, &eh);
	if (!is_ELF (eh))
	{
		return 0;
	}
	print_elf_header (eh);

	/* Section header table :  */
	sh_tbl = malloc (eh.e_shentsize * eh.e_shnum);
	if (!sh_tbl)
	{
		printf ("Failed to allocate %d bytes\n", (eh.e_shentsize * eh.e_shnum));
	}
	read_section_header_table (fd, eh, sh_tbl);
	print_section_headers (fd, eh, sh_tbl);

	/* Symbol tables :
	 * sh_tbl[i].sh_type
	 * |`- SHT_SYMTAB
	 *  `- SHT_DYNSYM
	 */
	print_symbols (fd, eh, sh_tbl);

	/* Save .text section as text.S
	 */
	save_text_section (fd, eh, sh_tbl);

	/* Disassemble .text section
	 * Logs asm instructions to stdout
	 * Currently supports ARMv7
	 */
	disassemble (fd, eh, sh_tbl);

	return 0;
}
