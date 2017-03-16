#include "utils.h"
/*
REF:https://github.com/TheCodeArtist/elf-parser
*/

void disassemble (int32_t fd, Elf32_Ehdr eh, Elf32_Shdr * sh_table)
{
	int32_t i;
	char *sh_str;				/* section-header string-table is also a section. */
	char *buf;					/* buffer to hold contents of the .text section */

	/* Read section-header string-table */
	debug ("eh.e_shstrndx = 0x%x\n", eh.e_shstrndx);
	sh_str = read_section (fd, sh_table[eh.e_shstrndx]);

	for (i = 0; i < eh.e_shnum; i++)
	{
		if (!strcmp (".text", (sh_str + sh_table[i].sh_name)))
		{
			printf ("Found section\t\".text\"\n");
			printf ("at offset\t0x%08x\n", sh_table[i].sh_offset);
			printf ("of size\t\t0x%08x\n", sh_table[i].sh_size);
			break;
		}
	}

	assert (lseek (fd, sh_table[i].sh_offset, SEEK_SET) == sh_table[i].sh_offset);
	buf = malloc (sh_table[i].sh_size);
	if (!buf)
	{
		printf ("Failed to allocate %dbytes!!\n", sh_table[i].sh_size);
		printf ("Failed to disaassemble!!\n", sh_table[i].sh_size);
		return;
	}
	assert (read (fd, buf, sh_table[i].sh_size) == sh_table[i].sh_size);

	/* Now buf contains the instructions (4bytes each) */

}

void read_elf_header (int32_t fd, Elf32_Ehdr * elf_header)
{
	assert (elf_header != NULL);
	assert (lseek (fd, (off_t) 0, SEEK_SET) == (off_t) 0);
	assert (read (fd, (void *) elf_header, sizeof (Elf32_Ehdr)) == sizeof (Elf32_Ehdr));
}

bool is_ELF (Elf32_Ehdr eh)
{
	/* ELF magic bytes are 0x7f,'E','L','F'
	 * Using  octal escape sequence to represent 0x7f
	 */
	if (!strncmp ((char *) eh.e_ident, "\177ELF", 4))
	{
		printf ("ELFMAGIC \t= ELF\n");
		/* IS a ELF file */
		return 1;
	}
	else
	{
		printf ("ELFMAGIC mismatch!\n");
		/* Not ELF file */
		return 0;
	}
}

