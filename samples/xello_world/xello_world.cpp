#include <stdlib.h>
#include "xe_api.h"

int main()
{
    putenv( "XE_ENABLE_VALIDATION_LAYER=1" );
    putenv( "XE_ENABLE_PARAMETER_VALIDATION=1" );

    xeInit( XE_INIT_FLAG_NONE );
    return 0;
}