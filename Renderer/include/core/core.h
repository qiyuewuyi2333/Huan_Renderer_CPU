




////////////////////////////////////////
//          Logger
#include "functional/log/logger.h"

#define LOG_WARNING(message)    ::huan_renderer_cpu::functional::Logger::get_instance()->warning(message)
#define LOG_ERROR(message)      ::huan_renderer_cpu::functional::Logger::get_instance()->error(message)
#define LOG_INFO(message)       ::huan_renderer_cpu::functional::Logger::get_instance()->info(message)
#define LOG_DEBUG(message)      ::huan_renderer_cpu::functional::Logger::get_instance()->debug(message)




////////////////////////////////////////
#ifdef DEBUG_MODE
#define RENDERER_ASSERT(condition, message) (!!(condition) || (\
    LOG_ERROR(message)) || (\
    assert(true)) \
)
#else
#define RENDERER_ASSERT(condition, message)
#endif