void print_elf_header (Elf32_Ehdr elf_header)
{

	/* Storage capacity class */
	printf ("Storage class\t= ");
	switch (elf_header.e_ident[EI_CLASS])
	{
	case ELFCLASS32:
		printf ("32-bit objects\n");
		break;

	case ELFCLASS64:
		printf ("64-bit objects\n");
		break;

	default:
		printf ("INVALID CLASS\n");
		break;
	}

	/* Data Format */
	printf ("Data format\t= ");
	switch (elf_header.e_ident[EI_DATA])
	{
	case ELFDATA2LSB:
		printf ("2's complement, little endian\n");
		break;

	case ELFDATA2MSB:
		printf ("2's complement, big endian\n");
		break;

	default:
		printf ("INVALID Format\n");
		break;
	}

	/* OS ABI */
	printf ("OS ABI\t\t= ");
	switch (elf_header.e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf ("UNIX System V ABI\n");
		break;

	case ELFOSABI_HPUX:
		printf ("HP-UX\n");
		break;

	case ELFOSABI_NETBSD:
		printf ("NetBSD\n");
		break;

	case ELFOSABI_LINUX:
		printf ("Linux\n");
		break;

	case ELFOSABI_SOLARIS:
		printf ("Sun Solaris\n");
		break;

	case ELFOSABI_AIX:
		printf ("IBM AIX\n");
		break;

	case ELFOSABI_IRIX:
		printf ("SGI Irix\n");
		break;

	case ELFOSABI_FREEBSD:
		printf ("FreeBSD\n");
		break;

	case ELFOSABI_TRU64:
		printf ("Compaq TRU64 UNIX\n");
		break;

	case ELFOSABI_MODESTO:
		printf ("Novell Modesto\n");
		break;

	case ELFOSABI_OPENBSD:
		printf ("OpenBSD\n");
		break;

	case ELFOSABI_ARM_AEABI:
		printf ("ARM EABI\n");
		break;

	case ELFOSABI_ARM:
		printf ("ARM\n");
		break;

	case ELFOSABI_STANDALONE:
		printf ("Standalone (embedded) app\n");
		break;

	default:
		printf ("Unknown (0x%x)\n", elf_header.e_ident[EI_OSABI]);
		break;
	}

	/* ELF filetype */
	printf ("Filetype \t= ");
	switch (elf_header.e_type)
	{
	case ET_NONE:
		printf ("N/A (0x0)\n");
		break;

	case ET_REL:
		printf ("Relocatable\n");
		break;

	case ET_EXEC:
		printf ("Executable\n");
		break;

	case ET_DYN:
		printf ("Shared Object\n");
		break;
	default:
		printf ("Unknown (0x%x)\n", elf_header.e_type);
		break;
	}

	/* ELF Machine-id */
	printf ("Machine\t\t= ");
	switch (elf_header.e_machine)
	{
	case EM_NONE:
		printf ("None (0x0)\n");
		break;

	case EM_386:
		printf ("INTEL x86 (0x%x)\n", EM_386);
		break;

	case EM_ARM:
		printf ("ARM (0x%x)\n", EM_ARM);
		break;
	default:
		printf ("Machine\t= 0x%x\n", elf_header.e_machine);
		break;
	}

	/* Entry point */
	printf ("Entry point\t= 0x%08x\n", elf_header.e_entry);

	/* ELF header size in bytes */
	printf ("ELF header size\t= 0x%08x\n", elf_header.e_ehsize);

	/* Program Header */
	printf ("\nProgram Header\t= ");
	printf ("0x%08x\n", elf_header.e_phoff);	/* start */
	printf ("\t\t  %d entries\n", elf_header.e_phnum);	/* num entry */
	printf ("\t\t  %d bytes\n", elf_header.e_phentsize);	/* size/entry */

	/* Section header starts at */
	printf ("\nSection Header\t= ");
	printf ("0x%08x\n", elf_header.e_shoff);	/* start */
	printf ("\t\t  %d entries\n", elf_header.e_shnum);	/* num entry */
	printf ("\t\t  %d bytes\n", elf_header.e_shentsize);	/* size/entry */
	printf ("\t\t  0x%08x (string table offset)\n", elf_header.e_shstrndx);

	/* File flags (Machine specific) */
	printf ("\nFile flags \t= 0x%08x\n", elf_header.e_flags);

	/* ELF file flags are machine specific.
	 * INTEL implements NO flags.
	 * ARM implements a few.
	 * Add support below to parse ELF file flags on ARM
	 */
	int32_t ef = elf_header.e_flags;
	printf ("\t\t  ");

	if (ef & EF_ARM_RELEXEC)
		printf (",RELEXEC ");

	if (ef & EF_ARM_HASENTRY)
		printf (",HASENTRY ");

	if (ef & EF_ARM_INTERWORK)
		printf (",INTERWORK ");

	if (ef & EF_ARM_APCS_26)
		printf (",APCS_26 ");

	if (ef & EF_ARM_APCS_FLOAT)
		printf (",APCS_FLOAT ");

	if (ef & EF_ARM_PIC)
		printf (",PIC ");

	if (ef & EF_ARM_ALIGN8)
		printf (",ALIGN8 ");

	if (ef & EF_ARM_NEW_ABI)
		printf (",NEW_ABI ");

	if (ef & EF_ARM_OLD_ABI)
		printf (",OLD_ABI ");

	if (ef & EF_ARM_SOFT_FLOAT)
		printf (",SOFT_FLOAT ");

	if (ef & EF_ARM_VFP_FLOAT)
		printf (",VFP_FLOAT ");

	if (ef & EF_ARM_MAVERICK_FLOAT)
		printf (",MAVERICK_FLOAT ");

	printf ("\n");

	/* MSB of flags conatins ARM EABI version */
	printf ("ARM EABI\t= Version %d\n", (ef & EF_ARM_EABIMASK) >> 24);

	printf ("\n");				/* End of ELF header */

}

void read_section_header_table (int32_t fd, Elf32_Ehdr eh, Elf32_Shdr sh_table[])
{
	uint32_t i;

	assert (lseek (fd, (off_t) eh.e_shoff, SEEK_SET) == (off_t) eh.e_shoff);

	for (i = 0; i < eh.e_shnum; i++)
	{
		assert (read (fd, (void *) &sh_table[i], eh.e_shentsize) == eh.e_shentsize);
	}

}

char *read_section (int32_t fd, Elf32_Shdr sh)
{
	char *buff = malloc (sh.sh_size);
	if (!buff)
	{
		printf ("%s:Failed to allocate %dbytes\n", __func__, sh.sh_size);
	}

	assert (buff != NULL);
	assert (lseek (fd, (off_t) sh.sh_offset, SEEK_SET) == (off_t) sh.sh_offset);
	assert (read (fd, (void *) buff, sh.sh_size) == sh.sh_size);

	return buff;
}

