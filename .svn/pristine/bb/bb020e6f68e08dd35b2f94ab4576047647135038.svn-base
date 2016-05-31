#pragma once

#include <exception>
#include <memory>
#include <type_traits>
#include <tuple>
#include <utility>

namespace fn {
    template<typename UnusedType>
    class function;

    namespace details {
        template<typename FunctionSignature>
        static bool is_not_empty_functor(function<FunctionSignature> const &func) {
            return static_cast<bool>(func);
        }

        template<typename UnusedType>
        static bool is_not_empty_functor(UnusedType const &) {
            return true;
        }
    }

    class bad_function_call : public std::exception {
    public:
        char const *what() const noexcept {
            return "bad_function_call";
        }
    };

    template<typename ReturnType, typename ... ArgumentTypes>
    class function<ReturnType(ArgumentTypes ...)> {
    public:
        using signature_type = ReturnType (*) (ArgumentTypes ...);

        function() : _free_function_ptr(nullptr) {
        }

        function(std::nullptr_t) : _free_function_ptr(nullptr) {
        }

        function(function const &func) {
            _free_function_ptr = func._free_function_ptr;
            if (func._function_holder_ptr.get() != nullptr) {
                _function_holder_ptr = func._function_holder_ptr->make_copy();
            }
        }

        function(function &&func) : _free_function_ptr(nullptr) {
            func.swap(*this);
        }

        function(signature_type func) : _free_function_ptr(func) {
        }

        template<typename FunctionType>
        function(FunctionType func) {
            _free_function_ptr = nullptr;
            if (details::is_not_empty_functor(func)) {
                _function_holder_ptr = std::unique_ptr<function_holder_base>(new function_holder<FunctionType>(func));
            }
        }

        function &operator=(function const &func) {
            function(func).swap(*this);
            return *this;
        }

        function &operator=(function &&func) {
            function(std::move(func)).swap(*this);
            return *this;
        }

        function &operator=(std::nullptr_t) {
            function().swap(*this);
            return *this;
        }

        template<class FunctionType>
        function &operator=(FunctionType &&func) {
            function(std::forward<FunctionType>(func)).swap(*this);
            return *this;
        }

        ReturnType operator()(ArgumentTypes ... args) const {
            if (!*this) {
                throw bad_function_call();
            }
            if (_free_function_ptr != nullptr) {
                return _free_function_ptr(std::forward<ArgumentTypes>(args) ...);
            }
            else {
                return _function_holder_ptr->invoke(std::forward<ArgumentTypes>(args) ...);
            }
        }

        explicit operator bool() const {
            return _free_function_ptr != nullptr || _function_holder_ptr.get() != nullptr;
        }

        void swap(function &other) {
            _function_holder_ptr.swap(other._function_holder_ptr);
            std::swap(_free_function_ptr, other._free_function_ptr);
        }

    private:
        class function_holder_base {
        public:
            function_holder_base() {
            }

            virtual ~function_holder_base() {
            }

            virtual ReturnType invoke(ArgumentTypes /*&&*/ ... args) = 0;

            virtual std::unique_ptr<function_holder_base> make_copy() = 0;

        private:
            function_holder_base(function_holder_base const &);

            void operator=(function_holder_base const &);
        };

        template<typename FunctionType>
        class function_holder : public function_holder_base {
        public:
            function_holder(FunctionType func) : _func(func) {
            }

            virtual ReturnType invoke(ArgumentTypes /*&&*/ ... args) {
                return _func(std::forward<ArgumentTypes>(args) ...);
            }

            virtual std::unique_ptr<function_holder_base> make_copy() {
                return std::unique_ptr<function_holder_base>(new function_holder(_func));
            }

        private:
            FunctionType _func;
        };

        signature_type _free_function_ptr;
        std::unique_ptr<function_holder_base> _function_holder_ptr;
    };

    template<typename ReturnType, typename ... ArgumentTypes>
    void swap(function<ReturnType(ArgumentTypes ...)> &lhs, function<ReturnType(ArgumentTypes ...)> &rhs) {
        lhs.swap(rhs);
    }
}


namespace fn {

    template<int Num>
    struct Placeholder {
    };

    __attribute__((unused)) static Placeholder<1> _1;
    __attribute__((unused)) static Placeholder<2> _2;

    namespace details {
        template<typename ... ArgumentTypes, int Num>
        auto substitute(std::tuple<ArgumentTypes ...>&& tuple, Placeholder<Num>) -> decltype(std::get<Num - 1>(std::forward<std::tuple<ArgumentTypes ...>>(tuple))) {
            return std::get<Num - 1>(std::forward<std::tuple<ArgumentTypes ...>>(tuple));
        }

        template<typename ... ArgumentTypes, typename T>
        T substitute(std::tuple<ArgumentTypes ...>&&, T&& value) {
            return value;
        }
    }

    template <class ... UnusedType>
    class Bind;

    template <class ReturnType, class ... FunctionArgumentTypes, class ... BoundArgumentTypes>
    class Bind <ReturnType (FunctionArgumentTypes ...), std::tuple<BoundArgumentTypes ...>> {
    public:
        using FunctionSignature = ReturnType (*) (FunctionArgumentTypes ...);
        using Tuple = std::tuple<typename std::decay<BoundArgumentTypes>::type ...>;

        template<typename ... ArgumentTypes>
        explicit Bind(FunctionSignature function_ptr, ArgumentTypes&& ... args)
            : _function_ptr(function_ptr)
            , _tuple(std::forward<ArgumentTypes>(args) ...) {
        }

        template<typename ... ArgumentTypes>
        ReturnType operator() (ArgumentTypes&& ... args) {
            return call(std::forward_as_tuple(std::forward<ArgumentTypes>(args) ...));
        }

    private:
        template<typename ... ArgumentTypes, typename ... SubstitutedArgumentTypes>
        typename std::enable_if<(sizeof ... (FunctionArgumentTypes)) != (sizeof ... (SubstitutedArgumentTypes)), ReturnType>::type
        call(std::tuple<ArgumentTypes ...>&& tuple, SubstitutedArgumentTypes&& ... args) {
            return call(std::forward<std::tuple<ArgumentTypes ...>>(tuple),
                        std::forward<SubstitutedArgumentTypes>(args) ...,
                        details::substitute(std::forward<std::tuple<ArgumentTypes ...>>(tuple),
                                            std::get<sizeof ... (SubstitutedArgumentTypes)>(_tuple)));
        }

        template<typename ... ArgumentTypes, typename ... SubstitutedArgumentTypes>
        typename std::enable_if<(sizeof ... (FunctionArgumentTypes)) == (sizeof ... (SubstitutedArgumentTypes)), ReturnType>::type
        call(std::tuple<ArgumentTypes ...>&&, SubstitutedArgumentTypes&& ... args) {
            return _function_ptr(std::forward<SubstitutedArgumentTypes>(args) ...);
        }

        FunctionSignature _function_ptr;
        Tuple _tuple;
    };

    template<class ReturnType, class ... FunctionArgumentTypes, class ... BoundArgumentTypes>
    typename std::enable_if<(sizeof ... (FunctionArgumentTypes)) <= (sizeof ... (BoundArgumentTypes)),
                             Bind<ReturnType(FunctionArgumentTypes ...), std::tuple<BoundArgumentTypes ...>>>::type
    bind(ReturnType (*function_ptr) (FunctionArgumentTypes ...), BoundArgumentTypes&& ... args) {
        return Bind<ReturnType (FunctionArgumentTypes ...), std::tuple<BoundArgumentTypes ...>>
               (function_ptr, std::forward<BoundArgumentTypes>(args) ...);
    }
}