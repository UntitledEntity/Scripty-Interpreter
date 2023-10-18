#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

#define ADD_KEYWORD "ADD"
#define SUB_KEYWORD "SUB"
#define MULT_KEYWORD "MULT"
#define DIV_KEYWORD "DIV"
#define PRINTS_KEYWORD "PRINTS"
#define PRINTF_KEYWORD "PRINTF"
#define PRINTV_KEYWORD "PRINTV"
#define SETVAR_KEYWORD "SETVAR"
#define SETVARF_KEYWORD "SETVARF"
#define MOV_KEYWORD "MOV"

enum CmdCodes {
    Add,
    Sub,
    Div,
    Mult,
    PrintS,
    PrintF,
    PrintV,
    SetVar,
    SetVarF,
    Move,
    Invalid
};

CmdCodes HashCmd( std::string const& in ) {
    if ( in == ADD_KEYWORD ) return Add;
    if ( in == SUB_KEYWORD ) return Sub;
    if ( in == MULT_KEYWORD ) return Mult;
    if ( in == DIV_KEYWORD ) return Div;
    if ( in == PRINTS_KEYWORD ) return PrintS;
    if ( in == PRINTF_KEYWORD ) return PrintF;
    if ( in == PRINTV_KEYWORD ) return PrintV;
    if ( in == SETVAR_KEYWORD ) return SetVar;
    if ( in == SETVARF_KEYWORD ) return SetVarF;
    if ( in == MOV_KEYWORD ) return Move;

    return Invalid;
}

bool is_number( const std::string& s )
{
    std::string::const_iterator it = s.begin( );
    while ( it != s.end( ) && std::isdigit( *it ) ) ++it;
    return !s.empty( ) && it == s.end( );
}

