#pragma once
#if __cplusplus >= 202302L
# include <windows.h>
# ifdef _NEXT_
#  include <print>
# else
#  include <cstdio>
# endif
# include <functional>
# include <queue>
# include <string>
# define CONSOLE_MOUSE_BUTTON_LEFT   FROM_LEFT_1ST_BUTTON_PRESSED
# define CONSOLE_MOUSE_BUTTON_MIDDLE FROM_LEFT_2ND_BUTTON_PRESSED
# define CONSOLE_MOUSE_BUTTON_RIGHT  RIGHTMOST_BUTTON_PRESSED
# define CONSOLE_MOUSE_CLICK         0x0000
# define CONSOLE_MOUSE_CLICK_DOUBLE  DOUBLE_CLICK
# define CONSOLE_MOUSE_MOVE          MOUSE_MOVED
# define CONSOLE_MOUSE_WHEEL         MOUSE_WHEELED
# define CONSOLE_TEXT_WHITE_WHITE    0x0007
# define CONSOLE_TEXT_BLUE_WHITE     0x0009
# define CONSOLE_TEXT_RED_WHITE      0x000c
# define UI_REVERT                   false
# define UI_TERMINATE                true
class console_ui final {
  public:
    struct func_args final {
        const DWORD button_state, ctrl_key_state, event_flag;
        console_ui *const ui;
        func_args &operator=( const func_args & ) = delete;
        explicit func_args(
          console_ui *const _ui                 = nullptr,
          const MOUSE_EVENT_RECORD _mouse_event = { {}, CONSOLE_MOUSE_BUTTON_LEFT, {}, {} } )
          : button_state{ std::move( _mouse_event.dwButtonState ) }
          , ctrl_key_state{ std::move( _mouse_event.dwControlKeyState ) }
          , event_flag{ std::move( _mouse_event.dwEventFlags ) }
          , ui{ std::move( _ui ) }
        { }
        func_args( const func_args &_src )
          : button_state{ _src.button_state }
          , ctrl_key_state{ _src.ctrl_key_state }
          , event_flag{ _src.event_flag }
          , ui{ _src.ui }
        { }
        explicit func_args( func_args &&_src )
          : button_state{ std::move( _src.button_state ) }
          , ctrl_key_state{ std::move( _src.ctrl_key_state ) }
          , event_flag{ std::move( _src.event_flag ) }
          , ui{ std::move( _src.ui ) }
        { }
        ~func_args() { }
    };
    using func_callback = std::function< bool( func_args ) >;
    using size_type     = std::size_t;
  private:
    struct ui_item_ final {
        const char *text;
        short default_color, highlight_color, last_color;
        COORD position;
        func_callback func;
        auto set_color( const short _color )
        {
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), _color );
            last_color = _color;
        }
        auto &operator=( const ui_item_ &_src )
        {
            text            = _src.text;
            default_color   = _src.default_color;
            highlight_color = _src.highlight_color;
            last_color      = _src.last_color;
            position        = _src.position;
            func            = _src.func;
            return *this;
        }
        auto operator==( const COORD &_mouse_position ) const
        {
            return position.Y == _mouse_position.Y && position.X <= _mouse_position.X
                && _mouse_position.X < ( position.X + static_cast< short >( strlen( text ) ) );
        }
        auto operator!=( const COORD &_mouse_position ) const
        {
            return !operator==( _mouse_position );
        }
        explicit ui_item_()
          : text{}
          , default_color{ CONSOLE_TEXT_WHITE_WHITE }
          , highlight_color{ CONSOLE_TEXT_BLUE_WHITE }
          , last_color{ CONSOLE_TEXT_WHITE_WHITE }
          , position{}
          , func{}
        { }
        explicit ui_item_(
          const char *const _text,
          const short _default_color,
          const short _highlight_color,
          const func_callback _func )
          : text{ _text }
          , default_color{ _default_color }
          , highlight_color{ _highlight_color }
          , last_color{ CONSOLE_TEXT_WHITE_WHITE }
          , position{}
          , func{ std::move( _func ) }
        { }
        explicit ui_item_( const ui_item_ &_src )
          : text{ _src.text }
          , default_color{ _src.default_color }
          , highlight_color{ _src.highlight_color }
          , last_color{ _src.last_color }
          , position{ _src.position }
          , func{ _src.func }
        { }
        explicit ui_item_( ui_item_ &&_src )
          : text{ std::move( _src.text ) }
          , default_color{ std::move( _src.default_color ) }
          , highlight_color{ std::move( _src.highlight_color ) }
          , last_color{ std::move( _src.last_color ) }
          , position{ std::move( _src.position ) }
          , func{ std::move( _src.func ) }
        { }
        ~ui_item_() { }
    };
    enum class console_attrs_ { normal, lock_text, lock_all };
    std::deque< ui_item_ > item_;
    short width_, height_;
    auto show_cursor_( const bool _is_show )
    {
        CONSOLE_CURSOR_INFO cursor;
        GetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cursor );
        cursor.bVisible = _is_show;
        SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cursor );
    }
    auto edit_console_attrs_( const console_attrs_ _mode )
    {
        DWORD attrs;
        GetConsoleMode( GetStdHandle( STD_INPUT_HANDLE ), &attrs );
        switch ( _mode ) {
            case console_attrs_::normal :
                attrs |= ENABLE_QUICK_EDIT_MODE;
                attrs |= ENABLE_INSERT_MODE;
                attrs |= ENABLE_MOUSE_INPUT;
                break;
            case console_attrs_::lock_text :
                attrs &= ~ENABLE_QUICK_EDIT_MODE;
                attrs &= ~ENABLE_INSERT_MODE;
                attrs |= ENABLE_MOUSE_INPUT;
                break;
            case console_attrs_::lock_all :
                attrs &= ~ENABLE_QUICK_EDIT_MODE;
                attrs &= ~ENABLE_INSERT_MODE;
                attrs &= ~ENABLE_MOUSE_INPUT;
                break;
        }
        SetConsoleMode( GetStdHandle( STD_INPUT_HANDLE ), attrs );
    }
    auto get_cursor_()
    {
        CONSOLE_SCREEN_BUFFER_INFO console;
        GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &console );
        return console.dwCursorPosition;
    }
    auto set_cursor_( const COORD &_position )
    {
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), _position );
    }
    auto wait_mouse_event_( const bool _move = true )
    {
        INPUT_RECORD record;
        DWORD reg;
        while ( true ) {
            Sleep( 10 );
            ReadConsoleInputA( GetStdHandle( STD_INPUT_HANDLE ), &record, 1, &reg );
            if ( record.EventType == MOUSE_EVENT
                 && _move | ( record.Event.MouseEvent.dwEventFlags != MOUSE_MOVED ) )
            {
                return record.Event.MouseEvent;
            }
        }
    }
    auto get_console_size_()
    {
        CONSOLE_SCREEN_BUFFER_INFO console;
        GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &console );
        height_ = console.dwSize.Y;
        width_  = console.dwSize.X;
    }
    auto cls_()
    {
        get_console_size_();
        set_cursor_( { 0, 0 } );
# ifdef _NEXT_
        std::print( "{}", std::string( width_ * height_, ' ' ) );
# else
        std::printf( std::string( width_ * height_, ' ' ).c_str() );
# endif
        set_cursor_( { 0, 0 } );
    }
    auto write_( const char *const _text, const bool _is_endl = false )
    {
# ifdef _NEXT_
        std::print( "{}{}", _text, _is_endl ? '\n' : '\0' );
# else
        std::printf( "%s%c", _text, _is_endl ? '\n' : '\0' );
# endif
    }
    auto rewrite_( const COORD &_position, const char *const _text )
    {
        set_cursor_( { 0, _position.Y } );
        write_( std::string( _position.X, ' ' ).c_str() );
        set_cursor_( { 0, _position.Y } );
        write_( _text );
        set_cursor_( { 0, _position.Y } );
    }
    auto init_pos_()
    {
        cls_();
        for ( auto &line : item_ ) {
            line.position = get_cursor_();
            line.set_color( line.default_color );
            write_( line.text, true );
        }
    }
    auto refresh_( const COORD &_hang_position )
    {
        for ( auto &line : item_ ) {
            if ( line == _hang_position && line.last_color != line.highlight_color ) {
                line.set_color( line.highlight_color );
                rewrite_( line.position, line.text );
            }
            if ( line != _hang_position && line.last_color != line.default_color ) {
                line.set_color( line.default_color );
                rewrite_( line.position, line.text );
            }
        }
    }
    auto call_func_( const MOUSE_EVENT_RECORD &_mouse_event )
    {
        bool is_exit{};
        for ( auto &line : item_ ) {
            if ( line != _mouse_event.dwMousePosition ) {
                continue;
            }
            if ( line.func == nullptr ) {
                break;
            }
            cls_();
            line.set_color( line.default_color );
            show_cursor_( false );
            edit_console_attrs_( console_attrs_::lock_all );
            is_exit = line.func( func_args{ this, _mouse_event } );
            show_cursor_( false );
            edit_console_attrs_( console_attrs_::lock_text );
            init_pos_();
            break;
        }
        return is_exit;
    }
  public:
    auto item_counter()
    {
        return item_.size();
    }
    auto &set_console(
      const UINT _code_page,
      const CHAR *const _title,
      const SHORT _width,
      const SHORT _height,
      const bool _fix_size,
      const bool _minimize_ctrl,
      const bool _close_window_ctrl,
      const BYTE _transparency )
    {
        SetConsoleOutputCP( _code_page );
        SetConsoleCP( _code_page );
        SetConsoleTitleA( _title );
        using namespace std::string_literals;
        system(
          "mode.com con cols="s.append( std::to_string( _width ) )
            .append( " lines=" )
            .append( std::to_string( _height ) )
            .c_str() );
        SetWindowLongPtrA(
          GetConsoleWindow(),
          GWL_STYLE,
          _fix_size
            ? GetWindowLongPtrA( GetConsoleWindow(), GWL_STYLE ) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX
            : GetWindowLongPtrA( GetConsoleWindow(), GWL_STYLE ) | WS_SIZEBOX | WS_MAXIMIZEBOX );
        SetWindowLongPtrA(
          GetConsoleWindow(),
          GWL_STYLE,
          _minimize_ctrl
            ? GetWindowLongPtrA( GetConsoleWindow(), GWL_STYLE ) | WS_MINIMIZEBOX
            : GetWindowLongPtrA( GetConsoleWindow(), GWL_STYLE ) & ~WS_MINIMIZEBOX );
        EnableMenuItem(
          GetSystemMenu( GetConsoleWindow(), FALSE ),
          SC_CLOSE,
          _close_window_ctrl ? MF_BYCOMMAND | MF_ENABLED : MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
        SetLayeredWindowAttributes( GetConsoleWindow(), 0, _transparency, LWA_ALPHA );
        return *this;
    }
    auto &lock( const bool _is_hide_cursor, const bool _is_lock_text )
    {
        show_cursor_( !_is_hide_cursor );
        edit_console_attrs_( _is_lock_text ? console_attrs_::lock_all : console_attrs_::normal );
        return *this;
    }
    auto &add_front(
      const char *const _text,
      const func_callback _func    = nullptr,
      const short _highlight_color = CONSOLE_TEXT_BLUE_WHITE,
      const short _default_color   = CONSOLE_TEXT_WHITE_WHITE )
    {
        item_.emplace_front( ui_item_{
          _text, _default_color, _func == nullptr ? _default_color : _highlight_color,
          std::move( _func ) } );
        return *this;
    }
    auto &add_back(
      const char *const _text,
      const func_callback _func    = nullptr,
      const short _highlight_color = CONSOLE_TEXT_BLUE_WHITE,
      const short _default_color   = CONSOLE_TEXT_WHITE_WHITE )
    {
        item_.emplace_back( ui_item_{
          _text, _default_color, _func == nullptr ? _default_color : _highlight_color,
          std::move( _func ) } );
        return *this;
    }
    auto &insert(
      const size_type _index,
      const char *const _text,
      const func_callback _func    = nullptr,
      const short _highlight_color = CONSOLE_TEXT_BLUE_WHITE,
      const short _default_color   = CONSOLE_TEXT_WHITE_WHITE )
    {
        item_.emplace(
          item_.cbegin() + _index,
          ui_item_{
            _text, _default_color, _func == nullptr ? _default_color : _highlight_color,
            std::move( _func ) } );
        return *this;
    }
    auto &edit(
      const size_type _index,
      const char *const _text,
      const func_callback _func    = nullptr,
      const short _highlight_color = CONSOLE_TEXT_BLUE_WHITE,
      const short _default_color   = CONSOLE_TEXT_WHITE_WHITE )
    {
        item_.at( _index ) = ui_item_{
          _text, _default_color, _func == nullptr ? _default_color : _highlight_color,
          std::move( _func ) };
        return *this;
    }
    auto &remove_front()
    {
        item_.pop_front();
        return *this;
    }
    auto &remove_back()
    {
        item_.pop_back();
        return *this;
    }
    auto &remove( const size_type _begin, const size_type _end )
    {
        item_.erase( item_.cbegin() + _begin, item_.cbegin() + _end );
        return *this;
    }
    auto &clear()
    {
        item_.clear();
        return *this;
    }
    auto &show()
    {
        show_cursor_( false );
        edit_console_attrs_( console_attrs_::lock_text );
        MOUSE_EVENT_RECORD mouse_event;
        init_pos_();
        auto func_return_value{ UI_REVERT };
        while ( func_return_value == UI_REVERT ) {
            mouse_event = wait_mouse_event_();
            switch ( mouse_event.dwEventFlags ) {
                case CONSOLE_MOUSE_MOVE : refresh_( mouse_event.dwMousePosition ); break;
                case CONSOLE_MOUSE_CLICK : {
                    if ( mouse_event.dwButtonState != false ) {
                        func_return_value = call_func_( mouse_event );
                    }
                    break;
                }
            }
            Sleep( 10 );
        }
        cls_();
        return *this;
    }
    explicit console_ui()
      : item_{}
      , width_{}
      , height_{}
    { }
    explicit console_ui( const console_ui &_src )
      : item_{ _src.item_ }
      , width_{}
      , height_{}
    { }
    explicit console_ui( console_ui &&_src )
      : item_{ std::move( _src.item_ ) }
      , width_{}
      , height_{}
    { }
    ~console_ui() { }
};
#else
# error "must be compiled on c++23 / gnu++23 or later C++ standards."
#endif