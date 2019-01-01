#include "Logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

// #include <iostream>
#include <experimental/filesystem> // or #include <filesystem>

namespace fs = std::experimental::filesystem;

namespace Sapphire
{

  Logger::Logger()
  {

  }

  Logger::~Logger()
  {

  }

  void Logger::init( const std::string& logPath )
  {
    auto pos = logPath.find_last_of( fs::path::preferred_separator );

    if( pos != std::string::npos )
    {
      std::string realPath = logPath.substr( 0, pos );
      fs::create_directories( realPath );
    }

    spdlog::init_thread_pool( 8192, 1 );

    auto stdout_sink = std::make_shared< spdlog::sinks::stdout_color_sink_mt >();
    auto daily_sink = std::make_shared< spdlog::sinks::daily_file_sink_mt >( logPath + ".log", 0, 0 );

    std::vector< spdlog::sink_ptr > sinks { stdout_sink, daily_sink };

    auto logger = std::make_shared< spdlog::async_logger >( "logger", sinks.begin(), sinks.end(),
                                                            spdlog::thread_pool(), spdlog::async_overflow_policy::block );


    spdlog::register_logger( logger );
    spdlog::set_pattern( "[%H:%M:%S.%e] [%^%l%$] %v" );
    spdlog::set_level( spdlog::level::debug );
    // always flush the log on criticial messages, otherwise it's done by libc
    // see: https://github.com/gabime/spdlog/wiki/7.-Flush-policy
    // nb: if the server crashes, log data can be missing from the file unless something logs critical just before it does
    spdlog::flush_on( spdlog::level::critical );
  }

  void Logger::error( const std::string& text )
  {
    spdlog::get( "logger" )->error( text );
  }

  void Logger::warn( const std::string& text )
  {
    spdlog::get( "logger" )->warn( text );
  }

  void Logger::info( const std::string& text )
  {
    spdlog::get( "logger" )->info( text );
  }

  void Logger::debug( const std::string& text )
  {
    spdlog::get( "logger" )->debug( text );
  }

  void Logger::fatal( const std::string& text )
  {
    spdlog::get( "logger" )->critical( text );
  }

  void Logger::trace( const std::string& text )
  {
    spdlog::get( "logger" )->trace( text );
  }

}