void print_section_headers (int32_t fd, Elf32_Ehdr eh, Elf32_Shdr sh_table[])
{
	uint32_t i;
	char *sh_str;				/* section-header string-table is also a section. */

	/* Read section-header string-table */
	debug ("eh.e_shstrndx = 0x%x\n", eh.e_shstrndx);
	sh_str = read_section (fd, sh_table[eh.e_shstrndx]);

	printf ("========================================");
	printf ("========================================\n");
	printf (" idx offset     load-addr  size       algn" " flags      type       section\n");
	printf ("========================================");
	printf ("========================================\n");

	for (i = 0; i < eh.e_shnum; i++)
	{
		printf (" %03d ", i);
		printf ("0x%08x ", sh_table[i].sh_offset);
		printf ("0x%08x ", sh_table[i].sh_addr);
		printf ("0x%08x ", sh_table[i].sh_size);
		printf ("%4d ", sh_table[i].sh_addralign);
		printf ("0x%08x ", sh_table[i].sh_flags);
		printf ("0x%08x ", sh_table[i].sh_type);
		printf ("%s\t", (sh_str + sh_table[i].sh_name));
		printf ("\n");
	}
	printf ("========================================");
	printf ("========================================\n");
	printf ("\n");				/* end of section header table */
}

void print_symbol_table (int32_t fd, Elf32_Ehdr eh, Elf32_Shdr sh_table[], uint32_t symbol_table)
{

	char *str_tbl;
	Elf32_Sym *sym_tbl;
	uint32_t i, symbol_count;

	sym_tbl = (Elf32_Sym *) read_section (fd, sh_table[symbol_table]);

	/* Read linked string-table
	 * Section containing the string table having names of
	 * symbols of this section
	 */
	uint32_t str_tbl_ndx = sh_table[symbol_table].sh_link;
	debug ("str_table_ndx = 0x%x\n", str_tbl_ndx);
	str_tbl = read_section (fd, sh_table[str_tbl_ndx]);

	symbol_count = (sh_table[symbol_table].sh_size / sizeof (Elf32_Sym));
	printf ("%d symbols\n", symbol_count);

	for (i = 0; i < symbol_count; i++)
	{
		printf ("0x%08x ", sym_tbl[i].st_value);
		printf ("0x%02x ", ELF32_ST_BIND (sym_tbl[i].st_info));
		printf ("0x%02x ", ELF32_ST_TYPE (sym_tbl[i].st_info));
		printf ("%s\n", (str_tbl + sym_tbl[i].st_name));
	}
}

void print_symbols (int32_t fd, Elf32_Ehdr eh, Elf32_Shdr sh_table[])
{
	uint32_t i;

	for (i = 0; i < eh.e_shnum; i++)
	{
		if ((sh_table[i].sh_type == SHT_SYMTAB) || (sh_table[i].sh_type == SHT_DYNSYM))
		{
			printf ("\n[Section %03d]", i);
			print_symbol_table (fd, eh, sh_table, i);
		}
	}
}

void save_text_section (int32_t fd, Elf32_Ehdr eh, Elf32_Shdr sh_table[])
{
	uint32_t i;
	int32_t fd2;				/* to write text.S in current directory */
	char *sh_str;				/* section-header string-table is also a section. */
	char *buf;					/* buffer to hold contents of the .text section */

	/*   */
	char *pwd = getcwd (NULL, (size_t) NULL);
	printf ("%s\n", pwd);
	pwd = realloc (pwd, strlen (pwd) + 8);
	strcat (pwd, "/text.S");
	printf ("%s\n", pwd);

	/* Read section-header string-table */
	debug ("eh.e_shstrndx = 0x%x\n", eh.e_shstrndx);
	sh_str = read_section (fd, sh_table[eh.e_shstrndx]);

	for (i = 0; i < eh.e_shnum; i++)
	{
		if (!strcmp (".text", (sh_str + sh_table[i].sh_name)))
		{
			printf ("Found section\t\".text\"\n");
			printf ("at offset\t0x%08x\n", sh_table[i].sh_offset);
			printf ("of size\t\t0x%08x\n", sh_table[i].sh_size);

			break;
		}
	}

	assert (lseek (fd, sh_table[i].sh_offset, SEEK_SET) == sh_table[i].sh_offset);
	buf = malloc (sh_table[i].sh_size);
	if (!buf)
	{
		printf ("Failed to allocate %dbytes!!\n", sh_table[i].sh_size);
		goto EXIT;
	}
	assert (read (fd, buf, sh_table[i].sh_size) == sh_table[i].sh_size);
	fd2 = open (pwd, O_RDWR | O_SYNC | O_CREAT, 0777);
	write (fd2, buf, sh_table[i].sh_size);
	fsync (fd2);

  EXIT:
	close (fd2);
	free (pwd);

}
