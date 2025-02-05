#pragma once
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
    using wide_std_string      = cpp_utils::wide_std_string;
    inline constexpr auto config_file_name{ "config.ini" };
    inline constexpr auto default_thread_sleep_time{ 1s };
    struct option_node final {
        struct sub_key final {
          private:
            std::atomic_flag value{};
          public:
            const ansi_char *const self_name;
            const ansi_char *const showed_name;
            auto enable()
            {
                value.test_and_set();
            }
            auto disable()
            {
                value.clear();
            }
            auto get() const
            {
                return value.test();
            }
            auto operator=( const sub_key & ) -> sub_key & = delete;
            auto operator=( sub_key && ) -> sub_key &      = delete;
            sub_key( const ansi_char *const _self_name, const ansi_char *const _showed_name )
              : self_name{ _self_name }
              , showed_name{ _showed_name }
            { }
            sub_key( const sub_key &_src )
              : value{ _src.get() }
              , self_name{ _src.self_name }
              , showed_name{ _src.showed_name }
            { }
            sub_key( sub_key &&_src )
              : value{ _src.get() }
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
            { { "hijack_execs", "劫持可执行文件" }, { "set_serv_startup_types", "设置服务启动类型" } } },
          { "window",
            "窗口显示",
            { { "topmost_show", "(*) 置顶显示" },
              { "disable_close_ctrl", "(*) 禁用关闭控件" },
              { "translucency", "(*) 半透明化" } } },
          { "experiment",
            "实验性内容",
            { { "fix_os_env", "(*) 修复操作系统环境" }, { "disable_x_option_hot_reload", "(-) 禁用标 (*) 选项热重载" } } } } } };
    inline const auto &is_disabled_x_option_hot_reload{ options[ "experiment" ][ "disable_x_option_hot_reload" ] };
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
        virtual auto prepare_reloading() -> void                                   = 0;
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
        virtual auto load( const bool _is_reloaded, ansi_std_string &_line ) -> void override final
        {
            if ( _is_reloaded ) {
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
        virtual auto prepare_reloading() -> void override final { }
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
        virtual auto prepare_reloading() -> void override final
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
        virtual auto prepare_reloading() -> void override final
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
    template < typename _chrono_type_ >
    inline auto wait( const _chrono_type_ _time )
    {
        constexpr _chrono_type_ zero{ 0 };
        constexpr _chrono_type_ one{ 1 };
        for ( auto i{ _time }; i > zero; --i ) {
            std::print( " {} 后返回.\r", i );
            cpp_utils::perf_sleep( one );
        }
    }
    inline auto quit( cpp_utils::console_ui_ansi::func_args )
    {
        return cpp_utils::console_value::ui_quit;
    }
    inline auto relaunch( cpp_utils::console_ui_ansi::func_args )
    {
        cpp_utils::relaunch_as_admin();
        return cpp_utils::console_value::ui_quit;
    }
    inline auto info( cpp_utils::console_ui_ansi::func_args )
    {
        auto visit_repo_webpage{ []( cpp_utils::console_ui_ansi::func_args )
        {
            ShellExecuteA( nullptr, "open", INFO_REPO_URL, nullptr, nullptr, SW_SHOWNORMAL );
            return cpp_utils::console_value::ui_back;
        } };
        cpp_utils::console_ui_ansi ui{};
        std::print( " -> 准备用户界面.\n" );
        ui.add_back( "                    [ 信  息 ]\n\n" )
          .add_back( " < 返回 ", quit, cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity )
          .add_back( "\n[ 名称 ]\n\n " INFO_FULL_NAME " \n\n[ 版本 ]\n\n " INFO_VERSION " " )
          .add_back( "\n[ 仓库 ]\n" )
          .add_back(
            " " INFO_REPO_URL " ", visit_repo_webpage,
            cpp_utils::console_value::text_default | cpp_utils::console_value::text_lvb_underscore )
          .add_back( "\n[ 许可证 ]\n\n " INFO_LICENSE " \n\n (C) 2023 - present " INFO_DEVELOPER "." )
          .show();
        return cpp_utils::console_value::ui_back;
    }
    inline auto toolkit( cpp_utils::console_ui_ansi::func_args )
    {
        std::print( " -> 准备用户界面.\n" );
        auto launch_cmd{ []( cpp_utils::console_ui_ansi::func_args _args )
        {
            const auto &is_disabled_close_ctrl{ options[ "window" ][ "disable_close_ctrl" ] };
            const auto &is_translucency{ options[ "window" ][ "translucency" ] };
            _args.parent_ui
              .set_console(
                INFO_SHORT_NAME " - 命令提示符", CHARSET_ID, 120, 30, false, false, is_disabled_close_ctrl.get() ? false : true,
                is_translucency.get() ? 230 : 255 )
              .lock( false, false );
            SetConsoleScreenBufferSize( GetStdHandle( STD_OUTPUT_HANDLE ), { 128, SHRT_MAX - 1 } );
            std::system( R"(C:\Windows\System32\cmd.exe)" );
            _args.parent_ui.set_console(
              INFO_SHORT_NAME, CHARSET_ID, CONSOLE_WIDTH, CONSOLE_HEIGHT, true, false,
              is_disabled_close_ctrl.get() ? false : true, is_translucency.get() ? 230 : 255 );
            return cpp_utils::console_value::ui_back;
        } };
        class cmd_executor final {
          private:
            const ansi_std_string cmd_;
          public:
            auto operator()( cpp_utils::console_ui_ansi::func_args )
            {
                std::print( " -> 执行操作系统命令.\n{}\n", ansi_std_string( CONSOLE_WIDTH, '-' ) );
                std::system( cmd_.c_str() );
                return cpp_utils::console_value::ui_back;
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
           R"(C:\Windows\System32\taskkill.exe /f /im explorer.exe && timeout /t 3 /nobreak && start C:\Windows\explorer.exe)"},
          {"恢复 USB 设备访问",
           R"(C:\Windows\System32\reg.exe add "HKLM\SYSTEM\CurrentControlSet\Services\USBSTOR" /f /t reg_dword /v Start /d 3)"},
          {"恢复 Google Chrome 离线游戏",
           R"(C:\Windows\System32\reg.exe delete "HKLM\SOFTWARE\Policies\Google\Chrome" /f /v AllowDinosaurEasterEgg)"        },
          {"恢复 Microsoft Edge 离线游戏",
           R"(C:\Windows\System32\reg.exe delete "HKLM\SOFTWARE\Policies\Microsoft\Edge" /f /v AllowSurfGame)"                }
        };
        cpp_utils::console_ui_ansi ui{};
        std::print( " -> 准备用户界面.\n" );
        ui.add_back( "                   [ 工 具 箱 ]\n\n" )
          .add_back( " < 返回 ", quit, cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity )
          .add_back( " > 命令提示符 ", launch_cmd )
          .add_back( "\n[ 常用操作 ]\n" );
        for ( const auto &common_op : common_ops ) {
            ui.add_back( std::format( " > {} ", common_op[ 0 ] ), cmd_executor{ common_op[ 1 ] } );
        }
        ui.show();
        return cpp_utils::console_value::ui_back;
    }
    auto set_console_attrs( const std::stop_token _msg )
    {
        const auto &is_translucency{ options[ "window" ][ "translucency" ] };
        const auto &is_disabled_close_ctrl{ options[ "window" ][ "disable_close_ctrl" ] };
        if ( is_disabled_x_option_hot_reload.get() ) {
            SetLayeredWindowAttributes( GetConsoleWindow(), RGB( 0, 0, 0 ), is_translucency.get() ? 230 : 255, LWA_ALPHA );
            EnableMenuItem(
              GetSystemMenu( GetConsoleWindow(), FALSE ), SC_CLOSE,
              is_disabled_close_ctrl.get() ? MF_BYCOMMAND | MF_DISABLED | MF_GRAYED : MF_BYCOMMAND | MF_ENABLED );
            return;
        }
        while ( !_msg.stop_requested() ) {
            SetLayeredWindowAttributes( GetConsoleWindow(), RGB( 0, 0, 0 ), is_translucency.get() ? 230 : 255, LWA_ALPHA );
            EnableMenuItem(
              GetSystemMenu( GetConsoleWindow(), FALSE ), SC_CLOSE,
              is_disabled_close_ctrl.get() ? MF_BYCOMMAND | MF_DISABLED | MF_GRAYED : MF_BYCOMMAND | MF_ENABLED );
            cpp_utils::perf_sleep( default_thread_sleep_time );
        }
    }
    auto topmost_show_window( const std::stop_token _msg )
    {
        const auto &is_topmost_shown{ options[ "window" ][ "topmost_show" ] };
        if ( is_disabled_x_option_hot_reload.get() && !is_topmost_shown.get() ) {
            return;
        }
        const auto this_window{ GetConsoleWindow() };
        const auto foreground_id{ GetWindowThreadProcessId( this_window, nullptr ) };
        const auto current_id{ GetCurrentThreadId() };
        auto core_op{ [ = ]
        {
            AttachThreadInput( current_id, foreground_id, TRUE );
            ShowWindow( this_window, SW_SHOWNORMAL );
            SetForegroundWindow( this_window );
            AttachThreadInput( current_id, foreground_id, FALSE );
            SetWindowPos( this_window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
            cpp_utils::perf_sleep( 100ms );
        } };
        if ( is_disabled_x_option_hot_reload.get() ) {
            while ( !_msg.stop_requested() ) {
                core_op();
            }
            SetWindowPos( GetConsoleWindow(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
            return;
        }
        while ( !_msg.stop_requested() ) {
            if ( !is_topmost_shown.get() ) {
                SetWindowPos( GetConsoleWindow(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
                cpp_utils::perf_sleep( default_thread_sleep_time );
                continue;
            }
            core_op();
        }
        SetWindowPos( GetConsoleWindow(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
    }
    auto fix_os_env( const std::stop_token _msg )
    {
        const auto &is_fixed_os_env{ options[ "experiment" ][ "fix_os_env" ] };
        if ( is_disabled_x_option_hot_reload.get() && !is_fixed_os_env.get() ) {
            return;
        }
        constexpr const ansi_char *hkcu_reg_dirs[]{
          R"(Software\Policies\Microsoft\Windows\System)", R"(Software\Microsoft\Windows\CurrentVersion\Policies\System)",
          R"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer)" };
        constexpr const ansi_char *execs[]{
          "mode.com", "chcp.com", "ntsd.exe",    "taskkill.exe", "sc.exe",      "net.exe",
          "reg.exe",  "cmd.exe",  "taskmgr.exe", "perfmon.exe",  "regedit.exe", "mmc.exe" };
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
        if ( is_disabled_x_option_hot_reload.get() ) {
            while ( !_msg.stop_requested() ) {
                core_op();
            }
            return;
        }
        while ( !_msg.stop_requested() ) {
            if ( !is_fixed_os_env.get() ) {
                cpp_utils::perf_sleep( default_thread_sleep_time );
                continue;
            }
            core_op();
        }
    }
    class config_op final {
      public:
        enum class mod { load, edit };
      private:
        const mod mod_data_;
        static constexpr auto option_button_color{
          cpp_utils::console_value::text_foreground_red | cpp_utils::console_value::text_foreground_green };
        auto load_( const bool _is_reloaded )
        {
            std::ifstream config_file{ config_file_name, std::ios::in };
            if ( !config_file.good() ) {
                return;
            }
            if ( _is_reloaded ) {
                std::print( " -> 准备配置重载.\n" );
                for ( auto &config : configs ) {
                    config->prepare_reloading();
                }
            }
            std::print( " -> 加载配置文件.\n" );
            ansi_std_string line{};
            ansi_std_string_view line_view{};
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
                    node_ptr->load( _is_reloaded, line );
                }
            }
        }
        auto sync()
        {
            std::print( "                    [ 配  置 ]\n\n\n" );
            load_( true );
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
            wait( 3s );
            return cpp_utils::console_value::ui_back;
        }
        auto open_file()
        {
            if ( std::ifstream{ config_file_name, std::ios::in }.good() ) {
                std::print( " -> 打开配置.\n" );
                ShellExecuteA( nullptr, "open", config_file_name, nullptr, nullptr, SW_SHOWNORMAL );
                return cpp_utils::console_value::ui_back;
            }
            std::print(
              "                    [ 配  置 ]\n\n\n"
              " (i) 无法读取配置文件.\n\n" );
            wait( 3s );
            return cpp_utils::console_value::ui_back;
        }
        class option_setter final {
          private:
            option_node::sub_key &sub_key_;
            const bool sub_key_value_;
          public:
            auto operator()( cpp_utils::console_ui_ansi::func_args )
            {
                switch ( sub_key_value_ ) {
                    case true : sub_key_.enable(); break;
                    case false : sub_key_.disable(); break;
                }
                return cpp_utils::console_value::ui_back;
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
            auto operator()( cpp_utils::console_ui_ansi::func_args )
            {
                cpp_utils::console_ui_ansi ui{};
                std::print( " -> 准备用户界面.\n" );
                ui.add_back( "                    [ 配  置 ]\n\n" )
                  .add_back(
                    std::format( " < 折叠 {} ", main_key_.showed_name ), quit,
                    cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity );
                for ( auto &sub_key : main_key_.sub_keys ) {
                    ui.add_back( std::format( "\n[ {} ]\n", sub_key.showed_name ) )
                      .add_back( " > 启用 ", option_setter{ sub_key, true }, option_button_color )
                      .add_back( " > 禁用 ", option_setter{ sub_key, false }, option_button_color );
                }
                ui.show();
                return cpp_utils::console_value::ui_back;
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
        auto edit_()
        {
            cpp_utils::console_ui_ansi ui{};
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
              .add_back( " < 返回 ", quit, cpp_utils::console_value::text_foreground_green | cpp_utils::console_value::text_foreground_intensity )
              .add_back( " > 同步配置 ", [ this ]( cpp_utils::console_ui_ansi::func_args ) { return sync(); } )
              .add_back( " > 打开配置文件 ", [ this ]( cpp_utils::console_ui_ansi::func_args ) { return open_file(); } )
              .add_back( "\n[ 选项 ]\n" );
            for ( auto &key : options.main_keys ) {
                ui.add_back( std::format( " > {} ", key.showed_name ), option_shower{ key } );
            }
            ui.show();
        }
      public:
        auto operator()( cpp_utils::console_ui_ansi::func_args )
        {
            switch ( mod_data_ ) {
                case mod::load : load_( false ); break;
                case mod::edit : edit_(); break;
            }
            return cpp_utils::console_value::ui_back;
        }
        auto operator=( const config_op & ) -> config_op & = delete;
        auto operator=( config_op && ) -> config_op &      = delete;
        config_op( const mod _mod_data )
          : mod_data_{ _mod_data }
        { }
        config_op( const config_op & ) = default;
        config_op( config_op && )      = default;
        ~config_op()                   = default;
    };
    class rule_op final {
      public:
        enum class mod { crack, restore };
      private:
        const mod mod_data_;
        const rule_node &rules_;
      public:
        auto operator()( cpp_utils::console_ui_ansi::func_args )
        {
            std::print( "                 [ 破 解 / 恢 复 ]\n\n\n" );
            if ( rules_.empty() ) {
                std::print( " (i) 规则为空.\n\n" );
                wait( 3s );
                return cpp_utils::console_value::ui_back;
            }
            const auto &crack_restore_option_node{ options[ "crack_restore" ] };
            const auto &is_hijacked_execs{ crack_restore_option_node[ "hijack_execs" ] };
            const auto &is_set_serv_startup_types{ crack_restore_option_node[ "set_serv_startup_types" ] };
            std::print( " -> 生成并执行操作系统命令.\n{}\n", ansi_std_string( CONSOLE_WIDTH, '-' ) );
            switch ( mod_data_ ) {
                case mod::crack : {
                    if ( is_hijacked_execs.get() ) {
                        for ( const auto &exec : rules_.execs ) {
                            std::system(
                              std::format(
                                R"(C:\Windows\System32\reg.exe add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution options\{}" /f /t reg_sz /v debugger /d "nul")",
                                exec )
                                .c_str() );
                        }
                    }
                    if ( is_set_serv_startup_types.get() ) {
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
                    break;
                }
                case mod::restore : {
                    if ( is_hijacked_execs.get() ) {
                        for ( const auto &exec : rules_.execs ) {
                            std::system(
                              std::format(
                                R"(C:\Windows\System32\reg.exe delete "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution options\{}" /f)",
                                exec )
                                .c_str() );
                        }
                    }
                    if ( is_set_serv_startup_types.get() ) {
                        for ( const auto &serv : rules_.servs ) {
                            std::system( std::format( R"(C:\Windows\System32\sc.exe config "{}" start= auto)", serv ).c_str() );
                        }
                    }
                    for ( const auto &serv : rules_.servs ) {
                        std::system( std::format( R"(C:\Windows\System32\net.exe start "{}")", serv ).c_str() );
                    }
                    break;
                }
            }
            return cpp_utils::console_value::ui_back;
        }
        auto operator=( const rule_op & ) -> rule_op & = delete;
        auto operator=( rule_op && ) -> rule_op &      = delete;
        rule_op( const mod _mod_data, const rule_node &_rule )
          : mod_data_{ _mod_data }
          , rules_{ _rule }
        { }
        rule_op( const rule_op & ) = default;
        rule_op( rule_op && )      = default;
        ~rule_op()                 = default;
    };
}