#include <cstdint>
#include <fstream>
#include <iostream>

#define ELF_NIDENT 16

// Эта структура описывает формат заголовока ELF файла
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

std::uintptr_t entry_point(const char *name)
{
    std::ifstream ifs{name, std::ios::binary};
    struct elf_hdr hdr;

    if (!ifs.read(reinterpret_cast<char *>(&hdr), sizeof(struct elf_hdr))) {
        return 0;
    }

    return hdr.e_entry;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Specify ELF filename" << std::endl;
        return 1;
    }

    entry_point(argv[1]);

    return 0;
}
