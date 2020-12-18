#include <win_kernel/file.h>
#include <win_kernel/memory_manager.h>
#include <win_kernel/kernel_objects.h>
#include <debug.h>

STATUS Translate_SCB_To_FCB(IN QWORD scb, OUT QWORD_PTR fcb)
{
    STATUS status;
    if((status = CopyGuestMemory(fcb, scb + SCB_FCB_OFFSET, sizeof(QWORD))) != STATUS_SUCCESS)
    {
        Print("Could not copy FCB address\n");
        return status;
    }
    return STATUS_SUCCESS;
}

STATUS Get_FCB_Field(IN QWORD fcb, IN QWORD field, OUT PVOID value)
{
    switch(field)
    {
        case FCB_MFT_INDEX:
            return CopyGuestMemory(value, fcb + field, sizeof(QWORD));
        default:
            Print("Could not find the specified field\n");
            ASSERT(FALSE);
    }
}