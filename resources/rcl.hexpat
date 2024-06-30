import std.ptr;
import std.mem;
import std.sys;
import png;

#pragma endian big
#pragma pattern_limit 750000

struct header {
    char model[32];
    char compile_date[48];
    char oem[32];
    u16 check1;
    u16 packing_type_t;
    u32 check2;
    u32 file_size;
    u32 unknown2;
    padding[128];
    u32 unknown3;
    u32 offset[4];
    u32 unknown4;
};

struct directory_offset_table {
    u32 magic_0128;
    u32 offset[73];
};

struct art_file_entry {
    u32 offset;
    u32 offset_2;
    u32 num_bytes;
    u32 num_bytes_2;
};

struct directory {
    u32 size;
    art_file_entry art_file_entries[(size-4)/16];
};

struct art_file {
    header_t header;
    Chunks chunks;
};

header file_header @$;
directory_offset_table dir_offset_tables[4] @$;
directory directories[292] @$;
art_file art_files[100] @$;

//File file1 @ file_table0.file_entries[1].offset;