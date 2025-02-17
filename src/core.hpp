#pragma once
#include <fstream>
#include "cpp_utils.hpp"
#include "info.hpp"
#define CONSOLE_WIDTH  50
#define CONSOLE_HEIGHT 25
#define CHARSET_ID     54936
#define CHARSET_NAME   "GB18030"
namespace core {
    using namespace std::chrono_literals;
    using namespace std::string_view_literals;
    using size_type            = cpp_utils::size_type;
    using ansi_char            = cpp_utils::ansi_char;
    using ansi_std_string      = cpp_utils::ansi_std_string;
    using ansi_std_string_view = cpp_utils::ansi_std_string_view;
    inline constexpr auto config_file_name{ "config.ini" };
    inline constexpr auto default_thread_sleep_time{ 1s };
    inline const auto current_window_handle{ GetConsoleWindow() };
    struct option_node final {
        struct sub_key final {
          private:
            std::atomic_flag value_{};
          public:
            const ansi_char *const self_name;
            const ansi_char *const showed_name;
            auto enable()
            {
                value_.test_and_set();
            }
            auto disable()
            {
                value_.clear();
            }
            auto get() const
            {
                return value_.test();
            }
            operator bool() const
            {
                return value_.test();
            }
            auto operator=( const sub_key & ) -> sub_key & = delete;
            auto operator=( sub_key && ) -> sub_key &      = delete;
            sub_key( const ansi_char *const _self_name, const ansi_char *const _showed_name )
              : self_name{ _self_name }
              , showed_name{ _showed_name }
            { }
            sub_key( const sub_key &_src )
              : value_{ _src }
              , self_name{ _src.self_name }
              , showed_name{ _src.showed_name }
            { }
            sub_key( sub_key &&_src )
              : value_{ _src }
              , self_name{ _src.self_name }
              , showed_name{ _src.showed_name }
            { }
            ~sub_key() = default;
        };
        struct main_key final {
            const ansi_char *const self_name;
            const ansi_char *const showed_name;
            std::vector< sub_key > sub_keys;
            auto &operator[]( const ansi_std_string_view _self_name )
            {
                for ( auto &key : sub_keys ) {
                    if ( _self_name == key.self_name ) {
                        return key;
                    }
                }
                std::abort();
            }
            const auto &operator[]( const ansi_std_string_view _self_name ) const
            {
                for ( const auto &key : sub_keys ) {
                    if ( _self_name == key.self_name ) {
                        return key;
                    }
                }
                std::abort();
            }
            auto operator=( const main_key & ) -> main_key & = delete;
            auto operator=( main_key && ) -> main_key &      = delete;
            main_key( const ansi_char *const _self_name, const ansi_char *const _showed_name, std::vector< sub_key > _sub_keys )
              : self_name{ _self_name }
              , showed_name{ _showed_name }
              , sub_keys{ std::move( _sub_keys ) }
            { }
            main_key( const main_key & ) = default;
            main_key( main_key && )      = default;
            ~main_key()                  = default;
        };
        std::vector< main_key > main_keys;
        auto &operator[]( const ansi_std_string_view _self_name )
        {
            for ( auto &key : main_keys ) {
                if ( _self_name == key.self_name ) {
                    return key;
                }
            }
            std::abort();
        }
        const auto &operator[]( const ansi_std_string_view _self_name ) const
        {
            for ( const auto &key : main_keys ) {
                if ( _self_name == key.self_name ) {
                    return key;
                }
            }
            std::abort();
        }
        auto operator=( const option_node & ) -> option_node & = delete;
        auto operator=( option_node && ) -> option_node &      = delete;
        option_node( std::vector< main_key > _main_keys )
          : main_keys{ std::move( _main_keys ) }
        { }
        option_node( const option_node & ) = default;
        option_node( option_node && )      = default;
        ~option_node()                     = default;
    };
    inline option_node options{
      { { { "crack_restore",
            "破解/恢复",
            { { "hijack_execs", "劫持可执行文件" },
              { "set_serv_startup_types", "设置服务启动类型" },
              { "fix_os_env", "(*) 修复操作系统环境" } } },
          { "window",
            "窗口显示",
            { { "keep_window_top", "(*) 置顶窗口" },
              { "disable_close_ctrl", "(*) 禁用关闭控件" },
              { "translucent", "(*) 半透明化" } } },
          { "misc",
            "杂项",
            { { "quick_exit_and_relaunch", "(-) 快速退出与重启" },
              { "disable_x_option_hot_reload", "(-) 禁用标 (*) 选项热重载" } } } } } };
    inline const auto &is_disable_x_option_hot_reload{ options[ "misc" ][ "disable_x_option_hot_reload" ] };
    struct rule_node final {
        const ansi_char *const showed_name;
        std::deque< ansi_std_string > execs;
        std::deque< ansi_std_string > servs;
        auto empty() const
        {
            return execs.empty() && servs.empty();
        }
        auto operator=( const rule_node & ) -> rule_node & = delete;
        auto operator=( rule_node && ) -> rule_node &      = delete;
        rule_node( const ansi_char *const _showed_name, std::deque< ansi_std_string > _execs, std::deque< ansi_std_string > _servs )
          : showed_name{ _showed_name }
          , execs{ std::move( _execs ) }
          , servs{ std::move( _servs ) }
        { }
        rule_node( const rule_node & ) = default;
        rule_node( rule_node && )      = default;
        ~rule_node()                   = default;
    };
    inline auto custom_rules{
      rule_node{ "自定义", {}, {} }
    };
    inline const rule_node builtin_rules[]{
      {"极域电子教室",
       { "StudentMain.exe", "DispcapHelper.exe", "VRCwPlayer.exe", "InstHelpApp.exe", "InstHelpApp64.exe", "TDOvrSet.exe",
          "GATESRV.exe", "ProcHelper64.exe", "MasterHelper.exe" },
       { "TDNetFilter", "TDFileFilter", "STUDSRV" }},
      {"联想智能云教室",
       { "vncviewer.exe", "tvnserver32.exe", "WfbsPnpInstall.exe", "WFBSMon.exe", "WFBSMlogon.exe", "WFBSSvrLogShow.exe",
          "ResetIp.exe", "FuncForWIN64.exe", "CertMgr.exe", "Fireware.exe", "BCDBootCopy.exe", "refreship.exe",
          "lenovoLockScreen.exe", "PortControl64.exe", "DesktopCheck.exe", "DeploymentManager.exe", "DeploymentAgent.exe",
          "XYNTService.exe" },
       { "BSAgentSvr", "tvnserver", "WFBSMlogon" } },
      {"红蜘蛛多媒体网络教室",
       { "rscheck.exe", "checkrs.exe", "REDAgent.exe", "PerformanceCheck.exe", "edpaper.exe", "Adapter.exe", "repview.exe",
          "FormatPaper.exe" },
       { "appcheck2", "checkapp2" }                }
    };
    class basic_config_node {
      public:
        const ansi_char *const self_name;
        virtual auto load( const bool, ansi_std_string & ) -> void                 = 0;
        virtual auto prepare_reload() -> void                                      = 0;
        virtual auto sync( ansi_std_string & ) -> void                             = 0;
        virtual auto operator=( const basic_config_node & ) -> basic_config_node & = delete;
        virtual auto operator=( basic_config_node && ) -> basic_config_node &      = delete;
        basic_config_node( const ansi_char *const _self_name )
          : self_name{ _self_name }
        { }
        basic_config_node( const basic_config_node & ) = delete;
        basic_config_node( basic_config_node && )      = delete;
        virtual ~basic_config_node()                   = default;
    };
    class option_op final : public basic_config_node {
      public:
        virtual auto load( const bool _is_reload, ansi_std_string &_line ) -> void override final
        {
            if ( _is_reload ) {
                return;
            }
            for ( auto &main_key : options.main_keys ) {
                for ( auto &sub_key : main_key.sub_keys ) {
                    if ( _line == std::format( "{}.{} = {}", main_key.self_name, sub_key.self_name, true ) ) {
                        sub_key.enable();
                    } else if ( _line == std::format( "{}.{} = {}", main_key.self_name, sub_key.self_name, false ) ) {
                        sub_key.disable();
                    }
                }
            }
        }
        virtual auto prepare_reload() -> void override final { }
        virtual auto sync( ansi_std_string &_out ) -> void override final
        {
            for ( const auto &main_key : options.main_keys ) {
                for ( const auto &sub_key : main_key.sub_keys ) {
                    _out.append( std::format( "{}.{} = {}\n", main_key.self_name, sub_key.self_name, sub_key.get() ) );
                }
            }
        }
        virtual auto operator=( const option_op & ) -> option_op & = delete;
        virtual auto operator=( option_op && ) -> option_op &      = delete;
        option_op()
          : basic_config_node{ "options" }
        { }
        option_op( const option_op & ) = delete;
        option_op( option_op && )      = delete;
        virtual ~option_op()           = default;
    };
    class custom_rules_execs_op final : public basic_config_node {
      public:
        virtual auto load( const bool, ansi_std_string &_line ) -> void override final
        {
            custom_rules.execs.emplace_back( std::move( _line ) );
        }
        virtual auto prepare_reload() -> void override final
        {
            custom_rules.execs.clear();
        }
        virtual auto sync( ansi_std_string &_out ) -> void override final
        {
            for ( const auto &exec : custom_rules.execs ) {
                _out.append( exec.c_str() ).push_back( '\n' );
            }
        }
        virtual auto operator=( const custom_rules_execs_op & ) -> custom_rules_execs_op & = delete;
        virtual auto operator=( custom_rules_execs_op && ) -> custom_rules_execs_op &      = delete;
        custom_rules_execs_op()
          : basic_config_node{ "custom_rules_execs" }
        { }
        custom_rules_execs_op( const custom_rules_execs_op & ) = delete;
        custom_rules_execs_op( custom_rules_execs_op && )      = delete;
        virtual ~custom_rules_execs_op()                       = default;
    };
    class custom_rules_servs_op final : public basic_config_node {
      public:
        virtual auto load( const bool, ansi_std_string &_line ) -> void override final
        {
            custom_rules.servs.emplace_back( std::move( _line ) );
        }
        virtual auto prepare_reload() -> void override final
        {
            custom_rules.servs.clear();
        }
        virtual auto sync( ansi_std_string &_out ) -> void override final
        {
            for ( const auto &serv : custom_rules.servs ) {
                _out.append( serv.c_str() ).push_back( '\n' );
            }
        }
        virtual auto operator=( const custom_rules_servs_op & ) -> custom_rules_servs_op & = delete;
        virtual auto operator=( custom_rules_servs_op && ) -> custom_rules_servs_op &      = delete;
        custom_rules_servs_op()
          : basic_config_node{ "custom_rules_servs" }
        { }
        custom_rules_servs_op( const custom_rules_servs_op & ) = delete;
        custom_rules_servs_op( custom_rules_servs_op && )      = delete;
        virtual ~custom_rules_servs_op()                       = default;
    };
    using basic_config_node_smart_ptr = std::unique_ptr< basic_config_node >;
    inline basic_config_node_smart_ptr configs[]{
      basic_config_node_smart_ptr{ new option_op }, basic_config_node_smart_ptr{ new custom_rules_execs_op },
      basic_config_node_smart_ptr{ new custom_rules_servs_op } };
    inline auto wait()
    {
        for ( auto i{ 3s }; i > 0s; --i ) {
            std::print( " {} 后返回.\r", i );
            cpp_utils::perf_sleep( 1s );
        }
    }
    inline auto exit( cpp_utils::console_ui::func_args )
    {
        return cpp_utils::console_ui::exit;
    }
    inline auto relaunch( cpp_utils::console_ui::func_args )
    {
        cpp_utils::relaunch_as_admin();
        return cpp_utils::console_ui::exit;
    }
    inline auto info( cpp_utils::console_ui::func_args )
    {
        auto visit_repo_webpage{ []( cpp_utils::console_ui::func_args ) static
        {
            ShellExecuteA( nullptr, "open", INFO_REPO_URL, nullptr, nullptr, SW_SHOWNORMAL );
            return cpp_utils::console_ui::back;
        } };
        cpp_utils::console_ui ui;
        std::print( " -> 准备用户界面.\n" );
        ui.add_back( "                    [ 信  息 ]\n\n" )
          .add_back( " < 返回 ", exit, cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity )
          .add_back( "\n[ 名称 ]\n\n " INFO_FULL_NAME " \n\n[ 版本 ]\n\n " INFO_VERSION " " )
          .add_back( "\n[ 仓库 ]\n" )
          .add_back(
            " " INFO_REPO_URL " ", visit_repo_webpage,
            cpp_utils::console_value::text_default | cpp_utils::console_value::text_foreground_intensity
              | cpp_utils::console_value::text_lvb_underscore )
          .add_back( "\n[ 许可证 ]\n\n " INFO_LICENSE " \n\n " INFO_COPYRIGHT )
          .show();
        return cpp_utils::console_ui::back;
    }
    inline auto toolkit( cpp_utils::console_ui::func_args )
    {
        std::print( " -> 准备用户界面.\n" );
        auto launch_cmd{ []( cpp_utils::console_ui::func_args _args ) static
        {
            cpp_utils::set_console_title( INFO_SHORT_NAME " - 命令提示符" );
            cpp_utils::set_console_size( 120, 30 );
            cpp_utils::fix_window_size( current_window_handle, false );
            cpp_utils::enable_window_maximize_ctrl( current_window_handle, true );
            _args.parent_ui.lock( false, false );
            SetConsoleScreenBufferSize( GetStdHandle( STD_OUTPUT_HANDLE ), { 128, SHRT_MAX - 1 } );
            std::system( R"(C:\Windows\System32\cmd.exe)" );
            cpp_utils::set_console_title( INFO_SHORT_NAME );
            cpp_utils::set_console_size( CONSOLE_WIDTH, CONSOLE_HEIGHT );
            cpp_utils::fix_window_size( current_window_handle, true );
            cpp_utils::enable_window_maximize_ctrl( current_window_handle, false );
            return cpp_utils::console_ui::back;
        } };
        class cmd_executor final {
          private:
            const ansi_std_string cmd_;
          public:
            auto operator()( cpp_utils::console_ui::func_args )
            {
                std::print( " -> 执行操作系统命令.\n{}\n", ansi_std_string( CONSOLE_WIDTH, '-' ) );
                std::system( cmd_.c_str() );
                return cpp_utils::console_ui::back;
            }
            auto operator=( const cmd_executor & ) -> cmd_executor & = delete;
            auto operator=( cmd_executor && ) -> cmd_executor &      = delete;
            cmd_executor( const ansi_char *const _cmd )
              : cmd_{ _cmd }
            { }
            cmd_executor( const cmd_executor & ) = default;
            cmd_executor( cmd_executor && )      = default;
            ~cmd_executor()                      = default;
        };
        constexpr const ansi_char *common_ops[][ 2 ]{
          {"重启资源管理器",
           R"(C:\Windows\System32\taskkill.exe /f /im explorer.exe && C:\Windows\System32\timeout.exe /t 3 /nobreak && start C:\Windows\explorer.exe)"},
          {"修复操作系统",
           R"(C:\Windows\System32\dism.exe /online /cleanup-image /restorehealth && C:\Windows\System32\sfc.exe /scannow)"                            },
          {"恢复 USB 设备访问",
           R"(C:\Windows\System32\reg.exe add "HKLM\SYSTEM\CurrentControlSet\Services\USBSTOR" /f /t reg_dword /v Start /d 3)"                        },
          {"恢复 Google Chrome 离线游戏",
           R"(C:\Windows\System32\reg.exe delete "HKLM\SOFTWARE\Policies\Google\Chrome" /f /v AllowDinosaurEasterEgg)"                                },
          {"恢复 Microsoft Edge 离线游戏",
           R"(C:\Windows\System32\reg.exe delete "HKLM\SOFTWARE\Policies\Microsoft\Edge" /f /v AllowSurfGame)"                                        }
        };
        cpp_utils::console_ui ui;
        std::print( " -> 准备用户界面.\n" );
        ui.add_back( "                   [ 工 具 箱 ]\n\n" )
          .add_back( " < 返回 ", exit, cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity )
          .add_back( " > 命令提示符 ", launch_cmd )
          .add_back( "\n[ 常用操作 ]\n" );
        for ( const auto &common_op : common_ops ) {
            ui.add_back( std::format( " > {} ", common_op[ 0 ] ), cmd_executor{ common_op[ 1 ] } );
        }
        ui.show();
        return cpp_utils::console_ui::back;
    }
    inline auto set_console_attrs( const std::stop_token _msg )
    {
        const auto &is_translucent{ options[ "window" ][ "translucent" ] };
        const auto &is_disable_close_ctrl{ options[ "window" ][ "disable_close_ctrl" ] };
        if ( is_disable_x_option_hot_reload ) {
            SetLayeredWindowAttributes( current_window_handle, RGB( 0, 0, 0 ), is_translucent ? 230 : 255, LWA_ALPHA );
            EnableMenuItem(
              GetSystemMenu( current_window_handle, FALSE ), SC_CLOSE,
              is_disable_close_ctrl ? MF_BYCOMMAND | MF_DISABLED | MF_GRAYED : MF_BYCOMMAND | MF_ENABLED );
            return;
        }
        while ( !_msg.stop_requested() ) {
            SetLayeredWindowAttributes( current_window_handle, RGB( 0, 0, 0 ), is_translucent ? 230 : 255, LWA_ALPHA );
            EnableMenuItem(
              GetSystemMenu( current_window_handle, FALSE ), SC_CLOSE,
              is_disable_close_ctrl ? MF_BYCOMMAND | MF_DISABLED | MF_GRAYED : MF_BYCOMMAND | MF_ENABLED );
            cpp_utils::perf_sleep( default_thread_sleep_time );
        }
    }
    inline auto keep_window_top( const std::stop_token _msg )
    {
        const auto &is_keep_window_top{ options[ "window" ][ "keep_window_top" ] };
        if ( is_disable_x_option_hot_reload && !is_keep_window_top ) {
            return;
        }
        constexpr auto sleep_time{ 100ms };
        const auto current_thread_id{ GetCurrentThreadId() };
        const auto current_window_thread_frocess_id{ GetWindowThreadProcessId( current_window_handle, nullptr ) };
        if ( is_disable_x_option_hot_reload ) {
            cpp_utils::loop_keep_window_top(
              current_window_handle, current_thread_id, current_window_thread_frocess_id, sleep_time,
              []( const std::stop_token _msg ) { return !_msg.stop_requested(); }, _msg );
            cpp_utils::cancle_top_window( current_window_handle );
            return;
        }
        while ( !_msg.stop_requested() ) {
            if ( !is_keep_window_top ) {
                cpp_utils::cancle_top_window( current_window_handle );
                cpp_utils::perf_sleep( default_thread_sleep_time );
                continue;
            }
            cpp_utils::keep_window_top( current_window_handle, current_thread_id, current_window_thread_frocess_id );
            cpp_utils::perf_sleep( sleep_time );
        }
        cpp_utils::cancle_top_window( current_window_handle );
    }
    inline auto fix_os_env( const std::stop_token _msg )
    {
        const auto &is_fix_os_env{ options[ "crack_restore" ][ "fix_os_env" ] };
        if ( is_disable_x_option_hot_reload && !is_fix_os_env ) {
            return;
        }
        constexpr const ansi_char *hkcu_reg_dirs[]{
          R"(Software\Policies\Microsoft\Windows\System)", R"(Software\Microsoft\Windows\CurrentVersion\Policies\System)",
          R"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer)" };
        constexpr const ansi_char *execs[]{
          "taskkill.exe", "sc.exe",      "net.exe", "reg.exe",  "cmd.exe", "taskmgr.exe",
          "perfmon.exe",  "regedit.exe", "mmc.exe", "dism.exe", "sfc.exe" };
        auto core_op{ [ = ]
        {
            for ( const auto &reg_dir : hkcu_reg_dirs ) {
                RegDeleteTreeA( HKEY_CURRENT_USER, reg_dir );
            }
            for ( const auto &exec : execs ) {
                RegDeleteTreeA(
                  HKEY_LOCAL_MACHINE,
                  std::format( R"(SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\{})", exec ).c_str() );
            }
            cpp_utils::perf_sleep( 1s );
        } };
        if ( is_disable_x_option_hot_reload ) {
            while ( !_msg.stop_requested() ) {
                core_op();
            }
            return;
        }
        while ( !_msg.stop_requested() ) {
            if ( !is_fix_os_env ) {
                cpp_utils::perf_sleep( default_thread_sleep_time );
                continue;
            }
            core_op();
        }
    }
    inline constexpr auto option_ctrl_color{
      cpp_utils::console_value::text_foreground_red | cpp_utils::console_value::text_foreground_green };
    inline auto load_config( const bool _is_reload )
    {
        std::ifstream config_file{ config_file_name, std::ios::in };
        if ( !config_file.good() ) {
            return;
        }
        if ( _is_reload ) {
            std::print( " -> 准备配置重载.\n" );
            for ( auto &config : configs ) {
                config->prepare_reload();
            }
        }
        std::print( " -> 加载配置文件.\n" );
        ansi_std_string line;
        ansi_std_string_view line_view;
        basic_config_node *node_ptr{ nullptr };
        while ( std::getline( config_file, line ) ) {
            line_view = line;
            if ( line_view.empty() ) {
                continue;
            }
            if ( line_view.front() == '#' ) {
                continue;
            }
            if ( line_view.size() >= 4 && line_view.substr( 0, sizeof( "[ " ) - 1 ) == "[ "
                 && line_view.substr( line_view.size() - sizeof( " ]" ) + 1, line_view.size() ) == " ]" )
            {
                line_view = line_view.substr( sizeof( "[ " ) - 1, line_view.size() - sizeof( " ]" ) - 1 );
                for ( auto &config : configs ) {
                    if ( line_view == config->self_name ) {
                        node_ptr = config.get();
                        break;
                    }
                    node_ptr = nullptr;
                }
                continue;
            }
            if ( node_ptr != nullptr ) {
                node_ptr->load( _is_reload, line );
            }
        }
    }
    inline auto edit_config( cpp_utils::console_ui::func_args )
    {
        auto sync{ []( cpp_utils::console_ui::func_args )
        {
            std::print( "                    [ 配  置 ]\n\n\n" );
            load_config( true );
            std::print( " -> 保存更改.\n" );
            ansi_std_string config_text{};
            for ( auto &config : configs ) {
                config_text.append( std::format( "[ {} ]\n", config->self_name ) );
                config->sync( config_text );
            }
            std::ofstream config_file{ config_file_name, std::ios::out | std::ios::trunc };
            config_file << std::format(
              "# " INFO_FULL_NAME
              "\n# [ 同步时间 ] UTC {}"
              "\n# [ 同步版本 ] " INFO_VERSION "\n# [ 字符编码 ] " CHARSET_NAME "\n",
              std::chrono::system_clock::now() )
                        << config_text << std::flush;
            std::print( "\n ({}) 同步配置{}.\n\n", config_file.good() ? 'i' : '!', config_file.good() ? "成功" : "失败" );
            wait();
            return cpp_utils::console_ui::back;
        } };
        auto open_file{ []( cpp_utils::console_ui::func_args )
        {
            if ( std::ifstream{ config_file_name, std::ios::in }.good() ) {
                std::print( " -> 打开配置.\n" );
                ShellExecuteA( nullptr, "open", config_file_name, nullptr, nullptr, SW_SHOWNORMAL );
                return cpp_utils::console_ui::back;
            }
            std::print(
              "                    [ 配  置 ]\n\n\n"
              " (i) 无法读取配置文件.\n\n" );
            wait();
            return cpp_utils::console_ui::back;
        } };
        class option_setter final {
          private:
            option_node::sub_key &sub_key_;
            const bool sub_key_value_;
          public:
            auto operator()( cpp_utils::console_ui::func_args )
            {
                switch ( sub_key_value_ ) {
                    case true : sub_key_.enable(); break;
                    case false : sub_key_.disable(); break;
                }
                return cpp_utils::console_ui::back;
            }
            auto operator=( const option_setter & ) -> option_setter & = delete;
            auto operator=( option_setter && ) -> option_setter &      = delete;
            option_setter( option_node::sub_key &_sub_key, const bool _sub_key_value )
              : sub_key_{ _sub_key }
              , sub_key_value_{ _sub_key_value }
            { }
            option_setter( const option_setter & ) = default;
            option_setter( option_setter && )      = default;
            ~option_setter()                       = default;
        };
        class option_shower final {
          private:
            option_node::main_key &main_key_;
          public:
            auto operator()( cpp_utils::console_ui::func_args )
            {
                cpp_utils::console_ui ui;
                std::print( " -> 准备用户界面.\n" );
                ui.add_back( "                    [ 配  置 ]\n\n" )
                  .add_back(
                    std::format( " < 折叠 {} ", main_key_.showed_name ), exit,
                    cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity );
                for ( auto &sub_key : main_key_.sub_keys ) {
                    ui.add_back( std::format( "\n[ {} ]\n", sub_key.showed_name ) )
                      .add_back( " > 启用 ", option_setter{ sub_key, true }, option_ctrl_color )
                      .add_back( " > 禁用 ", option_setter{ sub_key, false }, option_ctrl_color );
                }
                ui.show();
                return cpp_utils::console_ui::back;
            }
            auto operator=( const option_shower & ) -> option_shower & = delete;
            auto operator=( option_shower && ) -> option_shower &      = delete;
            option_shower( option_node::main_key &_main_key )
              : main_key_{ _main_key }
            { }
            option_shower( const option_shower & ) = default;
            option_shower( option_shower && )      = default;
            ~option_shower()                       = default;
        };
        cpp_utils::console_ui ui;
        std::print( " -> 准备用户界面.\n" );
        ui
          .add_back( std::format(
            "                    [ 配  置 ]\n\n\n"
            " (i) 所有选项默认禁用. 相关信息可参阅文档.\n"
            "     无标识选项可进行实时热重载.\n"
            "     标 (*) 选项热重载默认启用,\n"
            "     每 {} 自动执行, 可禁用.\n"
            "     标 (-) 选项无法进行热重载.\n",
            default_thread_sleep_time ) )
          .add_back( " < 返回 ", exit, cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity )
          .add_back( " > 同步配置 ", sync )
          .add_back( " > 打开配置文件 ", open_file )
          .add_back( "\n[ 选项 ]\n" );
        for ( auto &key : options.main_keys ) {
            ui.add_back( std::format( " > {} ", key.showed_name ), option_shower{ key } );
        }
        ui.show();
        return cpp_utils::console_ui::back;
    }
    inline const auto &crack_restore_option_node{ options[ "crack_restore" ] };
    inline const auto &is_hijack_execs{ crack_restore_option_node[ "hijack_execs" ] };
    inline const auto &is_set_serv_startup_types{ crack_restore_option_node[ "set_serv_startup_types" ] };
    class crack_with_rules final {
      public:
        const rule_node &rules_;
      public:
        auto operator()( cpp_utils::console_ui::func_args )
        {
            std::print( "                    [ 破  解 ]\n\n\n" );
            if ( rules_.empty() ) {
                std::print( " (i) 规则为空.\n\n" );
                wait();
                return cpp_utils::console_ui::back;
            }
            std::print( " -> 生成并执行操作系统命令.\n{}\n", ansi_std_string( CONSOLE_WIDTH, '-' ) );
            if ( is_hijack_execs ) {
                for ( const auto &exec : rules_.execs ) {
                    std::system(
                      std::format(
                        R"(C:\Windows\System32\reg.exe add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution options\{}" /f /t reg_sz /v debugger /d "nul")",
                        exec )
                        .c_str() );
                }
            }
            if ( is_set_serv_startup_types ) {
                for ( const auto &serv : rules_.servs ) {
                    std::system( std::format( R"(C:\Windows\System32\sc.exe config "{}" start= disabled)", serv ).c_str() );
                }
            }
            for ( const auto &exec : rules_.execs ) {
                std::system( std::format( R"(C:\Windows\System32\taskkill.exe /f /im "{}")", exec ).c_str() );
            }
            for ( const auto &serv : rules_.servs ) {
                std::system( std::format( R"(C:\Windows\System32\net.exe stop "{}" /y)", serv ).c_str() );
            }
            return cpp_utils::console_ui::back;
        }
        auto operator=( const crack_with_rules & ) -> crack_with_rules & = default;
        auto operator=( crack_with_rules && ) -> crack_with_rules &      = default;
        crack_with_rules( const rule_node &_rules )
          : rules_{ _rules }
        { }
        crack_with_rules( const crack_with_rules & ) = default;
        crack_with_rules( crack_with_rules && )      = default;
        ~crack_with_rules()                          = default;
    };
    class restore_with_rules final {
      public:
        const rule_node &rules_;
      public:
        auto operator()( cpp_utils::console_ui::func_args )
        {
            std::print( "                    [ 恢  复 ]\n\n\n" );
            if ( rules_.empty() ) {
                std::print( " (i) 规则为空.\n\n" );
                wait();
                return cpp_utils::console_ui::back;
            }
            std::print( " -> 生成并执行操作系统命令.\n{}\n", ansi_std_string( CONSOLE_WIDTH, '-' ) );
            if ( is_hijack_execs ) {
                for ( const auto &exec : rules_.execs ) {
                    std::system(
                      std::format(
                        R"(C:\Windows\System32\reg.exe delete "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution options\{}" /f)",
                        exec )
                        .c_str() );
                }
            }
            if ( is_set_serv_startup_types ) {
                for ( const auto &serv : rules_.servs ) {
                    std::system( std::format( R"(C:\Windows\System32\sc.exe config "{}" start= auto)", serv ).c_str() );
                }
            }
            for ( const auto &serv : rules_.servs ) {
                std::system( std::format( R"(C:\Windows\System32\net.exe start "{}")", serv ).c_str() );
            }
            return cpp_utils::console_ui::back;
        }
        auto operator=( const restore_with_rules & ) -> restore_with_rules & = default;
        auto operator=( restore_with_rules && ) -> restore_with_rules &      = default;
        restore_with_rules( const rule_node &_rules )
          : rules_{ _rules }
        { }
        restore_with_rules( const restore_with_rules & ) = default;
        restore_with_rules( restore_with_rules && )      = default;
        ~restore_with_rules()                            = default;
    };
}