int main( int argc, char* argv[ ] )
{
    if ( argc < 2 ) {
        std::cerr << "Please provide the link to the .scrpy file." << std::endl;
        exit( -1 );
    }

    std::cout << "Accepted file: " << argv[ 1 ] << std::endl;

    std::string FileName = argv[ 1 ];
    if ( FileName.find( ".scrpy" ) == std::string::npos ) {
        std::cerr << "Invalid file. Must have a .scrpy extension." << std::endl;
        exit( -1 );
    }

    std::ifstream infile( FileName );
   
    std::string line;
    // Splits line by '\n' chars, maybe change this to semicolons?
    while ( std::getline( infile, line ) )
    {
        // Exclude Comments
        if ( line.find( "//" ) != std::string::npos || line.find( "#" ) != std::string::npos )
            continue;

        std::stringstream liness( line );

        std::vector<std::string> Keywords = { };
        std::string curarg;

        // Split lines by spaces
        while ( std::getline( liness, curarg, ' ' ) ) {

            // store token string in the vector
            Keywords.push_back( curarg );
        }

        std::vector<std::string> cmds = { };
        std::vector<std::string> args = { };
        for ( int i = 0; i < Keywords.size( ); i++ ) {

            std::string in = Keywords.at( i );

            if ( !is_number( in ) ) {

                // 1-string arg vars
                if ( in == SETVAR_KEYWORD || in == SETVARF_KEYWORD ||
                    in == PRINTS_KEYWORD || in == PRINTV_KEYWORD)
                {
                    cmds.push_back( in );

                    std::string arg = Keywords.at( i + 1 );
                    args.push_back( arg );
                    i++;
                }
                // 2-string arg vars
                else if ( in == MOV_KEYWORD )
                {
                    cmds.push_back( in );
                    for ( int n = 1; n < 3; n++ ) {
                        std::string arg = Keywords.at( i + 1 );
                        args.push_back( arg );
                        i++;
                    }
                }
                else
                    cmds.push_back( in );
            }
            else
                args.push_back( in );

        }

        static std::vector < std::pair < std::string, int > > vars = { };

        for ( int i = 0; i < cmds.size( ); i++ ) {

            std::string curcmd = cmds.at( i );

            static bool print_line = false;
            static bool set_to_var = false;
            static std::string var_name_to_set = "";

            // Switching the hash of the name is supposedly faster than checking the strings manually, but I don't see why it would have any difference.
            // Not really worrying about execution time as its extremely simple
            switch ( HashCmd( curcmd ) ) {
            case CmdCodes::Add: {
                int a = atoi( args.at( 0 ).c_str() );
                int b = atoi( args.at( 1 ).c_str( ) );
                int val = a + b;
                if ( print_line ) {
                    std::cout << val << std::endl;
                    print_line = false;
                }

                if ( set_to_var ) {
                    vars.push_back( std::make_pair( var_name_to_set, val ) );
                    var_name_to_set = "";
                    set_to_var = false;
                }

            } break;
            case CmdCodes::Sub: {
                int a = atoi( args.at( 0 ).c_str( ) );
                int b = atoi( args.at( 1 ).c_str( ) );
                int val = a - b;

                if ( print_line ) {
                    std::cout << val << std::endl;
                    print_line = false;
                }

                if ( set_to_var ) {
                    vars.push_back( std::make_pair( var_name_to_set, val ) );
                    var_name_to_set = "";
                    set_to_var = false;
                }
            } break;
            case CmdCodes::Div: {
                int a = atoi( args.at( 0 ).c_str( ) );
                int b = atoi( args.at( 1 ).c_str( ) );
                int val = a / b;

                if ( print_line ) {
                    std::cout << val << std::endl;
                    print_line = false;
                }

                if ( set_to_var ) {
                    vars.push_back( std::make_pair( var_name_to_set, val ) );
                    var_name_to_set = "";
                    set_to_var = false;
                }

            } break;
            case CmdCodes::Mult: {
                int a = atoi( args.at( 0 ).c_str( ) );
                int b = atoi( args.at( 1 ).c_str( ) );
                int val = a * b;

                if ( print_line ) {
                    std::cout << val << std::endl;
                    print_line = false;
                }

                if ( set_to_var ) {
                    vars.push_back( std::make_pair( var_name_to_set, val ) );
                    var_name_to_set = "";
                    set_to_var = false;
                }
            } break;
            case CmdCodes::SetVar: {
                std::string a = args.at( 0 );

                int b = std::atoi( args.at( 1 ).c_str( ) );
                vars.push_back( std::make_pair( a, b ) );

            } break;
            case CmdCodes::Move: {
                std::string srcname = args.at( 0 );
                int srcpos = -1;

                std::string destname = args.at( 1 );
                int destpos = -1;

                // Search for both variables and the address we found it at
                for ( int i = 0; i < vars.size( ); i++ ) {
                    if ( ( srcpos != -1 ) && ( destpos != -1 ) )
                        break;

                    auto var = vars.at( i );
                    if ( var.first == srcname ) {
                        srcpos = i;
                    }
                    else if ( var.first == destname ) {
                        destpos = i;
                    }
                }

                if ( srcpos == -1 ) {
                    std::cerr << "ERROR: Unable to find variable '" << srcname << "'" << std::endl;
                    break;
                }

                // Dest was found
                if ( destpos != -1 ) {
                    // copy memory over from src to dest
                    vars.at( destpos ) = vars.at( srcpos );
                }
                // No dest, just make a variable
                else {
                    vars.push_back( std::make_pair(destname, vars.at( srcpos ).second) );
                }
                
            } break;
            case CmdCodes::SetVarF: {
                set_to_var = true;
                var_name_to_set = args.at( 0 );
            } break;
            case CmdCodes::PrintS: {
                std::string a = args.at( 0 );
                std::cout << a << std::endl;
            } break;
            case CmdCodes::PrintF: {
                print_line = true;
            } break;
            case CmdCodes::PrintV: {
                std::string varname = args.at( 0 );
                bool found = false;

                for ( const auto& var : vars ) {
                    if ( var.first == varname ) {
                        std::cout << var.second << std::endl;
                        found = true;
                        break;
                    }
                }

                if ( !found ) {
                    std::cout << "Variable " << varname << " not found." << std::endl;
                }
            } break;
            default:
                std::cout << "Invalid command read.";
                break;
            }

            
            
        }
    }
}
