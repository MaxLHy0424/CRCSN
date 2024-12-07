#pragma once
#include <windows.h>
#ifdef _NEXT_
# include <print>
#else
# include <cstdio>
#endif
#include <functional>
#include <string>
#include <vector>
#define CONSOLE_MOUSE_BUTTON_LEFT   FROM_LEFT_1ST_BUTTON_PRESSED
#define CONSOLE_MOUSE_BUTTON_MIDDLE FROM_LEFT_2ND_BUTTON_PRESSED
#define CONSOLE_MOUSE_BUTTON_RIGHT  RIGHTMOST_BUTTON_PRESSED
#define CONSOLE_MOUSE_CLICK         0x0
#define CONSOLE_MOUSE_CLICK_DOUBLE  DOUBLE_CLICK
#define CONSOLE_MOUSE_MOVE          MOUSE_MOVED
#define CONSOLE_MOUSE_WHEEL         MOUSE_WHEELED
#define CONSOLE_TEXT_WHITE_WHITE    0x07
#define CONSOLE_TEXT_BLUE_WHITE     0x09
#define CONSOLE_TEXT_RED_WHITE      0x0c
#define FN_BACK                     false
#define FN_EXIT                     true
class console_ui final {
  public:
    struct fn_args final {
        const DWORD button_state, ctrl_key_state, event_flag;
        console_ui *const ui;
        fn_args &operator=( const fn_args & ) = delete;
        explicit fn_args(
          console_ui *const _ui                 = nullptr,
          const MOUSE_EVENT_RECORD _mouse_event = { {}, CONSOLE_MOUSE_BUTTON_LEFT, {}, {} } )
          : button_state{ _mouse_event.dwButtonState }
          , ctrl_key_state{ _mouse_event.dwControlKeyState }
          , event_flag{ _mouse_event.dwEventFlags }
          , ui{ _ui }
        { }
        fn_args( const fn_args &_obj )
          : button_state{ _obj.button_state }
          , ctrl_key_state{ _obj.ctrl_key_state }
          , event_flag{ _obj.event_flag }
          , ui{ _obj.ui }
        { }
        ~fn_args() { }
    };
    using fn_callback = std::function< bool( fn_args ) >;
  private:
    using size_type_ = std::size_t;
    struct ui_item_ final {
        const char *text;
        short default_color, highlight_color, last_color;
        COORD position;
        fn_callback fn;
        auto set_color( const short _color )
        {
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), _color );
            last_color = _color;
        }
        auto &operator=( const ui_item_ &_obj )
        {
            text            = _obj.text;
            default_color   = _obj.default_color;
            highlight_color = _obj.highlight_color;
            last_color      = _obj.last_color;
            position        = _obj.position;
            fn              = _obj.fn;
            return *this;
        }
        auto operator==( const COORD &_mouse_position ) const
        {
            return ( position.Y == _mouse_position.Y ) && ( position.X <= _mouse_position.X )
                && ( _mouse_position.X < ( position.X + static_cast< short >( strlen( text ) ) ) );
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
          , fn{}
        { }
        explicit ui_item_(
          const char *const _text,
          const short _default_color,
          const short _highlight_color,
          const fn_callback _fn )
          : text{ _text }
          , default_color{ _default_color }
          , highlight_color{ _highlight_color }
          , last_color{ CONSOLE_TEXT_WHITE_WHITE }
          , position{}
          , fn{ std::move( _fn ) }
        { }
        explicit ui_item_( const ui_item_ &_obj )
          : text{ _obj.text }
          , default_color{ _obj.default_color }
          , highlight_color{ _obj.highlight_color }
          , last_color{ _obj.last_color }
          , position{ _obj.position }
          , fn{ _obj.fn }
        { }
        ~ui_item_() { }
    };
    enum console_attrs_ { v_normal = 0, v_lock_text = 1, v_lock_all = 2 };
    std::vector< ui_item_ > item_;
    short width_, height_;
    auto show_cursor_( const bool _mode )
    {
        CONSOLE_CURSOR_INFO cursor;
        GetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cursor );
        cursor.bVisible = _mode;
        SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cursor );
    }
    auto edit_console_attrs_( const console_attrs_ _mode )
    {
        DWORD attrs;
        GetConsoleMode( GetStdHandle( STD_INPUT_HANDLE ), &attrs );
        switch ( _mode ) {
            case v_normal :
                attrs |= ENABLE_QUICK_EDIT_MODE;
                attrs |= ENABLE_INSERT_MODE;
                attrs |= ENABLE_MOUSE_INPUT;
                break;
            case v_lock_text :
                attrs &= ~ENABLE_QUICK_EDIT_MODE;
                attrs &= ~ENABLE_INSERT_MODE;
                attrs |= ENABLE_MOUSE_INPUT;
                break;
            case v_lock_all :
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
            if ( ( record.EventType == MOUSE_EVENT )
                 && ( _move | ( record.Event.MouseEvent.dwEventFlags != MOUSE_MOVED ) ) )
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
#ifdef _NEXT_
        std::print( "{}", std::string( width_ * height_, ' ' ) );
#else
        std::printf( std::string( width_ * height_, ' ' ).c_str() );
#endif
        set_cursor_( { 0, 0 } );
    }
    auto write_( const char *const _text, const bool _is_endl = false )
    {
#ifdef _NEXT_
        std::print( "{}{}", _text, ( _is_endl ) ? ( '\n' ) : ( '\0' ) );
#else
        std::printf( "%s%c", _text, ( _is_endl ) ? ( '\n' ) : ( '\0' ) );
#endif
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
            if ( ( line == _hang_position ) && ( line.last_color != line.highlight_color ) ) {
                line.set_color( line.highlight_color );
                rewrite_( line.position, line.text );
            }
            if ( ( line != _hang_position ) && ( line.last_color != line.default_color ) ) {
                line.set_color( line.default_color );
                rewrite_( line.position, line.text );
            }
        }
    }
    auto call_fn_( const MOUSE_EVENT_RECORD &_mouse_event )
    {
        bool is_exit{};
        for ( auto &line : item_ ) {
            if ( line != _mouse_event.dwMousePosition ) {
                continue;
            }
            if ( line.fn == nullptr ) {
                break;
            }
            cls_();
            line.set_color( line.default_color );
            show_cursor_( false );
            edit_console_attrs_( v_lock_all );
            is_exit = line.fn( fn_args{ this, _mouse_event } );
            show_cursor_( false );
            edit_console_attrs_( v_lock_text );
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
          "mode con cols="s.append( std::to_string( _width ) )
            .append( " lines=" )
            .append( std::to_string( _height ) )
            .c_str() );
        SetWindowLongPtrA(
          GetConsoleWindow(),
          GWL_STYLE,
          ( _fix_size )
            ? ( GetWindowLongPtrA( GetConsoleWindow(), GWL_STYLE ) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX )
            : ( GetWindowLongPtrA( GetConsoleWindow(), GWL_STYLE ) | WS_SIZEBOX | WS_MAXIMIZEBOX ) );
        SetWindowLongPtrA(
          GetConsoleWindow(),
          GWL_STYLE,
          ( _minimize_ctrl )
            ? ( GetWindowLongPtrA( GetConsoleWindow(), GWL_STYLE ) | WS_MINIMIZEBOX )
            : ( GetWindowLongPtrA( GetConsoleWindow(), GWL_STYLE ) & ~WS_MINIMIZEBOX ) );
        EnableMenuItem(
          GetSystemMenu( GetConsoleWindow(), FALSE ),
          SC_CLOSE,
          ( _close_window_ctrl )
            ? ( MF_BYCOMMAND | MF_ENABLED )
            : ( MF_BYCOMMAND | MF_DISABLED | MF_GRAYED ) );
        SetLayeredWindowAttributes( GetConsoleWindow(), 0, _transparency, LWA_ALPHA );
        return *this;
    }
    auto &lock( const bool _is_hide_cursor, const bool _is_lock_text )
    {
        show_cursor_( !_is_hide_cursor );
        edit_console_attrs_( ( _is_lock_text ) ? ( v_lock_all ) : ( v_normal ) );
        return *this;
    }
    auto &add(
      const char *const _text,
      const fn_callback _fn        = nullptr,
      const short _highlight_color = CONSOLE_TEXT_BLUE_WHITE,
      const short _default_color   = CONSOLE_TEXT_WHITE_WHITE )
    {
        item_.emplace_back( ui_item_{
          _text, _default_color, ( _fn == nullptr ) ? ( _default_color ) : ( _highlight_color ),
          std::move( _fn ) } );
        return *this;
    }
    auto &insert(
      const size_type_ _index,
      const char *const _text,
      const fn_callback _fn        = nullptr,
      const short _highlight_color = CONSOLE_TEXT_BLUE_WHITE,
      const short _default_color   = CONSOLE_TEXT_WHITE_WHITE )
    {
        item_.emplace(
          item_.begin() + _index,
          ui_item_{
            _text, _default_color, ( _fn == nullptr ) ? ( _default_color ) : ( _highlight_color ),
            std::move( _fn ) } );
        return *this;
    }
    auto &edit(
      const size_type_ _index,
      const char *const _text,
      const fn_callback _fn        = nullptr,
      const short _highlight_color = CONSOLE_TEXT_BLUE_WHITE,
      const short _default_color   = CONSOLE_TEXT_WHITE_WHITE )
    {
        item_.at( _index ) = ui_item_{
          _text, _default_color, ( _fn == nullptr ) ? ( _default_color ) : ( _highlight_color ),
          std::move( _fn ) };
        return *this;
    }
    auto &revert()
    {
        item_.pop_back();
        return *this;
    }
    auto &remove( const size_type_ _begin, const size_type_ _end )
    {
        item_.erase( item_.begin() + _begin, item_.begin() + _end );
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
        edit_console_attrs_( v_lock_text );
        MOUSE_EVENT_RECORD mouse_event;
        init_pos_();
        auto fn_returned_value{ FN_BACK };
        while ( fn_returned_value == FN_BACK ) {
            mouse_event = wait_mouse_event_();
            switch ( mouse_event.dwEventFlags ) {
                case CONSOLE_MOUSE_MOVE : refresh_( mouse_event.dwMousePosition ); break;
                case CONSOLE_MOUSE_CLICK : {
                    if ( ( mouse_event.dwButtonState )
                         && ( mouse_event.dwButtonState != CONSOLE_MOUSE_WHEEL ) )
                    {
                        fn_returned_value = call_fn_( mouse_event );
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
    explicit console_ui( const console_ui &_obj )
      : item_{ _obj.item_ }
      , width_{}
      , height_{}
    { }
    explicit console_ui( console_ui &&_obj )
      : item_{ std::move( _obj.item_ ) }
      , width_{}
      , height_{}
    { }
    ~console_ui() { }
};