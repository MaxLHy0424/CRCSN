#include "core.hpp"
auto main() -> int
{
    cpp_utils::console_ui ui;
    ui.lock( true, true );
    cpp_utils::ignore_console_exit_signal( true );
    cpp_utils::fix_window_size( core::current_window_handle, true );
    cpp_utils::enable_window_maximize_ctrl( core::current_window_handle, false );
    cpp_utils::enable_window_close_ctrl( core::current_window_handle, true );
    cpp_utils::enable_window_minimize_ctrl( core::current_window_handle, false );
    cpp_utils::set_window_translucency( core::current_window_handle, 255 );
    cpp_utils::set_console_title( INFO_SHORT_NAME );
    cpp_utils::set_console_charset( CHARSET_ID );
    cpp_utils::set_console_size( CONSOLE_WIDTH, CONSOLE_HEIGHT );
    std::print( " -> 检测运行权限.\n" );
    if ( !cpp_utils::is_run_as_admin() ) {
        std::print( " -> 申请管理员权限.\n" );
        cpp_utils::relaunch_as_admin();
    }
    core::load_config( false );
    std::print( " -> 创建线程.\n" );
    cpp_utils::thread_pool threads;
    threads.add( core::keep_window_top ).add( core::set_console_attrs ).add( core::fix_os_env );
    const auto &is_enable_quick_exit_and_relaunch{ core::options[ "misc" ][ "quick_exit_and_relaunch" ] };
    if ( is_enable_quick_exit_and_relaunch ) {
        threads.detach_all();
    }
    std::print( " -> 准备用户界面.\n" );
    ui.add_back( "                    [ 主  页 ]\n\n" )
      .add_back(
        " < 退出 ", core::exit, cpp_utils::console_value::text_foreground_red | cpp_utils::console_value::text_foreground_intensity );
    if ( is_enable_quick_exit_and_relaunch ) {
        ui.add_back(
          " < 重启 ", core::relaunch,
          cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity );
    }
    ui.add_back( " > 信息 ", core::info )
      .add_back( " > 配置 ", core::edit_config )
      .add_back( " > 工具箱 ", core::toolkit )
      .add_back( "\n[ 破解 ]\n" )
      .add_back( std::format( " > {} ", core::custom_rules.showed_name ), core::crack_with_rules{ core::custom_rules } );
    for ( const auto &rule : core::builtin_rules ) {
        ui.add_back( std::format( " > {} ", rule.showed_name ), core::crack_with_rules{ rule } );
    }
    ui.add_back( "\n[ 恢复 ]\n" )
      .add_back( std::format( " > {} ", core::custom_rules.showed_name ), core::restore_with_rules{ core::custom_rules } );
    for ( const auto &rule : core::builtin_rules ) {
        ui.add_back( std::format( " > {} ", rule.showed_name ), core::restore_with_rules{ rule } );
    }
    ui.show().lock( true, true );
    std::print( " -> 清理资源.\n" );
    return EXIT_SUCCESS;
}