#include "AP_HIL.h"

#if AP_HIL_ENABLED

AP_HIL *AP_HIL::_singleton;

AP_HIL::AP_HIL()
{
    _singleton = this;
}

namespace AP {

AP_HIL *hil()
{
    return AP_HIL::get_singleton();
}

}

#endif // AP_HIL_ENABLED
