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
    u16 check1;
    u16 packing_type;
    u32 check2;
    u32 fs;
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

struct ArtFileEntry {
    u32 offset;
    u32 offset_chk;
    u32 num_bytes;
    u32 num_bytes_chk;
};

struct Directory {
    u32 size;
    ArtFileEntry art_file_entries[(size-4)/16];
};

struct ArtFile {
    header_t header;
    Chunks chunks;
};

Header file_header @$;
DirectoryOffsetTable dir_offset_tables[4] @$;
Directory directories[292] @$;
ArtFile art_files[100] @$;

//File file1 @ file_table0.file_entries[1].offset;