
#include "optional.hpp"
#include <vector>

/*
 * argparser: A commandline input parser.
 * 
 * If you are familar with command line, you must have noticed that every command has a number of options (arguments), for example:
 * 
 * ```
 * $ code --help
 * code 1.61.0
 * 
 * Usage: code [options][paths...]
 * 
 * To read from stdin, append '-' (e.g. 'ps aux | grep code | code -')
 * 
 * Options
 *   -d --diff <file> <file>           Compare two files with each other.
 *   -a --add <folder>                 Add folder(s) to the last active window.
 *   -g --goto <file:line[:character]> Open a file at the path on the specified line and character position.
 *   -n --new-window                   Force to open a new window.
 *   -r --reuse-window                 Force to open a file or folder in an already opened window.
 *   -w --wait                         Wait for the files to be closed before returning.
 *   -h --help                         Print usage.
 * ```
 * 
 * Here is a command line option parser framework `argparser`. It can help you write a parser in just few lines of code.
 * 
 * Basic usage example:
 * 
 * ```c++
 * int main(int argc, char* argv[]) {
 *     argparser::ArgParser parser("command-cli");
 *     
 *     parser.argument<bool>("verbose")                 // add an option `--version`
 *           .in_short('v')                             // use `-v` for abbrevation
 *           .help("Print more verbose infomation.");   // add description in help message
 *     
 *     parser.parse(argc, argv);                        // parse from `int argc, char* argv[]` 
 *     
 *     std::cout << parser.get<bool>("verbose") << std::endl;
 *     return 0;
 * }
 * ```
 * 
 * Note: A real world version https://github.com/p-ranav/argparse
 */

namespace argparser {

    /* 
     * Argparser Exception: 
     * 
     * runtime_error:               Represents errors made by command line user.
     *     ArgumentError            Errors when parsing a single argument.
     *         ParsingError         Failed to parse argument, for example 3.14 can not be parsed into a integer value..
     *         MissingArgument      Some options need one additional argument: `g++ -c <cpp file> -o <execuble>`. Missing these additional arguments will cause this problem.
     *     UnrecongizedInput        Some input that can NOT be recongized.
     * logic_error:                 Represents errors made by the programmer.
     *     ArgumentNotFound         ArgParser::get an undefined argument.
     *     ArgumentWrongType        ArgParser::get an argument with a wrong type, or use a undefined argument type (you should only use bool, int, std::string to define an argument). 
     */

    class ArgumentError: public std::runtime_error {
    public:
        explicit ArgumentError(const std::string& argname, const std::runtime_error& inner) noexcept :
            std::runtime_error("failed to parse argument '" + argname + "' : " + inner.what()) {}
    };

    class ParsingError: public std::runtime_error {
    public:
        explicit ParsingError(const std::string& unparsed, const std::string& what) noexcept :
            std::runtime_error("invalid argument '" + unparsed + "' (" + what + ")") {}
    };

    class MissingArgument: public std::runtime_error {
    public:
        explicit MissingArgument() noexcept : std::runtime_error("missing argument") {}
    };

    class UnrecongizedInput: public std::runtime_error {
    public:
        explicit UnrecongizedInput() noexcept : std::runtime_error("unrecongized input") {}
    };

    class ArgumentNotFound: public std::logic_error {
    public:
        explicit ArgumentNotFound() noexcept : std::logic_error("argument not found") {}
    };

    class ArgumentWrongType: public std::logic_error {
    public:
        explicit ArgumentWrongType() noexcept : std::logic_error("argument wrong type") {}
    };

    /*
     * Template function for parsing.
     * Only parsing from std::string and int are implemented.
     */

    template<typename T>
    T parse_from(const std::string& str) throw(ParsingError) { throw ArgumentWrongType(); }

    template<>
    std::string parse_from<std::string>(const std::string& str) throw(ParsingError) { return str; }
    
    template<>
    int parse_from<int>(const std::string& str) throw(ParsingError);

    /*
     * AbstractArgument: General definition of an argument. Contains argument infomation that is independent from its type (like int, std::string, bool).
     */

    class AbstractArgument {
    protected:
        std::string _name;              // used by `--name`
        std::string _description = "";  // infomation in `--help` page
        optional<char> _in_short;       // abbrevation like `-v`. nullptr for not using any abbrevation.
        bool _need_argument;            // need additional argument, like `gcc -o <file>`
    public:
        explicit AbstractArgument(const std::string& name, bool need_argument) noexcept : _name(name), _need_argument(need_argument) {}
        
        // General Parse function for different types of argument. 
        // if _need_argument == false, parse("") will be called when option `--name` is used. When `--name` is not used, this will never been called.
        virtual void parse(const std::string& input) = 0;

        const std::string& name() const noexcept {return _name; }
        const std::string& description() const noexcept {return _description; }
        bool need_argument() const noexcept { return _need_argument; }

        bool is_tag(const char * str) const noexcept {
            return str[0] == '-' && str[1] == '-' && _name == (str + 2);
        } 
        bool is_short_tag(const char* str) const noexcept {
            return str[0] == '-' && _in_short && str[1] == *_in_short;
        }

        virtual ~AbstractArgument() {}
    };

    /*
     * Argument: Argument Infomation with type T.
     */
    template<typename T>
    class Argument : public AbstractArgument{
        optional<T> _default;         // default value. nullptr for no default value.
        optional<T> _result;          // temporary value, set in parse(), get this value by get()

    public:
        Argument(const std::string& name) :
            AbstractArgument(name, true), _result(), _default() {}
        
        Argument& set_default(const T& value) {
            _default = value;
            return *this;
        }

        Argument& in_short(char ch) {
            _in_short = ch;
            return *this;
        }

        Argument& help(const std::string& description) {
            _description = description;
            return *this;
        }

        virtual void parse(const std::string& input) throw(ArgumentError) override;

        T get() throw(ArgumentError);

    };

    /*
     * Argument<bool>: Special implementation for bool. 
     */
    template<>
    class Argument<bool> : public AbstractArgument {
        bool result = false;
    public:
        Argument(const std::string& name) :
            AbstractArgument(name, false) {}

        Argument& in_short(char ch) {
            _in_short = ch;
            return *this;
        }

        Argument& help(const std::string& description) {
            _description = description;
            return *this;
        }

        virtual void parse(const std::string& input) override {
            result = true;
        }

        bool get() {
            return result;
        }
    };

    /*
     * Main class for argparse
     */
    class ArgParser {
        const std::string& _name;
        const std::string& _description;
        std::vector<AbstractArgument*> _args;
    public:
        ArgParser(const std::string& name, const std::string& description = "") :
            _name(name),
            _description(description) {}

        template<typename T>
        Argument<T>& argument(const std::string& name) {
            _args.push_back(new Argument<T>(name));
            return *dynamic_cast<Argument<T>*>(_args.back());
        }

        // Parse all input into `_args`
        void parse(int argc, const char ** argv) throw(ArgumentError, UnrecongizedInput);
        
        // Get a certain argument by name.
        template<typename T>
        T get(const std::string& name) throw(ArgumentNotFound, ArgumentWrongType, ArgumentError);

        ~ArgParser() {
            for(auto arg: _args) {
                delete arg;
            }
        }
    };

} // namespace argparser