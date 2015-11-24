#include "cat.h"

#include "../inc/intTypeDefs.h"
#include "../inc/screenUtils.h"
#include "../inc/kbDetect.h"
#include "../inc/kernelFunctions.h"
#include "../inc/fs.h"

void cat(fs_node_t* fsnode)
{
    newline();
    if ((fsnode->flags & 0x7) == FS_FILE)
    {
        const uint32 rbuff = fsnode->length;
        char buf[rbuff];
        uint32 sz = read_fs(fsnode, 0, rbuff, (uint8*) buf);
        uint32 j;
        for (j = 0; j < sz; j++)
            printch(buf[j], 0x0F);
        newline();
    }
}
