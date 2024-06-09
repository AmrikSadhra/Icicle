import std.ptr;
import std.mem;
import std.sys;
import png;

#pragma endian big
#pragma pattern_limit 750000

struct Header {
    char model[32];
    char compile_date[48];
    char oem[32];
    u64 unknown;
    u32 file_size;
    u32 unknown2;
    padding[128];
    u32 unknown3;
    u32 offset[4];
    u32 unknown4;
};


struct DirectoryOffsetTable {
    u32 magic_0128;
    u32 offset[73];
};


struct FileEntry {
    u32 offset;
    u32 offset_chk;
    u32 num_bytes;
    u32 num_bytes_chk;
};

struct FileTable {
    u32 size;
    FileEntry file_entries[(size-4)/16];
};

struct File {
    header_t header;
    Chunks chunks [[name("Chunks")]];
};


Header file_header @$;
DirectoryOffsetTable dir_offset_tables[4] @$;
FileTable file_table[292] @$;
File file[5129] @$;

//File file1 @ file_table0.file_entries[1].offset;