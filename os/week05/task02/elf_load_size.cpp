#include <cstdint>
#include <fstream>
#include <iostream>

#define ELF_NIDENT 16

// program header-ы такого типа нужно загрузить в
// память при загрузке приложения
#define PT_LOAD 1

// структура заголовка ELF файла
struct elf_hdr {
    std::uint8_t e_ident[ELF_NIDENT];
    std::uint16_t e_type;
    std::uint16_t e_machine;
    std::uint32_t e_version;
    std::uint64_t e_entry;
    std::uint64_t e_phoff;
    std::uint64_t e_shoff;
    std::uint32_t e_flags;
    std::uint16_t e_ehsize;
    std::uint16_t e_phentsize;
    std::uint16_t e_phnum;
    std::uint16_t e_shentsize;
    std::uint16_t e_shnum;
    std::uint16_t e_shstrndx;
} __attribute__((packed));

// структура записи в таблице program header-ов
struct elf_phdr {
    std::uint32_t p_type;
    std::uint32_t p_flags;
    std::uint64_t p_offset;
    std::uint64_t p_vaddr;
    std::uint64_t p_paddr;
    std::uint64_t p_filesz;
    std::uint64_t p_memsz;
    std::uint64_t p_align;
} __attribute__((packed));

std::size_t space(const char *name)
{
    // Ваш код здесь, name - имя ELF файла, с которым вы работаете
    // вернуть нужно количество байт, необходимых, чтобы загрузить
    // приложение в память
    std::ifstream ifs{name, std::ios::binary};
    struct elf_hdr hdr;

    if (!ifs.read(reinterpret_cast<char *>(&hdr), sizeof(struct elf_hdr))) {
        return 0;
    }

    if (!ifs.seekg(hdr.e_phoff)) {
        std::cerr << "Unable to seek in file" << std::endl;
        return 0;
    }

    struct elf_phdr phdr;
    std::size_t needed_size{0};

    for (std::size_t i = 0; i < hdr.e_phnum; ++i) {
        if (!ifs.read(reinterpret_cast<char *>(&phdr),
                      sizeof(struct elf_phdr))) {
            std::cerr << "Unable to read Program Header" << std::endl;
            return 0;
        }

        if (phdr.p_type == PT_LOAD) {
            needed_size += phdr.p_memsz;
        }
    }

    return needed_size;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Specify ELF file name to parse" << std::endl;
        return 1;
    }

    std::size_t size = space(argv[1]);
    std::cout << "0x" << std::hex << size << std::endl;

    return 0;
}
